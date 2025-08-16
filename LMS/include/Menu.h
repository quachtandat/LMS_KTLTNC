#ifndef MENU_H
#define MENU_H

#include "Library.h"
#include "User.h"
#include <memory>

class Menu {
private:
    Library& library;
    User* currentUser;
    bool isRunning;

public:
    Menu(Library& lib);
    ~Menu() = default;

    // Main menu system
    void run();
    void showMainMenu();
    void showLoginMenu();
    void showLibrarianMenu();
    void showReaderMenu();
    void showGuestMenu();

    // Authentication
    bool authenticateUser();
    void logout();
    bool isUserLoggedIn() const { return currentUser != nullptr; }
    User* getCurrentUser() const { return currentUser; }

    // Menu options
    void handleLibrarianChoice(int choice);
    void handleReaderChoice(int choice);
    void handleGuestChoice(int choice);

    // Librarian functions
    void addNewBook();
    void removeBook();
    void updateBook();
    void listAllBooks();
    void searchBooksLibrarian();
    void manageReaders();
    void generateReports();
    void viewStatistics();
    void viewBorrowHistoryForLibrarian();
    void configureAutoSave();

    // Reader functions
    void borrowBook();
    void returnBook();
    void viewBorrowHistory();
    void searchBooksReader();
    void viewAvailableBooksReader();
    void updateProfile();

    // Guest functions
    void viewLibraryInfo();
    void searchBooksGuest();
    void viewAvailableBooksGuest();
    void registerAccount();

    // Utility functions
    void clearScreen();
    void pauseScreen();
    void displayHeader(const std::string& title);
    void displayFooter();
    int getValidChoice(int min, int max);
    std::string getValidInput(const std::string& prompt);
    bool confirmAction(const std::string& message);
    
    // Helper methods for reader management
    void displayAllReaders();
    void addNewReader();
    void removeReader();
    void updateReader();
    void registerReaderAccount();

    // Error handling
    void displayError(const std::string& error);
    void displaySuccess(const std::string& message);
    void displayInfo(const std::string& info);

private:
    void initializeLibrary();
    void saveAndExit();
    std::string getPasswordInput();
    void displayWelcomeMessage();
    void displayGoodbyeMessage();
};

#endif // MENU_H
