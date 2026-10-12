#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
#include <vector>
#include "../Services/FileHandler.h"

class Attendance {
private:
    std::string attendanceId;
    std::string studentId;
    std::string courseId;
    std::string professorId;
    std::string date;
    std::string time;
    bool isPresent;
    std::string lectureNumber;
    std::string notes;

public:
    // Default constructor
    Attendance() : isPresent(true) {}
    
    // Parameterized constructor
    Attendance(const std::string& studId, const std::string& crsId, 
               const std::string& dt, bool present)
        : studentId(studId), courseId(crsId), date(dt), isPresent(present) {}
    
    // Getters
    std::string getAttendanceId() const { return attendanceId; }
    std::string getStudentId() const { return studentId; }
    std::string getCourseId() const { return courseId; }
    std::string getProfessorId() const { return professorId; }
    std::string getDate() const { return date; }
    std::string getTime() const { return time; }
    bool getIsPresent() const { return isPresent; }
    std::string getLectureNumber() const { return lectureNumber; }
    std::string getNotes() const { return notes; }
    
    // Setters
    void setAttendanceId(const std::string& id) { attendanceId = id; }
    void setStudentId(const std::string& id) { studentId = id; }
    void setCourseId(const std::string& id) { courseId = id; }
    void setProfessorId(const std::string& id) { professorId = id; }
    void setDate(const std::string& dt) { date = dt; }
    void setTime(const std::string& t) { time = t; }
    void setIsPresent(bool present) { isPresent = present; }
    void setLectureNumber(const std::string& num) { lectureNumber = num; }
    void setNotes(const std::string& n) { notes = n; }
    
    // Get status string
    std::string getStatusString() const {
        return isPresent ? "Present" : "Absent";
    }
    
    // Serialize to string
    std::string serialize() const {
        std::vector<std::string> fields = {
            attendanceId, studentId, courseId, professorId,
            date, time, isPresent ? "1" : "0", lectureNumber, notes
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize from string
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 9) {
            attendanceId = fields[0];
            studentId = fields[1];
            courseId = fields[2];
            professorId = fields[3];
            date = fields[4];
            time = fields[5];
            isPresent = fields[6] == "1";
            lectureNumber = fields[7];
            notes = fields[8];
        }
    }
};

// Attendance summary for a student in a course
struct AttendanceSummary {
    std::string studentId;
    std::string courseId;
    int totalLectures;
    int presentCount;
    int absentCount;
    double attendancePercentage;
    
    AttendanceSummary() : totalLectures(0), presentCount(0), absentCount(0), attendancePercentage(0) {}
    
    void calculate() {
        totalLectures = presentCount + absentCount;
        if (totalLectures > 0) {
            attendancePercentage = (static_cast<double>(presentCount) / totalLectures) * 100.0;
        }
    }
};

#endif // ATTENDANCE_H
