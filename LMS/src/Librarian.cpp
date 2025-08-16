#include "Librarian.h"
#include "Book.h"
#include "Reader.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

Librarian::Librarian(const std::string& username, const std::string& password,
                     const std::string& fullName, const std::string& email,
                     const std::string& employeeId, const std::string& department)
    : User(username, password, fullName, email, UserType::LIBRARIAN),
      employeeId(employeeId), department(department) {
}

void Librarian::displayInfo() const {
    User::displayInfo();
    std::cout << "Employee ID: " << employeeId << std::endl;
    std::cout << "Department: " << department << std::endl;
}

std::string Librarian::toFileString() const {
    std::ostringstream oss;
    oss << User::toFileString() << "|" << employeeId << "|" << department;
    return oss.str();
}

void Librarian::fromFileString(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    // Split the entire string by '|'
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    // Check if we have enough tokens (7 tokens for librarian: username|password|fullName|email|userType|employeeId|department)
    if (tokens.size() >= 7) {
        username = tokens[0];
        password = tokens[1];
        fullName = tokens[2];
        email = tokens[3];
        try {
            userType = static_cast<UserType>(std::stoi(tokens[4]));
        } catch (const std::exception& e) {
            userType = UserType::LIBRARIAN; // Default to LIBRARIAN
        }
        employeeId = tokens[5];
        department = tokens[6];
    }
}

bool Librarian::addBook(std::vector<std::unique_ptr<Book>>& books) {
    std::cout << "\n=== THEM SACH MOI ===" << std::endl;
    
    std::string title, author, isbn, publisher, location, description;
    int publicationYear, totalCopies;
    
    std::cout << "Nhap tieu de sach: ";
    std::getline(std::cin, title);
    
    std::cout << "Nhap ten tac gia: ";
    std::getline(std::cin, author);
    
    std::cout << "Nhap ISBN: ";
    std::getline(std::cin, isbn);
    
    std::cout << "Nhap nha xuat ban: ";
    std::getline(std::cin, publisher);
    
    std::cout << "Nhap nam xuat ban: ";
    std::cin >> publicationYear;
    std::cin.ignore();
    
    std::cout << "Nhap vi tri ke sach: ";
    std::getline(std::cin, location);
    
    std::cout << "Nhap so luong ban sao: ";
    std::cin >> totalCopies;
    std::cin.ignore();
    
    std::cout << "Nhap mo ta sach: ";
    std::getline(std::cin, description);
    
    // Generate book ID
    std::string bookId = Book::generateBookId();
    
    // Create new book
    auto newBook = std::make_unique<Book>(bookId, title, author, isbn, publisher,
                                         publicationYear, BookCategory::OTHER, location, totalCopies);
    newBook->setDescription(description);
    
    books.push_back(std::move(newBook));
    
    std::cout << "Sach da duoc them thanh cong voi ID: " << bookId << std::endl;
    return true;
}

bool Librarian::removeBook(std::vector<std::unique_ptr<Book>>& books) {
    std::cout << "\n=== XOA SACH ===" << std::endl;
    
    std::string bookId;
    std::cout << "Nhap ID sach can xoa: ";
    std::getline(std::cin, bookId);
    
    auto it = std::find_if(books.begin(), books.end(),
                           [&bookId](const std::unique_ptr<Book>& book) {
                               return book->getBookId() == bookId;
                           });
    
    if (it != books.end()) {
        std::cout << "Tim thay sach: " << (*it)->getTitle() << std::endl;
        std::cout << "Ban co chac chan muon xoa sach nay? (y/n): ";
        
        char confirm;
        std::cin >> confirm;
        std::cin.ignore();
        
        if (confirm == 'y' || confirm == 'Y') {
            books.erase(it);
            std::cout << "Sach da duoc xoa thanh cong!" << std::endl;
            return true;
        } else {
            std::cout << "Huy xoa sach!" << std::endl;
        }
    } else {
        std::cout << "Khong tim thay sach voi ID: " << bookId << std::endl;
    }
    
    return false;
}

bool Librarian::updateBook(std::vector<std::unique_ptr<Book>>& books) {
    std::cout << "\n=== CAP NHAT SACH ===" << std::endl;
    
    std::string bookId;
    std::cout << "Nhap ID sach can cap nhat: ";
    std::getline(std::cin, bookId);
    
    auto it = std::find_if(books.begin(), books.end(),
                           [&bookId](const std::unique_ptr<Book>& book) {
                               return book->getBookId() == bookId;
                           });
    
    if (it != books.end()) {
        std::cout << "Tim thay sach: " << (*it)->getTitle() << std::endl;
        
        std::string newTitle, newAuthor, newLocation;
        int newYear, newCopies;
        
        std::cout << "Nhap tieu de moi (de trong de giu nguyen): ";
        std::getline(std::cin, newTitle);
        if (!newTitle.empty()) {
            (*it)->setTitle(newTitle);
        }
        
        std::cout << "Nhap ten tac gia moi (de trong de giu nguyen): ";
        std::getline(std::cin, newAuthor);
        if (!newAuthor.empty()) {
            (*it)->setAuthor(newAuthor);
        }
        
        std::cout << "Nhap nam xuat ban moi (0 de giu nguyen): ";
        std::cin >> newYear;
        std::cin.ignore();
        if (newYear > 0) {
            (*it)->setPublicationYear(newYear);
        }
        
        std::cout << "Nhap vi tri moi (de trong de giu nguyen): ";
        std::getline(std::cin, newLocation);
        if (!newLocation.empty()) {
            (*it)->setLocation(newLocation);
        }
        
        std::cout << "Nhap so luong ban sao moi (0 de giu nguyen): ";
        std::cin >> newCopies;
        std::cin.ignore();
        if (newCopies > 0) {
            (*it)->setTotalCopies(newCopies);
        }
        
        std::cout << "Cap nhat sach thanh cong!" << std::endl;
        return true;
    } else {
        std::cout << "Khong tim thay sach voi ID: " << bookId << std::endl;
    }
    
    return false;
}

void Librarian::listAllBooks(const std::vector<Book*>& books) const {
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
        if (book) {
            std::cout << std::left << std::setw(10) << book->getBookId()
                      << std::setw(30) << (book->getTitle().length() > 28 ? 
                                          book->getTitle().substr(0, 25) + "..." : book->getTitle())
                      << std::setw(20) << (book->getAuthor().length() > 18 ? 
                                          book->getAuthor().substr(0, 15) + "..." : book->getAuthor())
                      << std::setw(15) << Book::statusToString(book->getStatus())
                      << std::setw(10) << book->getAvailableCopies() << "/" << book->getTotalCopies() << std::endl;
        }
    }
}

void Librarian::searchBooks(const std::vector<Book*>& books) const {
    std::cout << "\n=== TIM KIEM SACH ===" << std::endl;
    
    std::string keyword;
    std::cout << "Nhap tu khoa tim kiem: ";
    std::getline(std::cin, keyword);
    
    if (keyword.empty()) {
        std::cout << "Tu khoa khong duoc de trong!" << std::endl;
        return;
    }
    
    std::vector<const Book*> results;
    std::string lowerKeyword = Utils::toLower(keyword);
    
    for (const auto& book : books) {
        if (book) {
            std::string lowerTitle = Utils::toLower(book->getTitle());
            std::string lowerAuthor = Utils::toLower(book->getAuthor());
            std::string lowerIsbn = Utils::toLower(book->getIsbn());
            
            if (Utils::contains(lowerTitle, lowerKeyword) ||
                Utils::contains(lowerAuthor, lowerKeyword) ||
                Utils::contains(lowerIsbn, lowerKeyword)) {
                results.push_back(book);
            }
        }
    }
    
    if (results.empty()) {
        std::cout << "Khong tim thay sach nao phu hop!" << std::endl;
        return;
    }
    
    std::cout << "Tim thay " << results.size() << " sach:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const auto& book : results) {
        std::cout << "ID: " << book->getBookId() << std::endl;
        std::cout << "Tieu de: " << book->getTitle() << std::endl;
        std::cout << "Tac gia: " << book->getAuthor() << std::endl;
        std::cout << "Trang thai: " << Book::statusToString(book->getStatus()) << std::endl;
        std::cout << "Ban sao: " << book->getAvailableCopies() << "/" << book->getTotalCopies() << std::endl;
        std::cout << std::string(30, '-') << std::endl;
    }
}

void Librarian::manageReaders(std::vector<Reader*>& readers) {
    std::cout << "\n=== QUAN LY DOC GIA ===" << std::endl;
    
    if (readers.empty()) {
        std::cout << "Khong co doc gia nao!" << std::endl;
        return;
    }
    
    std::cout << "Danh sach doc gia:" << std::endl;
    std::cout << std::left << std::setw(15) << "Reader ID" 
              << std::setw(20) << "Username" 
              << std::setw(30) << "Ho ten" 
              << std::setw(20) << "Trang thai" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
    
    for (const auto& reader : readers) {
        if (reader) {
            std::cout << std::left << std::setw(15) << reader->getReaderId()
                      << std::setw(20) << reader->getUsername()
                      << std::setw(30) << (reader->getFullName().length() > 28 ? 
                                          reader->getFullName().substr(0, 25) + "..." : reader->getFullName())
                      << std::setw(20) << reader->getMembershipStatus() << std::endl;
        }
    }
}

void Librarian::generateReports(const std::vector<Book*>& books,
                               const std::vector<Reader*>& readers) const {
    std::cout << "\n=== BAO CAO THU VIEN ===" << std::endl;
    
    int totalBooks = 0;
    int availableBooks = 0;
    int borrowedBooks = 0;
    int reservedBooks = 0;
    
    for (const auto& book : books) {
        if (book) {
            totalBooks++;
            switch (book->getStatus()) {
                case BookStatus::AVAILABLE:
                    availableBooks++;
                    break;
                case BookStatus::BORROWED:
                    borrowedBooks++;
                    break;
                case BookStatus::RESERVED:
                    reservedBooks++;
                    break;
                default:
                    break;
            }
        }
    }
    
    std::cout << "Tong so sach: " << totalBooks << std::endl;
    std::cout << "Sach co san: " << availableBooks << std::endl;
    std::cout << "Sach da muon: " << borrowedBooks << std::endl;
    std::cout << "Sach da dat truoc: " << reservedBooks << std::endl;
    std::cout << "Tong so doc gia: " << readers.size() << std::endl;
    
    if (totalBooks > 0) {
        double utilizationRate = (static_cast<double>(borrowedBooks + reservedBooks) / totalBooks) * 100;
        std::cout << "Ty le su dung: " << std::fixed << std::setprecision(2) << utilizationRate << "%" << std::endl;
    }
}
