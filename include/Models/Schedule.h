#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <vector>
#include "../Services/FileHandler.h"

class Schedule {
private:
    std::string scheduleId;
    std::string courseId;
    std::string professorId;
    std::string roomId;       // Can be lecture hall or lab ID
    std::string dayOfWeek;    // Monday, Tuesday, etc.
    std::string startTime;
    std::string endTime;
    std::string scheduleType; // Lecture, Lab, Tutorial
    std::string academicYear;
    int semester;
    bool isActive;

public:
    // Default constructor
    Schedule() : semester(1), isActive(true) {}
    
    // Parameterized constructor
    Schedule(const std::string& crsId, const std::string& day, 
             const std::string& start, const std::string& end)
        : courseId(crsId), dayOfWeek(day), startTime(start), endTime(end),
          semester(1), isActive(true) {}
    
    // Getters
    std::string getScheduleId() const { return scheduleId; }
    std::string getCourseId() const { return courseId; }
    std::string getProfessorId() const { return professorId; }
    std::string getRoomId() const { return roomId; }
    std::string getDayOfWeek() const { return dayOfWeek; }
    std::string getStartTime() const { return startTime; }
    std::string getEndTime() const { return endTime; }
    std::string getScheduleType() const { return scheduleType; }
    std::string getAcademicYear() const { return academicYear; }
    int getSemester() const { return semester; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setScheduleId(const std::string& id) { scheduleId = id; }
    void setCourseId(const std::string& id) { courseId = id; }
    void setProfessorId(const std::string& id) { professorId = id; }
    void setRoomId(const std::string& id) { roomId = id; }
    void setDayOfWeek(const std::string& day) { dayOfWeek = day; }
    void setStartTime(const std::string& time) { startTime = time; }
    void setEndTime(const std::string& time) { endTime = time; }
    void setScheduleType(const std::string& type) { scheduleType = type; }
    void setAcademicYear(const std::string& year) { academicYear = year; }
    void setSemester(int sem) { semester = sem; }
    void setIsActive(bool active) { isActive = active; }
    
    // Get time slot string
    std::string getTimeSlot() const {
        return startTime + " - " + endTime;
    }
    
    // Get full schedule string
    std::string getFullScheduleString() const {
        return dayOfWeek + " " + getTimeSlot() + " (" + scheduleType + ")";
    }
    
    // Serialize to string
    std::string serialize() const {
        std::vector<std::string> fields = {
            scheduleId, courseId, professorId, roomId, dayOfWeek,
            startTime, endTime, scheduleType, academicYear,
            std::to_string(semester), isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize from string
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 11) {
            scheduleId = fields[0];
            courseId = fields[1];
            professorId = fields[2];
            roomId = fields[3];
            dayOfWeek = fields[4];
            startTime = fields[5];
            endTime = fields[6];
            scheduleType = fields[7];
            academicYear = fields[8];
            semester = FileHandler::toInt(fields[9]);
            isActive = fields[10] == "1";
        }
    }
};

// Academic Calendar Event
class CalendarEvent {
private:
    std::string eventId;
    std::string eventName;
    std::string eventType;    // Holiday, Exam Period, Registration, etc.
    std::string startDate;
    std::string endDate;
    std::string description;
    std::string academicYear;
    int semester;

public:
    CalendarEvent() : semester(0) {}
    
    // Getters
    std::string getEventId() const { return eventId; }
    std::string getEventName() const { return eventName; }
    std::string getEventType() const { return eventType; }
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }
    std::string getDescription() const { return description; }
    std::string getAcademicYear() const { return academicYear; }
    int getSemester() const { return semester; }
    
    // Setters
    void setEventId(const std::string& id) { eventId = id; }
    void setEventName(const std::string& name) { eventName = name; }
    void setEventType(const std::string& type) { eventType = type; }
    void setStartDate(const std::string& date) { startDate = date; }
    void setEndDate(const std::string& date) { endDate = date; }
    void setDescription(const std::string& desc) { description = desc; }
    void setAcademicYear(const std::string& year) { academicYear = year; }
    void setSemester(int sem) { semester = sem; }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            eventId, eventName, eventType, startDate, endDate,
            description, academicYear, std::to_string(semester)
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 8) {
            eventId = fields[0];
            eventName = fields[1];
            eventType = fields[2];
            startDate = fields[3];
            endDate = fields[4];
            description = fields[5];
            academicYear = fields[6];
            semester = FileHandler::toInt(fields[7]);
        }
    }
};

#endif // SCHEDULE_H
