#include "Loan.h"
#include <iostream>
using namespace std;

Loan::Loan(int loanID, int memberID, string loanDate)
    : loanID(loanID), memberID(memberID), loanDate(loanDate) {}

int Loan::getLoanID() const { return loanID; }
int Loan::getMemberID() const { return memberID; }

void Loan::addLoanDetail(const LoanDetail& detail) {
    loanDetails.push_back(detail);
}

void Loan::deleteLoanDetail(int loanDetailID) {
    for (auto it = loanDetails.begin(); it != loanDetails.end(); ++it) {
        if (it->getLoanDetailID() == loanDetailID) {
            loanDetails.erase(it);
            cout << "Loan detail deleted.\n";
            return;
        }
    }
    cout << "Loan detail not found.\n";
}

void Loan::viewLoanDetails() const {
    cout << "Loan ID: " << loanID << ", Member ID: " << memberID
         << ", Loan Date: " << loanDate << endl;
    for (const auto& detail : loanDetails) {
        detail.viewDetail();
    }
}