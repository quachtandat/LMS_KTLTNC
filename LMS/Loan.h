#ifndef LOAN_H
#define LOAN_H

#include <string>
#include <vector>
#include "LoanDetail.h"
using namespace std;

class Loan {
private:
    int loanID;
    int memberID;
    string loanDate;
    vector<LoanDetail> loanDetails;

public:
    Loan(int loanID, int memberID, string loanDate);

    int getLoanID() const;
    int getMemberID() const;

    void addLoanDetail(const LoanDetail& detail);
    void deleteLoanDetail(int loanDetailID);
    void viewLoanDetails() const;
};

#endif
