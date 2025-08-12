#include <iostream>
#include "LoanDetail.h"

LoanDetail::LoanDetail() : quantity(1), returned(false) {}

LoanDetail::LoanDetail(const std::string& loanId, const Book& book, int quantity, bool returned)
    : loanId(loanId), book(book), quantity(quantity), returned(returned) {}

// Getters
std::string LoanDetail::getLoanId() const { return loanId; }
Book LoanDetail::getBook() const { return book; }
int LoanDetail::getQuantity() const { return quantity; }
bool LoanDetail::isReturned() const { return returned; }

// Setters
void LoanDetail::setLoanId(const std::string& loanId) { this->loanId = loanId; }
void LoanDetail::setBook(const Book& book) { this->book = book; }
void LoanDetail::setQuantity(int quantity) { this->quantity = quantity; }
void LoanDetail::setReturned(bool returned) { this->returned = returned; }

// Methods
void LoanDetail::display() const {
    std::cout << "Loan ID: " << loanId << "\n";
    book.display();
    std::cout << "Quantity: " << quantity << "\n"
              << "Returned: " << (returned ? "Yes" : "No") << "\n";
}
