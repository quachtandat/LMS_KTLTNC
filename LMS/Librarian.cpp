#include "Librarian.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Librarian::Librarian() {}

Librarian::Librarian(const std::string& id, const std::string& name,
                     const std::string& email, const std::string& phone)
    : id(id), name(name), email(email), phone(phone) {}

void Librarian::viewPersonalInfoFromFile() const {
    std::ifstream in("./data/librarians.txt");
    if (!in.is_open()) {
        std::cout << "No librarian data file found!\n";
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string lid, lname, lemail, lphone;
        std::getline(ss, lid, '|');
        std::getline(ss, lname, '|');
        std::getline(ss, lemail, '|');
        std::getline(ss, lphone, '|');
        if (lid == id) {
            std::cout << "\n--- Personal Information ---\n";
            std::cout << "ID: " << lid << "\n";
            std::cout << "Full Name: " << lname << "\n";
            std::cout << "Email: " << lemail << "\n";
            std::cout << "Phone: " << lphone << "\n";
            return;
        }
    }
    std::cout << "No profile found for this librarian.\n";
}

void Librarian::editPersonalInfo() {
    std::cout << "\nEnter new full name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter new email: ";
    std::getline(std::cin, email);
    std::cout << "Enter new phone number: ";
    std::getline(std::cin, phone);
}

void Librarian::savePersonalInfoToFile() const {
    std::ifstream in("./data/librarians.txt");
    std::vector<std::string> lines;
    bool found = false;

    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream ss(line);
            std::string lid;
            std::getline(ss, lid, '|');
            if (lid == id) {
                lines.push_back(id + "|" + name + "|" + email + "|" + phone);
                found = true;
            } else {
                lines.push_back(line);
            }
        }
        in.close();
    }

    if (!found) {
        lines.push_back(id + "|" + name + "|" + email + "|" + phone);
    }

    std::ofstream out("./data/librarians.txt");
    for (auto& l : lines) out << l << "\n";
}

void Librarian::viewOtherLibrarians(const std::vector<Account>& accounts, const std::string& currentId) {
    std::cout << "\n--- Other Librarians ---\n";
    for (const auto& acc : accounts) {
        if (acc.getRole() == Role::LIBRARIAN && acc.getLinkedId() != currentId) {
            std::cout << "Username: " << acc.getUsername()
                      << " | ID: " << acc.getLinkedId() << "\n";
        }
    }
}

void Librarian::viewMembers(const std::vector<Account>& accounts) {
    std::cout << "\n--- Members List ---\n";
    for (const auto& acc : accounts) {
        if (acc.getRole() == Role::MEMBER) {
            std::cout << "Username: " << acc.getUsername()
                      << " | ID: " << acc.getLinkedId() << "\n";
        }
    }
}

void Librarian::deleteMember(std::vector<Account>& accounts, const std::string& username) {
    accounts.erase(std::remove_if(accounts.begin(), accounts.end(),
                                  [&](const Account& acc) {
                                      return acc.getRole() == Role::MEMBER && acc.getUsername() == username;
                                  }),
                   accounts.end());
}

void Librarian::addBook(std::vector<Book>& books) {
    std::string isbn, title, author, publisher, catId, catName;
    int year;
    bool available = true;

    std::cout << "Enter ISBN: "; std::getline(std::cin >> std::ws, isbn);
    std::cout << "Enter book title: "; std::getline(std::cin, title);
    std::cout << "Enter author: "; std::getline(std::cin, author);
    std::cout << "Enter publisher: "; std::getline(std::cin, publisher);
    std::cout << "Enter category ID: "; std::getline(std::cin, catId);
    std::cout << "Enter category name: "; std::getline(std::cin, catName);
    std::cout << "Enter publication year: "; std::cin >> year;

    Category cat(catId, catName);
    books.emplace_back(isbn, title, author, publisher, cat, year, available);
}

void Librarian::editBook(std::vector<Book>& books, const std::string& isbn) {
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            std::string title, author, publisher, catId, catName;
            int year;
            bool available;

            std::cout << "Enter new book title: "; std::getline(std::cin >> std::ws, title);
            std::cout << "Enter new author: "; std::getline(std::cin, author);
            std::cout << "Enter new publisher: "; std::getline(std::cin, publisher);
            std::cout << "Enter new category ID: "; std::getline(std::cin, catId);
            std::cout << "Enter new category name: "; std::getline(std::cin, catName);
            std::cout << "Enter new publication year: "; std::cin >> year;
            std::cout << "Available? (1=Yes, 0=No): "; std::cin >> available;

            Category cat(catId, catName);
            book.setTitle(title);
            book.setAuthor(author);
            book.setPublisher(publisher);
            book.setCategory(cat);
            book.setYearPublished(year);
            book.setAvailable(available);
            break;
        }
    }
}

void Librarian::deleteBook(std::vector<Book>& books, const std::string& isbn) {
    books.erase(std::remove_if(books.begin(), books.end(),
                               [&](const Book& book) {
                                   return book.getISBN() == isbn;
                               }),
                books.end());
}

void Librarian::viewBooks(const std::vector<Book>& books) {
    std::cout << "\n--- Book List ---\n";
    for (const auto& book : books) {
        std::cout << book.getISBN() << " | " << book.getTitle()
                  << " | " << book.getAuthor() << " | "
                  << book.getPublisher() << " | "
                  << book.getCategory().getName()
                  << " | " << book.getYearPublished()
                  << " | " << (book.isAvailable() ? "Available" : "Unavailable")
                  << "\n";
    }
}

void Librarian::searchBooks(const std::vector<Book>& books) {
    std::string keyword;
    std::cout << "Enter ISBN or Title keyword: ";
    std::getline(std::cin >> std::ws, keyword);
    std::cout << "\n--- Search Results ---\n";
    for (const auto& book : books) {
    if (book.getISBN().find(keyword) != std::string::npos ||
        book.getTitle().find(keyword) != std::string::npos) {
        
            std::cout << "ISBN: " << book.getISBN()
                    << " | Title: " << book.getTitle()
                    << " | Author: " << book.getAuthor()
                    << " | Publisher: " << book.getPublisher()
                    << " | Year: " << book.getYearPublished()
                    << " | Category: " << book.getCategory().getName()
                    << " | Status: " << (book.isAvailable() ? "Available" : "Not Available")
                    << "\n";
        }
    }
}

std::vector<Book> Librarian::loadBooksFromFile(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream in(filename);
    if (!in.is_open()) return books;

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string isbn, title, author, publisher, catId, catName;
        int year; bool available;

        std::getline(ss, isbn, '|');
        std::getline(ss, title, '|');
        std::getline(ss, author, '|');
        std::getline(ss, publisher, '|');
        std::getline(ss, catId, '|');
        std::getline(ss, catName, '|');
        ss >> year; ss.ignore(1, '|');
        ss >> available;

        Category cat(catId, catName);
        books.emplace_back(isbn, title, author, publisher, cat, year, available);
    }
    return books;
}

void Librarian::saveBooksToFile(const std::string& filename, const std::vector<Book>& books, bool append) {
    std::ofstream out(filename, append ? std::ios::app : std::ios::trunc);
    for (const auto& book : books) {
        out << book.getISBN() << "|"
            << book.getTitle() << "|"
            << book.getAuthor() << "|"
            << book.getPublisher() << "|"
            << book.getCategory().getID() << "|"
            << book.getCategory().getName() << "|"
            << book.getYearPublished() << "|"
            << book.isAvailable() << "\n";
    }
}
