#ifndef DATA_SERVICE_H
#define DATA_SERVICE_H

#include <string>
#include <vector>
#include <algorithm>
#include "../Config.h"
#include "../Models/Student.h"
#include "../Models/Professor.h"
#include "../Models/Admin.h"
#include "../Models/Course.h"
#include "../Models/Grade.h"
#include "../Models/Attendance.h"
#include "../Models/Schedule.h"
#include "../Models/Faculty.h"
#include "../Models/Department.h"
#include "../Models/LectureHall.h"
#include "../Models/Laboratory.h"
#include "../Models/Fee.h"
#include "../Models/Enrollment.h"
#include "FileHandler.h"

class DataService {
public:
    // ==================== STUDENT OPERATIONS ====================
    
    static std::vector<Student> getAllStudents() {
        std::vector<Student> students;
        std::vector<std::string> records = FileHandler::readAllLines(Config::STUDENTS_FILE);
        for (const auto& record : records) {
            Student student;
            student.deserialize(record);
            students.push_back(student);
        }
        return students;
    }
    
    static Student* getStudentById(const std::string& studentId) {
        std::string record = FileHandler::findRecord(Config::STUDENTS_FILE, studentId);
        if (!record.empty()) {
            Student* student = new Student();
            student->deserialize(record);
            return student;
        }
        return nullptr;
    }
    
    static bool saveStudent(const Student& student) {
        std::string record = FileHandler::findRecord(Config::STUDENTS_FILE, student.getStudentId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::STUDENTS_FILE, student.serialize());
        } else {
            return FileHandler::updateRecord(Config::STUDENTS_FILE, student.getStudentId(), student.serialize());
        }
    }
    
    static bool deleteStudent(const std::string& studentId) {
        return FileHandler::deleteRecord(Config::STUDENTS_FILE, studentId);
    }
    
    static int getNextStudentId() {
        std::vector<Student> students = getAllStudents();
        int maxId = 0;
        for (const auto& student : students) {
            std::string id = student.getStudentId();
            if (id.substr(0, 3) == "STU") {
                int num = FileHandler::toInt(id.substr(3));
                if (num > maxId) maxId = num;
            }
        }
        return maxId + 1;
    }
    
    // ==================== PROFESSOR OPERATIONS ====================
    
    static std::vector<Professor> getAllProfessors() {
        std::vector<Professor> professors;
        std::vector<std::string> records = FileHandler::readAllLines(Config::PROFESSORS_FILE);
        for (const auto& record : records) {
            Professor professor;
            professor.deserialize(record);
            professors.push_back(professor);
        }
        return professors;
    }
    
    static Professor* getProfessorById(const std::string& professorId) {
        std::string record = FileHandler::findRecord(Config::PROFESSORS_FILE, professorId);
        if (!record.empty()) {
            Professor* professor = new Professor();
            professor->deserialize(record);
            return professor;
        }
        return nullptr;
    }
    
    static bool saveProfessor(const Professor& professor) {
        std::string record = FileHandler::findRecord(Config::PROFESSORS_FILE, professor.getProfessorId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::PROFESSORS_FILE, professor.serialize());
        } else {
            return FileHandler::updateRecord(Config::PROFESSORS_FILE, professor.getProfessorId(), professor.serialize());
        }
    }
    
    static bool deleteProfessor(const std::string& professorId) {
        return FileHandler::deleteRecord(Config::PROFESSORS_FILE, professorId);
    }
    
    static int getNextProfessorId() {
        std::vector<Professor> professors = getAllProfessors();
        int maxId = 0;
        for (const auto& prof : professors) {
            std::string id = prof.getProfessorId();
            if (id.substr(0, 4) == "PROF") {
                int num = FileHandler::toInt(id.substr(4));
                if (num > maxId) maxId = num;
            }
        }
        return maxId + 1;
    }
    
    // ==================== COURSE OPERATIONS ====================
    
    static std::vector<Course> getAllCourses() {
        std::vector<Course> courses;
        std::vector<std::string> records = FileHandler::readAllLines(Config::COURSES_FILE);
        for (const auto& record : records) {
            Course course;
            course.deserialize(record);
            courses.push_back(course);
        }
        return courses;
    }
    
    static Course* getCourseById(const std::string& courseId) {
        std::string record = FileHandler::findRecord(Config::COURSES_FILE, courseId);
        if (!record.empty()) {
            Course* course = new Course();
            course->deserialize(record);
            return course;
        }
        return nullptr;
    }
    
    static bool saveCourse(const Course& course) {
        std::string record = FileHandler::findRecord(Config::COURSES_FILE, course.getCourseId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::COURSES_FILE, course.serialize());
        } else {
            return FileHandler::updateRecord(Config::COURSES_FILE, course.getCourseId(), course.serialize());
        }
    }
    
    static bool deleteCourse(const std::string& courseId) {
        return FileHandler::deleteRecord(Config::COURSES_FILE, courseId);
    }
    
    static std::vector<Course> getCoursesByProfessor(const std::string& professorId) {
        std::vector<Course> courses = getAllCourses();
        std::vector<Course> result;
        for (const auto& course : courses) {
            if (course.getInstructorId() == professorId) {
                result.push_back(course);
            }
        }
        return result;
    }
    
    // ==================== GRADE OPERATIONS ====================
    
    static std::vector<Grade> getAllGrades() {
        std::vector<Grade> grades;
        std::vector<std::string> records = FileHandler::readAllLines(Config::GRADES_FILE);
        for (const auto& record : records) {
            Grade grade;
            grade.deserialize(record);
            grades.push_back(grade);
        }
        return grades;
    }
    
    static std::vector<Grade> getGradesByStudent(const std::string& studentId) {
        std::vector<Grade> grades = getAllGrades();
        std::vector<Grade> result;
        for (const auto& grade : grades) {
            if (grade.getStudentId() == studentId) {
                result.push_back(grade);
            }
        }
        return result;
    }
    
    static std::vector<Grade> getGradesByCourse(const std::string& courseId) {
        std::vector<Grade> grades = getAllGrades();
        std::vector<Grade> result;
        for (const auto& grade : grades) {
            if (grade.getCourseId() == courseId) {
                result.push_back(grade);
            }
        }
        return result;
    }
    
    static Grade* getGrade(const std::string& studentId, const std::string& courseId) {
        std::vector<Grade> grades = getAllGrades();
        for (const auto& grade : grades) {
            if (grade.getStudentId() == studentId && grade.getCourseId() == courseId) {
                Grade* result = new Grade();
                *result = grade;
                return result;
            }
        }
        return nullptr;
    }
    
    static bool saveGrade(const Grade& grade) {
        std::string record = FileHandler::findRecord(Config::GRADES_FILE, grade.getGradeId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::GRADES_FILE, grade.serialize());
        } else {
            return FileHandler::updateRecord(Config::GRADES_FILE, grade.getGradeId(), grade.serialize());
        }
    }
    
    static bool deleteGrade(const std::string& gradeId) {
        return FileHandler::deleteRecord(Config::GRADES_FILE, gradeId);
    }
    
    // ==================== ATTENDANCE OPERATIONS ====================
    
    static std::vector<Attendance> getAllAttendance() {
        std::vector<Attendance> attendances;
        std::vector<std::string> records = FileHandler::readAllLines(Config::ATTENDANCE_FILE);
        for (const auto& record : records) {
            Attendance attendance;
            attendance.deserialize(record);
            attendances.push_back(attendance);
        }
        return attendances;
    }
    
    static std::vector<Attendance> getAttendanceByStudent(const std::string& studentId) {
        std::vector<Attendance> attendances = getAllAttendance();
        std::vector<Attendance> result;
        for (const auto& att : attendances) {
            if (att.getStudentId() == studentId) {
                result.push_back(att);
            }
        }
        return result;
    }
    
    static std::vector<Attendance> getAttendanceByCourse(const std::string& courseId) {
        std::vector<Attendance> attendances = getAllAttendance();
        std::vector<Attendance> result;
        for (const auto& att : attendances) {
            if (att.getCourseId() == courseId) {
                result.push_back(att);
            }
        }
        return result;
    }
    
    static AttendanceSummary getAttendanceSummary(const std::string& studentId, const std::string& courseId) {
        AttendanceSummary summary;
        summary.studentId = studentId;
        summary.courseId = courseId;
        
        std::vector<Attendance> attendances = getAllAttendance();
        for (const auto& att : attendances) {
            if (att.getStudentId() == studentId && att.getCourseId() == courseId) {
                if (att.getIsPresent()) {
                    summary.presentCount++;
                } else {
                    summary.absentCount++;
                }
            }
        }
        summary.calculate();
        return summary;
    }
    
    static bool saveAttendance(const Attendance& attendance) {
        std::string record = FileHandler::findRecord(Config::ATTENDANCE_FILE, attendance.getAttendanceId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::ATTENDANCE_FILE, attendance.serialize());
        } else {
            return FileHandler::updateRecord(Config::ATTENDANCE_FILE, attendance.getAttendanceId(), attendance.serialize());
        }
    }
    
    // ==================== SCHEDULE OPERATIONS ====================
    
    static std::vector<Schedule> getAllSchedules() {
        std::vector<Schedule> schedules;
        std::vector<std::string> records = FileHandler::readAllLines(Config::SCHEDULES_FILE);
        for (const auto& record : records) {
            Schedule schedule;
            schedule.deserialize(record);
            schedules.push_back(schedule);
        }
        return schedules;
    }
    
    static std::vector<Schedule> getSchedulesByCourse(const std::string& courseId) {
        std::vector<Schedule> schedules = getAllSchedules();
        std::vector<Schedule> result;
        for (const auto& sch : schedules) {
            if (sch.getCourseId() == courseId) {
                result.push_back(sch);
            }
        }
        return result;
    }
    
    static std::vector<Schedule> getSchedulesByProfessor(const std::string& professorId) {
        std::vector<Schedule> schedules = getAllSchedules();
        std::vector<Schedule> result;
        for (const auto& sch : schedules) {
            if (sch.getProfessorId() == professorId) {
                result.push_back(sch);
            }
        }
        return result;
    }
    
    static bool saveSchedule(const Schedule& schedule) {
        std::string record = FileHandler::findRecord(Config::SCHEDULES_FILE, schedule.getScheduleId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::SCHEDULES_FILE, schedule.serialize());
        } else {
            return FileHandler::updateRecord(Config::SCHEDULES_FILE, schedule.getScheduleId(), schedule.serialize());
        }
    }
    
    // ==================== CALENDAR OPERATIONS ====================
    
    static std::vector<CalendarEvent> getAllCalendarEvents() {
        std::vector<CalendarEvent> events;
        std::vector<std::string> records = FileHandler::readAllLines(Config::CALENDAR_FILE);
        for (const auto& record : records) {
            CalendarEvent event;
            event.deserialize(record);
            events.push_back(event);
        }
        return events;
    }
    
    static bool saveCalendarEvent(const CalendarEvent& event) {
        std::string record = FileHandler::findRecord(Config::CALENDAR_FILE, event.getEventId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::CALENDAR_FILE, event.serialize());
        } else {
            return FileHandler::updateRecord(Config::CALENDAR_FILE, event.getEventId(), event.serialize());
        }
    }
    
    // ==================== FACULTY OPERATIONS ====================
    
    static std::vector<Faculty> getAllFaculties() {
        std::vector<Faculty> faculties;
        std::vector<std::string> records = FileHandler::readAllLines(Config::FACULTIES_FILE);
        for (const auto& record : records) {
            Faculty faculty;
            faculty.deserialize(record);
            faculties.push_back(faculty);
        }
        return faculties;
    }
    
    static Faculty* getFacultyById(const std::string& facultyId) {
        std::string record = FileHandler::findRecord(Config::FACULTIES_FILE, facultyId);
        if (!record.empty()) {
            Faculty* faculty = new Faculty();
            faculty->deserialize(record);
            return faculty;
        }
        return nullptr;
    }
    
    static bool saveFaculty(const Faculty& faculty) {
        std::string record = FileHandler::findRecord(Config::FACULTIES_FILE, faculty.getFacultyId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::FACULTIES_FILE, faculty.serialize());
        } else {
            return FileHandler::updateRecord(Config::FACULTIES_FILE, faculty.getFacultyId(), faculty.serialize());
        }
    }
    
    static bool deleteFaculty(const std::string& facultyId) {
        return FileHandler::deleteRecord(Config::FACULTIES_FILE, facultyId);
    }
    
    // ==================== DEPARTMENT OPERATIONS ====================
    
    static std::vector<Department> getAllDepartments() {
        std::vector<Department> departments;
        std::vector<std::string> records = FileHandler::readAllLines(Config::DEPARTMENTS_FILE);
        for (const auto& record : records) {
            Department dept;
            dept.deserialize(record);
            departments.push_back(dept);
        }
        return departments;
    }
    
    static std::vector<Department> getDepartmentsByFaculty(const std::string& facultyId) {
        std::vector<Department> departments = getAllDepartments();
        std::vector<Department> result;
        for (const auto& dept : departments) {
            if (dept.getFacultyId() == facultyId) {
                result.push_back(dept);
            }
        }
        return result;
    }
    
    static Department* getDepartmentById(const std::string& departmentId) {
        std::string record = FileHandler::findRecord(Config::DEPARTMENTS_FILE, departmentId);
        if (!record.empty()) {
            Department* dept = new Department();
            dept->deserialize(record);
            return dept;
        }
        return nullptr;
    }
    
    static bool saveDepartment(const Department& department) {
        std::string record = FileHandler::findRecord(Config::DEPARTMENTS_FILE, department.getDepartmentId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::DEPARTMENTS_FILE, department.serialize());
        } else {
            return FileHandler::updateRecord(Config::DEPARTMENTS_FILE, department.getDepartmentId(), department.serialize());
        }
    }
    
    static bool deleteDepartment(const std::string& departmentId) {
        return FileHandler::deleteRecord(Config::DEPARTMENTS_FILE, departmentId);
    }
    
    // ==================== LECTURE HALL OPERATIONS ====================
    
    static std::vector<LectureHall> getAllLectureHalls() {
        std::vector<LectureHall> halls;
        std::vector<std::string> records = FileHandler::readAllLines(Config::LECTURE_HALLS_FILE);
        for (const auto& record : records) {
            LectureHall hall;
            hall.deserialize(record);
            halls.push_back(hall);
        }
        return halls;
    }
    
    static LectureHall* getLectureHallById(const std::string& hallId) {
        std::string record = FileHandler::findRecord(Config::LECTURE_HALLS_FILE, hallId);
        if (!record.empty()) {
            LectureHall* hall = new LectureHall();
            hall->deserialize(record);
            return hall;
        }
        return nullptr;
    }
    
    static bool saveLectureHall(const LectureHall& hall) {
        std::string record = FileHandler::findRecord(Config::LECTURE_HALLS_FILE, hall.getHallId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::LECTURE_HALLS_FILE, hall.serialize());
        } else {
            return FileHandler::updateRecord(Config::LECTURE_HALLS_FILE, hall.getHallId(), hall.serialize());
        }
    }
    
    static bool deleteLectureHall(const std::string& hallId) {
        return FileHandler::deleteRecord(Config::LECTURE_HALLS_FILE, hallId);
    }
    
    // ==================== LABORATORY OPERATIONS ====================
    
    static std::vector<Laboratory> getAllLaboratories() {
        std::vector<Laboratory> labs;
        std::vector<std::string> records = FileHandler::readAllLines(Config::LABORATORIES_FILE);
        for (const auto& record : records) {
            Laboratory lab;
            lab.deserialize(record);
            labs.push_back(lab);
        }
        return labs;
    }
    
    static Laboratory* getLaboratoryById(const std::string& labId) {
        std::string record = FileHandler::findRecord(Config::LABORATORIES_FILE, labId);
        if (!record.empty()) {
            Laboratory* lab = new Laboratory();
            lab->deserialize(record);
            return lab;
        }
        return nullptr;
    }
    
    static bool saveLaboratory(const Laboratory& lab) {
        std::string record = FileHandler::findRecord(Config::LABORATORIES_FILE, lab.getLabId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::LABORATORIES_FILE, lab.serialize());
        } else {
            return FileHandler::updateRecord(Config::LABORATORIES_FILE, lab.getLabId(), lab.serialize());
        }
    }
    
    static bool deleteLaboratory(const std::string& labId) {
        return FileHandler::deleteRecord(Config::LABORATORIES_FILE, labId);
    }
    
    // ==================== FEE OPERATIONS ====================
    
    static std::vector<FeeStructure> getAllFeeStructures() {
        std::vector<FeeStructure> fees;
        std::vector<std::string> records = FileHandler::readAllLines(Config::FEES_FILE);
        for (const auto& record : records) {
            FeeStructure fee;
            fee.deserialize(record);
            fees.push_back(fee);
        }
        return fees;
    }
    
    static bool saveFeeStructure(const FeeStructure& fee) {
        std::string record = FileHandler::findRecord(Config::FEES_FILE, fee.getFeeStructureId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::FEES_FILE, fee.serialize());
        } else {
            return FileHandler::updateRecord(Config::FEES_FILE, fee.getFeeStructureId(), fee.serialize());
        }
    }
    
    // ==================== ACADEMIC YEAR OPERATIONS ====================
    
    static std::vector<AcademicYear> getAllAcademicYears() {
        std::vector<AcademicYear> years;
        std::vector<std::string> records = FileHandler::readAllLines(Config::ACADEMIC_YEARS_FILE);
        for (const auto& record : records) {
            AcademicYear year;
            year.deserialize(record);
            years.push_back(year);
        }
        return years;
    }
    
    static AcademicYear* getCurrentAcademicYear() {
        std::vector<AcademicYear> years = getAllAcademicYears();
        for (const auto& year : years) {
            if (year.getIsCurrent()) {
                AcademicYear* result = new AcademicYear();
                *result = year;
                return result;
            }
        }
        return nullptr;
    }
    
    static bool saveAcademicYear(const AcademicYear& year) {
        std::string record = FileHandler::findRecord(Config::ACADEMIC_YEARS_FILE, year.getYearId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::ACADEMIC_YEARS_FILE, year.serialize());
        } else {
            return FileHandler::updateRecord(Config::ACADEMIC_YEARS_FILE, year.getYearId(), year.serialize());
        }
    }
    
    // ==================== ENROLLMENT OPERATIONS ====================
    
    static std::vector<Enrollment> getAllEnrollments() {
        std::vector<Enrollment> enrollments;
        std::vector<std::string> records = FileHandler::readAllLines(Config::ENROLLMENTS_FILE);
        for (const auto& record : records) {
            Enrollment enrollment;
            enrollment.deserialize(record);
            enrollments.push_back(enrollment);
        }
        return enrollments;
    }
    
    static std::vector<Enrollment> getEnrollmentsByStudent(const std::string& studentId) {
        std::vector<Enrollment> enrollments = getAllEnrollments();
        std::vector<Enrollment> result;
        for (const auto& enr : enrollments) {
            if (enr.getStudentId() == studentId) {
                result.push_back(enr);
            }
        }
        return result;
    }
    
    static std::vector<Enrollment> getEnrollmentsByCourse(const std::string& courseId) {
        std::vector<Enrollment> enrollments = getAllEnrollments();
        std::vector<Enrollment> result;
        for (const auto& enr : enrollments) {
            if (enr.getCourseId() == courseId) {
                result.push_back(enr);
            }
        }
        return result;
    }
    
    static bool saveEnrollment(const Enrollment& enrollment) {
        std::string record = FileHandler::findRecord(Config::ENROLLMENTS_FILE, enrollment.getEnrollmentId());
        if (record.empty()) {
            return FileHandler::appendLine(Config::ENROLLMENTS_FILE, enrollment.serialize());
        } else {
            return FileHandler::updateRecord(Config::ENROLLMENTS_FILE, enrollment.getEnrollmentId(), enrollment.serialize());
        }
    }
    
    // ==================== UTILITY FUNCTIONS ====================
    
    static double calculateStudentGPA(const std::string& studentId) {
        std::vector<Grade> grades = getGradesByStudent(studentId);
        if (grades.empty()) return 0.0;
        
        std::vector<GradeCalculator::CourseGrade> courseGrades;
        for (const auto& grade : grades) {
            Course* course = getCourseById(grade.getCourseId());
            if (course != nullptr) {
                GradeCalculator::CourseGrade cg;
                cg.percentage = grade.getPercentage();
                cg.creditHours = course->getCreditHours();
                courseGrades.push_back(cg);
                delete course;
            }
        }
        
        return GradeCalculator::calculateGPA(courseGrades);
    }
    
    static void updateStudentGPA(const std::string& studentId) {
        Student* student = getStudentById(studentId);
        if (student != nullptr) {
            double gpa = calculateStudentGPA(studentId);
            student->setGPA(gpa);
            saveStudent(*student);
            delete student;
        }
    }
};

#endif // DATA_SERVICE_H
