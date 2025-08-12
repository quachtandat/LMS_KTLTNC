#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

class Category {
private:
    std::string id;
    std::string name;

public:
    // Constructors
    Category();
    Category(const std::string& id, const std::string& name);

    // Getters
    std::string getID() const;
    std::string getName() const;

    // Setters
    void setID(const std::string& id);
    void setName(const std::string& name);

    // Display
    void display() const;
};

#endif
