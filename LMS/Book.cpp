#include <iostream>
#include "Book.h"

Book::Book() : yearPublished(0), available(true) {}

Book::Book(const std::string& isbn, const std::string& title,
           const std::string& author, const std::string& publisher,
           const Category& category, int yearPublished, bool available)
    : isbn(isbn), title(title), author(author), publisher(publisher),
      category(category), yearPublished(yearPublished), available(available) {}

std::string Book::getISBN() const { return isbn; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getPublisher() const { return publisher; }
Category Book::getCategory() const { return category; }
int Book::getYearPublished() const { return yearPublished; }
bool Book::isAvailable() const { return available; }

void Book::setISBN(const std::string& isbn) { this->isbn = isbn; }
void Book::setTitle(const std::string& title) { this->title = title; }
void Book::setAuthor(const std::string& author) { this->author = author; }
void Book::setPublisher(const std::string& publisher) { this->publisher = publisher; }
void Book::setCategory(const Category& category) { this->category = category; }
void Book::setYearPublished(int yearPublished) { this->yearPublished = yearPublished; }
void Book::setAvailable(bool available) { this->available = available; }

void Book::display() const {
    std::cout << "ISBN: " << isbn << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "Category: " << category.getName() << "\n"
              << "Year Published: " << yearPublished << "\n"
              << "Publisher: " << publisher << "\n" // thêm phần in nhà xuất bản
              << "Available: " << (available ? "Yes" : "No") << "\n";
}
