#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <vector>
#include "../Services/FileHandler.h"

// Equipment specification structure as per requirements
struct EquipmentSpec {
    std::string productId;
    std::string productName;
    std::string productDescription;
    std::string category;      // Seating, AC, Fans, Lighting, Computers
    int quantity;
    std::string status;        // Working, Under Maintenance, Broken
    
    EquipmentSpec() : quantity(1), status("Working") {}
    
    EquipmentSpec(const std::string& id, const std::string& name, 
                  const std::string& desc, const std::string& cat)
        : productId(id), productName(name), productDescription(desc),
          category(cat), quantity(1), status("Working") {}
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            productId, productName, productDescription, category,
            std::to_string(quantity), status
        };
        return FileHandler::join(fields, ',');  // Use comma as internal delimiter
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data, ',');
        if (fields.size() >= 6) {
            productId = fields[0];
            productName = fields[1];
            productDescription = fields[2];
            category = fields[3];
            quantity = FileHandler::toInt(fields[4]);
            status = fields[5];
        }
    }
};

// Equipment class for managing equipment catalog
class Equipment {
private:
    std::string equipmentId;
    std::string equipmentName;
    std::string equipmentType;
    std::string description;
    std::string manufacturer;
    std::string model;
    double unitPrice;
    std::string purchaseDate;
    std::string warrantyExpiry;
    bool isActive;

public:
    Equipment() : unitPrice(0), isActive(true) {}
    
    Equipment(const std::string& id, const std::string& name, const std::string& type)
        : equipmentId(id), equipmentName(name), equipmentType(type),
          unitPrice(0), isActive(true) {}
    
    // Getters
    std::string getEquipmentId() const { return equipmentId; }
    std::string getEquipmentName() const { return equipmentName; }
    std::string getEquipmentType() const { return equipmentType; }
    std::string getDescription() const { return description; }
    std::string getManufacturer() const { return manufacturer; }
    std::string getModel() const { return model; }
    double getUnitPrice() const { return unitPrice; }
    std::string getPurchaseDate() const { return purchaseDate; }
    std::string getWarrantyExpiry() const { return warrantyExpiry; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setEquipmentId(const std::string& id) { equipmentId = id; }
    void setEquipmentName(const std::string& name) { equipmentName = name; }
    void setEquipmentType(const std::string& type) { equipmentType = type; }
    void setDescription(const std::string& desc) { description = desc; }
    void setManufacturer(const std::string& mfr) { manufacturer = mfr; }
    void setModel(const std::string& mdl) { model = mdl; }
    void setUnitPrice(double price) { unitPrice = price; }
    void setPurchaseDate(const std::string& date) { purchaseDate = date; }
    void setWarrantyExpiry(const std::string& date) { warrantyExpiry = date; }
    void setIsActive(bool active) { isActive = active; }
    
    // Serialize
    std::string serialize() const {
        std::vector<std::string> fields = {
            equipmentId, equipmentName, equipmentType, description,
            manufacturer, model, std::to_string(unitPrice),
            purchaseDate, warrantyExpiry, isActive ? "1" : "0"
        };
        return FileHandler::join(fields);
    }
    
    // Deserialize
    void deserialize(const std::string& data) {
        std::vector<std::string> fields = FileHandler::split(data);
        if (fields.size() >= 10) {
            equipmentId = fields[0];
            equipmentName = fields[1];
            equipmentType = fields[2];
            description = fields[3];
            manufacturer = fields[4];
            model = fields[5];
            unitPrice = FileHandler::toDouble(fields[6]);
            purchaseDate = fields[7];
            warrantyExpiry = fields[8];
            isActive = fields[9] == "1";
        }
    }
};

#endif // EQUIPMENT_H
