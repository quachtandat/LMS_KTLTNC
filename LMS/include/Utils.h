#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <chrono>
#include <random>

class Utils {
public:
    Utils() = delete; // Static class, no instances allowed
    ~Utils() = delete;

    // String utilities
    static std::string toUpper(const std::string& str);
    static std::string toLower(const std::string& str);
    static std::string capitalize(const std::string& str);
    static std::string trimString(const std::string& str);
    static std::string removeExtraSpaces(const std::string& str);
    static bool startsWith(const std::string& str, const std::string& prefix);
    static bool endsWith(const std::string& str, const std::string& suffix);
    static bool contains(const std::string& str, const std::string& substr);
    static std::string replace(const std::string& str, const std::string& oldStr, const std::string& newStr);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    static std::string join(const std::vector<std::string>& strings, const std::string& delimiter);

    // Number utilities
    static bool isNumber(const std::string& str);
    static int stringToInt(const std::string& str);
    static std::string intToString(int num);
    static double stringToDouble(const std::string& str);
    static std::string doubleToString(double num);
    static bool isInRange(int value, int min, int max);
    static int clamp(int value, int min, int max);

    // Date and time utilities
    static std::string getCurrentDateTime();
    static std::string getCurrentDate();
    static std::string getCurrentTime();
    static std::string formatDateTime(const std::chrono::system_clock::time_point& time);
    static std::chrono::system_clock::time_point parseDateTime(const std::string& dateTimeStr);
    static std::string getTimeDifference(const std::chrono::system_clock::time_point& start,
                                        const std::chrono::system_clock::time_point& end);
    static bool isDateValid(const std::string& dateStr);
    static bool isTimeValid(const std::string& timeStr);

    // Validation utilities
    static bool isValidEmail(const std::string& email);
    static bool isValidPhoneNumber(const std::string& phone);
    static bool isValidISBN(const std::string& isbn);
    static bool isValidYear(int year);
    static bool isValidName(const std::string& name);
    static bool isValidUsername(const std::string& username);
    static bool isValidPassword(const std::string& password);

    // Random utilities
    static int getRandomNumber(int min, int max);
    static std::string getRandomString(int length);
    static std::string getRandomId(const std::string& prefix = "");
    static std::string generateUUID();

    // File utilities
    static std::string getFileExtension(const std::string& filename);
    static std::string getFileName(const std::string& filepath);
    static std::string getDirectory(const std::string& filepath);
    static bool isValidFilename(const std::string& filename);
    static std::string sanitizeFilename(const std::string& filename);

    // Formatting utilities
    static std::string centerText(const std::string& text, int width);
    static std::string leftAlignText(const std::string& text, int width);
    static std::string rightAlignText(const std::string& text, int width);
    static std::string createTableRow(const std::vector<std::string>& columns, const std::vector<int>& widths);
    static std::string createSeparator(char separator, int length);
    static std::string formatCurrency(double amount, const std::string& currency = "$");

    // Platform utilities
    static std::string getPlatformName();
    static bool isWindows();
    static bool isLinux();
    static std::string getHomeDirectory();
    static std::string getTempDirectory();

private:
    static std::random_device rd;
    static std::mt19937 gen;
    static bool genInitialized;
    
    static void initializeRandomGenerator();
    static std::string getPlatformSpecificPath(const std::string& path);
};

#endif // UTILS_H
