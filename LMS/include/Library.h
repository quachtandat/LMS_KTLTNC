#ifndef LIBRARY_H
#define LIBRARY_H

#include "User.h"
#include "Book.h"
#include "Librarian.h"
#include "Reader.h"
#include "BorrowRecord.h"
#include <vector>
#include <memory>
#include <unordered_map>

class Library {
private:
    std::string libraryName;
    std::string address;
    std::string phoneNumber;
    std::string email;
    std::vector<std::unique_ptr<Book>> books;
    std::vector<std::unique_ptr<User>> users;
    std::vector<std::unique_ptr<Librarian>> librarians;
    std::vector<std::unique_ptr<Reader>> readers;
    std::vector<std::unique_ptr<BorrowRecord>> borrowRecords;
    std::unordered_map<std::string, User*> userMap; // username -> User*
    std::unordered_map<std::string, Book*> bookMap; // bookId -> Book*
    
    // Auto save settings
    bool autoSaveEnabled;
    int autoSaveInterval;
    int operationCount;
    
    // ID counters for auto-generation
    static int bookIdCounter;
    static int readerIdCounter;

public:
    Library() = default;
    Library(const std::string& name, const std::string& address, 
            const std::string& phone, const std::string& email);
    
    // Delete copy constructor and assignment operator
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;
    
    // Allow move constructor and assignment operator
    Library(Library&&) = default;
    Library& operator=(Library&&) = default;
    
    ~Library() = default;

    // Getters
    std::string getLibraryName() const { return libraryName; }
    std::string getAddress() const { return address; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }

    // User management
    bool addUser(std::unique_ptr<User> user);
    bool removeUser(const std::string& username);
    User* findUser(const std::string& username);
    bool authenticateUser(const std::string& username, const std::string& password);
    UserType getUserType(const std::string& username);

    // Book management
    bool addBook(std::unique_ptr<Book> book);
    bool removeBook(const std::string& bookTitle);
    bool updateBook(const std::string& bookTitle);
    Book* findBook(const std::string& bookId);
    Book* findBookByTitle(const std::string& bookTitle);
    std::vector<Book*> searchBooks(const std::string& keyword);
    std::vector<Book*> getAvailableBooks() const;
    void listAllBooks() const;
    
    // ID generation
    std::string generateBookId();
    std::string generateReaderId();

    // Library operations
    bool borrowBook(const std::string& username, const std::string& bookTitle);
    bool returnBook(const std::string& username, const std::string& bookTitle);
    bool reserveBook(const std::string& username, const std::string& bookId);
    void generateLibraryReport() const;
    void displayLibraryInfo() const;
    
    // Borrow record management
    void addBorrowRecord(const std::string& username, const std::string& bookTitle, const std::string& bookId);
    void updateBorrowRecord(const std::string& username, const std::string& bookTitle);
    std::vector<BorrowRecord*> getBorrowRecordsByUsername(const std::string& username);
    std::vector<BorrowRecord*> getAllBorrowRecords() const;



    // Data persistence
    bool loadData();
    bool saveData() const;
    bool loadUsers();
    bool saveUsers() const;
    bool loadBooks();
    bool saveBooks() const;
    bool loadBorrowRecords();
    bool saveBorrowRecords() const;
    
    // Auto save functionality
    void enableAutoSave(bool enable = true);
    bool isAutoSaveEnabled() const;
    void setAutoSaveInterval(int operations);
    int getAutoSaveInterval() const;
    void incrementOperationCount();

    // Statistics
    int getTotalBooks() const { return books.size(); }
    int getTotalUsers() const { return users.size(); }
    int getAvailableBooksCount() const;
    int getBorrowedBooksCount() const;
    void displayStatistics() const;
    void displayBorrowHistoryForLibrarian() const;

private:
    void initializeMaps();
    bool validateBookData(const Book& book) const;
    bool validateUserData(const User& user) const;
};

#endif // LIBRARY_H
