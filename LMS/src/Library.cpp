#include "Library.h"
#include "FileManager.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Static member initialization for Library
int Library::bookIdCounter = 1001;
int Library::readerIdCounter = 1;

Library::Library(const std::string& name, const std::string& address, 
                 const std::string& phone, const std::string& email)
    : libraryName(name), address(address), phoneNumber(phone), email(email),
      autoSaveEnabled(true), autoSaveInterval(5), operationCount(0) {
    initializeMaps();
}

bool Library::addUser(std::unique_ptr<User> user) {
    if (!user) return false;
    
    std::string username = user->getUsername();
    if (userMap.find(username) != userMap.end()) {
        std::cout << "Username da ton tai!" << std::endl;
        return false;
    }
    
    if (!validateUserData(*user)) {
        std::cout << "Du lieu nguoi dung khong hop le!" << std::endl;
        return false;
    }
    
    // Add to appropriate vector based on user type
    if (user->getUserType() == UserType::LIBRARIAN) {
        auto librarian = std::make_unique<Librarian>(*static_cast<Librarian*>(user.get()));
        librarians.push_back(std::move(librarian));
        users.push_back(std::move(user));
        userMap[username] = librarians.back().get();
    } else if (user->getUserType() == UserType::READER) {
        auto reader = std::make_unique<Reader>(*static_cast<Reader*>(user.get()));
        readers.push_back(std::move(reader));
        users.push_back(std::move(user));
        userMap[username] = readers.back().get();
    }
    
    std::cout << "Them nguoi dung thanh cong!" << std::endl;
    
    // Auto save after adding user
    saveUsers();
    incrementOperationCount();
    return true;
}

bool Library::removeUser(const std::string& username) {
    auto it = userMap.find(username);
    if (it == userMap.end()) {
        std::cout << "Khong tim thay nguoi dung!" << std::endl;
        return false;
    }
    
    UserType userType = it->second->getUserType();
    
    // Remove from appropriate vector
    if (userType == UserType::LIBRARIAN) {
        auto libIt = std::find_if(librarians.begin(), librarians.end(),
                                  [&username](const std::unique_ptr<Librarian>& lib) {
                                      return lib->getUsername() == username;
                                  });
        if (libIt != librarians.end()) {
            librarians.erase(libIt);
        }
    } else if (userType == UserType::READER) {
        auto readerIt = std::find_if(readers.begin(), readers.end(),
                                    [&username](const std::unique_ptr<Reader>& reader) {
                                        return reader->getUsername() == username;
                                    });
        if (readerIt != readers.end()) {
            readers.erase(readerIt);
        }
    }
    
    // Remove from users vector
    auto userIt = std::find_if(users.begin(), users.end(),
                               [&username](const std::unique_ptr<User>& user) {
                                   return user->getUsername() == username;
                               });
    if (userIt != users.end()) {
        users.erase(userIt);
    }
    
    // Remove from map
    userMap.erase(it);
    
    std::cout << "Xoa nguoi dung thanh cong!" << std::endl;
    
    // Auto save after removing user
    saveUsers();
    incrementOperationCount();
    return true;
}

User* Library::findUser(const std::string& username) {
    auto it = userMap.find(username);
    return (it != userMap.end()) ? it->second : nullptr;
}

bool Library::authenticateUser(const std::string& username, const std::string& password) {
    User* user = findUser(username);
    if (!user) return false;
    return user->authenticate(password);
}

UserType Library::getUserType(const std::string& username) {
    User* user = findUser(username);
    return user ? user->getUserType() : UserType::READER; // Default to READER
}

bool Library::addBook(std::unique_ptr<Book> book) {
    if (!book) return false;
    
    std::string bookId = book->getBookId();
    if (bookMap.find(bookId) != bookMap.end()) {
        std::cout << "Book ID da ton tai!" << std::endl;
        return false;
    }
    
    if (!validateBookData(*book)) {
        std::cout << "Du lieu sach khong hop le!" << std::endl;
        return false;
    }
    
    books.push_back(std::move(book));
    bookMap[bookId] = books.back().get();
    
    std::cout << "Them sach thanh cong!" << std::endl;
    
    // Auto save after adding book
    saveBooks();
    incrementOperationCount();
    return true;
}

bool Library::removeBook(const std::string& bookTitle) {
    Book* book = findBookByTitle(bookTitle);
    if (!book) {
        std::cout << "Khong tim thay sach voi ten: " << bookTitle << std::endl;
        return false;
    }
    
    std::string bookId = book->getBookId();
    
    // Remove from books vector
    auto bookIt = std::find_if(books.begin(), books.end(),
                               [&bookId](const std::unique_ptr<Book>& book) {
                                   return book->getBookId() == bookId;
                               });
    if (bookIt != books.end()) {
        books.erase(bookIt);
    }
    
    // Remove from map
    bookMap.erase(bookId);
    
    std::cout << "Xoa sach '" << bookTitle << "' thanh cong!" << std::endl;
    
    // Auto save after removing book
    saveBooks();
    incrementOperationCount();
    return true;
}

bool Library::updateBook(const std::string& bookTitle) {
    Book* book = findBookByTitle(bookTitle);
    if (!book) {
        std::cout << "Khong tim thay sach voi ten: " << bookTitle << std::endl;
        return false;
    }
    
    // Update book information
    std::string newTitle, newAuthor, newLocation;
    int newYear, newCopies;
    
    std::cout << "Cap nhat sach: " << bookTitle << std::endl;
    std::cout << "Nhap tieu de moi (de trong de giu nguyen): ";
    std::getline(std::cin, newTitle);
    if (!newTitle.empty()) {
        book->setTitle(newTitle);
    }
    
    std::cout << "Nhap ten tac gia moi (de trong de giu nguyen): ";
    std::getline(std::cin, newAuthor);
    if (!newAuthor.empty()) {
        book->setAuthor(newAuthor);
    }
    
    std::cout << "Nhap nam xuat ban moi (0 de giu nguyen): ";
    std::cin >> newYear;
    std::cin.ignore();
    if (newYear > 0) {
        book->setPublicationYear(newYear);
    }
    
    std::cout << "Nhap vi tri moi (de trong de giu nguyen): ";
    std::getline(std::cin, newLocation);
    if (!newLocation.empty()) {
        book->setLocation(newLocation);
    }
    
    std::cout << "Nhap so luong ban sao moi (0 de giu nguyen): ";
    std::cin >> newCopies;
    std::cin.ignore();
    if (newCopies > 0) {
        book->setTotalCopies(newCopies);
    }
    
    std::cout << "Cap nhat sach '" << bookTitle << "' thanh cong!" << std::endl;
    
    // Auto save after updating book
    saveBooks();
    incrementOperationCount();
    return true;
}

Book* Library::findBook(const std::string& bookId) {
    auto it = bookMap.find(bookId);
    return (it != bookMap.end()) ? it->second : nullptr;
}

Book* Library::findBookByTitle(const std::string& bookTitle) {
    for (const auto& book : books) {
        if (book->getTitle() == bookTitle) {
            return book.get();
        }
    }
    return nullptr;
}

std::vector<Book*> Library::searchBooks(const std::string& keyword) {
    std::vector<Book*> results;
    std::string lowerKeyword = Utils::toLower(keyword);
    
    for (const auto& book : books) {
        std::string lowerTitle = Utils::toLower(book->getTitle());
        std::string lowerAuthor = Utils::toLower(book->getAuthor());
        std::string lowerIsbn = Utils::toLower(book->getIsbn());
        
        if (Utils::contains(lowerTitle, lowerKeyword) ||
            Utils::contains(lowerAuthor, lowerKeyword) ||
            Utils::contains(lowerIsbn, lowerKeyword)) {
            results.push_back(book.get());
        }
    }
    
    return results;
}

std::vector<Book*> Library::getAvailableBooks() const {
    std::vector<Book*> availableBooks;
    for (const auto& book : books) {
        if (book->isAvailable()) {
            availableBooks.push_back(book.get());
        }
    }
    return availableBooks;
}

void Library::listAllBooks() const {
    std::cout << "\n=== DANH SACH TAT CA SACH ===" << std::endl;
    
    if (books.empty()) {
        std::cout << "Khong co sach nao trong thu vien!" << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(30) << "Tieu de" 
              << std::setw(20) << "Tac gia" 
              << std::setw(15) << "Trang thai" 
              << std::setw(10) << "Ban sao" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
    
    for (const auto& book : books) {
        std::cout << std::left << std::setw(10) << book->getBookId()
                  << std::setw(30) << (book->getTitle().length() > 28 ? 
                                      book->getTitle().substr(0, 25) + "..." : book->getTitle())
                  << std::setw(20) << (book->getAuthor().length() > 18 ? 
                                      book->getAuthor().substr(0, 15) + "..." : book->getAuthor())
                  << std::setw(15) << Book::statusToString(book->getStatus())
                  << std::setw(10) << book->getAvailableCopies() << "/" << book->getTotalCopies() << std::endl;
    }
}

bool Library::borrowBook(const std::string& username, const std::string& bookTitle) {
    User* user = findUser(username);
    Book* book = findBookByTitle(bookTitle);
    
    if (!user || !book) {
        std::cout << "Nguoi dung hoac sach khong ton tai!" << std::endl;
        return false;
    }
    
    if (user->getUserType() != UserType::READER) {
        std::cout << "Chi doc gia moi duoc muon sach!" << std::endl;
        return false;
    }
    
    if (!book->isAvailable()) {
        std::cout << "Sach '" << bookTitle << "' khong co san!" << std::endl;
        return false;
    }
    
    if (book->borrowBook()) {
        std::cout << "Muon sach '" << bookTitle << "' thanh cong!" << std::endl;
        
        // Add borrow record
        addBorrowRecord(username, bookTitle, book->getBookId());
        
        // Auto save after borrowing book
        saveBooks();
        saveUsers();
        saveBorrowRecords();
        incrementOperationCount();
        return true;
    }
    
    return false;
}

bool Library::returnBook(const std::string& username, const std::string& bookTitle) {
    User* user = findUser(username);
    Book* book = findBookByTitle(bookTitle);
    
    if (!user || !book) {
        std::cout << "Nguoi dung hoac sach khong ton tai!" << std::endl;
        return false;
    }
    
    if (user->getUserType() != UserType::READER) {
        std::cout << "Chi doc gia moi duoc tra sach!" << std::endl;
        return false;
    }
    
    if (book->returnBook()) {
        std::cout << "Tra sach '" << bookTitle << "' thanh cong!" << std::endl;
        
        // Update borrow record
        updateBorrowRecord(username, bookTitle);
        
        // Auto save after returning book
        saveBooks();
        saveUsers();
        saveBorrowRecords();
        incrementOperationCount();
        return true;
    }
    
    return false;
}

void Library::addBorrowRecord(const std::string& username, const std::string& bookTitle, const std::string& bookId) {
    auto record = std::make_unique<BorrowRecord>(username, bookTitle, bookId);
    borrowRecords.push_back(std::move(record));
}

void Library::updateBorrowRecord(const std::string& username, const std::string& bookTitle) {
    for (auto& record : borrowRecords) {
        if (record->getUsername() == username && record->getBookTitle() == bookTitle && !record->getIsReturned()) {
            record->setReturnDate(std::time(nullptr));
            record->setIsReturned(true);
            break;
        }
    }
}

std::vector<BorrowRecord*> Library::getBorrowRecordsByUsername(const std::string& username) {
    std::vector<BorrowRecord*> userRecords;
    for (const auto& record : borrowRecords) {
        if (record->getUsername() == username) {
            userRecords.push_back(record.get());
        }
    }
    return userRecords;
}

std::vector<BorrowRecord*> Library::getAllBorrowRecords() const {
    std::vector<BorrowRecord*> allRecords;
    for (const auto& record : borrowRecords) {
        allRecords.push_back(record.get());
    }
    return allRecords;
}

bool Library::reserveBook(const std::string& username, const std::string& bookId) {
    User* user = findUser(username);
    Book* book = findBook(bookId);
    
    if (!user || !book) {
        std::cout << "Nguoi dung hoac sach khong ton tai!" << std::endl;
        return false;
    }
    
    if (!book->isAvailable()) {
        std::cout << "Sach khong co san!" << std::endl;
        return false;
    }
    
    if (book->reserveBook()) {
        std::cout << "Dat truoc sach thanh cong!" << std::endl;
        return true;
    }
    
    return false;
}

void Library::generateLibraryReport() const {
    std::cout << "\n=== BAO CAO THU VIEN ===" << std::endl;
    std::cout << "Ten thu vien: " << libraryName << std::endl;
    std::cout << "Dia chi: " << address << std::endl;
    std::cout << "Dien thoai: " << phoneNumber << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << std::endl;
    
    displayStatistics();
}

void Library::displayLibraryInfo() const {
    std::cout << "\n=== THONG TIN THU VIEN ===" << std::endl;
    std::cout << "Ten: " << libraryName << std::endl;
    std::cout << "Dia chi: " << address << std::endl;
    std::cout << "Dien thoai: " << phoneNumber << std::endl;
    std::cout << "Email: " << email << std::endl;
}

bool Library::loadData() {
    // Ensure data directory exists
    if (!FileManager::ensureDataDirectory()) {
        std::cout << "Khong the tao thu muc data!" << std::endl;
        return false;
    }
    
    bool success = true;
    success &= loadUsers();
    success &= loadBooks();
    success &= loadBorrowRecords();
    return success;
}

bool Library::saveData() const {
    std::cout << "Dang luu du lieu..." << std::endl;
    
    bool success = true;
    success &= saveUsers();
    success &= saveBooks();
    success &= saveBorrowRecords();
    
    if (success) {
        std::cout << "Luu du lieu thanh cong!" << std::endl;
    } else {
        std::cout << "Luu du lieu that bai!" << std::endl;
    }
    
    return success;
}

bool Library::loadUsers() {
    // Clear existing data
    users.clear();
    librarians.clear();
    readers.clear();
    userMap.clear();
    
    // Load librarians
    std::vector<std::unique_ptr<User>> tempLibrarians;
    if (!FileManager::loadLibrariansFromFile(FileManager::getDataDirectory() + "/librarians.txt", tempLibrarians)) {
        std::cout << "Khong the tai du lieu thu thu!" << std::endl;
    }
    
    // Load readers
    std::vector<std::unique_ptr<User>> tempReaders;
    if (!FileManager::loadReadersFromFile(FileManager::getDataDirectory() + "/readers.txt", tempReaders)) {
        std::cout << "Khong the tai du lieu doc gia!" << std::endl;
    }
    
    // Add librarians to users and librarians vectors
    for (auto& librarian : tempLibrarians) {
        if (librarian && librarian->getUserType() == UserType::LIBRARIAN) {
            auto libPtr = std::make_unique<Librarian>(*static_cast<Librarian*>(librarian.get()));
            librarians.push_back(std::move(libPtr));
            users.push_back(std::make_unique<Librarian>(*static_cast<Librarian*>(librarian.get())));
        }
    }
    
    // Add readers to users and readers vectors
    for (auto& reader : tempReaders) {
        if (reader && reader->getUserType() == UserType::READER) {
            auto readerPtr = std::make_unique<Reader>(*static_cast<Reader*>(reader.get()));
            readers.push_back(std::move(readerPtr));
            users.push_back(std::make_unique<Reader>(*static_cast<Reader*>(reader.get())));
        }
    }
    
    // Rebuild maps
    initializeMaps();
    return true;
}

bool Library::saveUsers() const {
    std::cout << "Dang luu du lieu nguoi dung..." << std::endl;
    
    // Save librarians
    std::vector<std::unique_ptr<User>> librarianUsers;
    for (const auto& user : users) {
        if (user->getUserType() == UserType::LIBRARIAN) {
            librarianUsers.push_back(std::make_unique<Librarian>(*static_cast<Librarian*>(user.get())));
        }
    }
    
    if (!FileManager::saveLibrariansToFile(FileManager::getDataDirectory() + "/librarians.txt", librarianUsers)) {
        std::cout << "Khong the luu du lieu thu thu!" << std::endl;
        std::cout << "Loi: " << FileManager::getLastError() << std::endl;
        return false;
    }
    
    // Save readers
    std::vector<std::unique_ptr<User>> readerUsers;
    for (const auto& user : users) {
        if (user->getUserType() == UserType::READER) {
            readerUsers.push_back(std::make_unique<Reader>(*static_cast<Reader*>(user.get())));
        }
    }
    
    if (!FileManager::saveReadersToFile(FileManager::getDataDirectory() + "/readers.txt", readerUsers)) {
        std::cout << "Khong the luu du lieu doc gia!" << std::endl;
        std::cout << "Loi: " << FileManager::getLastError() << std::endl;
        return false;
    }
    
    std::cout << "Luu du lieu nguoi dung thanh cong!" << std::endl;
    return true;
}

bool Library::loadBooks() {
    if (!FileManager::loadBooksFromFile(FileManager::getDataDirectory() + "/books.txt", books)) {
        std::cout << "Khong the tai du lieu sach!" << std::endl;
        return false;
    }
    
    // Rebuild book map
    bookMap.clear();
    for (const auto& book : books) {
        bookMap[book->getBookId()] = book.get();
    }
    
    return true;
}

bool Library::saveBooks() const {
    std::cout << "Dang luu du lieu sach..." << std::endl;
    
    if (!FileManager::saveBooksToFile(FileManager::getDataDirectory() + "/books.txt", books)) {
        std::cout << "Khong the luu du lieu sach!" << std::endl;
        std::cout << "Loi: " << FileManager::getLastError() << std::endl;
        return false;
    }
    
    std::cout << "Luu du lieu sach thanh cong!" << std::endl;
    return true;
}



int Library::getAvailableBooksCount() const {
    int count = 0;
    for (const auto& book : books) {
        if (book->isAvailable()) {
            count++;
        }
    }
    return count;
}

int Library::getBorrowedBooksCount() const {
    int count = 0;
    for (const auto& book : books) {
        if (book->getStatus() == BookStatus::BORROWED) {
            count++;
        }
    }
    return count;
}

void Library::displayStatistics() const {
    std::cout << "=== THONG KE ===" << std::endl;
    std::cout << "Tong so sach: " << getTotalBooks() << std::endl;
    std::cout << "Sach co san: " << getAvailableBooksCount() << std::endl;
    std::cout << "Sach da muon: " << getBorrowedBooksCount() << std::endl;
    std::cout << "Tong so nguoi dung: " << getTotalUsers() << std::endl;
    std::cout << "So thu thu: " << librarians.size() << std::endl;
    std::cout << "So doc gia: " << readers.size() << std::endl;
}

void Library::initializeMaps() {
    userMap.clear();
    bookMap.clear();
    
    for (auto& user : users) {
        userMap[user->getUsername()] = user.get();
    }
    
    for (auto& book : books) {
        bookMap[book->getBookId()] = book.get();
    }
}

bool Library::validateBookData(const Book& book) const {
    if (book.getTitle().empty() || book.getAuthor().empty() || 
        book.getIsbn().empty() || book.getLocation().empty()) {
        return false;
    }
    
    if (book.getPublicationYear() < 1800 || book.getPublicationYear() > 2024) {
        return false;
    }
    
    if (book.getTotalCopies() <= 0) {
        return false;
    }
    
    return true;
}

bool Library::validateUserData(const User& user) const {
    if (user.getUsername().empty() || user.getPassword().empty() ||
        user.getFullName().empty() || user.getEmail().empty()) {
        return false;
    }
    
    // Basic email validation
    if (user.getEmail().find('@') == std::string::npos) {
        return false;
    }
    
    return true;
}

std::string Library::generateBookId() {
    std::stringstream ss;
    ss << "BK" << bookIdCounter++;
    return ss.str();
}

std::string Library::generateReaderId() {
    std::stringstream ss;
    ss << "RD" << std::setfill('0') << std::setw(3) << readerIdCounter++;
    return ss.str();
}

bool Library::loadBorrowRecords() {
    if (!FileManager::loadBorrowRecordsFromFile(FileManager::getDataDirectory() + "/borrow_records.txt", borrowRecords)) {
        std::cout << "Khong the tai du lieu muon tra sach!" << std::endl;
        return false;
    }
    
    return true;
}

bool Library::saveBorrowRecords() const {
    std::cout << "Dang luu du lieu muon tra sach..." << std::endl;
    
    if (!FileManager::saveBorrowRecordsToFile(FileManager::getDataDirectory() + "/borrow_records.txt", borrowRecords)) {
        std::cout << "Khong the luu du lieu muon tra sach!" << std::endl;
        std::cout << "Loi: " << FileManager::getLastError() << std::endl;
        return false;
    }
    
    std::cout << "Luu du lieu muon tra sach thanh cong!" << std::endl;
    return true;
}

// Auto save functionality implementation
void Library::enableAutoSave(bool enable) {
    autoSaveEnabled = enable;
}

bool Library::isAutoSaveEnabled() const {
    return autoSaveEnabled;
}

void Library::setAutoSaveInterval(int operations) {
    if (operations > 0) {
        autoSaveInterval = operations;
    }
}

int Library::getAutoSaveInterval() const {
    return autoSaveInterval;
}

void Library::incrementOperationCount() {
    operationCount++;
    if (autoSaveEnabled && operationCount >= autoSaveInterval) {
        std::cout << "[AUTO-SAVE] Đang lưu dữ liệu..." << std::endl;
        saveData();
        operationCount = 0;
        std::cout << "[AUTO-SAVE] Đã lưu dữ liệu thành công!" << std::endl;
    }
}

void Library::displayBorrowHistoryForLibrarian() const {
    std::cout << "\n=== LICH SU MUON TRA SACH - THU THU ===" << std::endl;
    
    if (borrowRecords.empty()) {
        std::cout << "Chua co lich su muon tra sach nao!" << std::endl;
        return;
    }
    
    // Hiển thị tổng quan
    std::cout << "Tong so giao dich: " << borrowRecords.size() << std::endl;
    
    int totalBorrowed = 0;
    int totalReturned = 0;
    int totalOverdue = 0;
    
    for (const auto& record : borrowRecords) {
        if (record->getIsReturned()) {
            totalReturned++;
        } else {
            totalBorrowed++;
            if (record->isOverdue()) {
                totalOverdue++;
            }
        }
    }
    
    std::cout << "Sach dang muon: " << totalBorrowed << std::endl;
    std::cout << "Sach da tra: " << totalReturned << std::endl;
    std::cout << "Sach qua han: " << totalOverdue << std::endl;
    std::cout << std::endl;
    
    // Hiển thị chi tiết từng giao dịch
    std::cout << std::left << std::setw(15) << "Doc gia" 
              << std::setw(20) << "Ten sach" 
              << std::setw(12) << "Ngay muon" 
              << std::setw(12) << "Han tra" 
              << std::setw(12) << "Ngay tra" 
              << std::setw(10) << "Trang thai" 
              << std::setw(10) << "Qua han" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    for (const auto& record : borrowRecords) {
        std::cout << std::left << std::setw(15) << (record->getUsername().length() > 14 ? 
                                      record->getUsername().substr(0, 12) + ".." : record->getUsername())
                  << std::setw(20) << (record->getBookTitle().length() > 19 ? 
                                      record->getBookTitle().substr(0, 17) + ".." : record->getBookTitle())
                  << std::setw(12) << record->getBorrowDateString()
                  << std::setw(12) << record->getDueDateString()
                  << std::setw(12) << record->getReturnDateString()
                  << std::setw(10) << (record->getIsReturned() ? "Da tra" : "Dang muon")
                  << std::setw(10) << (record->isOverdue() ? "Co" : "Khong") << std::endl;
    }
    
    // Hiển thị cảnh báo sách quá hạn
    if (totalOverdue > 0) {
        std::cout << std::endl;
        std::cout << "[CANH BAO] Co " << totalOverdue << " sach qua han!" << std::endl;
        std::cout << "Danh sach sach qua han:" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        for (const auto& record : borrowRecords) {
            if (!record->getIsReturned() && record->isOverdue()) {
                std::cout << "Doc gia: " << record->getUsername() 
                          << " | Sach: " << record->getBookTitle()
                          << " | Qua han: " << record->getDaysOverdue() << " ngay" << std::endl;
            }
        }
    }
    
    // Hiển thị thống kê theo độc giả
    std::cout << std::endl;
    std::cout << "=== THONG KE THEO DOC GIA ===" << std::endl;
    
    std::unordered_map<std::string, int> readerBorrowCount;
    std::unordered_map<std::string, int> readerOverdueCount;
    
    for (const auto& record : borrowRecords) {
        std::string username = record->getUsername();
        readerBorrowCount[username]++;
        if (!record->getIsReturned() && record->isOverdue()) {
            readerOverdueCount[username]++;
        }
    }
    
    std::cout << std::left << std::setw(15) << "Doc gia" 
              << std::setw(15) << "Tong muon" 
              << std::setw(15) << "Qua han" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    
    for (const auto& pair : readerBorrowCount) {
        std::string username = pair.first;
        int totalBorrows = pair.second;
        int overdueCount = readerOverdueCount[username];
        
        std::cout << std::left << std::setw(15) << (username.length() > 14 ? 
                                      username.substr(0, 12) + ".." : username)
                  << std::setw(15) << totalBorrows
                  << std::setw(15) << overdueCount << std::endl;
    }
}
