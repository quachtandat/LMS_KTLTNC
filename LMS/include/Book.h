#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <chrono>

enum class BookStatus {
    AVAILABLE,
    BORROWED,
    RESERVED,
    MAINTENANCE
};

enum class BookCategory {
    FICTION,
    NON_FICTION,
    SCIENCE,
    TECHNOLOGY,
    HISTORY,
    PHILOSOPHY,
    LITERATURE,
    OTHER
};

class Book {
private:
    std::string bookId;
    std::string title;
    std::string author;
    std::string isbn;
    std::string publisher;
    int publicationYear;
    BookCategory category;
    BookStatus status;
    std::string location; // Shelf number
    int totalCopies;
    int availableCopies;
    std::string description;
    std::chrono::system_clock::time_point lastModified;

public:
    Book() = default;
    Book(const std::string& bookId, const std::string& title, const std::string& author,
         const std::string& isbn, const std::string& publisher, int publicationYear,
         BookCategory category, const std::string& location, int totalCopies);
    ~Book() = default;

    // Getters
    std::string getBookId() const { return bookId; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }
    std::string getPublisher() const { return publisher; }
    int getPublicationYear() const { return publicationYear; }
    BookCategory getCategory() const { return category; }
    BookStatus getStatus() const { return status; }
    std::string getLocation() const { return location; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }
    std::string getDescription() const { return description; }

    // Setters
    void setTitle(const std::string& title) { this->title = title; }
    void setAuthor(const std::string& author) { this->author = author; }
    void setIsbn(const std::string& isbn) { this->isbn = isbn; }
    void setPublisher(const std::string& publisher) { this->publisher = publisher; }
    void setPublicationYear(int year) { publicationYear = year; }
    void setCategory(BookCategory category) { this->category = category; }
    void setStatus(BookStatus status) { this->status = status; }
    void setLocation(const std::string& location) { this->location = location; }
    void setTotalCopies(int copies) { totalCopies = copies; }
    void setDescription(const std::string& description) { this->description = description; }

    // Book management methods
    bool borrowBook();
    bool returnBook();
    bool reserveBook();
    bool isAvailable() const;
    void updateAvailability();
    void displayInfo() const;
    std::string toFileString() const;
    void fromFileString(const std::string& data);

    // Static methods
    static std::string categoryToString(BookCategory category);
    static BookCategory stringToCategory(const std::string& categoryStr);
    static std::string statusToString(BookStatus status);
    static BookStatus stringToStatus(const std::string& statusStr);
    static std::string generateBookId();
};

#endif // BOOK_H
