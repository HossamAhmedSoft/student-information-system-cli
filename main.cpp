/*
 * University Student Information System (SIS)
 * Main Application Entry Point
 * Developed by: Integrated Solutions Company
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

#include "include/Config.h"
#include "include/Utils/ConsoleUI.h"
#include "include/Utils/Validators.h"
#include "include/Utils/GradeCalculator.h"
#include "include/Services/FileHandler.h"
#include "include/Services/AuthService.h"
#include "include/Services/DataService.h"

using namespace std;
using namespace ConsoleUI;

// Forward declarations
void showMainMenu();
void showStudentPortal();
void showProfessorPortal();
void showAdminPortal();
void loginScreen();

// Get current date string
string getCurrentDate() {
    time_t now = time(0);
    
    return "string(buffer)";
}

// Generate unique ID
int idCounter = 1000;
string generateId(const string& prefix) {
    return prefix + to_string(++idCounter);
}

// ==================== STUDENT PORTAL ====================

void viewStudentProfile() {
    Student* student = AuthService::getInstance()->getCurrentStudent();
    if (!student) return;
    
    printHeader("MY PROFILE");
    
    cout << "  Student ID    : " << student->getStudentId() << endl;
    cout << "  Name          : " << student->getFullName() << endl;
    cout << "  Email         : " << student->getEmail() << endl;
    cout << "  Phone         : " << student->getPhone() << endl;
    cout << "  Academic Level: " << student->getAcademicLevelString() << endl;
    cout << "  Group         : " << student->getGroupNumber() << endl;
    cout << "  Section       : " << student->getSectionNumber() << endl;
    cout << "  GPA           : " << fixed << setprecision(2) << student->getGPA() << endl;
    cout << "  Status        : " << student->getEnrollmentStatus() << endl;
    
    waitForKey();
}

void viewStudentGrades() {
    Student* student = AuthService::getInstance()->getCurrentStudent();
    if (!student) return;
    
    printHeader("MY GRADES");
    
    vector<Grade> grades = DataService::getGradesByStudent(student->getStudentId());
    
    if (grades.empty()) {
        printInfo("No grades recorded yet.");
    } else {
        vector<pair<string, int>> headers = {
            {"Course", 15}, {"Ass1", 8}, {"Ass2", 8}, {"CW", 8}, 
            {"Final", 8}, {"Total", 8}, {"%", 8}, {"Grade", 10}
        };
        printTableHeader(headers);
        
        for (const auto& grade : grades) {
            Course* course = DataService::getCourseById(grade.getCourseId());
            string courseName = course ? course->getCourseName() : grade.getCourseId();
            if (course) delete course;
            
            vector<pair<string, int>> row = {
                {courseName.substr(0, 14), 15},
                {to_string((int)grade.getAssignment1()), 8},
                {to_string((int)grade.getAssignment2()), 8},
                {to_string((int)grade.getCourseWork()), 8},
                {to_string((int)grade.getFinalExam()), 8},
                {to_string((int)grade.getTotalGrade()), 8},
                {to_string((int)grade.getPercentage()) + "%", 8},
                {grade.getEvaluation(), 10}
            };
            printTableRow(row);
        }
        
        cout << "\n  Cumulative GPA: " << fixed << setprecision(2) 
             << DataService::calculateStudentGPA(student->getStudentId()) << endl;
    }
    
    waitForKey();
}

void viewStudentSchedule() {
    Student* student = AuthService::getInstance()->getCurrentStudent();
    if (!student) return;
    
    printHeader("MY SCHEDULE");
    
    vector<Enrollment> enrollments = DataService::getEnrollmentsByStudent(student->getStudentId());
    
    if (enrollments.empty()) {
        printInfo("No courses enrolled.");
    } else {
        for (const auto& enr : enrollments) {
            Course* course = DataService::getCourseById(enr.getCourseId());
            if (course) {
                cout << "\n  Course: " << course->getCourseName() << " (" << course->getCourseId() << ")" << endl;
                
                vector<Schedule> schedules = DataService::getSchedulesByCourse(course->getCourseId());
                for (const auto& sch : schedules) {
                    cout << "    " << sch.getDayOfWeek() << " " << sch.getTimeSlot() 
                         << " - " << sch.getScheduleType() << endl;
                }
                delete course;
            }
        }
    }
    
    waitForKey();
}

void viewStudentFees() {
    Student* student = AuthService::getInstance()->getCurrentStudent();
    if (!student) return;
    
    printHeader("MY TUITION FEES");
    
    cout << "  Total Fees    : $" << fixed << setprecision(2) << student->getTotalFees() << endl;
    cout << "  Amount Paid   : $" << student->getFeesPaid() << endl;
    cout << "  Balance Due   : $" << student->getFeesRemaining() << endl;
    cout << "  Payment Status: " << (student->isFeesFullyPaid() ? "PAID" : "PENDING") << endl;
    cout << "  Payment %     : " << student->getPaymentPercentage() << "%" << endl;
    
    waitForKey();
}

void viewStudentAttendance() {
    Student* student = AuthService::getInstance()->getCurrentStudent();
    if (!student) return;
    
    printHeader("MY ATTENDANCE");
    
    vector<Enrollment> enrollments = DataService::getEnrollmentsByStudent(student->getStudentId());
    
    for (const auto& enr : enrollments) {
        Course* course = DataService::getCourseById(enr.getCourseId());
        if (course) {
            AttendanceSummary summary = DataService::getAttendanceSummary(
                student->getStudentId(), course->getCourseId());
            
            cout << "\n  " << course->getCourseName() << endl;
            cout << "    Present: " << summary.presentCount 
                 << " | Absent: " << summary.absentCount
                 << " | Rate: " << fixed << setprecision(1) 
                 << summary.attendancePercentage << "%" << endl;
            delete course;
        }
    }
    
    waitForKey();
}

void showStudentPortal() {
    while (true) {
        printHeader("STUDENT PORTAL - " + AuthService::getInstance()->getCurrentUser()->getFullName());
        
        printMenuOption(1, "View My Profile");
        printMenuOption(2, "View My Grades & GPA");
        printMenuOption(3, "View My Schedule");
        printMenuOption(4, "View Tuition Fees");
        printMenuOption(5, "View Attendance");
        printMenuOption(0, "Logout");
        
        int choice = getIntInput("Select option", 0, 5);
        
        switch (choice) {
            case 1: viewStudentProfile(); break;
            case 2: viewStudentGrades(); break;
            case 3: viewStudentSchedule(); break;
            case 4: viewStudentFees(); break;
            case 5: viewStudentAttendance(); break;
            case 0: return;
        }
    }
}

// ==================== PROFESSOR PORTAL ====================

void manageStudentGrades() {
    Professor* prof = AuthService::getInstance()->getCurrentProfessor();
    if (!prof) return;
    
    printHeader("MANAGE STUDENT GRADES");
    
    vector<Course> courses = DataService::getCoursesByProfessor(prof->getProfessorId());
    
    if (courses.empty()) {
        printInfo("No courses assigned.");
        waitForKey();
        return;
    }
    
    cout << "  Your Courses:" << endl;
    for (size_t i = 0; i < courses.size(); i++) {
        cout << "  [" << (i+1) << "] " << courses[i].getCourseName() << endl;
    }
    
    int courseChoice = getIntInput("Select course", 1, courses.size());
    Course& selectedCourse = courses[courseChoice - 1];
    
    printSubHeader("Students in " + selectedCourse.getCourseName());
    
    vector<Enrollment> enrollments = DataService::getEnrollmentsByCourse(selectedCourse.getCourseId());
    
    if (enrollments.empty()) {
        printInfo("No students enrolled.");
        waitForKey();
        return;
    }
    
    for (size_t i = 0; i < enrollments.size(); i++) {
        Student* student = DataService::getStudentById(enrollments[i].getStudentId());
        if (student) {
            cout << "  [" << (i+1) << "] " << student->getFullName() 
                 << " (" << student->getStudentId() << ")" << endl;
            delete student;
        }
    }
    
    int studentChoice = getIntInput("Select student", 1, enrollments.size());
    string studentId = enrollments[studentChoice - 1].getStudentId();
    
    // Get or create grade
    Grade* existingGrade = DataService::getGrade(studentId, selectedCourse.getCourseId());
    Grade grade;
    
    if (existingGrade) {
        grade = *existingGrade;
        delete existingGrade;
    } else {
        grade.setGradeId(generateId("GRD"));
        grade.setStudentId(studentId);
        grade.setCourseId(selectedCourse.getCourseId());
        grade.setProfessorId(prof->getProfessorId());
        grade.setCourseType(selectedCourse.getCourseType());
    }
    
    GradeCalculator::GradeComponents maxMarks = grade.getMaxMarks();
    
    printSubHeader("Enter Grades (Current values shown)");
    
    cout << "  Course Type: " << selectedCourse.getCourseTypeString() << endl;
    cout << "  Max Marks - Ass1: " << maxMarks.assignment1 
         << ", Ass2: " << maxMarks.assignment2
         << ", CW: " << maxMarks.courseWork
         << ", Final: " << maxMarks.finalExam << endl;
    
   
    
    grade.setDateRecorded(getCurrentDate());
    
    if (DataService::saveGrade(grade)) {
        DataService::updateStudentGPA(studentId);
        printSuccess("Grade saved! Total: " + to_string((int)grade.getTotalGrade()) + 
                    " (" + grade.getEvaluation() + ")");
    } else {
        printError("Failed to save grade.");
    }
    
    waitForKey();
}

void manageAttendance() {
    Professor* prof = AuthService::getInstance()->getCurrentProfessor();
    if (!prof) return;
    
    printHeader("MANAGE ATTENDANCE");
    
    vector<Course> courses = DataService::getCoursesByProfessor(prof->getProfessorId());
    
    if (courses.empty()) {
        printInfo("No courses assigned.");
        waitForKey();
        return;
    }
    
    cout << "  Your Courses:" << endl;
    for (size_t i = 0; i < courses.size(); i++) {
        cout << "  [" << (i+1) << "] " << courses[i].getCourseName() << endl;
    }
    
    int courseChoice = getIntInput("Select course", 1, courses.size());
    Course& selectedCourse = courses[courseChoice - 1];
    
    string lectureNum = getInput("Lecture Number");
    string date = getCurrentDate();
    
    vector<Enrollment> enrollments = DataService::getEnrollmentsByCourse(selectedCourse.getCourseId());
    
    printSubHeader("Mark Attendance for " + date);
    
    for (const auto& enr : enrollments) {
        Student* student = DataService::getStudentById(enr.getStudentId());
        if (student) {
            bool present = confirm(student->getFullName() + " - Present?");
            
            Attendance att;
            att.setAttendanceId(generateId("ATT"));
            att.setStudentId(student->getStudentId());
            att.setCourseId(selectedCourse.getCourseId());
            att.setProfessorId(prof->getProfessorId());
            att.setDate(date);
            att.setLectureNumber(lectureNum);
            att.setIsPresent(present);
            
            DataService::saveAttendance(att);
            delete student;
        }
    }
    
    printSuccess("Attendance recorded!");
    waitForKey();
}

void viewAssignedCourses() {
    Professor* prof = AuthService::getInstance()->getCurrentProfessor();
    if (!prof) return;
    
    printHeader("MY ASSIGNED COURSES");
    
    vector<Course> courses = DataService::getCoursesByProfessor(prof->getProfessorId());
    
    if (courses.empty()) {
        printInfo("No courses assigned.");
    } else {
        for (const auto& course : courses) {
            cout << "\n  " << course.getCourseName() << " (" << course.getCourseId() << ")" << endl;
            cout << "    Type: " << course.getCourseTypeString() << endl;
            cout << "    Credits: " << course.getCreditHours() << endl;
            cout << "    Level: " << course.getAcademicLevel() << endl;
        }
    }
    
    waitForKey();
}

void viewAcademicCalendar() {
    printHeader("ACADEMIC CALENDAR");
    
    vector<CalendarEvent> events = DataService::getAllCalendarEvents();
    
    if (events.empty()) {
        printInfo("No calendar events.");
    } else {
        for (const auto& event : events) {
            cout << "\n  " << event.getEventName() << endl;
            cout << "    Type: " << event.getEventType() << endl;
            cout << "    Date: " << event.getStartDate() << " - " << event.getEndDate() << endl;
            cout << "    " << event.getDescription() << endl;
        }
    }
    
    waitForKey();
}

void showProfessorPortal() {
    while (true) {
        printHeader("PROFESSOR PORTAL - " + AuthService::getInstance()->getCurrentUser()->getFullName());
        
        printMenuOption(1, "Manage Student Grades");
        printMenuOption(2, "Manage Attendance");
        printMenuOption(3, "View Assigned Courses");
        printMenuOption(4, "View Academic Calendar");
        printMenuOption(5, "View My Schedule");
        printMenuOption(0, "Logout");
        
        int choice = getIntInput("Select option", 0, 5);
        
        switch (choice) {
            case 1: manageStudentGrades(); break;
            case 2: manageAttendance(); break;
            case 3: viewAssignedCourses(); break;
            case 4: viewAcademicCalendar(); break;
            case 5: {
                Professor* prof = AuthService::getInstance()->getCurrentProfessor();
                vector<Schedule> schedules = DataService::getSchedulesByProfessor(prof->getProfessorId());
                printHeader("MY SCHEDULE");
                for (const auto& sch : schedules) {
                    cout << "  " << sch.getFullScheduleString() << endl;
                }
                waitForKey();
                break;
            }
            case 0: return;
        }
    }
}

// ==================== ADMIN PORTAL ====================

void manageStudents() {
    while (true) {
        printHeader("STUDENT MANAGEMENT");
        
        printMenuOption(1, "View All Students");
        printMenuOption(2, "Add New Student");
        printMenuOption(3, "Update Student");
        printMenuOption(4, "Delete Student");
        printMenuOption(0, "Back");
        
        int choice = getIntInput("Select option", 0, 4);
        
        if (choice == 0) return;
        
        if (choice == 1) {
            vector<Student> students = DataService::getAllStudents();
            printSubHeader("All Students (" + to_string(students.size()) + ")");
            
            for (const auto& s : students) {
                cout << "  " << s.getStudentId() << " - " << s.getFullName() 
                     << " (Level " << s.getAcademicLevel() << ", GPA: " 
                     << fixed << setprecision(2) << s.getGPA() << ")" << endl;
            }
            waitForKey();
        }
        else if (choice == 2) {
            printSubHeader("Add New Student");
            
            Student student;
            int nextId = DataService::getNextStudentId();
            string studentId = "STU" + string(3 - to_string(nextId).length(), '0') + to_string(nextId);
            
            student.setStudentId(studentId);
            student.setUsername(getInput("Username"));
            student.setPassword(getInput("Password"));
            student.setFirstName(getInput("First Name"));
            student.setLastName(getInput("Last Name"));
            student.setEmail(getInput("Email"));
            student.setPhone(getInput("Phone"));
            student.setAcademicLevel(getIntInput("Academic Level (1-4)", 1, 4));
            student.setGroupNumber(getInput("Group Number"));
            student.setSectionNumber(getInput("Section Number"));
            student.setTotalFees(getDoubleInput("Total Fees", 0, 100000));
            student.setRegistrationDate(getCurrentDate());
            
            if (DataService::saveStudent(student)) {
                printSuccess("Student added with ID: " + studentId);
            } else {
                printError("Failed to add student.");
            }
            waitForKey();
        }
        else if (choice == 3) {
            string id = getInput("Enter Student ID to update");
            Student* student = DataService::getStudentById(id);
            
            if (student) {
                printSubHeader("Update Student: " + student->getFullName());
                
                string newPhone = getInput("Phone (" + student->getPhone() + ")");
                if (!newPhone.empty()) student->setPhone(newPhone);
                
                string newEmail = getInput("Email (" + student->getEmail() + ")");
                if (!newEmail.empty()) student->setEmail(newEmail);
                
                int newLevel = getIntInput("Level (current: " + to_string(student->getAcademicLevel()) + ")", 1, 4);
                student->setAcademicLevel(newLevel);
                
                if (DataService::saveStudent(*student)) {
                    printSuccess("Student updated.");
                } else {
                    printError("Failed to update.");
                }
                delete student;
            } else {
                printError("Student not found.");
            }
            waitForKey();
        }
        else if (choice == 4) {
            string id = getInput("Enter Student ID to delete");
            if (confirm("Are you sure?")) {
                if (DataService::deleteStudent(id)) {
                    printSuccess("Student deleted.");
                } else {
                    printError("Failed to delete.");
                }
            }
            waitForKey();
        }
    }
}

void manageProfessors() {
    while (true) {
        printHeader("PROFESSOR MANAGEMENT");
        
        printMenuOption(1, "View All Professors");
        printMenuOption(2, "Add New Professor");
        printMenuOption(3, "Assign Course to Professor");
        printMenuOption(0, "Back");
        
        int choice = getIntInput("Select option", 0, 3);
        
        if (choice == 0) return;
        
        if (choice == 1) {
            vector<Professor> profs = DataService::getAllProfessors();
            printSubHeader("All Professors");
            
            for (const auto& p : profs) {
                cout << "  " << p.getProfessorId() << " - " << p.getFullName() 
                     << " (" << p.getAcademicRank() << ")" << endl;
            }
            waitForKey();
        }
        else if (choice == 2) {
            printSubHeader("Add New Professor");
            
            Professor prof;
            int nextId = DataService::getNextProfessorId();
            string profId = "PROF" + string(3 - to_string(nextId).length(), '0') + to_string(nextId);
            
            prof.setProfessorId(profId);
            prof.setUsername(getInput("Username"));
            prof.setPassword(getInput("Password"));
            prof.setFirstName(getInput("First Name"));
            prof.setLastName(getInput("Last Name"));
            prof.setEmail(getInput("Email"));
            prof.setAcademicRank(getInput("Academic Rank"));
            prof.setSpecialization(getInput("Specialization"));
            prof.setRegistrationDate(getCurrentDate());
            
            if (DataService::saveProfessor(prof)) {
                printSuccess("Professor added with ID: " + profId);
            } else {
                printError("Failed to add professor.");
            }
            waitForKey();
        }
        else if (choice == 3) {
            string profId = getInput("Professor ID");
            string courseId = getInput("Course ID");
            
            Course* course = DataService::getCourseById(courseId);
            if (course) {
                course->setInstructorId(profId);
                DataService::saveCourse(*course);
                printSuccess("Course assigned.");
                delete course;
            } else {
                printError("Course not found.");
            }
            waitForKey();
        }
    }
}

void manageCourses() {
    while (true) {
        printHeader("COURSE MANAGEMENT");
        
        printMenuOption(1, "View All Courses");
        printMenuOption(2, "Add New Course");
        printMenuOption(3, "Delete Course");
        printMenuOption(0, "Back");
        
        int choice = getIntInput("Select option", 0, 3);
        
        if (choice == 0) return;
        
        if (choice == 1) {
            vector<Course> courses = DataService::getAllCourses();
            for (const auto& c : courses) {
                cout << "\n  " << c.getCourseId() << " - " << c.getCourseName() << endl;
                cout << "    Type: " << c.getCourseTypeString() 
                     << " | Credits: " << c.getCreditHours() << endl;
            }
            waitForKey();
        }
        else if (choice == 2) {
            Course course;
            course.setCourseId(getInput("Course ID"));
            course.setCourseName(getInput("Course Name"));
            course.setCourseDescription(getInput("Description"));
            
            cout << "  Course Type:" << endl;
            cout << "  [1] Practical (150 marks)" << endl;
            cout << "  [2] Practical (100 marks - Big Data/DB/Office)" << endl;
            cout << "  [3] Theoretical (100 marks)" << endl;
            
            int typeChoice = getIntInput("Select type", 1, 3);
            course.setCourseType(static_cast<Config::CourseType>(typeChoice));
            course.setCreditHours(getIntInput("Credit Hours", 1, 6));
            course.setAcademicLevel(getIntInput("Academic Level", 1, 4));
            
            if (DataService::saveCourse(course)) {
                printSuccess("Course added.");
            }
            waitForKey();
        }
        else if (choice == 3) {
            string id = getInput("Course ID to delete");
            if (confirm("Delete course?") && DataService::deleteCourse(id)) {
                printSuccess("Deleted.");
            }
            waitForKey();
        }
    }
}

void manageFacilities() {
    while (true) {
        printHeader("FACILITIES MANAGEMENT");
        
        printMenuOption(1, "Manage Lecture Halls");
        printMenuOption(2, "Manage Laboratories");
        printMenuOption(3, "Manage Faculties");
        printMenuOption(4, "Manage Departments");
        printMenuOption(0, "Back");
        
        int choice = getIntInput("Select option", 0, 4);
        
        if (choice == 0) return;
        
        if (choice == 1) {
            printSubHeader("Lecture Halls");
            printMenuOption(1, "View All");
            printMenuOption(2, "Add New");
            
            int subChoice = getIntInput("Option", 1, 2);
            
            if (subChoice == 1) {
                vector<LectureHall> halls = DataService::getAllLectureHalls();
                for (const auto& h : halls) {
                    cout << "\n  " << h.getHallCode() << " - " << h.getHallName() << endl;
                    cout << "    Capacity: " << h.getCapacity() << " students" << endl;
                    cout << "    Building: " << h.getBuildingName() << ", Floor: " << h.getFloor() << endl;
                    cout << "    Equipment: Seats(" << h.getTotalSeating() << "), AC(" 
                         << h.getTotalAC() << "), Fans(" << h.getTotalFans() << "), Lights(" 
                         << h.getTotalLighting() << ")" << endl;
                }
            }
            else if (subChoice == 2) {
                LectureHall hall;
                hall.setHallId(generateId("HALL"));
                hall.setHallCode(getInput("Hall Code"));
                hall.setHallName(getInput("Hall Name"));
                hall.setBuildingName(getInput("Building Name"));
                hall.setFloor(getInput("Floor"));
                hall.setCapacity(getIntInput("Capacity", 1, 500));
                hall.setDescription(getInput("Description"));
                
                // Add equipment specs
                int numAC = getIntInput("Number of AC units", 0, 20);
                if (numAC > 0) {
                    EquipmentSpec ac;
                    ac.productId = generateId("AC");
                    ac.productName = "Air Conditioner";
                    ac.productDescription = "Central cooling system";
                    ac.category = "AC";
                    ac.quantity = numAC;
                    hall.addAirConditioning(ac);
                }
                
                int numFans = getIntInput("Number of fans", 0, 50);
                if (numFans > 0) {
                    EquipmentSpec fan;
                    fan.productId = generateId("FAN");
                    fan.productName = "Ceiling Fan";
                    fan.productDescription = "Ceiling mounted fan";
                    fan.category = "Fans";
                    fan.quantity = numFans;
                    hall.addFan(fan);
                }
                
                int numLights = getIntInput("Number of lights", 0, 100);
                if (numLights > 0) {
                    EquipmentSpec light;
                    light.productId = generateId("LGT");
                    light.productName = "LED Light";
                    light.productDescription = "LED tube light";
                    light.category = "Lighting";
                    light.quantity = numLights;
                    hall.addLighting(light);
                }
                
                if (DataService::saveLectureHall(hall)) {
                    printSuccess("Lecture Hall added.");
                }
            }
            waitForKey();
        }
        else if (choice == 2) {
            printSubHeader("Laboratories");
            printMenuOption(1, "View All");
            printMenuOption(2, "Add New");
            
            int subChoice = getIntInput("Option", 1, 2);
            
            if (subChoice == 1) {
                vector<Laboratory> labs = DataService::getAllLaboratories();
                for (const auto& l : labs) {
                    cout << "\n  " << l.getLabCode() << " - " << l.getLabName() << endl;
                    cout << "    Type: " << l.getLabType() << endl;
                    cout << "    Capacity: " << l.getCapacity() << ", Computers: " << l.getNumComputers() << endl;
                }
            }
            else if (subChoice == 2) {
                Laboratory lab;
                lab.setLabId(generateId("LAB"));
                lab.setLabCode(getInput("Lab Code"));
                lab.setLabName(getInput("Lab Name"));
                lab.setLabType(getInput("Lab Type (Computer/Physics/Chemistry)"));
                lab.setBuildingName(getInput("Building Name"));
                lab.setCapacity(getIntInput("Capacity", 1, 100));
                lab.setNumComputers(getIntInput("Number of Computers", 0, 100));
                lab.setNumSeats(getIntInput("Number of Seats", 1, 100));
                
                if (DataService::saveLaboratory(lab)) {
                    printSuccess("Laboratory added.");
                }
            }
            waitForKey();
        }
        else if (choice == 3) {
            printSubHeader("Faculties");
            vector<Faculty> faculties = DataService::getAllFaculties();
            for (const auto& f : faculties) {
                cout << "  " << f.getFacultyCode() << " - " << f.getFacultyName() << endl;
            }
            
            if (confirm("Add new faculty?")) {
                Faculty fac;
                fac.setFacultyId(generateId("FAC"));
                fac.setFacultyCode(getInput("Faculty Code"));
                fac.setFacultyName(getInput("Faculty Name"));
                fac.setLocation(getInput("Location"));
                DataService::saveFaculty(fac);
                printSuccess("Faculty added.");
            }
            waitForKey();
        }
        else if (choice == 4) {
            printSubHeader("Departments");
            vector<Department> depts = DataService::getAllDepartments();
            for (const auto& d : depts) {
                cout << "  " << d.getDepartmentCode() << " - " << d.getDepartmentName() << endl;
            }
            
            if (confirm("Add new department?")) {
                Department dept;
                dept.setDepartmentId(generateId("DEP"));
                dept.setDepartmentCode(getInput("Department Code"));
                dept.setDepartmentName(getInput("Department Name"));
                dept.setFacultyId(getInput("Faculty ID"));
                DataService::saveDepartment(dept);
                printSuccess("Department added.");
            }
            waitForKey();
        }
    }
}

void manageAcademicYears() {
    printHeader("ACADEMIC YEARS");
    
    vector<AcademicYear> years = DataService::getAllAcademicYears();
    for (const auto& y : years) {
        cout << "  " << y.getYearName() << (y.getIsCurrent() ? " [CURRENT]" : "") << endl;
    }
    
    if (confirm("Add new academic year?")) {
        AcademicYear year;
        year.setYearId(generateId("AY"));
        year.setYearName(getInput("Year Name (e.g., 2024-2025)"));
        year.setStartDate(getInput("Start Date (DD/MM/YYYY)"));
        year.setEndDate(getInput("End Date (DD/MM/YYYY)"));
        year.setIsCurrent(confirm("Is this the current year?"));
        
        DataService::saveAcademicYear(year);
        printSuccess("Academic year added.");
    }
    
    waitForKey();
}

void manageFees() {
    printHeader("FEE MANAGEMENT");
    
    vector<FeeStructure> fees = DataService::getAllFeeStructures();
    for (const auto& f : fees) {
        cout << "  Level " << f.getAcademicLevel() << ": $" << f.getTotalFee() << endl;
    }
    
    if (confirm("Add/Update fee structure?")) {
        FeeStructure fee;
        fee.setFeeStructureId(generateId("FEE"));
        fee.setAcademicYear(getInput("Academic Year"));
        fee.setAcademicLevel(getIntInput("Academic Level", 1, 4));
        fee.setTuitionFee(getDoubleInput("Tuition Fee", 0, 50000));
        fee.setRegistrationFee(getDoubleInput("Registration Fee", 0, 1000));
        fee.setLibraryFee(getDoubleInput("Library Fee", 0, 500));
        fee.setLabFee(getDoubleInput("Lab Fee", 0, 1000));
        
        DataService::saveFeeStructure(fee);
        printSuccess("Fee structure saved.");
    }
    
    waitForKey();
}

void showAdminPortal() {
    while (true) {
        printHeader("ADMINISTRATION PORTAL");
        
        printMenuOption(1, "Manage Students");
        printMenuOption(2, "Manage Professors");
        printMenuOption(3, "Manage Courses");
        printMenuOption(4, "Manage Facilities (Halls/Labs)");
        printMenuOption(5, "Manage Academic Years");
        printMenuOption(6, "Manage Fees");
        printMenuOption(0, "Logout");
        
        int choice = getIntInput("Select option", 0, 6);
        
        switch (choice) {
            case 1: manageStudents(); break;
            case 2: manageProfessors(); break;
            case 3: manageCourses(); break;
            case 4: manageFacilities(); break;
            case 5: manageAcademicYears(); break;
            case 6: manageFees(); break;
            case 0: return;
        }
    }
}

// ==================== LOGIN & MAIN ====================

void loginScreen() {
    printHeader("LOGIN");
    
    string username = getInput("Username");
    string password = getPasswordInput("Password");
    
    if (AuthService::getInstance()->login(username, password)) {
        printSuccess("Login successful!");
        
        switch (AuthService::getInstance()->getCurrentUserType()) {
            case Config::UserType::STUDENT:
                showStudentPortal();
                break;
            case Config::UserType::PROFESSOR:
                showProfessorPortal();
                break;
            case Config::UserType::ADMIN:
                showAdminPortal();
                break;
        }
        
        AuthService::getInstance()->logout();
    } else {
        printError("Invalid username or password.");
        waitForKey();
    }
}

void showMainMenu() {
    while (true) {
        printWelcomeBanner(Config::APP_NAME, Config::APP_VERSION);
        
        setColor(Color::DARK_GRAY);
        printCentered(Config::COMPANY_NAME);
        resetColor();
        cout << endl;
        
        printMenuOption(1, "Login");
        printMenuOption(0, "Exit");
        
        int choice = getIntInput("Select option", 0, 1);
        
        if (choice == 0) {
            printGoodbye();
            break;
        }
        
        loginScreen();
    }
}

int main() {
    // Initialize system
    FileHandler::ensureDataDirectory(Config::DATA_DIR);
    AuthService::getInstance()->initializeDefaultAdmin();
    
    // Run main menu
    showMainMenu();
    
    return 0;
}
