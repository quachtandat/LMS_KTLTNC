#include "LoanDetail.h"
#include <iostream>
using namespace std;

LoanDetail::LoanDetail(int loanDetailID, int loanID, int bookID, string dueDate)
    : loanDetailID(loanDetailID), loanID(loanID), bookID(bookID), dueDate(dueDate) {}

int LoanDetail::getLoanDetailID() const { return loanDetailID; }
int LoanDetail::getLoanID() const { return loanID; }
int LoanDetail::getBookID() const { return bookID; }
string LoanDetail::getDueDate() const { return dueDate; }

void LoanDetail::viewDetail() const {
    cout << "LoanDetail ID: " << loanDetailID
         << ", Loan ID: " << loanID
         << ", Book ID: " << bookID
         << ", Due Date: " << dueDate << endl;
}
