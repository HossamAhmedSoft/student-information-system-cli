#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <vector>
#include "../Services/FileHandler.h"

class Faculty {
private:
    std::string facultyId;
    std::string facultyCode;
    std::string facultyName;
    std::string deanId;       // Professor ID of the dean
    std::string location;
    std::string phone;
    std::string email;
    std::string description;
    std::string establishedDate;
    bool isActive;

public:
    // Default constructor
    Faculty() : isActive(true) {}
    
    // Parameterized constructor
    Faculty(const std::string& id, const std::string& code, const std::string& name)
        : facultyId(id), facultyCode(code), facultyName(name), isActive(true) {}
    
    // Getters
    std::string getFacultyId() const { return facultyId; }
    std::string getFacultyCode() const { return facultyCode; }
    std::string getFacultyName() const { return facultyName; }
    std::string getDeanId() const { return deanId; }
    std::string getLocation() const { return location; }
    std::string getPhone() const { return phone; }
    std::string getEmail() const { return email; }
    std::string getDescription() const { return description; }
    std::string getEstablishedDate() const { return establishedDate; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setFacultyId(const std::string& id) { facultyId = id; }
    void setFacultyCode(const std::string& code) { facultyCode = code; }
    void setFacultyName(const std::string& name) { facultyName = name; }
    void setDeanId(const std::string& id) { deanId = id; }
    void setLocation(const std::string& loc) { location = loc; }
    void setPhone(const std::string& ph) { phone = ph; }
    void setEmail(const std::string& mail) { email = mail; }
    void setDescription(const std::string& desc) { description = desc; }
    void setEstablishedDate(const std::string& date) { establishedDate = date; }
    void setIsActive(bool active) { isActive = active; }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            facultyId, facultyCode, facultyName, deanId, location,
            phone, email, description, establishedDate, isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 10) {
            facultyId = fields[0];
            facultyCode = fields[1];
            facultyName = fields[2];
            deanId = fields[3];
            location = fields[4];
            phone = fields[5];
            email = fields[6];
            description = fields[7];
            establishedDate = fields[8];
            isActive = fields[9] == "1";
        }
    }
};

#endif // FACULTY_H
