#ifndef LOAN_H
#define LOAN_H

#include <string>
#include <vector>
#include "LoanDetail.h"

class Loan {
private:
    std::string loanId;        // Ma phieu muon
    std::string memberId;      // Ma doc gia
    std::string loanDate;      // Ngay muon
    std::string dueDate;       // Ngay phai tra
    std::string returnDate;    // Ngay tra thuc te (neu co)
    std::vector<LoanDetail> details; // Danh sach chi tiet muon

public:
    Loan();
    Loan(const std::string& loanId, const std::string& memberId,
         const std::string& loanDate, const std::string& dueDate);

    // Getters
    std::string getLoanId() const;
    std::string getMemberId() const;
    std::string getLoanDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;
    std::vector<LoanDetail> getDetails() const;

    // Setters
    void setLoanId(const std::string& loanId);
    void setMemberId(const std::string& memberId);
    void setLoanDate(const std::string& loanDate);
    void setDueDate(const std::string& dueDate);
    void setReturnDate(const std::string& returnDate);

    // Methods
    void addDetail(const LoanDetail& detail);
    void display() const;
};

#endif