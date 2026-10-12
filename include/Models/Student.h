#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <vector>

class Student : public User {
private:
    std::string studentId;
    std::string facultyId;
    std::string departmentId;
    int academicLevel;      // 1, 2, 3, 4
    int academicYear;       // Enrollment year
    std::string groupNumber;
    std::string sectionNumber;
    double totalFees;
    double feesPaid;
    double gpa;
    int totalCredits;
    std::string enrollmentStatus;  // Active, Graduated, Suspended, Withdrawn
    std::string advisorId;

public:
    // Default constructor
    Student() : User(), academicLevel(1), academicYear(0), totalFees(0), 
                feesPaid(0), gpa(0), totalCredits(0), enrollmentStatus("Active") {
        setUserType(Config::UserType::STUDENT);
    }
    
    // Parameterized constructor
    Student(const std::string& id, const std::string& uname, const std::string& pwd,
            const std::string& fname, const std::string& lname)
        : User(id, uname, pwd, fname, lname, Config::UserType::STUDENT),
          academicLevel(1), academicYear(0), totalFees(0), feesPaid(0), 
          gpa(0), totalCredits(0), enrollmentStatus("Active") {
        studentId = id;
    }
    
    // Getters
    std::string getStudentId() const { return studentId; }
    std::string getFacultyId() const { return facultyId; }
    std::string getDepartmentId() const { return departmentId; }
    int getAcademicLevel() const { return academicLevel; }
    int getAcademicYear() const { return academicYear; }
    std::string getGroupNumber() const { return groupNumber; }
    std::string getSectionNumber() const { return sectionNumber; }
    double getTotalFees() const { return totalFees; }
    double getFeesPaid() const { return feesPaid; }
    double getFeesRemaining() const { return totalFees - feesPaid; }
    double getGPA() const { return gpa; }
    int getTotalCredits() const { return totalCredits; }
    std::string getEnrollmentStatus() const { return enrollmentStatus; }
    std::string getAdvisorId() const { return advisorId; }
    
    // Setters
    void setStudentId(const std::string& id) { studentId = id; setUserId(id); }
    void setFacultyId(const std::string& id) { facultyId = id; }
    void setDepartmentId(const std::string& id) { departmentId = id; }
    void setAcademicLevel(int level) { academicLevel = level; }
    void setAcademicYear(int year) { academicYear = year; }
    void setGroupNumber(const std::string& group) { groupNumber = group; }
    void setSectionNumber(const std::string& section) { sectionNumber = section; }
    void setTotalFees(double fees) { totalFees = fees; }
    void setFeesPaid(double paid) { feesPaid = paid; }
    void setGPA(double newGpa) { gpa = newGpa; }
    void setTotalCredits(int credits) { totalCredits = credits; }
    void setEnrollmentStatus(const std::string& status) { enrollmentStatus = status; }
    void setAdvisorId(const std::string& id) { advisorId = id; }
    
    // Add payment
    void addPayment(double amount) {
        feesPaid += amount;
        if (feesPaid > totalFees) feesPaid = totalFees;
    }
    
    // Check if fees are fully paid
    bool isFeesFullyPaid() const {
        return feesPaid >= totalFees;
    }
    
    // Get payment percentage
    double getPaymentPercentage() const {
        if (totalFees == 0) return 100.0;
        return (feesPaid / totalFees) * 100.0;
    }
    
    // Get academic level as string
    std::string getAcademicLevelString() const {
        switch (academicLevel) {
            case 1: return "Freshman";
            case 2: return "Sophomore";
            case 3: return "Junior";
            case 4: return "Senior";
            default: return "Unknown";
        }
    }
    
    // Serialize to string
    std::string serialize() const override {
        std::vector<std::string> fields = {
            studentId, getUsername(), getPassword(), getFirstName(), getLastName(),
            getEmail(), getPhone(), getAddress(), getDateOfBirth(), getRegistrationDate(),
            std::to_string(static_cast<int>(getUserType())), getIsActive() ? "1" : "0",
            facultyId, departmentId, std::to_string(academicLevel), std::to_string(academicYear),
            groupNumber, sectionNumber, std::to_string(totalFees), std::to_string(feesPaid),
            std::to_string(gpa), std::to_string(totalCredits), enrollmentStatus, advisorId
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize from string
    void deserialize(const std::string& data) override {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 24) {
            studentId = fields[0];
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
            academicLevel = FileHandler::toInt(fields[14]);
            academicYear = FileHandler::toInt(fields[15]);
            groupNumber = fields[16];
            sectionNumber = fields[17];
            totalFees = FileHandler::toDouble(fields[18]);
            feesPaid = FileHandler::toDouble(fields[19]);
            gpa = FileHandler::toDouble(fields[20]);
            totalCredits = FileHandler::toInt(fields[21]);
            enrollmentStatus = fields[22];
            advisorId = fields[23];
        }
    }
};

#endif // STUDENT_H
