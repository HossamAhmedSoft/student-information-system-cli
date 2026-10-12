#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "../Config.h"
#include "../Services/FileHandler.h"

class Course {
private:
    std::string courseId;
    std::string courseName;
    std::string courseDescription;
    std::string departmentId;
    Config::CourseType courseType;
    int maxMarks;              // 150 for practical, 100 for others
    int creditHours;
    std::string prerequisiteCourseId;
    std::string instructorId;
    int academicLevel;         // Which year level (1-4)
    int semester;              // 1 or 2
    std::string academicYear;  // e.g., "2024-2025"
    bool isActive;

public:
    // Default constructor
    Course() : courseType(Config::CourseType::THEORETICAL), maxMarks(100), 
               creditHours(3), academicLevel(1), semester(1), isActive(true) {}
    
    // Parameterized constructor
    Course(const std::string& id, const std::string& name, Config::CourseType type)
        : courseId(id), courseName(name), courseType(type), creditHours(3),
          academicLevel(1), semester(1), isActive(true) {
        maxMarks = (type == Config::CourseType::PRACTICAL_150) ? 150 : 100;
    }
    
    // Getters
    std::string getCourseId() const { return courseId; }
    std::string getCourseName() const { return courseName; }
    std::string getCourseDescription() const { return courseDescription; }
    std::string getDepartmentId() const { return departmentId; }
    Config::CourseType getCourseType() const { return courseType; }
    int getMaxMarks() const { return maxMarks; }
    int getCreditHours() const { return creditHours; }
    std::string getPrerequisiteCourseId() const { return prerequisiteCourseId; }
    std::string getInstructorId() const { return instructorId; }
    int getAcademicLevel() const { return academicLevel; }
    int getSemester() const { return semester; }
    std::string getAcademicYear() const { return academicYear; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setCourseId(const std::string& id) { courseId = id; }
    void setCourseName(const std::string& name) { courseName = name; }
    void setCourseDescription(const std::string& desc) { courseDescription = desc; }
    void setDepartmentId(const std::string& id) { departmentId = id; }
    void setCourseType(Config::CourseType type) { 
        courseType = type;
        maxMarks = (type == Config::CourseType::PRACTICAL_150) ? 150 : 100;
    }
    void setMaxMarks(int marks) { maxMarks = marks; }
    void setCreditHours(int hours) { creditHours = hours; }
    void setPrerequisiteCourseId(const std::string& id) { prerequisiteCourseId = id; }
    void setInstructorId(const std::string& id) { instructorId = id; }
    void setAcademicLevel(int level) { academicLevel = level; }
    void setSemester(int sem) { semester = sem; }
    void setAcademicYear(const std::string& year) { academicYear = year; }
    void setIsActive(bool active) { isActive = active; }
    
    // Get course type as string
    std::string getCourseTypeString() const {
        switch (courseType) {
            case Config::CourseType::PRACTICAL_150: return "Practical (150)";
            case Config::CourseType::PRACTICAL_100: return "Practical (100)";
            case Config::CourseType::THEORETICAL: return "Theoretical";
            default: return "Unknown";
        }
    }
    
    // Get curriculum structure
    std::string getCurriculumStructure() const {
        if (courseType == Config::CourseType::THEORETICAL) {
            return "Theoretical";
        }
        return "Practical";
    }
    
    // Serialize to string
    std::string serialize() const {
        std::vector<std::string> fields = {
            courseId, courseName, courseDescription, departmentId,
            std::to_string(static_cast<int>(courseType)), std::to_string(maxMarks),
            std::to_string(creditHours), prerequisiteCourseId, instructorId,
            std::to_string(academicLevel), std::to_string(semester), academicYear,
            isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize from string
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 13) {
            courseId = fields[0];
            courseName = fields[1];
            courseDescription = fields[2];
            departmentId = fields[3];
            courseType = static_cast<Config::CourseType>(FileHandler::toInt(fields[4]));
            maxMarks = FileHandler::toInt(fields[5]);
            creditHours = FileHandler::toInt(fields[6]);
            prerequisiteCourseId = fields[7];
            instructorId = fields[8];
            academicLevel = FileHandler::toInt(fields[9]);
            semester = FileHandler::toInt(fields[10]);
            academicYear = fields[11];
            isActive = fields[12] == "1";
        }
    }
};

#endif // COURSE_H
