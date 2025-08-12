#ifndef LOANDETAIL_H
#define LOANDETAIL_H

#include <string>
#include "Book.h"

class LoanDetail {
private:
    std::string loanId;    // Ma phieu muon
    Book book;             // Sach muon
    int quantity;          // So luong muon
    bool returned;         // Ða tra hay chua

public:
    LoanDetail();
    LoanDetail(const std::string& loanId, const Book& book, int quantity, bool returned = false);

    // Getters
    std::string getLoanId() const;
    Book getBook() const;
    int getQuantity() const;
    bool isReturned() const;

    // Setters
    void setLoanId(const std::string& loanId);
    void setBook(const Book& book);
    void setQuantity(int quantity);
    void setReturned(bool returned);

    // Methods
    void display() const;
};

#endif
