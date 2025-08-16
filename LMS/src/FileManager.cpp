#include "FileManager.h"
#include "User.h"
#include "Librarian.h"
#include "Reader.h"
#include "Book.h"
#include "Library.h"
#include "BorrowRecord.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

// Static member initialization
std::string FileManager::lastError;
const std::string FileManager::DATA_DIR = "D:/thuvien/data";
const std::string FileManager::BACKUP_DIR = "backup";

bool FileManager::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool FileManager::createFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file.close();
        return true;
    }
    setLastError("Khong the tao file: " + filename);
    return false;
}

bool FileManager::deleteFile(const std::string& filename) {
    if (std::filesystem::exists(filename)) {
        return std::filesystem::remove(filename);
    }
    return false;
}

std::string FileManager::getCurrentDirectory() {
    return std::filesystem::current_path().string();
}

std::string FileManager::getDataDirectory() {
    std::string currentDir = getCurrentDirectory();
    // If we're in build directory, go up one level
    if (currentDir.find("build") != std::string::npos) {
        return currentDir + "/../data";
    }
    return currentDir + "/data";
}

bool FileManager::saveUsersToFile(const std::string& filename, 
                                 const std::vector<std::unique_ptr<User>>& users) {
    // Ensure data directory exists
    if (!ensureDataDirectory()) {
        return false;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    for (const auto& user : users) {
        file << user->toFileString() << std::endl;
    }
    
    file.close();
    return true;
}

bool FileManager::loadUsersFromFile(const std::string& filename,
                                   std::vector<std::unique_ptr<User>>& users) {
    if (!fileExists(filename)) {
        return false; // File doesn't exist, not an error
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            auto user = User::createUser(UserType::READER); // Default type
            if (user) {
                user->fromFileString(line);
                users.push_back(std::move(user));
            }
        }
    }
    
    file.close();
    return true;
}

bool FileManager::saveLibrariansToFile(const std::string& filename,
                                       const std::vector<std::unique_ptr<User>>& librarians) {
    // Ensure data directory exists
    if (!ensureDataDirectory()) {
        return false;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    for (const auto& librarian : librarians) {
        if (librarian->getUserType() == UserType::LIBRARIAN) {
            file << librarian->toFileString() << std::endl;
        }
    }
    
    file.close();
    return true;
}

bool FileManager::loadLibrariansFromFile(const std::string& filename,
                                         std::vector<std::unique_ptr<User>>& librarians) {
    if (!fileExists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            auto librarian = std::make_unique<Librarian>();
            if (librarian) {
                librarian->fromFileString(line);
                librarians.push_back(std::move(librarian));
            }
        }
    }
    
    file.close();
    return true;
}

bool FileManager::saveReadersToFile(const std::string& filename,
                                    const std::vector<std::unique_ptr<User>>& readers) {
    // Ensure data directory exists
    if (!ensureDataDirectory()) {
        return false;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    for (const auto& reader : readers) {
        if (reader->getUserType() == UserType::READER) {
            file << reader->toFileString() << std::endl;
        }
    }
    
    file.close();
    return true;
}

bool FileManager::loadReadersFromFile(const std::string& filename,
                                      std::vector<std::unique_ptr<User>>& readers) {
    if (!fileExists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            auto reader = std::make_unique<Reader>();
            if (reader) {
                reader->fromFileString(line);
                readers.push_back(std::move(reader));
            }
        }
    }
    
    file.close();
    return true;
}

bool FileManager::saveBooksToFile(const std::string& filename,
                                 const std::vector<std::unique_ptr<Book>>& books) {
    // Ensure data directory exists
    if (!ensureDataDirectory()) {
        return false;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    for (const auto& book : books) {
        file << book->toFileString() << std::endl;
    }
    
    file.close();
    return true;
}

bool FileManager::loadBooksFromFile(const std::string& filename,
                                    std::vector<std::unique_ptr<Book>>& books) {
    if (!fileExists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            auto book = std::make_unique<Book>();
            if (book) {
                book->fromFileString(line);
                books.push_back(std::move(book));
            }
        }
    }
    
    file.close();
    return true;
}

bool FileManager::saveLibraryConfig(const std::string& filename, const Library& library) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    file << library.getLibraryName() << std::endl;
    file << library.getAddress() << std::endl;
    file << library.getPhoneNumber() << std::endl;
    file << library.getEmail() << std::endl;
    
    file.close();
    return true;
}



bool FileManager::loadLibraryConfig(const std::string& filename, Library& library) {
    if (!fileExists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    std::string libraryName, address, phoneNumber, email;
    
    // Read library configuration from file
    // Expected format: each field on a separate line (name, address, phone, email)
    if (std::getline(file, libraryName) && 
        std::getline(file, address) && 
        std::getline(file, phoneNumber) && 
        std::getline(file, email)) {
        
        // Trim whitespace from each field
        libraryName = trimString(libraryName);
        address = trimString(address);
        phoneNumber = trimString(phoneNumber);
        email = trimString(email);
        
        // Create a new Library object with the loaded configuration
        library = Library(libraryName, address, phoneNumber, email);
    } else {
        setLastError("File cau hinh thu vien khong hop le hoac trong");
        file.close();
        return false;
    }
    
    file.close();
    return true;
}

bool FileManager::createBackup(const std::string& sourceDir, const std::string& backupDir) {
    try {
        if (!std::filesystem::exists(backupDir)) {
            std::filesystem::create_directories(backupDir);
        }
        
        std::filesystem::copy(sourceDir, backupDir, 
                             std::filesystem::copy_options::recursive | 
                             std::filesystem::copy_options::overwrite_existing);
        return true;
    } catch (const std::exception& e) {
        setLastError("Loi khi tao backup: " + std::string(e.what()));
        return false;
    }
}

bool FileManager::restoreFromBackup(const std::string& backupDir, const std::string& targetDir) {
    try {
        if (!std::filesystem::exists(backupDir)) {
            setLastError("Thu muc backup khong ton tai");
            return false;
        }
        
        std::filesystem::copy(backupDir, targetDir, 
                             std::filesystem::copy_options::recursive | 
                             std::filesystem::copy_options::overwrite_existing);
        return true;
    } catch (const std::exception& e) {
        setLastError("Loi khi restore: " + std::string(e.what()));
        return false;
    }
}

std::vector<std::string> FileManager::listBackupFiles(const std::string& backupDir) {
    std::vector<std::string> backupFiles;
    
    if (!std::filesystem::exists(backupDir)) {
        return backupFiles;
    }
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(backupDir)) {
            if (entry.is_regular_file()) {
                backupFiles.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::exception& e) {
        setLastError("Loi khi doc thu muc backup: " + std::string(e.what()));
    }
    
    return backupFiles;
}

std::vector<std::string> FileManager::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string FileManager::trimString(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::string FileManager::escapeString(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c == '|' || c == '\\' || c == '\n' || c == '\r') {
            result += '\\';
        }
        result += c;
    }
    return result;
}

std::string FileManager::unescapeString(const std::string& str) {
    std::string result;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '\\' && i + 1 < str.length()) {
            result += str[i + 1];
            ++i;
        } else {
            result += str[i];
        }
    }
    return result;
}

bool FileManager::isValidFilename(const std::string& filename) {
    if (filename.empty()) return false;
    
    // Check for invalid characters
    std::string invalidChars = "<>:\"|?*";
    for (char c : invalidChars) {
        if (filename.find(c) != std::string::npos) {
            return false;
        }
    }
    
    return true;
}

std::string FileManager::sanitizeFilename(const std::string& filename) {
    std::string result = filename;
    
    // Replace invalid characters with underscores
    std::string invalidChars = "<>:\"|?*";
    for (char c : invalidChars) {
        std::replace(result.begin(), result.end(), c, '_');
    }
    
    // Remove leading/trailing spaces and dots
    result = trimString(result);
    while (result.back() == '.') {
        result.pop_back();
    }
    
    return result;
}

std::string FileManager::getLastError() {
    return lastError;
}

void FileManager::clearLastError() {
    lastError.clear();
}

bool FileManager::hasError() {
    return !lastError.empty();
}

void FileManager::setLastError(const std::string& error) {
    lastError = error;
}

std::string FileManager::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeT), "%Y%m%d_%H%M%S");
    return ss.str();
}

bool FileManager::ensureDirectoryExists(const std::string& dirPath) {
    try {
        if (!std::filesystem::exists(dirPath)) {
            return std::filesystem::create_directories(dirPath);
        }
        return true;
    } catch (const std::exception& e) {
        setLastError("Loi khi tao thu muc: " + std::string(e.what()));
        return false;
    }
}

bool FileManager::ensureDataDirectory() {
    return ensureDirectoryExists(getDataDirectory());
}

bool FileManager::saveBorrowRecordsToFile(const std::string& filename,
                                         const std::vector<std::unique_ptr<BorrowRecord>>& records) {
    // Ensure data directory exists
    if (!ensureDataDirectory()) {
        return false;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    for (const auto& record : records) {
        file << record->toFileString() << std::endl;
    }
    
    file.close();
    return true;
}

bool FileManager::loadBorrowRecordsFromFile(const std::string& filename,
                                           std::vector<std::unique_ptr<BorrowRecord>>& records) {
    if (!fileExists(filename)) {
        return false; // File doesn't exist, not an error
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        setLastError("Khong the mo file: " + filename);
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            auto record = std::make_unique<BorrowRecord>("", "", "");
            if (record && record->fromFileString(line)) {
                records.push_back(std::move(record));
            }
        }
    }
    
    file.close();
    return true;
}
