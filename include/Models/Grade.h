#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <vector>
#include "../Config.h"
#include "../Services/FileHandler.h"
#include "../Utils/GradeCalculator.h"

class Grade {
private:
    std::string gradeId;
    std::string studentId;
    std::string courseId;
    std::string professorId;
    Config::CourseType courseType;
    double assignment1;
    double assignment2;
    double courseWork;
    double finalExam;
    double totalGrade;
    double percentage;
    std::string letterGrade;
    std::string evaluation;
    std::string academicYear;
    int semester;
    std::string dateRecorded;
    bool isFinalized;

public:
    // Default constructor
    Grade() : courseType(Config::CourseType::THEORETICAL), assignment1(0), 
              assignment2(0), courseWork(0), finalExam(0), totalGrade(0),
              percentage(0), semester(1), isFinalized(false) {}
    
    // Parameterized constructor
    Grade(const std::string& studId, const std::string& crsId, Config::CourseType type)
        : studentId(studId), courseId(crsId), courseType(type),
          assignment1(0), assignment2(0), courseWork(0), finalExam(0),
          totalGrade(0), percentage(0), semester(1), isFinalized(false) {}
    
    // Getters
    std::string getGradeId() const { return gradeId; }
    std::string getStudentId() const { return studentId; }
    std::string getCourseId() const { return courseId; }
    std::string getProfessorId() const { return professorId; }
    Config::CourseType getCourseType() const { return courseType; }
    double getAssignment1() const { return assignment1; }
    double getAssignment2() const { return assignment2; }
    double getCourseWork() const { return courseWork; }
    double getFinalExam() const { return finalExam; }
    double getTotalGrade() const { return totalGrade; }
    double getPercentage() const { return percentage; }
    std::string getLetterGrade() const { return letterGrade; }
    std::string getEvaluation() const { return evaluation; }
    std::string getAcademicYear() const { return academicYear; }
    int getSemester() const { return semester; }
    std::string getDateRecorded() const { return dateRecorded; }
    bool getIsFinalized() const { return isFinalized; }
    
    // Setters
    void setGradeId(const std::string& id) { gradeId = id; }
    void setStudentId(const std::string& id) { studentId = id; }
    void setCourseId(const std::string& id) { courseId = id; }
    void setProfessorId(const std::string& id) { professorId = id; }
    void setCourseType(Config::CourseType type) { courseType = type; }
    void setAcademicYear(const std::string& year) { academicYear = year; }
    void setSemester(int sem) { semester = sem; }
    void setDateRecorded(const std::string& date) { dateRecorded = date; }
    void setIsFinalized(bool finalized) { isFinalized = finalized; }
    
    // Set individual grades with max validation
    
    
    // Calculate total grade and update evaluation
    void calculateTotal() {
        // Sum up all components directly (they are already weighted)
        totalGrade = assignment1 + assignment2 + courseWork + finalExam;
        
        // Calculate percentage
        double maxGrade = (courseType == Config::CourseType::PRACTICAL_150) ? 150.0 : 100.0;
        percentage = (totalGrade / maxGrade) * 100.0;
        
        // Get letter grade and evaluation
        letterGrade = GradeCalculator::getLetterGrade(percentage);
        evaluation = GradeCalculator::getGradeEvaluation(percentage);
    }
    
    // Get max marks for each component
    GradeCalculator::GradeComponents getMaxMarks() const {
        return GradeCalculator::getMaxMarks(courseType);
    }
    
    // Check if passed
    bool isPassed() const {
        return GradeCalculator::isPassed(percentage);
    }
    
    // Get GPA points for this course
    double getGPAPoints() const {
        return GradeCalculator::getGPAPoints(percentage);
    }
    
    // Serialize to string
    std::string serialize() const {
        std::vector<std::string> fields = {
            gradeId, studentId, courseId, professorId,
            std::to_string(static_cast<int>(courseType)),
            std::to_string(assignment1), std::to_string(assignment2),
            std::to_string(courseWork), std::to_string(finalExam),
            std::to_string(totalGrade), std::to_string(percentage),
            letterGrade, evaluation, academicYear, std::to_string(semester),
            dateRecorded, isFinalized ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize from string
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 17) {
            gradeId = fields[0];
            studentId = fields[1];
            courseId = fields[2];
            professorId = fields[3];
            courseType = static_cast<Config::CourseType>(FileHandler::toInt(fields[4]));
            assignment1 = FileHandler::toDouble(fields[5]);
            assignment2 = FileHandler::toDouble(fields[6]);
            courseWork = FileHandler::toDouble(fields[7]);
            finalExam = FileHandler::toDouble(fields[8]);
            totalGrade = FileHandler::toDouble(fields[9]);
            percentage = FileHandler::toDouble(fields[10]);
            letterGrade = fields[11];
            evaluation = fields[12];
            academicYear = fields[13];
            semester = FileHandler::toInt(fields[14]);
            dateRecorded = fields[15];
            isFinalized = fields[16] == "1";
        }
    }
};

#endif // GRADE_H
