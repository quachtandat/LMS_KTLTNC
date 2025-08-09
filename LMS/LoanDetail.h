#ifndef LOANDETAIL_H
#define LOANDETAIL_H

#include <string>
using namespace std;

class LoanDetail {
private:
    int loanDetailID;
    int loanID;
    int bookID;
    string dueDate;

public:
    LoanDetail(int loanDetailID, int loanID, int bookID, string dueDate);

    int getLoanDetailID() const;
    int getLoanID() const;
    int getBookID() const;
    string getDueDate() const;

    void viewDetail() const;
};

#endif
