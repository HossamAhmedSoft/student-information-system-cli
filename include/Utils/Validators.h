#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <string>
#include <regex>
#include <algorithm>

namespace Validators {
    
    // Check if string is empty or whitespace only
    inline bool isEmpty(const std::string& str) {
        return str.empty() || std::all_of(str.begin(), str.end(), ::isspace);
    }
    
    // Validate email format
    inline bool isValidEmail(const std::string& email) {
        const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return std::regex_match(email, pattern);
    }
    
    // Validate phone number (basic)
    inline bool isValidPhone(const std::string& phone) {
        const std::regex pattern(R"(^\+?[0-9]{10,15}$)");
        return std::regex_match(phone, pattern);
    }
    
    // Validate ID format (alphanumeric)
    inline bool isValidId(const std::string& id) {
        if (id.empty()) return false;
        return std::all_of(id.begin(), id.end(), [](char c) {
            return std::isalnum(c) || c == '-' || c == '_';
        });
    }
    
    // Validate name (letters and spaces only)
    inline bool isValidName(const std::string& name) {
        if (isEmpty(name)) return false;
        return std::all_of(name.begin(), name.end(), [](char c) {
            return std::isalpha(c) || c == ' ' || c == '-' || c == '\'';
        });
    }
    
    // Validate numeric string
    inline bool isNumeric(const std::string& str) {
        if (str.empty()) return false;
        return std::all_of(str.begin(), str.end(), ::isdigit);
    }
    
    // Validate grade (0-100 or 0-150)
    inline bool isValidGrade(double grade, double maxGrade) {
        return grade >= 0 && grade <= maxGrade;
    }
    
    // Validate year format (YYYY)
    inline bool isValidYear(const std::string& year) {
        if (year.length() != 4) return false;
        if (!isNumeric(year)) return false;
        int y = std::stoi(year);
        return y >= 1900 && y <= 2100;
    }
    
    // Validate academic year format (YYYY-YYYY)
    inline bool isValidAcademicYear(const std::string& academicYear) {
        if (academicYear.length() != 9) return false;
        if (academicYear[4] != '-') return false;
        std::string year1 = academicYear.substr(0, 4);
        std::string year2 = academicYear.substr(5, 4);
        if (!isValidYear(year1) || !isValidYear(year2)) return false;
        return std::stoi(year2) == std::stoi(year1) + 1;
    }
    
    // Validate date format (DD/MM/YYYY)
    inline bool isValidDate(const std::string& date) {
        const std::regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/[0-9]{4}$)");
        return std::regex_match(date, pattern);
    }
    
    // Validate time format (HH:MM)
    inline bool isValidTime(const std::string& time) {
        const std::regex pattern(R"(^([01]?[0-9]|2[0-3]):[0-5][0-9]$)");
        return std::regex_match(time, pattern);
    }
    
    // Validate password strength
    inline bool isStrongPassword(const std::string& password) {
        if (password.length() < 6) return false;
        bool hasUpper = false, hasLower = false, hasDigit = false;
        for (char c : password) {
            if (std::isupper(c)) hasUpper = true;
            if (std::islower(c)) hasLower = true;
            if (std::isdigit(c)) hasDigit = true;
        }
        return hasUpper && hasLower && hasDigit;
    }
    
    // Validate academic level (1-4)
    inline bool isValidAcademicLevel(int level) {
        return level >= 1 && level <= 4;
    }
    
    // Validate percentage (0-100)
    inline bool isValidPercentage(double percentage) {
        return percentage >= 0.0 && percentage <= 100.0;
    }
    
    // Trim whitespace from string
    inline std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }
    
    // Convert string to uppercase
    inline std::string toUpper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    
    // Convert string to lowercase
    inline std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
}

#endif // VALIDATORS_H
