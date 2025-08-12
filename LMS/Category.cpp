#include <iostream>
#include "Category.h"

Category::Category() {}

Category::Category(const std::string& id, const std::string& name)
    : id(id), name(name) {}

// Getters
std::string Category::getID() const { return id; }
std::string Category::getName() const { return name; }

// Setters
void Category::setID(const std::string& id) { this->id = id; }
void Category::setName(const std::string& name) { this->name = name; }

// Display
void Category::display() const {
    std::cout << "Category ID: " << id << "\n"
              << "Category Name: " << name << "\n";
}
