#include "Account.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

Account::Account() : username(""), password(""), role(Role::MEMBER), linkedId("") {}

Account::Account(const std::string& username, const std::string& password,
                 Role role, const std::string& linkedId)
    : username(username), password(password), role(role), linkedId(linkedId) {}

std::string Account::getUsername() const { return username; }
Role Account::getRole() const { return role; }
std::string Account::getLinkedId() const { return linkedId; }

bool Account::checkPassword(const std::string& pass) const {
    return password == pass;
}

std::vector<Account> Account::loadFromFile(const std::string& filename) {
    std::vector<Account> accounts;
    std::ifstream in(filename);
    if (!in.is_open()) return accounts;

    std::string user, pass, id;
    int roleInt;
    while (in >> user >> pass >> roleInt >> id) {
        accounts.emplace_back(user, pass, static_cast<Role>(roleInt), id);
    }
    return accounts;
}

void Account::saveToFile(const std::string& filename, const std::vector<Account>& accounts) {
    std::ofstream out(filename);
    for (const auto& acc : accounts) {
        out << acc.username << " " << acc.password << " " << static_cast<int>(acc.role)
            << " " << acc.linkedId << "\n";
    }
}

// Sinh ID dạng L001 hoặc M001
static std::string generateId(Role role, const std::vector<Account>& accounts) {
    int count = 0;
    for (const auto& acc : accounts) {
        if (acc.getRole() == role) count++;
    }
    std::ostringstream oss;
    oss << (role == Role::LIBRARIAN ? "L" : "M")
        << std::setw(3) << std::setfill('0') << (count + 1);
    return oss.str();
}

void Account::registerAccountAuto(std::vector<Account>& accounts, const std::string& username, const std::string& password) {
    // Kiểm tra username đã tồn tại chưa
    for (const auto& acc : accounts) {
        if (acc.getUsername() == username) {
            std::cout << "⚠ Username da ton tai! Vui long chon username khac.\n";
            return;
        }
    }

    // Xác định role: tài khoản đầu tiên là Librarian
    Role role = accounts.empty() ? Role::LIBRARIAN : Role::MEMBER;

    // Sinh ID tự động
    std::string id = generateId(role, accounts);

    // Thêm vào danh sách
    accounts.emplace_back(username, password, role, id);

    std::cout << " Dang ky thanh cong tai khoan: " 
              << (role == Role::LIBRARIAN ? "Librarian" : "Member");
}
Account* Account::login(std::vector<Account>& accounts,
                        const std::string& username,
                        const std::string& password) {
    for (auto& acc : accounts) {
        if (acc.getUsername() == username && acc.checkPassword(password)) {
            return &acc;
        }
    }
    return nullptr;
}
