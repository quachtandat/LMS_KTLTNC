#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Category.h"

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    std::string publisher; // Thêm tên nhà xuất bản
    Category category;
    int yearPublished;
    bool available;

public:
    Book();
    Book(const std::string& isbn, const std::string& title,
         const std::string& author, const std::string& publisher, // thêm vào constructor
         const Category& category, int yearPublished, bool available = true);

    std::string getISBN() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const; // getter mới
    Category getCategory() const;
    int getYearPublished() const;
    bool isAvailable() const;

    void setISBN(const std::string& isbn);
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setPublisher(const std::string& publisher); // setter mới
    void setCategory(const Category& category);
    void setYearPublished(int yearPublished);
    void setAvailable(bool available);

    void display() const;
};

#endif
