#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "User.h"
#include <vector>

class Professor : public User {
private:
    std::string professorId;
    std::string facultyId;
    std::string departmentId;
    std::string specialization;
    std::string academicRank;      // Professor, Associate Professor, Assistant Professor, Lecturer
    std::string officeLocation;
    std::string officeHours;
    double salary;
    std::string hireDate;
    std::string contractType;      // Full-time, Part-time, Visiting
    std::vector<std::string> assignedCourseIds;

public:
    // Default constructor
    Professor() : User(), salary(0) {
        setUserType(Config::UserType::PROFESSOR);
    }
    
    // Parameterized constructor
    Professor(const std::string& id, const std::string& uname, const std::string& pwd,
              const std::string& fname, const std::string& lname)
        : User(id, uname, pwd, fname, lname, Config::UserType::PROFESSOR), salary(0) {
        professorId = id;
    }
    
    // Getters
    std::string getProfessorId() const { return professorId; }
    std::string getFacultyId() const { return facultyId; }
    std::string getDepartmentId() const { return departmentId; }
    std::string getSpecialization() const { return specialization; }
    std::string getAcademicRank() const { return academicRank; }
    std::string getOfficeLocation() const { return officeLocation; }
    std::string getOfficeHours() const { return officeHours; }
    double getSalary() const { return salary; }
    std::string getHireDate() const { return hireDate; }
    std::string getContractType() const { return contractType; }
    std::vector<std::string> getAssignedCourseIds() const { return assignedCourseIds; }
    
    // Setters
    void setProfessorId(const std::string& id) { professorId = id; setUserId(id); }
    void setFacultyId(const std::string& id) { facultyId = id; }
    void setDepartmentId(const std::string& id) { departmentId = id; }
    void setSpecialization(const std::string& spec) { specialization = spec; }
    void setAcademicRank(const std::string& rank) { academicRank = rank; }
    void setOfficeLocation(const std::string& location) { officeLocation = location; }
    void setOfficeHours(const std::string& hours) { officeHours = hours; }
    void setSalary(double sal) { salary = sal; }
    void setHireDate(const std::string& date) { hireDate = date; }
    void setContractType(const std::string& type) { contractType = type; }
    void setAssignedCourseIds(const std::vector<std::string>& ids) { assignedCourseIds = ids; }
    
    // Add assigned course
    void addAssignedCourse(const std::string& courseId) {
        assignedCourseIds.push_back(courseId);
    }
    
    // Remove assigned course
    void removeAssignedCourse(const std::string& courseId) {
        auto it = std::find(assignedCourseIds.begin(), assignedCourseIds.end(), courseId);
        if (it != assignedCourseIds.end()) {
            assignedCourseIds.erase(it);
        }
    }
    
    // Check if course is assigned
    bool isCourseAssigned(const std::string& courseId) const {
        return std::find(assignedCourseIds.begin(), assignedCourseIds.end(), courseId) 
               != assignedCourseIds.end();
    }
    
    // Get number of assigned courses
    int getAssignedCoursesCount() const {
        return assignedCourseIds.size();
    }
    
    // Convert assigned courses to string (comma-separated)
    std::string getAssignedCoursesString() const {
        std::string result;
        for (size_t i = 0; i < assignedCourseIds.size(); i++) {
            result += assignedCourseIds[i];
            if (i < assignedCourseIds.size() - 1) {
                result += ",";
            }
        }
        return result;
    }
    
    // Parse assigned courses from string
    void parseAssignedCourses(const std::string& coursesStr) {
        assignedCourseIds.clear();
        std::stringstream ss(coursesStr);
        std::string courseId;
        while (std::getline(ss, courseId, ',')) {
            if (!courseId.empty()) {
                assignedCourseIds.push_back(courseId);
            }
        }
    }
    
    // Serialize to string
    std::string serialize() const override {
        std::vector<std::string> fields = {
            professorId, getUsername(), getPassword(), getFirstName(), getLastName(),
            getEmail(), getPhone(), getAddress(), getDateOfBirth(), getRegistrationDate(),
            std::to_string(static_cast<int>(getUserType())), getIsActive() ? "1" : "0",
            facultyId, departmentId, specialization, academicRank,
            officeLocation, officeHours, std::to_string(salary),
            hireDate, contractType, getAssignedCoursesString()
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize from string
    void deserialize(const std::string& data) override {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 22) {
            professorId = fields[0];
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
            facultyId = fields[12];
            departmentId = fields[13];
            specialization = fields[14];
            academicRank = fields[15];
            officeLocation = fields[16];
            officeHours = fields[17];
            salary = FileHandler::toDouble(fields[18]);
            hireDate = fields[19];
            contractType = fields[20];
            parseAssignedCourses(fields[21]);
        }
    }
};

#endif // PROFESSOR_H
