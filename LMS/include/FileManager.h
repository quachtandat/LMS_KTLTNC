#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

class User;
class Book;
class Library;
class BorrowRecord;

class FileManager {
public:
    FileManager() = default;
    ~FileManager() = default;

    // File operations
    static bool fileExists(const std::string& filename);
    static bool createFile(const std::string& filename);
    static bool deleteFile(const std::string& filename);
    static std::string getCurrentDirectory();
    static std::string getDataDirectory();
    static bool ensureDataDirectory();

    // User data management
    static bool saveUsersToFile(const std::string& filename, 
                               const std::vector<std::unique_ptr<User>>& users);
    static bool loadUsersFromFile(const std::string& filename,
                                 std::vector<std::unique_ptr<User>>& users);
    static bool saveLibrariansToFile(const std::string& filename,
                                    const std::vector<std::unique_ptr<User>>& librarians);
    static bool loadLibrariansFromFile(const std::string& filename,
                                      std::vector<std::unique_ptr<User>>& librarians);
    static bool saveReadersToFile(const std::string& filename,
                                 const std::vector<std::unique_ptr<User>>& readers);
    static bool loadReadersFromFile(const std::string& filename,
                                   std::vector<std::unique_ptr<User>>& readers);

    // Book data management
    static bool saveBooksToFile(const std::string& filename,
                               const std::vector<std::unique_ptr<Book>>& books);
    static bool loadBooksFromFile(const std::string& filename,
                                 std::vector<std::unique_ptr<Book>>& books);

    // Borrow record management
    static bool saveBorrowRecordsToFile(const std::string& filename,
                                       const std::vector<std::unique_ptr<BorrowRecord>>& records);
    static bool loadBorrowRecordsFromFile(const std::string& filename,
                                         std::vector<std::unique_ptr<BorrowRecord>>& records);



    // Library configuration
    static bool saveLibraryConfig(const std::string& filename, const Library& library);
    static bool loadLibraryConfig(const std::string& filename, Library& library);

    // Backup and restore
    static bool createBackup(const std::string& sourceDir, const std::string& backupDir);
    static bool restoreFromBackup(const std::string& backupDir, const std::string& targetDir);
    static std::vector<std::string> listBackupFiles(const std::string& backupDir);

    // Utility functions
    static std::vector<std::string> splitString(const std::string& str, char delimiter);
    static std::string trimString(const std::string& str);
    static std::string escapeString(const std::string& str);
    static std::string unescapeString(const std::string& str);
    static bool isValidFilename(const std::string& filename);
    static std::string sanitizeFilename(const std::string& filename);

    // Error handling
    static std::string getLastError();
    static void clearLastError();
    static bool hasError();

private:
    static std::string lastError;
    static const std::string DATA_DIR;
    static const std::string BACKUP_DIR;
    
    static void setLastError(const std::string& error);
    static std::string getTimestamp();
    static bool ensureDirectoryExists(const std::string& dirPath);
};

#endif // FILEMANAGER_H
