#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <string>
#include <vector>
#include "Account.h"
#include "Book.h"

class Librarian {
private:
    std::string id;       // ID thủ thư (linkedId trong Account)
    std::string name;
    std::string email;
    std::string phone;

public:
    Librarian();
    Librarian(const std::string& id, const std::string& name,
              const std::string& email, const std::string& phone);

    // --- Quản lý thông tin cá nhân ---
    void viewPersonalInfoFromFile() const;  // đọc từ librarians.txt
    void editPersonalInfo();
    void savePersonalInfoToFile() const;    // lưu vào librarians.txt
    
    // --- Quản lý thủ thư ---
    static void viewOtherLibrarians(const std::vector<Account>& accounts, const std::string& currentId);

    // --- Quản lý tài khoản thành viên ---
    static void viewMembers(const std::vector<Account>& accounts);
    static void deleteMember(std::vector<Account>& accounts, const std::string& username);

    // --- Quản lý sách ---
    static void addBook(std::vector<Book>& books);
    static void editBook(std::vector<Book>& books, const std::string& isbn);
    static void deleteBook(std::vector<Book>& books, const std::string& isbn);
    static void viewBooks(const std::vector<Book>& books);
    static void searchBooks(const std::vector<Book>& books);
    static std::vector<Book> loadBooksFromFile(const std::string& filename);
    static void saveBooksToFile(const std::string& filename, const std::vector<Book>& books, bool append = false);
};

#endif
