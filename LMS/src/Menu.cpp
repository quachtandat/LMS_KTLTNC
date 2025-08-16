#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>

Menu::Menu(Library& lib) : library(lib), currentUser(nullptr), isRunning(true) {
    initializeLibrary();
}

void Menu::run() {
    displayWelcomeMessage();
    
    while (isRunning) {
        if (!currentUser) {
            showMainMenu();
        } else {
            if (currentUser->getUserType() == UserType::LIBRARIAN) {
                showLibrarianMenu();
            } else if (currentUser->getUserType() == UserType::READER) {
                showReaderMenu();
            }
        }
    }
    
    displayGoodbyeMessage();
}

void Menu::showMainMenu() {
    displayHeader("MENU CHINH");
    std::cout << "1. Dang nhap" << std::endl;
    std::cout << "2. Dang ky tai khoan" << std::endl;
    std::cout << "3. Xem thong tin thu vien" << std::endl;
    std::cout << "4. Thoat" << std::endl;
    std::cout << std::endl;
    
    int choice = getValidChoice(1, 4);
    
    switch (choice) {
        case 1:
            if (authenticateUser()) {
                displaySuccess("Dang nhap thanh cong!");
            } else {
                displayError("Dang nhap that bai! Vui long kiem tra lai username va password.");
            }
            break;
        case 2:
            registerAccount();
            break;
        case 3:
            library.displayLibraryInfo();
            pauseScreen();
            break;
        case 4:
            saveAndExit();
            break;
    }
}

void Menu::showLoginMenu() {
    displayHeader("DANG NHAP");
    std::cout << "Username: ";
    std::string username = getValidInput("");
    
    std::cout << "Password: ";
    std::string password = getPasswordInput();
    
    if (library.authenticateUser(username, password)) {
        currentUser = library.findUser(username);
        displaySuccess("Dang nhap thanh cong!");
    } else {
        displayError("Username hoac password khong dung!");
    }
}

void Menu::showLibrarianMenu() {
    displayHeader("MENU THU THU");
    std::cout << "1. Them sach moi" << std::endl;
    std::cout << "2. Xoa sach" << std::endl;
    std::cout << "3. Cap nhat sach" << std::endl;
    std::cout << "4. Danh sach tat ca sach" << std::endl;
    std::cout << "5. Tim kiem sach" << std::endl;
    std::cout << "6. Quan ly doc gia" << std::endl;
    std::cout << "7. Tao bao cao" << std::endl;
    std::cout << "8. Xem lich su muon tra" << std::endl;
    std::cout << "9. Cai dat tu dong luu" << std::endl;
    std::cout << "10. Dang xuat" << std::endl;
    std::cout << "11. Thoat" << std::endl;
    std::cout << std::endl;
    
    int choice = getValidChoice(1, 11);
    handleLibrarianChoice(choice);
}

void Menu::showReaderMenu() {
    displayHeader("MENU DOC GIA");
    std::cout << "1. Muon sach" << std::endl;
    std::cout << "2. Tra sach" << std::endl;
    std::cout << "3. Xem lich su muon sach" << std::endl;
    std::cout << "4. Tim kiem sach" << std::endl;
    std::cout << "5. Xem sach co san" << std::endl;
    std::cout << "6. Cap nhat thong tin ca nhan" << std::endl;
    std::cout << "7. Dang xuat" << std::endl;
    std::cout << "8. Thoat" << std::endl;
    std::cout << std::endl;
    
    int choice = getValidChoice(1, 8);
    handleReaderChoice(choice);
}

void Menu::showGuestMenu() {
    displayHeader("MENU KHACH");
    std::cout << "1. Xem thong tin thu vien" << std::endl;
    std::cout << "2. Tim kiem sach" << std::endl;
    std::cout << "3. Xem sach co san" << std::endl;
    std::cout << "4. Quay lai" << std::endl;
    std::cout << std::endl;
    
    int choice = getValidChoice(1, 4);
    handleGuestChoice(choice);
}

bool Menu::authenticateUser() {
    showLoginMenu();
    return currentUser != nullptr;
}

void Menu::logout() {
    if (currentUser) {
        displayInfo("Dang xuat thanh cong!");
        currentUser = nullptr;
    }
}

void Menu::handleLibrarianChoice(int choice) {
    switch (choice) {
        case 1:
            addNewBook();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            updateBook();
            break;
        case 4:
            listAllBooks();
            break;
        case 5:
            searchBooksLibrarian();
            break;
        case 6:
            manageReaders();
            break;
        case 7:
            generateReports();
            break;
        case 8:
            viewBorrowHistoryForLibrarian();
            break;
        case 9:
            configureAutoSave();
            break;
        case 10:
            logout();
            break;
        case 11:
            saveAndExit();
            break;
    }
    pauseScreen();
}

void Menu::handleReaderChoice(int choice) {
    switch (choice) {
        case 1:
            borrowBook();
            break;
        case 2:
            returnBook();
            break;
        case 3:
            viewBorrowHistory();
            break;
        case 4:
            searchBooksReader();
            break;
        case 5:
            viewAvailableBooksReader();
            break;
        case 6:
            updateProfile();
            break;
        case 7:
            logout();
            break;
        case 8:
            saveAndExit();
            break;
    }
    pauseScreen();
}

void Menu::handleGuestChoice(int choice) {
    switch (choice) {
        case 1:
            viewLibraryInfo();
            break;
        case 2:
            searchBooksGuest();
            break;
        case 3:
            viewAvailableBooksGuest();
            break;
        case 4:
            // Return to main menu
            break;
    }
}

// Librarian functions
void Menu::addNewBook() {
    displayHeader("THEM SACH MOI");
    
    std::cout << "Nhap thong tin sach moi:" << std::endl;
    
    // Tự động tạo Book ID
    std::string bookId = library.generateBookId();
    std::cout << "Book ID tu dong: " << bookId << std::endl;
    
    std::string title = getValidInput("Tieu de sach");
    std::string author = getValidInput("Ten tac gia");
    std::string isbn = getValidInput("ISBN");
    std::string publisher = getValidInput("Nha xuat ban");
    
    int year;
    while (true) {
        std::cout << "Nam xuat ban: ";
        if (std::cin >> year && year >= 1800 && year <= 2025) {
            std::cin.ignore();
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayError("Nam xuat ban khong hop le! Vui long nhap lai.");
        }
    }
    
    std::cout << "Chon the loai sach:" << std::endl;
    std::cout << "1. Van hoc" << std::endl;
    std::cout << "2. Khoa hoc" << std::endl;
    std::cout << "3. Lich su" << std::endl;
    std::cout << "4. Triet hoc" << std::endl;
    std::cout << "5. Khac" << std::endl;
    
    int categoryChoice = getValidChoice(1, 5);
    BookCategory category;
    switch (categoryChoice) {
        case 1: category = BookCategory::LITERATURE; break;
        case 2: category = BookCategory::SCIENCE; break;
        case 3: category = BookCategory::HISTORY; break;
        case 4: category = BookCategory::PHILOSOPHY; break;
        default: category = BookCategory::OTHER; break;
    }
    
    std::string location = getValidInput("Vi tri trong thu vien (vi du: A1)");
    
    int copies;
    while (true) {
        std::cout << "So luong ban sao: ";
        if (std::cin >> copies && copies > 0) {
            std::cin.ignore();
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayError("So luong ban sao khong hop le! Vui long nhap lai.");
            return;
        }
    }
    
    auto book = std::make_unique<Book>(bookId, title, author, isbn, publisher, year, category, location, copies);
    
    if (library.addBook(std::move(book))) {
        displaySuccess("Them sach '" + title + "' thanh cong voi ID: " + bookId);
    } else {
        displayError("Khong the them sach! Kiem tra lai thong tin.");
    }
}

void Menu::removeBook() {
    std::cout << "Nhap ten sach can xoa: ";
    std::string bookTitle = getValidInput("");
    
    if (library.removeBook(bookTitle)) {
        displaySuccess("Xoa sach thanh cong!");
    } else {
        displayError("Khong the xoa sach!");
    }
}

void Menu::updateBook() {
    std::cout << "Nhap ten sach can cap nhat: ";
    std::string bookTitle = getValidInput("");
    
    if (library.updateBook(bookTitle)) {
        displaySuccess("Cap nhat sach thanh cong!");
    } else {
        displayError("Khong the cap nhat sach!");
    }
}

void Menu::listAllBooks() {
    library.listAllBooks();
}

void Menu::searchBooksLibrarian() {
    std::cout << "Nhap tu khoa tim kiem: ";
    std::string keyword = getValidInput("");
    
    auto results = library.searchBooks(keyword);
    if (results.empty()) {
        displayInfo("Khong tim thay sach nao phu hop!");
    } else {
        std::cout << "Tim thay " << results.size() << " sach:" << std::endl;
        for (const auto& book : results) {
            book->displayInfo();
        }
    }
}

void Menu::manageReaders() {
    displayHeader("QUAN LY DOC GIA");
    
    std::cout << "Chon chuc nang:" << std::endl;
    std::cout << "1. Xem danh sach doc gia" << std::endl;
    std::cout << "2. Them doc gia moi" << std::endl;
    std::cout << "3. Xoa doc gia" << std::endl;
    std::cout << "4. Cap nhat thong tin doc gia" << std::endl;
    std::cout << "5. Quay lai" << std::endl;
    
    int choice = getValidChoice(1, 5);
    
    switch (choice) {
        case 1:
            displayAllReaders();
            break;
        case 2:
            addNewReader();
            break;
        case 3:
            removeReader();
            break;
        case 4:
            updateReader();
            break;
        case 5:
            return;
    }
}

void Menu::generateReports() {
    library.generateLibraryReport();
}

void Menu::viewStatistics() {
    library.displayStatistics();
}

// Reader functions
void Menu::borrowBook() {
    std::cout << "Nhap ten sach can muon: ";
    std::string bookTitle = getValidInput("");
    
    if (library.borrowBook(currentUser->getUsername(), bookTitle)) {
        displaySuccess("Muon sach thanh cong!");
    } else {
        displayError("Khong the muon sach!");
    }
}

void Menu::returnBook() {
    std::cout << "Nhap ten sach can tra: ";
    std::string bookTitle = getValidInput("");
    
    if (library.returnBook(currentUser->getUsername(), bookTitle)) {
        displaySuccess("Tra sach thanh cong!");
    } else {
        displayError("Khong the tra sach!");
    }
}

void Menu::viewBorrowHistory() {
    if (currentUser->getUserType() == UserType::READER) {
        displayHeader("LICH SU MUON TRA SACH");
        
        auto records = library.getBorrowRecordsByUsername(currentUser->getUsername());
        if (records.empty()) {
            displayInfo("Ban chua co lich su muon tra sach nao!");
            return;
        }
        
        std::cout << std::left << std::setw(15) << "Ten sach" 
                  << std::setw(12) << "Ngay muon" 
                  << std::setw(12) << "Han tra" 
                  << std::setw(12) << "Ngay tra" 
                  << std::setw(10) << "Trang thai" << std::endl;
        std::cout << std::string(70, '-') << std::endl;
        
        for (const auto& record : records) {
            std::cout << std::left << std::setw(15) << (record->getBookTitle().length() > 14 ? 
                                      record->getBookTitle().substr(0, 12) + ".." : record->getBookTitle())
                      << std::setw(12) << record->getBorrowDateString()
                      << std::setw(12) << record->getDueDateString()
                      << std::setw(12) << record->getReturnDateString()
                      << std::setw(10) << (record->getIsReturned() ? "Da tra" : "Dang muon") << std::endl;
        }
        
        // Hiển thị thông tin quá hạn
        for (const auto& record : records) {
            if (!record->getIsReturned() && record->isOverdue()) {
                std::cout << "\n[CHU Y] Sach '" << record->getBookTitle() 
                          << "' da qua han " << record->getDaysOverdue() << " ngay!" << std::endl;
            }
        }
    }
}

void Menu::searchBooksReader() {
    std::cout << "Nhap tu khoa tim kiem: ";
    std::string keyword = getValidInput("");
    
    auto results = library.searchBooks(keyword);
    if (results.empty()) {
        displayInfo("Khong tim thay sach nao phu hop!");
    } else {
        std::cout << "Tim thay " << results.size() << " sach:" << std::endl;
        for (const auto& book : results) {
            book->displayInfo();
        }
    }
}

void Menu::viewAvailableBooksReader() {
    if (currentUser->getUserType() == UserType::READER) {
        Reader* reader = static_cast<Reader*>(currentUser);
        reader->viewAvailableBooks(library.getAvailableBooks());
    }
}

void Menu::updateProfile() {
    if (!currentUser) {
        displayError("Ban chua dang nhap!");
        return;
    }
    
    displayHeader("CAP NHAT THONG TIN CA NHAN");
    
    std::cout << "Thong tin hien tai:" << std::endl;
    std::cout << "Ho ten: " << currentUser->getFullName() << std::endl;
    std::cout << "Email: " << currentUser->getEmail() << std::endl;
    std::cout << std::endl;
    
    std::cout << "Nhap thong tin moi (de trong de giu nguyen):" << std::endl;
    
    std::string newFullName = getValidInput("Ho ten moi");
    if (!newFullName.empty()) {
        currentUser->setFullName(newFullName);
    }
    
    std::string newEmail = getValidInput("Email moi");
    if (!newEmail.empty()) {
        currentUser->setEmail(newEmail);
    }
    
    std::cout << "Ban co muon doi mat khau? (y/n): ";
    char changePassword;
    std::cin >> changePassword;
    std::cin.ignore();
    
    if (changePassword == 'y' || changePassword == 'Y') {
        std::cout << "Nhap mat khau cu: ";
        std::string oldPassword = getPasswordInput();
        
        if (currentUser->authenticate(oldPassword)) {
            std::cout << "Nhap mat khau moi: ";
            std::string newPassword = getPasswordInput();
            std::cout << "Xac nhan mat khau moi: ";
            std::string confirmPassword = getPasswordInput();
            
            if (newPassword == confirmPassword) {
                currentUser->setPassword(newPassword);
                displaySuccess("Doi mat khau thanh cong!");
            } else {
                displayError("Mat khau xac nhan khong dung!");
            }
        } else {
            displayError("Mat khau cu khong dung!");
        }
    }
    
    displaySuccess("Cap nhat thong tin thanh cong!");
    
    // Auto save after updating profile
    library.saveUsers();
}

// Guest functions
void Menu::viewLibraryInfo() {
    library.displayLibraryInfo();
}

void Menu::registerAccount() {
    displayHeader("DANG KY TAI KHOAN");
    
    std::cout << "Chon loai tai khoan:" << std::endl;
    std::cout << "1. Doc gia" << std::endl;
    std::cout << "2. Quay lai" << std::endl;
    
    int choice = getValidChoice(1, 2);
    if (choice == 1) {
        registerReaderAccount();
    }
}

// Utility functions
void Menu::clearScreen() {
    #ifdef WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void Menu::pauseScreen() {
    std::cout << "\nNhan Enter de tiep tuc...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::displayHeader(const std::string& title) {
    clearScreen();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << Utils::centerText(title, 50) << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::endl;
}

void Menu::displayFooter() {
    std::cout << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

int Menu::getValidChoice(int min, int max) {
    int choice;
    while (true) {
        std::cout << "Nhap lua chon (" << min << "-" << max << "): ";
        if (std::cin >> choice && choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayError("Lua chon khong hop le! Vui long nhap lai.");
        }
    }
}

std::string Menu::getValidInput(const std::string& prompt) {
    std::cout << prompt << ": ";
    std::string input;
    std::getline(std::cin, input);
    return Utils::trimString(input);
}

bool Menu::confirmAction(const std::string& message) {
    std::cout << message << " (y/n): ";
    char response;
    std::cin >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return (response == 'y' || response == 'Y');
}

std::string Menu::getPasswordInput() {
    std::string password;
    std::getline(std::cin, password);
    return password;
}

void Menu::displayError(const std::string& error) {
    std::cout << "[LOI] " << error << std::endl;
}

void Menu::displaySuccess(const std::string& message) {
    std::cout << "[THANH CONG] " << message << std::endl;
}

void Menu::displayInfo(const std::string& info) {
    std::cout << "[THONG TIN] " << info << std::endl;
}

// Guest functions
void Menu::searchBooksGuest() {
    std::cout << "Nhap tu khoa tim kiem: ";
    std::string keyword = getValidInput("");
    
    auto results = library.searchBooks(keyword);
    if (results.empty()) {
        displayInfo("Khong tim thay sach nao phu hop!");
    } else {
        std::cout << "Tim thay " << results.size() << " sach:" << std::endl;
        for (const auto& book : results) {
            book->displayInfo();
        }
    }
}

void Menu::viewAvailableBooksGuest() {
    library.listAllBooks();
}

void Menu::initializeLibrary() {
    // Load existing data
    if (!library.loadData()) {
        displayInfo("Khong co du lieu cu, tao du lieu moi...");
        
        // Create default librarian account
        auto librarian = std::make_unique<Librarian>("admin", "admin123", 
                                                   "Administrator", "admin@library.com",
                                                   "EMP001", "IT");
        library.addUser(std::move(librarian));
        
        // Create some sample books
        auto book1 = std::make_unique<Book>(library.generateBookId(), "The Great Gatsby", "F. Scott Fitzgerald",
                                           "978-0743273565", "Scribner", 1925,
                                           BookCategory::LITERATURE, "A1", 3);
        library.addBook(std::move(book1));
        
        auto book2 = std::make_unique<Book>(library.generateBookId(), "To Kill a Mockingbird", "Harper Lee",
                                           "978-0446310789", "Grand Central", 1960,
                                           BookCategory::LITERATURE, "A2", 2);
        library.addBook(std::move(book2));
        
        // Save data
        library.saveData();
        displaySuccess("Tao du lieu mau thanh cong!");
    }
}

void Menu::saveAndExit() {
    if (confirmAction("Ban co chac chan muon thoat?")) {
        library.saveData();
        isRunning = false;
    }
}

void Menu::displayWelcomeMessage() {
    std::cout << "Chao mung den voi He thong Quan ly Thu vien!" << std::endl;
    std::cout << "Tai khoan mac dinh: admin / admin123" << std::endl;
    std::cout << "Tinh nang tu dong luu du lieu: BAT (luu sau moi 5 thao tac)" << std::endl;
    std::cout << std::endl;
}

void Menu::displayGoodbyeMessage() {
    std::cout << "Cam on ban da su dung he thong!" << std::endl;
    std::cout << "Hen gap lai!" << std::endl;
}

// Helper methods for reader management
void Menu::displayAllReaders() {
    std::cout << "\n=== DANH SACH DOC GIA ===" << std::endl;
    library.displayStatistics(); // This will show reader count
    // TODO: Implement detailed reader list display
}

void Menu::addNewReader() {
    displayHeader("THEM DOC GIA MOI");
    
    std::cout << "Nhap thong tin doc gia moi:" << std::endl;
    
    std::cout << "Username: ";
    std::string username = getValidInput("");
    std::cout << "Password: ";
    std::string password = getPasswordInput();

    std::cout << "Xac nhan mat khau: ";
    std::string confirmPassword = getPasswordInput();
    
    if (password != confirmPassword) {
        displayError("Mat khau xac nhan khong dung!");
        return;
    }
    
    std::string fullName = getValidInput("Ho ten day du");
    std::string email = getValidInput("Email");
    
    // Tự động tạo Reader ID
    std::string readerId = library.generateReaderId();
    std::cout << "Reader ID tu dong: " << readerId << std::endl;
    
    auto reader = std::make_unique<Reader>(username, password, fullName, email, readerId);
    
    if (library.addUser(std::move(reader))) {
        displaySuccess("Them doc gia '" + fullName + "' thanh cong voi ID: " + readerId);
    } else {
        displayError("Khong the them doc gia! Kiem tra lai thong tin.");
    }
}

void Menu::removeReader() {
    std::cout << "Nhap username cua doc gia can xoa: ";
    std::string username = getValidInput("Username");
    
    if (confirmAction("Ban co chac chan muon xoa doc gia nay?")) {
        if (library.removeUser(username)) {
            displaySuccess("Xoa doc gia thanh cong!");
        } else {
            displayError("Khong the xoa doc gia!");
        }
    }
}

void Menu::updateReader() {
    std::cout << "Nhap username cua doc gia can cap nhat: ";
    std::string username = getValidInput("Username");
    
    User* user = library.findUser(username);
    if (!user || user->getUserType() != UserType::READER) {
        displayError("Khong tim thay doc gia!");
        return;
    }
    
    displayHeader("CAP NHAT THONG TIN DOC GIA");
    std::cout << "Thong tin hien tai:" << std::endl;
    std::cout << "Ho ten: " << user->getFullName() << std::endl;
    std::cout << "Email: " << user->getEmail() << std::endl;
    
    std::string newFullName = getValidInput("Ho ten moi (de trong de giu nguyen)");
    if (!newFullName.empty()) {
        user->setFullName(newFullName);
    }
    
    std::string newEmail = getValidInput("Email moi (de trong de giu nguyen)");
    if (!newEmail.empty()) {
        user->setEmail(newEmail);
    }
    
    displaySuccess("Cap nhat thong tin doc gia thanh cong!");
    
    // Auto save after updating reader
    library.saveUsers();
}



void Menu::registerReaderAccount() {
    displayHeader("DANG KY TAI KHOAN DOC GIA");
    
    std::cout << "Nhap thong tin tai khoan:" << std::endl;

    std::cout << "Username: ";
    std::string username = getValidInput("");
    std::cout << "Password: ";
    std::string password = getPasswordInput();

    std::cout << "Xac nhan mat khau: ";
    std::string confirmPassword = getPasswordInput();
    
    if (password != confirmPassword) {
        displayError("Mat khau xac nhan khong dung!");
        return;
    }
    
    std::string fullName = getValidInput("Ho ten day du");
    std::string email = getValidInput("Email");
    
    // Tự động tạo Reader ID
    std::string readerId = library.generateReaderId();
    std::cout << "Reader ID tu dong: " << readerId << std::endl;
    
    auto reader = std::make_unique<Reader>(username, password, fullName, email, readerId);
    
    if (library.addUser(std::move(reader))) {
        displaySuccess("Dang ky tai khoan thanh cong voi ID: " + readerId);
        std::cout << "Ban co the dang nhap voi tai khoan vua tao." << std::endl;
    } else {
        displayError("Khong the dang ky tai khoan! Kiem tra lai thong tin.");
    }
}

void Menu::configureAutoSave() {
    displayHeader("CAI DAT TU DONG LUU");
    
    std::cout << "Trang thai hien tai:" << std::endl;
    std::cout << "Tu dong luu: " << (library.isAutoSaveEnabled() ? "BAT" : "TAT") << std::endl;
    std::cout << "So thao tac truoc khi luu: " << library.getAutoSaveInterval() << std::endl;
    std::cout << std::endl;
    
    std::cout << "Chon chuc nang:" << std::endl;
    std::cout << "1. Bat/Tat tu dong luu" << std::endl;
    std::cout << "2. Thay doi so thao tac truoc khi luu" << std::endl;
    std::cout << "3. Luu du lieu ngay bay gio" << std::endl;
    std::cout << "4. Quay lai" << std::endl;
    
    int choice = getValidChoice(1, 4);
    
    switch (choice) {
        case 1: {
            bool currentState = library.isAutoSaveEnabled();
            library.enableAutoSave(!currentState);
            displaySuccess("Da " + std::string(currentState ? "TAT" : "BAT") + " tu dong luu!");
            break;
        }
        case 2: {
            std::cout << "Nhap so thao tac truoc khi tu dong luu (1-20): ";
            int interval;
            if (std::cin >> interval && interval >= 1 && interval <= 20) {
                library.setAutoSaveInterval(interval);
                displaySuccess("Da cap nhat so thao tac truoc khi luu!");
            } else {
                displayError("So thao tac khong hop le!");
            }
            std::cin.ignore();
            break;
        }
        case 3: {
            if (library.saveData()) {
                displaySuccess("Luu du lieu thanh cong!");
            } else {
                displayError("Luu du lieu that bai!");
            }
            break;
        }
        case 4:
            return;
    }
}

void Menu::viewBorrowHistoryForLibrarian() {
    library.displayBorrowHistoryForLibrarian();
}
