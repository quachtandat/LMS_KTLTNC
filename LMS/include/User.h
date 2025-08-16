#ifndef USER_H
#define USER_H

#include <string>
#include <memory>

enum class UserType {
    LIBRARIAN,
    READER
};

class User {
protected:
    std::string username;
    std::string password;
    std::string fullName;
    std::string email;
    UserType userType;

public:
    User() = default;
    User(const std::string& username, const std::string& password, 
         const std::string& fullName, const std::string& email, UserType type);
    virtual ~User() = default;

    // Getters
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getFullName() const { return fullName; }
    std::string getEmail() const { return email; }
    UserType getUserType() const { return userType; }

    // Setters
    void setUsername(const std::string& username) { this->username = username; }
    void setPassword(const std::string& password) { this->password = password; }
    void setFullName(const std::string& fullName) { this->fullName = fullName; }
    void setEmail(const std::string& email) { this->email = email; }

    // Virtual methods
    virtual bool authenticate(const std::string& inputPassword) const;
    virtual void displayInfo() const;
    virtual std::string toFileString() const;
    virtual void fromFileString(const std::string& data);

    // Static methods
    static std::unique_ptr<User> createUser(UserType type);
};

#endif // USER_H
