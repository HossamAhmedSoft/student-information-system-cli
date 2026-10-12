#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include "../Services/FileHandler.h"

class Department {
private:
    std::string departmentId;
    std::string departmentCode;
    std::string departmentName;
    std::string facultyId;
    std::string headOfDepartmentId;  // Professor ID
    std::string location;
    std::string phone;
    std::string email;
    std::string description;
    bool isActive;

public:
    // Default constructor
    Department() : isActive(true) {}
    
    // Parameterized constructor
    Department(const std::string& id, const std::string& code, 
               const std::string& name, const std::string& facId)
        : departmentId(id), departmentCode(code), departmentName(name), 
          facultyId(facId), isActive(true) {}
    
    // Getters
    std::string getDepartmentId() const { return departmentId; }
    std::string getDepartmentCode() const { return departmentCode; }
    std::string getDepartmentName() const { return departmentName; }
    std::string getFacultyId() const { return facultyId; }
    std::string getHeadOfDepartmentId() const { return headOfDepartmentId; }
    std::string getLocation() const { return location; }
    std::string getPhone() const { return phone; }
    std::string getEmail() const { return email; }
    std::string getDescription() const { return description; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setDepartmentId(const std::string& id) { departmentId = id; }
    void setDepartmentCode(const std::string& code) { departmentCode = code; }
    void setDepartmentName(const std::string& name) { departmentName = name; }
    void setFacultyId(const std::string& id) { facultyId = id; }
    void setHeadOfDepartmentId(const std::string& id) { headOfDepartmentId = id; }
    void setLocation(const std::string& loc) { location = loc; }
    void setPhone(const std::string& ph) { phone = ph; }
    void setEmail(const std::string& mail) { email = mail; }
    void setDescription(const std::string& desc) { description = desc; }
    void setIsActive(bool active) { isActive = active; }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            departmentId, departmentCode, departmentName, facultyId,
            headOfDepartmentId, location, phone, email, description,
            isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 10) {
            departmentId = fields[0];
            departmentCode = fields[1];
            departmentName = fields[2];
            facultyId = fields[3];
            headOfDepartmentId = fields[4];
            location = fields[5];
            phone = fields[6];
            email = fields[7];
            description = fields[8];
            isActive = fields[9] == "1";
        }
    }
};

#endif // DEPARTMENT_H
