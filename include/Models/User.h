#ifndef USER_H
#define USER_H

#include <string>
#include "../Config.h"
#include "../Services/FileHandler.h"

class User {
protected:
    std::string userId;
    std::string username;
    std::string password;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    std::string address;
    std::string dateOfBirth;
    std::string registrationDate;
    Config::UserType userType;
    bool isActive;

public:

    User() : isActive(true), userType(Config::UserType::STUDENT) {
    
    
    }
    
    
    User(const std::string& id, const std::string& uname, const std::string& pwd,
         const std::string& fname, const std::string& lname, Config::UserType type)
        : userId(id), username(uname), password(pwd), firstName(fname), 
          lastName(lname), userType(type), isActive(true) {}
    

    virtual ~User() {}
    
    // Getters
    std::string getUserId() const { return userId; }
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getFullName() const { return firstName + " " + lastName; }
    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }
    std::string getAddress() const { return address; }
    std::string getDateOfBirth() const { return dateOfBirth; }
    std::string getRegistrationDate() const { return registrationDate; }
    Config::UserType getUserType() const { return userType; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setUserId(const std::string& id) { userId = id; }
    void setUsername(const std::string& uname) { username = uname; }
    void setPassword(const std::string& pwd) { password = pwd; }
    void setFirstName(const std::string& fname) { firstName = fname; }
    void setLastName(const std::string& lname) { lastName = lname; }
    void setEmail(const std::string& mail) { email = mail; }
    void setPhone(const std::string& ph) { phone = ph; }
    void setAddress(const std::string& addr) { address = addr; }
    void setDateOfBirth(const std::string& dob) { dateOfBirth = dob; }
    void setRegistrationDate(const std::string& date) { registrationDate = date; }
    void setUserType(Config::UserType type) { userType = type; }
    void setIsActive(bool active) { isActive = active; }
    
    // Authenticate user
    bool authenticate(const std::string& pwd) const {
        return password == pwd;
    }
    
    // Get user type as string
    std::string getUserTypeString() const {
        switch (userType) {
            case Config::UserType::STUDENT: return "Student";
            case Config::UserType::PROFESSOR: return "Professor";
            case Config::UserType::ADMIN: return "Administrator";
            default: return "Unknown";
        }
    }
    
    // Serialize user to string for file storage
    virtual std::string serialize() const {
        std::vector<std::string> fields = {
            userId, username, password, firstName, lastName,
            email, phone, address, dateOfBirth, registrationDate,
            std::to_string(static_cast<int>(userType)),
            isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize user from string
    virtual void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 12) {
            userId = fields[0];
            username = fields[1];
            password = fields[2];
            firstName = fields[3];
            lastName = fields[4];
            email = fields[5];
            phone = fields[6];
            address = fields[7];
            dateOfBirth = fields[8];
            registrationDate = fields[9];
            userType = static_cast<Config::UserType>(FileHandler::toInt(fields[10]));
            isActive = fields[11] == "1";
        }
    }
};

#endif // USER_H
