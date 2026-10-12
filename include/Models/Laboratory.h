#ifndef LABORATORY_H
#define LABORATORY_H

#include <string>
#include <vector>
#include <sstream>
#include "../Services/FileHandler.h"
#include "Equipment.h"

class Laboratory {
private:
    std::string labId;
    std::string labCode;
    std::string labName;
    std::string buildingName;
    std::string floor;
    std::string labType;              // Computer Lab, Physics Lab, Chemistry Lab, etc.
    int capacity;                      // Number of students
    int numComputers;
    int numSeats;
    std::vector<EquipmentSpec> airConditioning;
    std::vector<EquipmentSpec> fans;
    std::vector<EquipmentSpec> lighting;
    std::vector<EquipmentSpec> computers;  // Computer specs
    std::string description;
    std::string supervisorId;          // Professor/Staff ID
    bool isActive;
    bool isAvailable;

public:
    Laboratory() : capacity(0), numComputers(0), numSeats(0), 
                   isActive(true), isAvailable(true) {}
    
    Laboratory(const std::string& id, const std::string& code, 
               const std::string& name, int cap)
        : labId(id), labCode(code), labName(name), capacity(cap),
          numComputers(0), numSeats(cap), isActive(true), isAvailable(true) {}
    
    // Getters
    std::string getLabId() const { return labId; }
    std::string getLabCode() const { return labCode; }
    std::string getLabName() const { return labName; }
    std::string getBuildingName() const { return buildingName; }
    std::string getFloor() const { return floor; }
    std::string getLabType() const { return labType; }
    int getCapacity() const { return capacity; }
    int getNumComputers() const { return numComputers; }
    int getNumSeats() const { return numSeats; }
    std::vector<EquipmentSpec> getAirConditioning() const { return airConditioning; }
    std::vector<EquipmentSpec> getFans() const { return fans; }
    std::vector<EquipmentSpec> getLighting() const { return lighting; }
    std::vector<EquipmentSpec> getComputers() const { return computers; }
    std::string getDescription() const { return description; }
    std::string getSupervisorId() const { return supervisorId; }
    bool getIsActive() const { return isActive; }
    bool getIsAvailable() const { return isAvailable; }
    
    // Setters
    void setLabId(const std::string& id) { labId = id; }
    void setLabCode(const std::string& code) { labCode = code; }
    void setLabName(const std::string& name) { labName = name; }
    void setBuildingName(const std::string& bldg) { buildingName = bldg; }
    void setFloor(const std::string& fl) { floor = fl; }
    void setLabType(const std::string& type) { labType = type; }
    void setCapacity(int cap) { capacity = cap; }
    void setNumComputers(int num) { numComputers = num; }
    void setNumSeats(int num) { numSeats = num; }
    void setDescription(const std::string& desc) { description = desc; }
    void setSupervisorId(const std::string& id) { supervisorId = id; }
    void setIsActive(bool active) { isActive = active; }
    void setIsAvailable(bool available) { isAvailable = available; }
    
    // Equipment management
    void addAirConditioning(const EquipmentSpec& spec) { airConditioning.push_back(spec); }
    void addFan(const EquipmentSpec& spec) { fans.push_back(spec); }
    void addLighting(const EquipmentSpec& spec) { lighting.push_back(spec); }
    void addComputer(const EquipmentSpec& spec) { 
        computers.push_back(spec);
        numComputers += spec.quantity;
    }
    
    void clearAirConditioning() { airConditioning.clear(); }
    void clearFans() { fans.clear(); }
    void clearLighting() { lighting.clear(); }
    void clearComputers() { 
        computers.clear(); 
        numComputers = 0;
    }
    
    // Get total equipment counts
    int getTotalAC() const {
        int total = 0;
        for (const auto& ac : airConditioning) total += ac.quantity;
        return total;
    }
    
    int getTotalFans() const {
        int total = 0;
        for (const auto& f : fans) total += f.quantity;
        return total;
    }
    
    int getTotalLighting() const {
        int total = 0;
        for (const auto& l : lighting) total += l.quantity;
        return total;
    }
    
    // Serialize equipment list to string
    std::string serializeEquipmentList(const std::vector<EquipmentSpec>& eqList) const {
        std::string result;
        for (size_t i = 0; i < eqList.size(); i++) {
            result += eqList[i].serialize();
            if (i < eqList.size() - 1) result += ";";
        }
        return result;
    }
    
    // Deserialize equipment list from string
    std::vector<EquipmentSpec> deserializeEquipmentList(const std::string& data) const {
        std::vector<EquipmentSpec> result;
        if (data.empty()) return result;
        
        std::stringstream ss(data);
        std::string item;
        while (std::getline(ss, item, ';')) {
            if (!item.empty()) {
                EquipmentSpec spec;
                spec.deserialize(item);
                result.push_back(spec);
            }
        }
        return result;
    }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            labId, labCode, labName, buildingName, floor, labType,
            std::to_string(capacity), std::to_string(numComputers), std::to_string(numSeats),
            serializeEquipmentList(airConditioning),
            serializeEquipmentList(fans),
            serializeEquipmentList(lighting),
            serializeEquipmentList(computers),
            description, supervisorId,
            isActive ? "1" : "0",
            isAvailable ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 17) {
            labId = fields[0];
            labCode = fields[1];
            labName = fields[2];
            buildingName = fields[3];
            floor = fields[4];
            labType = fields[5];
            capacity = FileHandler::toInt(fields[6]);
            numComputers = FileHandler::toInt(fields[7]);
            numSeats = FileHandler::toInt(fields[8]);
            airConditioning = deserializeEquipmentList(fields[9]);
            fans = deserializeEquipmentList(fields[10]);
            lighting = deserializeEquipmentList(fields[11]);
            computers = deserializeEquipmentList(fields[12]);
            description = fields[13];
            supervisorId = fields[14];
            isActive = fields[15] == "1";
            isAvailable = fields[16] == "1";
        }
    }
};

#endif // LABORATORY_H
