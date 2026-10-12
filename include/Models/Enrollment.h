#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
#include <vector>
#include "../Services/FileHandler.h"

class Enrollment {
private:
    std::string enrollmentId;
    std::string studentId;
    std::string courseId;
    std::string academicYear;
    int semester;
    std::string enrollmentDate;
    std::string status;        // Enrolled, Completed, Dropped, Withdrawn
    std::string groupNumber;
    std::string sectionNumber;

public:
    Enrollment() : semester(1), status("Enrolled") {}
    
    Enrollment(const std::string& studId, const std::string& crsId, 
               const std::string& year, int sem)
        : studentId(studId), courseId(crsId), academicYear(year),
          semester(sem), status("Enrolled") {}
    
    // Getters
    std::string getEnrollmentId() const { return enrollmentId; }
    std::string getStudentId() const { return studentId; }
    std::string getCourseId() const { return courseId; }
    std::string getAcademicYear() const { return academicYear; }
    int getSemester() const { return semester; }
    std::string getEnrollmentDate() const { return enrollmentDate; }
    std::string getStatus() const { return status; }
    std::string getGroupNumber() const { return groupNumber; }
    std::string getSectionNumber() const { return sectionNumber; }
    
    // Setters
    void setEnrollmentId(const std::string& id) { enrollmentId = id; }
    void setStudentId(const std::string& id) { studentId = id; }
    void setCourseId(const std::string& id) { courseId = id; }
    void setAcademicYear(const std::string& year) { academicYear = year; }
    void setSemester(int sem) { semester = sem; }
    void setEnrollmentDate(const std::string& date) { enrollmentDate = date; }
    void setStatus(const std::string& stat) { status = stat; }
    void setGroupNumber(const std::string& group) { groupNumber = group; }
    void setSectionNumber(const std::string& section) { sectionNumber = section; }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            enrollmentId, studentId, courseId, academicYear,
            std::to_string(semester), enrollmentDate, status,
            groupNumber, sectionNumber
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 9) {
            enrollmentId = fields[0];
            studentId = fields[1];
            courseId = fields[2];
            academicYear = fields[3];
            semester = FileHandler::toInt(fields[4]);
            enrollmentDate = fields[5];
            status = fields[6];
            groupNumber = fields[7];
            sectionNumber = fields[8];
        }
    }
};

#endif // ENROLLMENT_H
