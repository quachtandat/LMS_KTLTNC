#include "Utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <regex>
#include <filesystem>

// Static member initialization
std::random_device Utils::rd;
std::mt19937 Utils::gen(rd());
bool Utils::genInitialized = false;

// String utilities
std::string Utils::toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Utils::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string Utils::capitalize(const std::string& str) {
    if (str.empty()) return str;
    
    std::string result = str;
    result[0] = std::toupper(result[0]);
    return result;
}

std::string Utils::trimString(const std::string& str) {
    if (str.empty()) return str;
    
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

std::string Utils::removeExtraSpaces(const std::string& str) {
    std::string result;
    bool lastWasSpace = true;
    
    for (char c : str) {
        if (std::isspace(c)) {
            if (!lastWasSpace) {
                result += ' ';
                lastWasSpace = true;
            }
        } else {
            result += c;
            lastWasSpace = false;
        }
    }
    
    // Remove trailing space
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

bool Utils::startsWith(const std::string& str, const std::string& prefix) {
    if (prefix.length() > str.length()) return false;
    return str.compare(0, prefix.length(), prefix) == 0;
}

bool Utils::endsWith(const std::string& str, const std::string& suffix) {
    if (suffix.length() > str.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

bool Utils::contains(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

std::string Utils::replace(const std::string& str, const std::string& oldStr, const std::string& newStr) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(oldStr, pos)) != std::string::npos) {
        result.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
    return result;
}

std::vector<std::string> Utils::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    
    tokens.push_back(str.substr(start));
    return tokens;
}

std::string Utils::join(const std::vector<std::string>& strings, const std::string& delimiter) {
    if (strings.empty()) return "";
    
    std::string result = strings[0];
    for (size_t i = 1; i < strings.size(); ++i) {
        result += delimiter + strings[i];
    }
    return result;
}

// Number utilities
bool Utils::isNumber(const std::string& str) {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') start = 1;
    
    bool hasDigit = false;
    for (size_t i = start; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) return false;
        hasDigit = true;
    }
    
    return hasDigit;
}

int Utils::stringToInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::exception&) {
        return 0;
    }
}

std::string Utils::intToString(int num) {
    return std::to_string(num);
}

double Utils::stringToDouble(const std::string& str) {
    try {
        return std::stod(str);
    } catch (const std::exception&) {
        return 0.0;
    }
}

std::string Utils::doubleToString(double num) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << num;
    return oss.str();
}

bool Utils::isInRange(int value, int min, int max) {
    return value >= min && value <= max;
}

int Utils::clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Date and time utilities
std::string Utils::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Utils::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeT), "%Y-%m-%d");
    return ss.str();
}

std::string Utils::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeT), "%H:%M:%S");
    return ss.str();
}

std::string Utils::formatDateTime(const std::chrono::system_clock::time_point& time) {
    auto timeT = std::chrono::system_clock::to_time_t(time);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::chrono::system_clock::time_point Utils::parseDateTime(const std::string& dateTimeStr) {
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    auto timeT = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(timeT);
}

std::string Utils::getTimeDifference(const std::chrono::system_clock::time_point& start,
                                     const std::chrono::system_clock::time_point& end) {
    auto duration = end - start;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration) % 60;
    
    std::ostringstream oss;
    if (hours.count() > 0) {
        oss << hours.count() << "h " << minutes.count() << "m";
    } else {
        oss << minutes.count() << "m";
    }
    
    return oss.str();
}

bool Utils::isDateValid(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

bool Utils::isTimeValid(const std::string& timeStr) {
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%H:%M:%S");
    return !ss.fail();
}

// Validation utilities
bool Utils::isValidEmail(const std::string& email) {
    std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailRegex);
}

bool Utils::isValidPhoneNumber(const std::string& phone) {
    std::regex phoneRegex(R"(\+?[0-9\s\-\(\)]{10,})");
    return std::regex_match(phone, phoneRegex);
}

bool Utils::isValidISBN(const std::string& isbn) {
    // Remove hyphens and spaces
    std::string cleanIsbn = isbn;
    cleanIsbn.erase(std::remove(cleanIsbn.begin(), cleanIsbn.end(), '-'), cleanIsbn.end());
    cleanIsbn.erase(std::remove(cleanIsbn.begin(), cleanIsbn.end(), ' '), cleanIsbn.end());
    
    // Check length (ISBN-10 or ISBN-13)
    if (cleanIsbn.length() != 10 && cleanIsbn.length() != 13) return false;
    
    // Check if all characters are digits (except last character for ISBN-10)
    for (size_t i = 0; i < cleanIsbn.length() - 1; ++i) {
        if (!std::isdigit(cleanIsbn[i])) return false;
    }
    
    return true;
}

bool Utils::isValidYear(int year) {
    return year >= 1800 && year <= 2024;
}

bool Utils::isValidName(const std::string& name) {
    if (name.empty() || name.length() < 2) return false;
    
    // Check if contains only letters, spaces, and common punctuation
    for (char c : name) {
        if (!std::isalpha(c) && !std::isspace(c) && c != '-' && c != '\'') {
            return false;
        }
    }
    
    return true;
}

bool Utils::isValidUsername(const std::string& username) {
    if (username.empty() || username.length() < 3) return false;
    
    // Check if contains only alphanumeric characters and underscores
    for (char c : username) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }
    
    return true;
}

bool Utils::isValidPassword(const std::string& password) {
    return password.length() >= 6;
}

// Random utilities
int Utils::getRandomNumber(int min, int max) {
    if (!genInitialized) {
        initializeRandomGenerator();
    }
    
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

std::string Utils::getRandomString(int length) {
    if (!genInitialized) {
        initializeRandomGenerator();
    }
    
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::uniform_int_distribution<> dis(0, chars.length() - 1);
    
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += chars[dis(gen)];
    }
    
    return result;
}

std::string Utils::getRandomId(const std::string& prefix) {
    if (!genInitialized) {
        initializeRandomGenerator();
    }
    
    std::uniform_int_distribution<> dis(1000, 9999);
    std::ostringstream oss;
    oss << prefix << dis(gen);
    return oss.str();
}

std::string Utils::generateUUID() {
    if (!genInitialized) {
        initializeRandomGenerator();
    }
    
    std::uniform_int_distribution<> dis(0, 15);
    const std::string hex = "0123456789abcdef";
    
    std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    for (char& c : uuid) {
        if (c == 'x') {
            c = hex[dis(gen)];
        } else if (c == 'y') {
            c = hex[dis(gen) & 0x3 | 0x8];
        }
    }
    
    return uuid;
}

// File utilities
std::string Utils::getFileExtension(const std::string& filename) {
    size_t pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return "";
}

std::string Utils::getFileName(const std::string& filepath) {
    size_t pos = filepath.find_last_of("/\\");
    if (pos != std::string::npos) {
        return filepath.substr(pos + 1);
    }
    return filepath;
}

std::string Utils::getDirectory(const std::string& filepath) {
    size_t pos = filepath.find_last_of("/\\");
    if (pos != std::string::npos) {
        return filepath.substr(0, pos);
    }
    return "";
}

bool Utils::isValidFilename(const std::string& filename) {
    if (filename.empty()) return false;
    
    std::string invalidChars = "<>:\"|?*";
    for (char c : invalidChars) {
        if (filename.find(c) != std::string::npos) {
            return false;
        }
    }
    
    return true;
}

std::string Utils::sanitizeFilename(const std::string& filename) {
    std::string result = filename;
    
    // Replace invalid characters with underscores
    std::string invalidChars = "<>:\"|?*";
    for (char c : invalidChars) {
        std::replace(result.begin(), result.end(), c, '_');
    }
    
    // Remove leading/trailing spaces and dots
    result = trimString(result);
    while (!result.empty() && result.back() == '.') {
        result.pop_back();
    }
    
    return result;
}

// Formatting utilities
std::string Utils::centerText(const std::string& text, int width) {
    if (text.length() >= width) return text;
    
    int padding = (width - text.length()) / 2;
    return std::string(padding, ' ') + text;
}

std::string Utils::leftAlignText(const std::string& text, int width) {
    if (text.length() >= width) return text.substr(0, width);
    return text + std::string(width - text.length(), ' ');
}

std::string Utils::rightAlignText(const std::string& text, int width) {
    if (text.length() >= width) return text.substr(0, width);
    return std::string(width - text.length(), ' ') + text;
}

std::string Utils::createTableRow(const std::vector<std::string>& columns, const std::vector<int>& widths) {
    std::string result = "|";
    
    for (size_t i = 0; i < columns.size() && i < widths.size(); ++i) {
        result += " " + leftAlignText(columns[i], widths[i]) + " |";
    }
    
    return result;
}

std::string Utils::createSeparator(char separator, int length) {
    return std::string(length, separator);
}

std::string Utils::formatCurrency(double amount, const std::string& currency) {
    std::ostringstream oss;
    oss << currency << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}

// Platform utilities
std::string Utils::getPlatformName() {
    #ifdef WIN32
    return "Windows";
    #elif defined(__linux__)
    return "Linux";
    #elif defined(__APPLE__)
    return "macOS";
    #else
    return "Unknown";
    #endif
}

bool Utils::isWindows() {
    #ifdef WIN32
    return true;
    #else
    return false;
    #endif
}

bool Utils::isLinux() {
    #ifdef __linux__
    return true;
    #else
    return false;
    #endif
}

std::string Utils::getHomeDirectory() {
    #ifdef WIN32
    const char* homeDir = std::getenv("USERPROFILE");
    #else
    const char* homeDir = std::getenv("HOME");
    #endif
    
    return homeDir ? homeDir : "";
}

std::string Utils::getTempDirectory() {
    #ifdef WIN32
    const char* tempDir = std::getenv("TEMP");
    if (!tempDir) tempDir = std::getenv("TMP");
    #else
    const char* tempDir = std::getenv("TMPDIR");
    if (!tempDir) tempDir = "/tmp";
    #endif
    
    return tempDir ? tempDir : "";
}

// Private methods
void Utils::initializeRandomGenerator() {
    if (!genInitialized) {
        gen.seed(rd());
        genInitialized = true;
    }
}

std::string Utils::getPlatformSpecificPath(const std::string& path) {
    #ifdef WIN32
    // Convert forward slashes to backslashes on Windows
    std::string result = path;
    std::replace(result.begin(), result.end(), '/', '\\');
    return result;
    #else
    return path;
    #endif
}
