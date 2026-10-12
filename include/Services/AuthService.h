#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>
#include <memory>
#include "../Config.h"
#include "../Models/User.h"
#include "../Models/Student.h"
#include "../Models/Professor.h"
#include "../Models/Admin.h"
#include "FileHandler.h"

class AuthService {
private:
    static AuthService* instance;
    User* currentUser;
    Config::UserType currentUserType;
    bool isLoggedIn;
    
    AuthService() : currentUser(nullptr), isLoggedIn(false) {}

public:
    // Singleton pattern
    static AuthService* getInstance() {
        if (instance == nullptr) {
            instance = new AuthService();
        }
        return instance;
    }
    
    // Login with username and password
    bool login(const std::string& username, const std::string& password) {
        // Check admins first
        std::vector<std::string> adminRecords = FileHandler::readAllLines(Config::USERS_FILE);
        for (const auto& record : adminRecords) {
            std::vector<std::string> fields = FileHandler::split(record);
            if (fields.size() >= 12) {
                if (fields[1] == username && fields[2] == password) {
                    int userType = FileHandler::toInt(fields[10]);
                    
                    if (userType == static_cast<int>(Config::UserType::ADMIN)) {
                        Admin* admin = new Admin();
                        admin->deserialize(record);
                        currentUser = admin;
                        currentUserType = Config::UserType::ADMIN;
                        isLoggedIn = true;
                        return true;
                    }
                }
            }
        }
        
        // Check students
        std::vector<std::string> studentRecords = FileHandler::readAllLines(Config::STUDENTS_FILE);
        for (const auto& record : studentRecords) {
            std::vector<std::string> fields = FileHandler::split(record);
            if (fields.size() >= 12) {
                if (fields[1] == username && fields[2] == password) {
                    Student* student = new Student();
                    student->deserialize(record);
                    currentUser = student;
                    currentUserType = Config::UserType::STUDENT;
                    isLoggedIn = true;
                    return true;
                }
            }
        }
        
        // Check professors
        std::vector<std::string> profRecords = FileHandler::readAllLines(Config::PROFESSORS_FILE);
        for (const auto& record : profRecords) {
            std::vector<std::string> fields = FileHandler::split(record);
            if (fields.size() >= 12) {
                if (fields[1] == username && fields[2] == password) {
                    Professor* professor = new Professor();
                    professor->deserialize(record);
                    currentUser = professor;
                    currentUserType = Config::UserType::PROFESSOR;
                    isLoggedIn = true;
                    return true;
                }
            }
        }
        
        return false;
    }
    
    // Logout
    void logout() {
        if (currentUser != nullptr) {
            delete currentUser;
            currentUser = nullptr;
        }
        isLoggedIn = false;
    }
    
    // Check if logged in
    bool getIsLoggedIn() const { return isLoggedIn; }
    
    // Get current user
    User* getCurrentUser() const { return currentUser; }
    
    // Get current user type
    Config::UserType getCurrentUserType() const { return currentUserType; }
    
    // Get current user as Student
    Student* getCurrentStudent() const {
        if (currentUserType == Config::UserType::STUDENT) {
            return dynamic_cast<Student*>(currentUser);
        }
        return nullptr;
    }
    
    // Get current user as Professor
    Professor* getCurrentProfessor() const {
        if (currentUserType == Config::UserType::PROFESSOR) {
            return dynamic_cast<Professor*>(currentUser);
        }
        return nullptr;
    }
    
    // Get current user as Admin
    Admin* getCurrentAdmin() const {
        if (currentUserType == Config::UserType::ADMIN) {
            return dynamic_cast<Admin*>(currentUser);
        }
        return nullptr;
    }
    
    // Initialize default admin if no users exist
    void initializeDefaultAdmin() {
        FileHandler::ensureDataDirectory(Config::DATA_DIR);
        
        if (!FileHandler::fileExists(Config::USERS_FILE) || 
            FileHandler::countRecords(Config::USERS_FILE) == 0) {
            
            Admin defaultAdmin;
            defaultAdmin.setAdminId("ADM001");
            defaultAdmin.setUsername(Config::DEFAULT_ADMIN_USERNAME);
            defaultAdmin.setPassword(Config::DEFAULT_ADMIN_PASSWORD);
            defaultAdmin.setFirstName("System");
            defaultAdmin.setLastName("Administrator");
            defaultAdmin.setEmail("admin@university.edu");
            defaultAdmin.setPhone("1234567890");
            defaultAdmin.setDepartment("IT");
            defaultAdmin.setPosition("System Administrator");
            defaultAdmin.setAccessLevel("Super Admin");
            defaultAdmin.setIsActive(true);
            
            FileHandler::appendLine(Config::USERS_FILE, defaultAdmin.serialize());
        }
    }
    
    // Change password
    bool changePassword(const std::string& oldPassword, const std::string& newPassword) {
        if (!isLoggedIn || currentUser == nullptr) return false;
        
        if (currentUser->getPassword() != oldPassword) return false;
        
        currentUser->setPassword(newPassword);
        
        // Update in file based on user type
        std::string filename;
        switch (currentUserType) {
            case Config::UserType::STUDENT:
                filename = Config::STUDENTS_FILE;
                break;
            case Config::UserType::PROFESSOR:
                filename = Config::PROFESSORS_FILE;
                break;
            case Config::UserType::ADMIN:
                filename = Config::USERS_FILE;
                break;
        }
        
        return FileHandler::updateRecord(filename, currentUser->getUserId(), 
                                         currentUser->serialize());
    }
    
    // Destructor
    ~AuthService() {
        logout();
    }
};

// Initialize static member
AuthService* AuthService::instance = nullptr;

#endif // AUTH_SERVICE_H
