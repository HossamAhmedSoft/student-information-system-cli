#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Config {
    // Application Info
    const std::string APP_NAME = "University Student Information System";
    const std::string APP_VERSION = "1.0.0";
    const std::string COMPANY_NAME = "Integrated Solutions Company";
    
    // Data File Paths
    const std::string DATA_DIR = "data/";
    const std::string USERS_FILE = DATA_DIR + "users.dat";
    const std::string STUDENTS_FILE = DATA_DIR + "students.dat";
    const std::string PROFESSORS_FILE = DATA_DIR + "professors.dat";
    const std::string COURSES_FILE = DATA_DIR + "courses.dat";
    const std::string GRADES_FILE = DATA_DIR + "grades.dat";
    const std::string ATTENDANCE_FILE = DATA_DIR + "attendance.dat";
    const std::string SCHEDULES_FILE = DATA_DIR + "schedules.dat";
    const std::string FACULTIES_FILE = DATA_DIR + "faculties.dat";
    const std::string DEPARTMENTS_FILE = DATA_DIR + "departments.dat";
    const std::string LECTURE_HALLS_FILE = DATA_DIR + "lecture_halls.dat";
    const std::string LABORATORIES_FILE = DATA_DIR + "laboratories.dat";
    const std::string FEES_FILE = DATA_DIR + "fees.dat";
    const std::string ACADEMIC_YEARS_FILE = DATA_DIR + "academic_years.dat";
    const std::string ENROLLMENTS_FILE = DATA_DIR + "enrollments.dat";
    const std::string EQUIPMENT_FILE = DATA_DIR + "equipment.dat";
    const std::string CALENDAR_FILE = DATA_DIR + "calendar.dat";
    
    // User Types
    enum class UserType {
        STUDENT = 1,
        PROFESSOR = 2,
        ADMIN = 3
    };
    
    // Course Types
    enum class CourseType {
        PRACTICAL_150 = 1,  // Practical courses graded out of 150
        PRACTICAL_100 = 2,  // Practical courses graded out of 100 (Big Data, Database, MS Office)
        THEORETICAL = 3     // Theoretical courses graded out of 100
    };
    
    // Grade Distribution for Practical Courses (150 or 100 marks)
    namespace PracticalGrades {
        const double ASS1_PERCENT = 0.20;  // 20%
        const double ASS2_PERCENT = 0.30;  // 30%
        const double CW_PERCENT = 0.20;    // 20%
        const double FINAL_PERCENT = 0.30; // 30%
    }
    
    // Grade Distribution for Theoretical Courses (100 marks)
    namespace TheoreticalGrades {
        const double ASS1_PERCENT = 0.20;  // 20%
        const double ASS2_PERCENT = 0.20;  // 20%
        const double CW_PERCENT = 0.60;    // 60%
        const double FINAL_PERCENT = 0.00; // No final exam
    }
    
    // Grade Evaluation Thresholds (percentage)
    namespace GradeEvaluation {
        const double EXCELLENT = 85.0;
        const double VERY_GOOD = 75.0;
        const double GOOD = 65.0;
        const double PASS = 60.0;
    }
    
    // GPA Scale (4.0 scale)
    namespace GPAScale {
        const double EXCELLENT = 4.0;
        const double VERY_GOOD = 3.5;
        const double GOOD = 3.0;
        const double PASS = 2.0;
        const double FAIL = 0.0;
    }
    
    // Academic Levels
    const int MAX_ACADEMIC_LEVELS = 4;
    
    // Default Admin Credentials
    const std::string DEFAULT_ADMIN_USERNAME = "admin";
    const std::string DEFAULT_ADMIN_PASSWORD = "admin123";
}

#endif // CONFIG_H
