#ifndef LECTURE_HALL_H
#define LECTURE_HALL_H

#include <string>
#include <vector>
#include <sstream>
#include "../Services/FileHandler.h"
#include "Equipment.h"

class LectureHall {
private:
    std::string hallId;
    std::string hallCode;
    std::string hallName;
    std::string buildingName;
    std::string floor;
    int capacity;                          // Number of students
    std::vector<EquipmentSpec> seating;    // Seating specs
    std::vector<EquipmentSpec> airConditioning;  // AC specs
    std::vector<EquipmentSpec> fans;       // Fan specs
    std::vector<EquipmentSpec> lighting;   // Lighting specs
    std::string description;
    bool isActive;
    bool isAvailable;

public:
    LectureHall() : capacity(0), isActive(true), isAvailable(true) {}
    
    LectureHall(const std::string& id, const std::string& code, 
                const std::string& name, int cap)
        : hallId(id), hallCode(code), hallName(name), capacity(cap),
          isActive(true), isAvailable(true) {}
    
    // Getters
    std::string getHallId() const { return hallId; }
    std::string getHallCode() const { return hallCode; }
    std::string getHallName() const { return hallName; }
    std::string getBuildingName() const { return buildingName; }
    std::string getFloor() const { return floor; }
    int getCapacity() const { return capacity; }
    std::vector<EquipmentSpec> getSeating() const { return seating; }
    std::vector<EquipmentSpec> getAirConditioning() const { return airConditioning; }
    std::vector<EquipmentSpec> getFans() const { return fans; }
    std::vector<EquipmentSpec> getLighting() const { return lighting; }
    std::string getDescription() const { return description; }
    bool getIsActive() const { return isActive; }
    bool getIsAvailable() const { return isAvailable; }
    
    // Setters
    void setHallId(const std::string& id) { hallId = id; }
    void setHallCode(const std::string& code) { hallCode = code; }
    void setHallName(const std::string& name) { hallName = name; }
    void setBuildingName(const std::string& bldg) { buildingName = bldg; }
    void setFloor(const std::string& fl) { floor = fl; }
    void setCapacity(int cap) { capacity = cap; }
    void setDescription(const std::string& desc) { description = desc; }
    void setIsActive(bool active) { isActive = active; }
    void setIsAvailable(bool available) { isAvailable = available; }
    
    // Equipment management
    void addSeating(const EquipmentSpec& spec) { seating.push_back(spec); }
    void addAirConditioning(const EquipmentSpec& spec) { airConditioning.push_back(spec); }
    void addFan(const EquipmentSpec& spec) { fans.push_back(spec); }
    void addLighting(const EquipmentSpec& spec) { lighting.push_back(spec); }
    
    void clearSeating() { seating.clear(); }
    void clearAirConditioning() { airConditioning.clear(); }
    void clearFans() { fans.clear(); }
    void clearLighting() { lighting.clear(); }
    
    // Get total equipment counts
    int getTotalSeating() const {
        int total = 0;
        for (const auto& s : seating) total += s.quantity;
        return total;
    }
    
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
            hallId, hallCode, hallName, buildingName, floor,
            std::to_string(capacity),
            serializeEquipmentList(seating),
            serializeEquipmentList(airConditioning),
            serializeEquipmentList(fans),
            serializeEquipmentList(lighting),
            description,
            isActive ? "1" : "0",
            isAvailable ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 13) {
            hallId = fields[0];
            hallCode = fields[1];
            hallName = fields[2];
            buildingName = fields[3];
            floor = fields[4];
            capacity = FileHandler::toInt(fields[5]);
            seating = deserializeEquipmentList(fields[6]);
            airConditioning = deserializeEquipmentList(fields[7]);
            fans = deserializeEquipmentList(fields[8]);
            lighting = deserializeEquipmentList(fields[9]);
            description = fields[10];
            isActive = fields[11] == "1";
            isAvailable = fields[12] == "1";
        }
    }
};

#endif // LECTURE_HALL_H
