#ifndef GRADE_CALCULATOR_H
#define GRADE_CALCULATOR_H

#include <string>
#include <vector>
#include "../Config.h"

namespace GradeCalculator {
    
    // Grade component structure
    struct GradeComponents {
        double assignment1;
        double assignment2;
        double courseWork;
        double finalExam;
    };
    
    // Calculate total grade for a course
    inline double calculateTotalGrade(const GradeComponents& components, Config::CourseType courseType) {
        double total = 0.0;
        double maxGrade = (courseType == Config::CourseType::PRACTICAL_150) ? 150.0 : 100.0;
        
        if (courseType == Config::CourseType::THEORETICAL) {
            // Theoretical: 20% Ass1, 20% Ass2, 60% CW, No Final
            total = components.assignment1 * Config::TheoreticalGrades::ASS1_PERCENT +
                    components.assignment2 * Config::TheoreticalGrades::ASS2_PERCENT +
                    components.courseWork * Config::TheoreticalGrades::CW_PERCENT;
        } else {
            // Practical (150 or 100): 20% Ass1, 30% Ass2, 20% CW, 30% Final
            total = components.assignment1 * Config::PracticalGrades::ASS1_PERCENT +
                    components.assignment2 * Config::PracticalGrades::ASS2_PERCENT +
                    components.courseWork * Config::PracticalGrades::CW_PERCENT +
                    components.finalExam * Config::PracticalGrades::FINAL_PERCENT;
        }
        
        return total;
    }
    
    // Calculate percentage from total grade
    inline double calculatePercentage(double totalGrade, Config::CourseType courseType) {
        double maxGrade = (courseType == Config::CourseType::PRACTICAL_150) ? 150.0 : 100.0;
        return (totalGrade / maxGrade) * 100.0;
    }
    
    // Get grade evaluation string
    inline std::string getGradeEvaluation(double percentage) {
        if (percentage >= Config::GradeEvaluation::EXCELLENT) return "Excellent";
        if (percentage >= Config::GradeEvaluation::VERY_GOOD) return "Very Good";
        if (percentage >= Config::GradeEvaluation::GOOD) return "Good";
        if (percentage >= Config::GradeEvaluation::PASS) return "Pass";
        return "Fail";
    }
    
    // Get letter grade
    inline std::string getLetterGrade(double percentage) {
        if (percentage >= 90) return "A+";
        if (percentage >= 85) return "A";
        if (percentage >= 80) return "B+";
        if (percentage >= 75) return "B";
        if (percentage >= 70) return "C+";
        if (percentage >= 65) return "C";
        if (percentage >= 60) return "D";
        return "F";
    }
    
    // Get GPA points for a grade
    inline double getGPAPoints(double percentage) {
        if (percentage >= Config::GradeEvaluation::EXCELLENT) return Config::GPAScale::EXCELLENT;
        if (percentage >= Config::GradeEvaluation::VERY_GOOD) return Config::GPAScale::VERY_GOOD;
        if (percentage >= Config::GradeEvaluation::GOOD) return Config::GPAScale::GOOD;
        if (percentage >= Config::GradeEvaluation::PASS) return Config::GPAScale::PASS;
        return Config::GPAScale::FAIL;
    }
    
    // Calculate GPA from multiple courses
    struct CourseGrade {
        double percentage;
        int creditHours;
    };
    
    inline double calculateGPA(const std::vector<CourseGrade>& grades) {
        if (grades.empty()) return 0.0;
        
        double totalPoints = 0.0;
        int totalCredits = 0;
        
        for (const auto& grade : grades) {
            double gpaPoints = getGPAPoints(grade.percentage);
            totalPoints += gpaPoints * grade.creditHours;
            totalCredits += grade.creditHours;
        }
        
        if (totalCredits == 0) return 0.0;
        return totalPoints / totalCredits;
    }
    
    // Calculate cumulative GPA
    inline double calculateCumulativeGPA(const std::vector<std::pair<double, int>>& semesterGPAs) {
        // Each pair contains (semester GPA, credit hours for that semester)
        if (semesterGPAs.empty()) return 0.0;
        
        double totalPoints = 0.0;
        int totalCredits = 0;
        
        for (const auto& semester : semesterGPAs) {
            totalPoints += semester.first * semester.second;
            totalCredits += semester.second;
        }
        
        if (totalCredits == 0) return 0.0;
        return totalPoints / totalCredits;
    }
    
    // Get max marks for each component based on course type
    inline GradeComponents getMaxMarks(Config::CourseType courseType) {
        GradeComponents max;
        double maxTotal = (courseType == Config::CourseType::PRACTICAL_150) ? 150.0 : 100.0;
        
        if (courseType == Config::CourseType::THEORETICAL) {
            max.assignment1 = maxTotal * Config::TheoreticalGrades::ASS1_PERCENT;  // 20
            max.assignment2 = maxTotal * Config::TheoreticalGrades::ASS2_PERCENT;  // 20
            max.courseWork = maxTotal * Config::TheoreticalGrades::CW_PERCENT;     // 60
            max.finalExam = 0;  // No final
        } else {
            max.assignment1 = maxTotal * Config::PracticalGrades::ASS1_PERCENT;
            max.assignment2 = maxTotal * Config::PracticalGrades::ASS2_PERCENT;
            max.courseWork = maxTotal * Config::PracticalGrades::CW_PERCENT;
            max.finalExam = maxTotal * Config::PracticalGrades::FINAL_PERCENT;
        }
        
        return max;
    }
    
    // Check if student passed the course
    inline bool isPassed(double percentage) {
        return percentage >= Config::GradeEvaluation::PASS;
    }
    
    // Get academic standing based on GPA
    inline std::string getAcademicStanding(double gpa) {
        if (gpa >= 3.7) return "Dean's List";
        if (gpa >= 3.0) return "Good Standing";
        if (gpa >= 2.0) return "Academic Warning";
        return "Academic Probation";
    }
}

#endif // GRADE_CALCULATOR_H
