#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include <vector>
#include <memory>

class Book;
class Reader;

class Librarian : public User {
private:
    std::string employeeId;
    std::string department;

public:
    Librarian() = default;
    Librarian(const std::string& username, const std::string& password,
              const std::string& fullName, const std::string& email,
              const std::string& employeeId, const std::string& department);
    ~Librarian() override = default;

    // Getters
    std::string getEmployeeId() const { return employeeId; }
    std::string getDepartment() const { return department; }

    // Setters
    void setEmployeeId(const std::string& employeeId) { this->employeeId = employeeId; }
    void setDepartment(const std::string& department) { this->department = department; }

    // Override methods
    void displayInfo() const override;
    std::string toFileString() const override;
    void fromFileString(const std::string& data) override;

    // Librarian specific methods
    bool addBook(std::vector<std::unique_ptr<Book>>& books);
    bool removeBook(std::vector<std::unique_ptr<Book>>& books);
    bool updateBook(std::vector<std::unique_ptr<Book>>& books);
    void listAllBooks(const std::vector<Book*>& books) const;
    void searchBooks(const std::vector<Book*>& books) const;
    void manageReaders(std::vector<Reader*>& readers);
    void generateReports(const std::vector<Book*>& books,
                        const std::vector<Reader*>& readers) const;
};

#endif // LIBRARIAN_H
