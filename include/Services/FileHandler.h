#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

class FileHandler {
public:
    // Delimiter for CSV-style file storage
    static const char DELIMITER = '|';
    static const char RECORD_DELIMITER = '\n';
    
    // Ensure data directory exists
    static bool ensureDataDirectory(const std::string& path) {
        try {
            std::filesystem::path dir(path);
            if (!std::filesystem::exists(dir)) {
                return std::filesystem::create_directories(dir);
            }
            return true;
        } catch (...) {
            return false;
        }
    }
    
    // Check if file exists
    static bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }
    
    // Read all lines from a file
    static std::vector<std::string> readAllLines(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    lines.push_back(line);
                }
            }
            file.close();
        }
        
        return lines;
    }
    
    // Write all lines to a file (overwrite)
    static bool writeAllLines(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream file(filename);
        
        if (file.is_open()) {
            for (const auto& line : lines) {
                file << line << RECORD_DELIMITER;
            }
            file.close();
            return true;
        }
        
        return false;
    }
    
    // Append a line to a file
    static bool appendLine(const std::string& filename, const std::string& line) {
        std::ofstream file(filename, std::ios::app);
        
        if (file.is_open()) {
            file << line << RECORD_DELIMITER;
            file.close();
            return true;
        }
        
        return false;
    }
    
    // Split a line by delimiter
    static std::vector<std::string> split(const std::string& line, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    // Split with default delimiter
    static std::vector<std::string> split(const std::string& line) {
        return split(line, DELIMITER);
    }
    
    // Join tokens with delimiter
    static std::string join(const std::vector<std::string>& tokens, char delimiter) {
        std::string result;
        for (size_t i = 0; i < tokens.size(); i++) {
            result += tokens[i];
            if (i < tokens.size() - 1) {
                result += delimiter;
            }
        }
        return result;
    }
    
    // Join with default delimiter
    static std::string join(const std::vector<std::string>& tokens) {
        return join(tokens, DELIMITER);
    }
    
    // Generate unique ID
    static std::string generateId(const std::string& prefix) {
        static int counter = 0;
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        return prefix + std::to_string(timestamp) + std::to_string(++counter);
    }
    
    // Update a record in file (by matching first field - ID)
    static bool updateRecord(const std::string& filename, const std::string& id, const std::string& newRecord) {
        std::vector<std::string> lines = readAllLines(filename);
        bool found = false;
        
        for (auto& line : lines) {
            std::vector<std::string> tokens = split(line);
            if (!tokens.empty() && tokens[0] == id) {
                line = newRecord;
                found = true;
                break;
            }
        }
        
        if (found) {
            return writeAllLines(filename, lines);
        }
        
        return false;
    }
    
    // Delete a record from file (by matching first field - ID)
    static bool deleteRecord(const std::string& filename, const std::string& id) {
        std::vector<std::string> lines = readAllLines(filename);
        std::vector<std::string> newLines;
        bool found = false;
        
        for (const auto& line : lines) {
            std::vector<std::string> tokens = split(line);
            if (!tokens.empty() && tokens[0] == id) {
                found = true;
            } else {
                newLines.push_back(line);
            }
        }
        
        if (found) {
            return writeAllLines(filename, newLines);
        }
        
        return false;
    }
    
    // Find a record by ID
    static std::string findRecord(const std::string& filename, const std::string& id) {
        std::vector<std::string> lines = readAllLines(filename);
        
        for (const auto& line : lines) {
            std::vector<std::string> tokens = split(line);
            if (!tokens.empty() && tokens[0] == id) {
                return line;
            }
        }
        
        return "";
    }
    
    // Find records by a specific field value
    static std::vector<std::string> findRecordsByField(const std::string& filename, int fieldIndex, const std::string& value) {
        std::vector<std::string> results;
        std::vector<std::string> lines = readAllLines(filename);
        
        for (const auto& line : lines) {
            std::vector<std::string> tokens = split(line);
            if ((int)tokens.size() > fieldIndex && tokens[fieldIndex] == value) {
                results.push_back(line);
            }
        }
        
        return results;
    }
    
    // Count records in file
    static int countRecords(const std::string& filename) {
        std::vector<std::string> lines = readAllLines(filename);
        return lines.size();
    }
    
    // Clear a file
    static bool clearFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::trunc);
        if (file.is_open()) {
            file.close();
            return true;
        }
        return false;
    }
    
    // Backup a file
    static bool backupFile(const std::string& filename) {
        if (!fileExists(filename)) return false;
        
        std::string backupName = filename + ".bak";
        std::ifstream src(filename, std::ios::binary);
        std::ofstream dst(backupName, std::ios::binary);
        
        if (src.is_open() && dst.is_open()) {
            dst << src.rdbuf();
            src.close();
            dst.close();
            return true;
        }
        
        return false;
    }
    
    // Safe string to int conversion
    static int toInt(const std::string& str, int defaultValue = 0) {
        try {
            return std::stoi(str);
        } catch (...) {
            return defaultValue;
        }
    }
    
    // Safe string to double conversion
    static double toDouble(const std::string& str, double defaultValue = 0.0) {
        try {
            return std::stod(str);
        } catch (...) {
            return defaultValue;
        }
    }
};

#endif // FILE_HANDLER_H
