#include "Book.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

Book::Book(const std::string& bookId, const std::string& title, const std::string& author,
           const std::string& isbn, const std::string& publisher, int publicationYear,
           BookCategory category, const std::string& location, int totalCopies)
    : bookId(bookId), title(title), author(author), isbn(isbn), publisher(publisher),
      publicationYear(publicationYear), category(category), status(BookStatus::AVAILABLE),
      location(location), totalCopies(totalCopies), availableCopies(totalCopies),
      lastModified(std::chrono::system_clock::now()) {
}

bool Book::borrowBook() {
    if (status == BookStatus::AVAILABLE && availableCopies > 0) {
        availableCopies--;
        if (availableCopies == 0) {
            status = BookStatus::BORROWED;
        }
        lastModified = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

bool Book::returnBook() {
    if (availableCopies < totalCopies) {
        availableCopies++;
        if (status == BookStatus::BORROWED && availableCopies == totalCopies) {
            status = BookStatus::AVAILABLE;
        }
        lastModified = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

bool Book::reserveBook() {
    if (status == BookStatus::AVAILABLE) {
        status = BookStatus::RESERVED;
        lastModified = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

bool Book::isAvailable() const {
    return status == BookStatus::AVAILABLE && availableCopies > 0;
}

void Book::updateAvailability() {
    if (availableCopies == 0) {
        status = BookStatus::BORROWED;
    } else if (availableCopies == totalCopies) {
        status = BookStatus::AVAILABLE;
    }
}

void Book::displayInfo() const {
    std::cout << "\n=== THONG TIN SACH ===" << std::endl;
    std::cout << "ID: " << bookId << std::endl;
    std::cout << "Tieu de: " << title << std::endl;
    std::cout << "Tac gia: " << author << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Nha xuat ban: " << publisher << std::endl;
    std::cout << "Nam xuat ban: " << publicationYear << std::endl;
    std::cout << "The loai: " << categoryToString(category) << std::endl;
    std::cout << "Trang thai: " << statusToString(status) << std::endl;
    std::cout << "Vi tri: " << location << std::endl;
    std::cout << "Ban sao: " << availableCopies << "/" << totalCopies << std::endl;
    if (!description.empty()) {
        std::cout << "Mo ta: " << description << std::endl;
    }
    std::cout << "Cap nhat lan cuoi: " << Utils::formatDateTime(lastModified) << std::endl;
}

std::string Book::toFileString() const {
    std::ostringstream oss;
    auto timeT = std::chrono::system_clock::to_time_t(lastModified);
    
    oss << bookId << "|" << title << "|" << author << "|" << isbn << "|" 
        << publisher << "|" << publicationYear << "|" << static_cast<int>(category) << "|"
        << static_cast<int>(status) << "|" << location << "|" << totalCopies << "|"
        << availableCopies << "|" << description << "|" << timeT;
    
    return oss.str();
}

void Book::fromFileString(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    
    if (std::getline(iss, bookId, '|') &&
        std::getline(iss, title, '|') &&
        std::getline(iss, author, '|') &&
        std::getline(iss, isbn, '|') &&
        std::getline(iss, publisher, '|') &&
        std::getline(iss, token, '|')) {
        try {
            publicationYear = std::stoi(token);
        } catch (const std::exception& e) {
            std::cerr << "Loi khi doc nam xuat ban: " << token << std::endl;
            publicationYear = 2024; // Default year
        }
        
        if (std::getline(iss, token, '|')) {
            try {
                category = static_cast<BookCategory>(std::stoi(token));
            } catch (const std::exception& e) {
                std::cerr << "Loi khi doc the loai sach: " << token << std::endl;
                category = BookCategory::FICTION; // Default category
            }
        }
        
        if (std::getline(iss, token, '|')) {
            try {
                status = static_cast<BookStatus>(std::stoi(token));
            } catch (const std::exception& e) {
                std::cerr << "Loi khi doc trang thai sach: " << token << std::endl;
                status = BookStatus::AVAILABLE; // Default status
            }
        }
        
        if (std::getline(iss, location, '|') &&
            std::getline(iss, token, '|')) {
            try {
                totalCopies = std::stoi(token);
            } catch (const std::exception& e) {
                std::cerr << "Loi khi doc tong so ban sao: " << token << std::endl;
                totalCopies = 1; // Default copies
            }
        }
        
        if (std::getline(iss, token, '|')) {
            try {
                availableCopies = std::stoi(token);
            } catch (const std::exception& e) {
                std::cerr << "Loi khi doc so ban sao co san: " << token << std::endl;
                availableCopies = totalCopies; // Default to total copies
            }
        }
        
        if (std::getline(iss, description, '|') &&
            std::getline(iss, token, '|')) {
            time_t timeT = std::stoll(token);
            lastModified = std::chrono::system_clock::from_time_t(timeT);
        }
    }
}

std::string Book::categoryToString(BookCategory category) {
    switch (category) {
        case BookCategory::FICTION: return "Tieu thuyet";
        case BookCategory::NON_FICTION: return "Phi huyen thoai";
        case BookCategory::SCIENCE: return "Khoa hoc";
        case BookCategory::TECHNOLOGY: return "Cong nghe";
        case BookCategory::HISTORY: return "Lich su";
        case BookCategory::PHILOSOPHY: return "Triet hoc";
        case BookCategory::LITERATURE: return "Van hoc";
        case BookCategory::OTHER: return "Khac";
        default: return "Khong xac dinh";
    }
}

BookCategory Book::stringToCategory(const std::string& categoryStr) {
    std::string lower = Utils::toLower(categoryStr);
    if (lower == "tieu thuyet" || lower == "fiction") return BookCategory::FICTION;
    if (lower == "phi huyen thoai" || lower == "non-fiction") return BookCategory::NON_FICTION;
    if (lower == "khoa hoc" || lower == "science") return BookCategory::SCIENCE;
    if (lower == "cong nghe" || lower == "technology") return BookCategory::TECHNOLOGY;
    if (lower == "lich su" || lower == "history") return BookCategory::HISTORY;
    if (lower == "triet hoc" || lower == "philosophy") return BookCategory::PHILOSOPHY;
    if (lower == "van hoc" || lower == "literature") return BookCategory::LITERATURE;
    return BookCategory::OTHER;
}

std::string Book::statusToString(BookStatus status) {
    switch (status) {
        case BookStatus::AVAILABLE: return "Co san";
        case BookStatus::BORROWED: return "Da muon";
        case BookStatus::RESERVED: return "Da dat truoc";
        case BookStatus::MAINTENANCE: return "Bao tri";
        default: return "Khong xac dinh";
    }
}

BookStatus Book::stringToStatus(const std::string& statusStr) {
    std::string lower = Utils::toLower(statusStr);
    if (lower == "co san" || lower == "available") return BookStatus::AVAILABLE;
    if (lower == "da muon" || lower == "borrowed") return BookStatus::BORROWED;
    if (lower == "da dat truoc" || lower == "reserved") return BookStatus::RESERVED;
    if (lower == "bao tri" || lower == "maintenance") return BookStatus::MAINTENANCE;
    return BookStatus::AVAILABLE;
}

std::string Book::generateBookId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 9999);
    
    std::ostringstream oss;
    oss << "BK" << dis(gen);
    return oss.str();
}
