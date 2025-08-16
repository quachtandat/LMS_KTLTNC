#ifndef READER_H
#define READER_H

#include "User.h"
#include "BorrowRecord.h"
#include <vector>
#include <memory>
#include <chrono>

class Book;

class Reader : public User {
private:
    std::string readerId;
    int maxBooksAllowed;
    std::string membershipStatus; // "ACTIVE", "SUSPENDED", "EXPIRED"

public:
    Reader() = default;
    Reader(const std::string& username, const std::string& password,
           const std::string& fullName, const std::string& email,
           const std::string& readerId);
    ~Reader() override = default;

    // Getters
    std::string getReaderId() const { return readerId; }
    int getMaxBooksAllowed() const { return maxBooksAllowed; }
    std::string getMembershipStatus() const { return membershipStatus; }

    // Setters
    void setReaderId(const std::string& readerId) { this->readerId = readerId; }
    void setMaxBooksAllowed(int maxBooks) { maxBooksAllowed = maxBooks; }
    void setMembershipStatus(const std::string& status) { membershipStatus = status; }

    // Override methods
    void displayInfo() const override;
    std::string toFileString() const override;
    void fromFileString(const std::string& data) override;

    // Reader specific methods
    bool borrowBook(const std::string& bookId);
    bool returnBook(const std::string& bookId);
    void viewBorrowHistory() const;
    void searchBooks(const std::vector<Book*>& books) const;
    void viewAvailableBooks(const std::vector<Book*>& books) const;
    bool canBorrowMoreBooks() const;
    void updateMembershipStatus();
    std::vector<std::string> getCurrentBorrowedBooks() const;
};

#endif // READER_H
