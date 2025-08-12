#include <iostream>
#include "Loan.h"

Loan::Loan() {}

Loan::Loan(const std::string& loanId, const std::string& memberId,
           const std::string& loanDate, const std::string& dueDate)
    : loanId(loanId), memberId(memberId), loanDate(loanDate), dueDate(dueDate) {}

// Getters
std::string Loan::getLoanId() const { return loanId; }
std::string Loan::getMemberId() const { return memberId; }
std::string Loan::getLoanDate() const { return loanDate; }
std::string Loan::getDueDate() const { return dueDate; }
std::string Loan::getReturnDate() const { return returnDate; }
std::vector<LoanDetail> Loan::getDetails() const { return details; }

// Setters
void Loan::setLoanId(const std::string& loanId) { this->loanId = loanId; }
void Loan::setMemberId(const std::string& memberId) { this->memberId = memberId; }
void Loan::setLoanDate(const std::string& loanDate) { this->loanDate = loanDate; }
void Loan::setDueDate(const std::string& dueDate) { this->dueDate = dueDate; }
void Loan::setReturnDate(const std::string& returnDate) { this->returnDate = returnDate; }

// Methods
void Loan::addDetail(const LoanDetail& detail) {
    details.push_back(detail);
}

void Loan::display() const {
    std::cout << "Loan ID: " << loanId << "\n"
              << "Member ID: " << memberId << "\n"
              << "Loan Date: " << loanDate << "\n"
              << "Due Date: " << dueDate << "\n"
              << "Return Date: " << (returnDate.empty() ? "Not returned" : returnDate) << "\n";

    std::cout << "\n--- Loan Details ---\n";
    for (const auto& d : details) {
        d.display();
        std::cout << "--------------------\n";
    }
}
