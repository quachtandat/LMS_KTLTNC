#include <iostream>
#include "Account.h"

int main() {
    std::string filename = "./data/accounts.txt";
    std::vector<Account> accounts = Account::loadFromFile(filename);
    Account* currentUser = nullptr;

    while (true) {
        if (!currentUser) {
            std::cout << "\n1. Dang nhap\n2. Dang ky\n3. Thoat\nChon: ";
            int choice; std::cin >> choice;

            if (choice == 1) {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                currentUser = Account::login(accounts, user, pass);
                if (currentUser) {
                    std::cout << "Dang nhap thanh cong tai khoan: "
                              << (currentUser->getRole() == Role::LIBRARIAN ? "Librarian" : "Member");
                              
                } else {
                    std::cout << "Sai thong tin dang nhap!\n";
                }
            }
            else if (choice == 2) {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;

                size_t oldSize = accounts.size(); // lưu lại số lượng cũ
                Account::registerAccountAuto(accounts, user, pass);
                
                // Chỉ lưu file nếu thực sự có thêm tài khoản
                if (accounts.size() > oldSize) {
                    Account::saveToFile(filename, accounts);
                }
            }
            else break;
        }
        
    }
    return 0;
}
