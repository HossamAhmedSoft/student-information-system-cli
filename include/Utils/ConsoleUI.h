#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>

namespace ConsoleUI {
    // Console Colors
    enum class Color {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        GRAY = 7,
        DARK_GRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };

    // Set console text color
    inline void setColor(Color textColor, Color bgColor = Color::BLACK) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (int)bgColor * 16 + (int)textColor);
    }

    // Reset to default colors
    inline void resetColor() {
        setColor(Color::WHITE, Color::BLACK);
    }

    // Clear console screen
    inline void clearScreen() {
        system("cls");
    }

    // Print horizontal line
    inline void printLine(char c = '=', int length = 70) {
        setColor(Color::DARK_CYAN);
        for (int i = 0; i < length; i++) std::cout << c;
        std::cout << std::endl;
        resetColor();
    }

    // Print centered text
    inline void printCentered(const std::string& text, int width = 70) {
        int padding = (width - text.length()) / 2;
        if (padding > 0) std::cout << std::string(padding, ' ');
        std::cout << text << std::endl;
    }

    // Print header
    inline void printHeader(const std::string& title) {
        clearScreen();
        printLine('=');
        setColor(Color::CYAN);
        printCentered(title);
        resetColor();
        printLine('=');
        std::cout << std::endl;
    }

    // Print sub-header
    inline void printSubHeader(const std::string& title) {
        std::cout << std::endl;
        setColor(Color::YELLOW);
        printLine('-', 50);
        std::cout << "  " << title << std::endl;
        printLine('-', 50);
        resetColor();
    }

    // Print success message
    inline void printSuccess(const std::string& message) {
        setColor(Color::GREEN);
        std::cout << "\n  [SUCCESS] " << message << std::endl;
        resetColor();
    }

    // Print error message
    inline void printError(const std::string& message) {
        setColor(Color::RED);
        std::cout << "\n  [ERROR] " << message << std::endl;
        resetColor();
    }

    // Print warning message
    inline void printWarning(const std::string& message) {
        setColor(Color::YELLOW);
        std::cout << "\n  [WARNING] " << message << std::endl;
        resetColor();
    }

    // Print info message
    inline void printInfo(const std::string& message) {
        setColor(Color::CYAN);
        std::cout << "\n  [INFO] " << message << std::endl;
        resetColor();
    }

    // Print menu option
    inline void printMenuOption(int number, const std::string& text) {
        setColor(Color::YELLOW);
        std::cout << "  [" << number << "] ";
        setColor(Color::WHITE);
        std::cout << text << std::endl;
    }

    // Print menu option with custom key
    inline void printMenuOption(const std::string& key, const std::string& text) {
        setColor(Color::YELLOW);
        std::cout << "  [" << key << "] ";
        setColor(Color::WHITE);
        std::cout << text << std::endl;
    }

    // Get user input with prompt
    inline std::string getInput(const std::string& prompt) {
        setColor(Color::GREEN);
        std::cout << "\n  " << prompt << ": ";
        setColor(Color::WHITE);
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    // Get integer input
    inline int getIntInput(const std::string& prompt, int min = INT_MIN, int max = INT_MAX) {
        while (true) {
            std::string input = getInput(prompt);
            try {
                int value = std::stoi(input);
                if (value >= min && value <= max) {
                    return value;
                }
                printError("Please enter a number between " + std::to_string(min) + " and " + std::to_string(max));
            } catch (...) {
                printError("Invalid input. Please enter a valid number.");
            }
        }
    }

    // Get double input
    inline double getDoubleInput(const std::string& prompt, double min = -1e9, double max = 1e9) {
        while (true) {
            std::string input = getInput(prompt);
            try {
                double value = std::stod(input);
                if (value >= min && value <= max) {
                    return value;
                }
                printError("Please enter a number between " + std::to_string(min) + " and " + std::to_string(max));
            } catch (...) {
                printError("Invalid input. Please enter a valid number.");
            }
        }
    }

    // Get password input (hidden)
    inline std::string getPasswordInput(const std::string& prompt) {
        setColor(Color::GREEN);
        std::cout << "\n  " << prompt << ": ";
        setColor(Color::WHITE);
        
        std::string password;
        char ch;
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & ~ENABLE_ECHO_INPUT);
        
        std::getline(std::cin, password);
        
        SetConsoleMode(hStdin, mode);
        std::cout << std::endl;
        return password;
    }

    // Wait for key press
    inline void waitForKey() {
        setColor(Color::DARK_GRAY);
        std::cout << "\n  Press Enter to continue...";
        resetColor();
        std::cin.get();
    }

    // Confirm action (Y/N)
    inline bool confirm(const std::string& message) {
        setColor(Color::YELLOW);
        std::cout << "\n  " << message << " (Y/N): ";
        setColor(Color::WHITE);
        std::string input;
        std::getline(std::cin, input);
        return (input == "Y" || input == "y" || input == "yes" || input == "Yes");
    }

    // Print table header
    inline void printTableHeader(const std::vector<std::pair<std::string, int>>& columns) {
        setColor(Color::DARK_CYAN);
        std::cout << "  ";
        for (const auto& col : columns) {
            std::cout << std::left << std::setw(col.second) << col.first;
        }
        std::cout << std::endl;
        std::cout << "  ";
        for (const auto& col : columns) {
            for (int i = 0; i < col.second - 1; i++) std::cout << "-";
            std::cout << " ";
        }
        std::cout << std::endl;
        resetColor();
    }

    // Print table row
    inline void printTableRow(const std::vector<std::pair<std::string, int>>& values) {
        std::cout << "  ";
        for (const auto& val : values) {
            std::cout << std::left << std::setw(val.second) << val.first;
        }
        std::cout << std::endl;
    }

    // Print welcome banner
    inline void printWelcomeBanner(const std::string& appName, const std::string& version) {
        clearScreen();
        setColor(Color::CYAN);
        printLine('*');
        std::cout << std::endl;
        printCentered("███████╗██╗███████╗");
        printCentered("██╔════╝██║██╔════╝");
        printCentered("███████╗██║███████╗");
        printCentered("╚════██║██║╚════██║");
        printCentered("███████║██║███████║");
        printCentered("╚══════╝╚═╝╚══════╝");
        std::cout << std::endl;
        setColor(Color::WHITE);
        printCentered(appName);
        setColor(Color::DARK_GRAY);
        printCentered("Version " + version);
        std::cout << std::endl;
        setColor(Color::CYAN);
        printLine('*');
        resetColor();
    }

    // Print goodbye message
    inline void printGoodbye() {
        clearScreen();
        setColor(Color::CYAN);
        printLine('=');
        std::cout << std::endl;
        printCentered("Thank you for using the Student Information System!");
        printCentered("Goodbye!");
        std::cout << std::endl;
        printLine('=');
        resetColor();
    }
}

#endif // CONSOLE_UI_H
