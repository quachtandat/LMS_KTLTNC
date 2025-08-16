#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include <string>
#include <ctime>

class BorrowRecord {
private:
    std::string recordId;
    std::string username;
    std::string bookTitle;  // Sử dụng tên sách thay vì ID
    std::string bookId;     // Giữ lại để tham chiếu
    time_t borrowDate;
    time_t returnDate;
    time_t dueDate;
    bool isReturned;

public:
    BorrowRecord(const std::string& username, const std::string& bookTitle, 
                 const std::string& bookId, int borrowDays = 14);
    
    // Getters
    std::string getRecordId() const { return recordId; }
    std::string getUsername() const { return username; }
    std::string getBookTitle() const { return bookTitle; }
    std::string getBookId() const { return bookId; }
    time_t getBorrowDate() const { return borrowDate; }
    time_t getReturnDate() const { return returnDate; }
    time_t getDueDate() const { return dueDate; }
    bool getIsReturned() const { return isReturned; }
    
    // Setters
    void setReturnDate(time_t returnDate) { this->returnDate = returnDate; }
    void setIsReturned(bool returned) { isReturned = returned; }
    
    // Utility functions
    std::string getBorrowDateString() const;
    std::string getReturnDateString() const;
    std::string getDueDateString() const;
    int getDaysOverdue() const;
    bool isOverdue() const;
    
    // File operations
    std::string toFileString() const;
    bool fromFileString(const std::string& line);
    
    // Static functions
    static std::string generateRecordId();
    static std::string formatDate(time_t time);
    static time_t parseDate(const std::string& dateStr);
};

#endif // BORROW_RECORD_H
