#include <iostream>
#include "Account.h"
#include "Librarian.h"
#include "Book.h"

int main() {
    std::string accFile = "./data/accounts.txt";
    std::string bookFile = "./data/books.txt";
    
    std::vector<Account> accounts = Account::loadFromFile(accFile);
    std::vector<Book> books = Librarian::loadBooksFromFile(bookFile); // ✅ Load 1 lần duy nhất
    
    Account* currentUser = nullptr;

    while (true) {
        if (!currentUser) {
            std::cout << "\n1. Login\n2. Register\n3. Exit\nSelect: ";
            int choice; std::cin >> choice;

            if (choice == 1) {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                currentUser = Account::login(accounts, user, pass);
                if (!currentUser) {
                    std::cout << "Invalid username or password!\n";
                }
            }
            else if (choice == 2) {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                size_t oldSize = accounts.size();
                Account::registerAccountAuto(accounts, user, pass);
                if (accounts.size() > oldSize)
                    Account::saveToFile(accFile, accounts);
            }
            else break;
        }
        else {
            if (currentUser->getRole() == Role::LIBRARIAN) {
                Librarian lib(currentUser->getLinkedId(), "Unknown Name", "", "");

                int ch;
                std::cout << "\n--- LIBRARIAN MENU ---\n"
                          << "1. View personal info\n"
                          << "2. Edit personal info\n"
                          << "3. View other librarians\n"
                          << "4. View members\n"
                          << "5. Delete member\n"
                          << "6. Add book\n"
                          << "7. Edit book\n"
                          << "8. Delete book\n"
                          << "9. View books\n"
                          << "10. Search books\n"
                          << "11. Save books to file (overwrite)\n"
                          << "0. Logout\nSelect: ";
                std::cin >> ch;

                if (ch == 1) lib.viewPersonalInfoFromFile();
                else if (ch == 2) { lib.editPersonalInfo(); lib.savePersonalInfoToFile(); }
                else if (ch == 3) Librarian::viewOtherLibrarians(accounts, currentUser->getLinkedId());
                else if (ch == 4) Librarian::viewMembers(accounts);
                else if (ch == 5) {
                    std::string uname;
                    std::cout << "Enter member username to delete: ";
                    std::cin >> uname;
                    Librarian::deleteMember(accounts, uname);
                    Account::saveToFile(accFile, accounts);
                }
                else if (ch == 6) Librarian::addBook(books);
                else if (ch == 7) {
                    std::string isbn;
                    std::cout << "Enter ISBN of the book to edit: ";
                    std::cin >> isbn;
                    Librarian::editBook(books, isbn);
                }
                else if (ch == 8) {
                    std::string isbn;
                    std::cout << "Enter ISBN of the book to delete: ";
                    std::cin >> isbn;
                    Librarian::deleteBook(books, isbn);
                }
                else if (ch == 9) Librarian::viewBooks(books);
                else if (ch == 10) Librarian::searchBooks(books);
                else if (ch == 11) {
                    Librarian::saveBooksToFile(bookFile, books, false); // ✅ overwrite để tránh trùng
                    std::cout << "Books saved successfully!\n";
                }
                else if (ch == 0) currentUser = nullptr;
            }
            else {
                std::cout << "Member features are not implemented yet.\n";
                currentUser = nullptr;
            }
        }
    }
}
