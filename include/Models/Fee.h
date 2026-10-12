#ifndef FEE_H
#define FEE_H

#include <string>
#include <vector>
#include "../Services/FileHandler.h"

// Fee structure for different academic levels/programs
class FeeStructure {
private:
    std::string feeStructureId;
    std::string academicYear;
    std::string facultyId;
    std::string departmentId;
    int academicLevel;
    double tuitionFee;
    double registrationFee;
    double libraryFee;
    double labFee;
    double technologyFee;
    double activityFee;
    double totalFee;
    std::string description;
    bool isActive;

public:
    FeeStructure() : academicLevel(1), tuitionFee(0), registrationFee(0),
                     libraryFee(0), labFee(0), technologyFee(0), activityFee(0),
                     totalFee(0), isActive(true) {}
    
    // Getters
    std::string getFeeStructureId() const { return feeStructureId; }
    std::string getAcademicYear() const { return academicYear; }
    std::string getFacultyId() const { return facultyId; }
    std::string getDepartmentId() const { return departmentId; }
    int getAcademicLevel() const { return academicLevel; }
    double getTuitionFee() const { return tuitionFee; }
    double getRegistrationFee() const { return registrationFee; }
    double getLibraryFee() const { return libraryFee; }
    double getLabFee() const { return labFee; }
    double getTechnologyFee() const { return technologyFee; }
    double getActivityFee() const { return activityFee; }
    double getTotalFee() const { return totalFee; }
    std::string getDescription() const { return description; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setFeeStructureId(const std::string& id) { feeStructureId = id; }
    void setAcademicYear(const std::string& year) { academicYear = year; }
    void setFacultyId(const std::string& id) { facultyId = id; }
    void setDepartmentId(const std::string& id) { departmentId = id; }
    void setAcademicLevel(int level) { academicLevel = level; }
    void setTuitionFee(double fee) { tuitionFee = fee; calculateTotal(); }
    void setRegistrationFee(double fee) { registrationFee = fee; calculateTotal(); }
    void setLibraryFee(double fee) { libraryFee = fee; calculateTotal(); }
    void setLabFee(double fee) { labFee = fee; calculateTotal(); }
    void setTechnologyFee(double fee) { technologyFee = fee; calculateTotal(); }
    void setActivityFee(double fee) { activityFee = fee; calculateTotal(); }
    void setDescription(const std::string& desc) { description = desc; }
    void setIsActive(bool active) { isActive = active; }
    
    // Calculate total fee
    void calculateTotal() {
        totalFee = tuitionFee + registrationFee + libraryFee + 
                   labFee + technologyFee + activityFee;
    }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            feeStructureId, academicYear, facultyId, departmentId,
            std::to_string(academicLevel), std::to_string(tuitionFee),
            std::to_string(registrationFee), std::to_string(libraryFee),
            std::to_string(labFee), std::to_string(technologyFee),
            std::to_string(activityFee), std::to_string(totalFee),
            description, isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 14) {
            feeStructureId = fields[0];
            academicYear = fields[1];
            facultyId = fields[2];
            departmentId = fields[3];
            academicLevel = FileHandler::toInt(fields[4]);
            tuitionFee = FileHandler::toDouble(fields[5]);
            registrationFee = FileHandler::toDouble(fields[6]);
            libraryFee = FileHandler::toDouble(fields[7]);
            labFee = FileHandler::toDouble(fields[8]);
            technologyFee = FileHandler::toDouble(fields[9]);
            activityFee = FileHandler::toDouble(fields[10]);
            totalFee = FileHandler::toDouble(fields[11]);
            description = fields[12];
            isActive = fields[13] == "1";
        }
    }
};

// Payment record for student fees
class FeePayment {
private:
    std::string paymentId;
    std::string studentId;
    std::string feeStructureId;
    double amountPaid;
    std::string paymentDate;
    std::string paymentMethod;   // Cash, Card, Bank Transfer, Online
    std::string receiptNumber;
    std::string notes;
    std::string processedBy;     // Admin ID

public:
    FeePayment() : amountPaid(0) {}
    
    // Getters
    std::string getPaymentId() const { return paymentId; }
    std::string getStudentId() const { return studentId; }
    std::string getFeeStructureId() const { return feeStructureId; }
    double getAmountPaid() const { return amountPaid; }
    std::string getPaymentDate() const { return paymentDate; }
    std::string getPaymentMethod() const { return paymentMethod; }
    std::string getReceiptNumber() const { return receiptNumber; }
    std::string getNotes() const { return notes; }
    std::string getProcessedBy() const { return processedBy; }
    
    // Setters
    void setPaymentId(const std::string& id) { paymentId = id; }
    void setStudentId(const std::string& id) { studentId = id; }
    void setFeeStructureId(const std::string& id) { feeStructureId = id; }
    void setAmountPaid(double amount) { amountPaid = amount; }
    void setPaymentDate(const std::string& date) { paymentDate = date; }
    void setPaymentMethod(const std::string& method) { paymentMethod = method; }
    void setReceiptNumber(const std::string& receipt) { receiptNumber = receipt; }
    void setNotes(const std::string& n) { notes = n; }
    void setProcessedBy(const std::string& id) { processedBy = id; }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            paymentId, studentId, feeStructureId, std::to_string(amountPaid),
            paymentDate, paymentMethod, receiptNumber, notes, processedBy
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 9) {
            paymentId = fields[0];
            studentId = fields[1];
            feeStructureId = fields[2];
            amountPaid = FileHandler::toDouble(fields[3]);
            paymentDate = fields[4];
            paymentMethod = fields[5];
            receiptNumber = fields[6];
            notes = fields[7];
            processedBy = fields[8];
        }
    }
};

// Academic Year structure
class AcademicYear {
private:
    std::string yearId;
    std::string yearName;       // e.g., "2024-2025"
    std::string startDate;
    std::string endDate;
    bool isCurrent;
    bool isActive;

public:
    AcademicYear() : isCurrent(false), isActive(true) {}
    
    // Getters
    std::string getYearId() const { return yearId; }
    std::string getYearName() const { return yearName; }
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }
    bool getIsCurrent() const { return isCurrent; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setYearId(const std::string& id) { yearId = id; }
    void setYearName(const std::string& name) { yearName = name; }
    void setStartDate(const std::string& date) { startDate = date; }
    void setEndDate(const std::string& date) { endDate = date; }
    void setIsCurrent(bool current) { isCurrent = current; }
    void setIsActive(bool active) { isActive = active; }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            yearId, yearName, startDate, endDate,
            isCurrent ? "1" : "0", isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 6) {
            yearId = fields[0];
            yearName = fields[1];
            startDate = fields[2];
            endDate = fields[3];
            isCurrent = fields[4] == "1";
            isActive = fields[5] == "1";
        }
    }
};

#endif // FEE_H
