#include "BorrowRecord.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <vector>

BorrowRecord::BorrowRecord(const std::string& username, const std::string& bookTitle, 
                           const std::string& bookId, int borrowDays)
    : username(username), bookTitle(bookTitle), bookId(bookId), isReturned(false) {
    
    // Tạo ID cho record
    recordId = generateRecordId();
    
    // Thời gian mượn sách
    borrowDate = std::time(nullptr);
    
    // Thời gian hạn trả (mặc định 14 ngày)
    dueDate = borrowDate + (borrowDays * 24 * 60 * 60);
    
    // Thời gian trả sách (chưa trả)
    returnDate = 0;
}

std::string BorrowRecord::getBorrowDateString() const {
    return formatDate(borrowDate);
}

std::string BorrowRecord::getReturnDateString() const {
    if (returnDate == 0) return "Chưa trả";
    return formatDate(returnDate);
}

std::string BorrowRecord::getDueDateString() const {
    return formatDate(dueDate);
}

int BorrowRecord::getDaysOverdue() const {
    if (isReturned) return 0;
    
    time_t now = std::time(nullptr);
    if (now > dueDate) {
        return (now - dueDate) / (24 * 60 * 60);
    }
    return 0;
}

bool BorrowRecord::isOverdue() const {
    return !isReturned && (std::time(nullptr) > dueDate);
}

std::string BorrowRecord::toFileString() const {
    std::stringstream ss;
    ss << recordId << "|"
       << username << "|"
       << bookTitle << "|"
       << bookId << "|"
       << borrowDate << "|"
       << returnDate << "|"
       << dueDate << "|"
       << (isReturned ? "1" : "0");
    return ss.str();
}

bool BorrowRecord::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() != 8) return false;
    
    recordId = tokens[0];
    username = tokens[1];
    bookTitle = tokens[2];
    bookId = tokens[3];
    borrowDate = std::stoll(tokens[4]);
    returnDate = std::stoll(tokens[5]);
    dueDate = std::stoll(tokens[6]);
    isReturned = (tokens[7] == "1");
    
    return true;
}

std::string BorrowRecord::generateRecordId() {
    static int counter = 1;
    std::stringstream ss;
    ss << "BR" << std::setfill('0') << std::setw(6) << counter++;
    return ss.str();
}

std::string BorrowRecord::formatDate(time_t time) {
    if (time == 0) return "N/A";
    
    std::tm* tm = std::localtime(&time);
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << tm->tm_mday << "/"
       << std::setfill('0') << std::setw(2) << (tm->tm_mon + 1) << "/"
       << (tm->tm_year + 1900);
    return ss.str();
}

time_t BorrowRecord::parseDate(const std::string& dateStr) {
    if (dateStr == "N/A" || dateStr.empty()) return 0;
    
    std::tm tm = {};
    std::stringstream ss(dateStr);
    char delimiter;
    
    ss >> tm.tm_mday >> delimiter >> tm.tm_mon >> delimiter >> tm.tm_year;
    tm.tm_mon--; // tm_mon bắt đầu từ 0
    tm.tm_year -= 1900; // tm_year tính từ 1900
    
    return std::mktime(&tm);
}
