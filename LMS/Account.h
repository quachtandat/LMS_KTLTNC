#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

enum class Role {
    MEMBER = 0,
    LIBRARIAN = 1
};

class Account {
private:
    std::string username;
    std::string password;
    Role role;
    std::string linkedId;

public:
    Account();
    Account(const std::string& username, const std::string& password,
            Role role, const std::string& linkedId);

    std::string getUsername() const;
    Role getRole() const;
    std::string getLinkedId() const;
    bool checkPassword(const std::string& pass) const;

    static std::vector<Account> loadFromFile(const std::string& filename);
    static void saveToFile(const std::string& filename, const std::vector<Account>& accounts);

    // Đăng ký tự động gán role & ID
    static void registerAccountAuto(std::vector<Account>& accounts, const std::string& username, const std::string& password);

    static Account* login(std::vector<Account>& accounts,
                          const std::string& username,
                          const std::string& password);
};

#endif
