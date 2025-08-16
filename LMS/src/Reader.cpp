#include "Reader.h"
#include "Book.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

Reader::Reader(const std::string& username, const std::string& password,
               const std::string& fullName, const std::string& email,
               const std::string& readerId)
    : User(username, password, fullName, email, UserType::READER),
      readerId(readerId), maxBooksAllowed(5), membershipStatus("ACTIVE") {
}

void Reader::displayInfo() const {
    User::displayInfo();
    std::cout << "Reader ID: " << readerId << std::endl;
    std::cout << "Max Books Allowed: " << maxBooksAllowed << std::endl;
    std::cout << "Membership Status: " << membershipStatus << std::endl;
}

std::string Reader::toFileString() const {
    std::ostringstream oss;
    oss << User::toFileString() << "|" << readerId << "|" << maxBooksAllowed << "|" << membershipStatus;
    return oss.str();
}

void Reader::fromFileString(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    // Split the entire string by '|'
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    // Check if we have enough tokens for basic reader info (at least 7 tokens: username|password|fullName|email|userType|readerId|maxBooks|status)
    if (tokens.size() >= 7) {
        username = tokens[0];
        password = tokens[1];
        fullName = tokens[2];
        email = tokens[3];
        try {
            userType = static_cast<UserType>(std::stoi(tokens[4]));
        } catch (const std::exception& e) {
            userType = UserType::READER; // Default to READER
        }
        readerId = tokens[5];
        try {
            maxBooksAllowed = std::stoi(tokens[6]);
        } catch (const std::exception& e) {
            maxBooksAllowed = 5; // Default max books
        }
        membershipStatus = tokens.size() > 7 ? tokens[7] : "ACTIVE";
    }
}

// These methods are now handled by the Library class, so we'll provide simple implementations
bool Reader::borrowBook(const std::string& bookId) {
    // This is now handled by Library::borrowBook
    std::cout << "Phuong thuc nay da duoc chuyen sang Library class!" << std::endl;
    return false;
}

bool Reader::returnBook(const std::string& bookId) {
    // This is now handled by Library::returnBook
    std::cout << "Phuong thuc nay da duoc chuyen sang Library class!" << std::endl;
    return false;
}

void Reader::viewBorrowHistory() const {
    // This is now handled by Menu::viewBorrowHistory
    std::cout << "Phuong thuc nay da duoc chuyen sang Menu class!" << std::endl;
}

void Reader::searchBooks(const std::vector<Book*>& books) const {
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
            
            if (Utils::contains(lowerTitle, lowerKeyword) ||
                Utils::contains(lowerAuthor, lowerKeyword)) {
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

void Reader::viewAvailableBooks(const std::vector<Book*>& books) const {
    std::cout << "\n=== SACH CO SAN ===" << std::endl;
    
    std::vector<const Book*> availableBooks;
    for (const auto& book : books) {
        if (book && book->getStatus() == BookStatus::AVAILABLE) {
            availableBooks.push_back(book);
        }
    }
    
    if (availableBooks.empty()) {
        std::cout << "Khong co sach nao co san!" << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(30) << "Tieu de" 
              << std::setw(20) << "Tac gia" 
              << std::setw(15) << "Vi tri" 
              << std::setw(10) << "Ban sao" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
    
    for (const auto& book : availableBooks) {
        std::cout << std::left << std::setw(10) << book->getBookId()
                  << std::setw(30) << (book->getTitle().length() > 28 ? 
                                      book->getTitle().substr(0, 25) + "..." : book->getTitle())
                  << std::setw(20) << (book->getAuthor().length() > 18 ? 
                                      book->getAuthor().substr(0, 15) + "..." : book->getAuthor())
                  << std::setw(15) << book->getLocation()
                  << std::setw(10) << book->getAvailableCopies() << std::endl;
    }
}

bool Reader::canBorrowMoreBooks() const {
    // This is now handled by the Library class
    return true; // Placeholder implementation
}

void Reader::updateMembershipStatus() {
    // This is now handled by the Library class
    // Placeholder implementation
}

std::vector<std::string> Reader::getCurrentBorrowedBooks() const {
    // This is now handled by the Library class
    return std::vector<std::string>(); // Placeholder implementation
}
