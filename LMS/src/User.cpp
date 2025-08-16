#include "User.h"
#include "Librarian.h"
#include "Reader.h"
#include <iostream>
#include <sstream>

User::User(const std::string& username, const std::string& password, 
           const std::string& fullName, const std::string& email, UserType type)
    : username(username), password(password), fullName(fullName), email(email), userType(type) {
}

bool User::authenticate(const std::string& inputPassword) const {
    return password == inputPassword;
}

void User::displayInfo() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Full Name: " << fullName << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "User Type: " << (userType == UserType::LIBRARIAN ? "Librarian" : "Reader") << std::endl;
}

std::string User::toFileString() const {
    std::ostringstream oss;
    oss << username << "|" << password << "|" << fullName << "|" << email << "|" 
        << static_cast<int>(userType);
    return oss.str();
}

void User::fromFileString(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    
    if (std::getline(iss, username, '|') &&
        std::getline(iss, password, '|') &&
        std::getline(iss, fullName, '|') &&
        std::getline(iss, email, '|') &&
        std::getline(iss, token, '|')) {
        try {
            userType = static_cast<UserType>(std::stoi(token));
        } catch (const std::exception& e) {
            std::cerr << "Loi khi doc loai nguoi dung: " << token << std::endl;
            userType = UserType::READER; // Default to READER
        }
    }
}

std::unique_ptr<User> User::createUser(UserType type) {
    switch (type) {
        case UserType::LIBRARIAN:
            return std::make_unique<Librarian>();
        case UserType::READER:
            return std::make_unique<Reader>();
        default:
            return nullptr;
    }
}
