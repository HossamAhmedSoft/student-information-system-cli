#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
private:
    std::string adminId;
    std::string department;
    std::string position;
    std::string accessLevel;  // Super Admin, Admin, Operator
    std::string workHours;

public:
    // Default constructor
    Admin() : User() {
        setUserType(Config::UserType::ADMIN);
    }
    
    // Parameterized constructor
    Admin(const std::string& id, const std::string& uname, const std::string& pwd,
          const std::string& fname, const std::string& lname)
        : User(id, uname, pwd, fname, lname, Config::UserType::ADMIN) {
        adminId = id;
    }
    
    // Getters
    std::string getAdminId() const { return adminId; }
    std::string getDepartment() const { return department; }
    std::string getPosition() const { return position; }
    std::string getAccessLevel() const { return accessLevel; }
    std::string getWorkHours() const { return workHours; }
    
    // Setters
    void setAdminId(const std::string& id) { adminId = id; setUserId(id); }
    void setDepartment(const std::string& dept) { department = dept; }
    void setPosition(const std::string& pos) { position = pos; }
    void setAccessLevel(const std::string& level) { accessLevel = level; }
    void setWorkHours(const std::string& hours) { workHours = hours; }
    
    // Check if super admin
    bool isSuperAdmin() const {
        return accessLevel == "Super Admin";
    }
    
    // Serialize to string
    std::string serialize() const override {
        std::vector<std::string> fields = {
            adminId, getUsername(), getPassword(), getFirstName(), getLastName(),
            getEmail(), getPhone(), getAddress(), getDateOfBirth(), getRegistrationDate(),
            std::to_string(static_cast<int>(getUserType())), getIsActive() ? "1" : "0",
            department, position, accessLevel, workHours
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize from string
    void deserialize(const std::string& data) override {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 16) {
            adminId = fields[0];
            setUserId(fields[0]);
            setUsername(fields[1]);
            setPassword(fields[2]);
            setFirstName(fields[3]);
            setLastName(fields[4]);
            setEmail(fields[5]);
            setPhone(fields[6]);
            setAddress(fields[7]);
            setDateOfBirth(fields[8]);
            setRegistrationDate(fields[9]);
            setUserType(static_cast<Config::UserType>(FileHandler::toInt(fields[10])));
            setIsActive(fields[11] == "1");
            department = fields[12];
            position = fields[13];
            accessLevel = fields[14];
            workHours = fields[15];
        }
    }
};

#endif // ADMIN_H
