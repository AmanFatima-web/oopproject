#include "Equipment.h"

// ---------------- Equipment ----------------
Equipment::Equipment(int id, MyString name, MyString stat, Date lastUsed) {
    equipmentID = id;
    equipmentName = name;
    status = stat;
    isContaminated = false;
    sterilizationStatus = MyString("Not Sterilized");
    lastUsedDate = lastUsed;
}

Equipment::~Equipment() {
}

void Equipment::sterilize() {
    isContaminated = false;
    sterilizationStatus = MyString("Sterilized");
    cout << equipmentName << " has been sterilized." << endl;
}

bool Equipment::checkAvailability() const {
    if (isContaminated) {
        return false;
    }
    return status == MyString("Available");
}

int Equipment::getEquipmentID() const {
    return equipmentID;
}

MyString Equipment::getEquipmentName() const {
    return equipmentName;
}

MyString Equipment::getStatus() const {
    return status;
}

void Equipment::setStatus(const MyString& newStatus) {
    status = newStatus;
}

bool Equipment::getIsContaminated() const {
    return isContaminated;
}

void Equipment::displayInfo() const {
    cout << "Equipment ID: " << equipmentID
        << " | Name: " << equipmentName
        << " | Status: " << status
        << " | Sterilization: " << sterilizationStatus << endl;
}

// ---------------- ElectronicDevice ----------------
ElectronicDevice::ElectronicDevice(int id, MyString name, MyString stat, Date lastUsed,
    MyString volt, Date calibDate)
    : Equipment(id, name, stat, lastUsed), voltage(volt), calibrationDate(calibDate) {
}

void ElectronicDevice::performMaintenance() {
    cout << "Performing electrical safety check on " << equipmentName
        << " (Voltage: " << voltage << ")" << endl;
}

void ElectronicDevice::calibrate() {
    cout << equipmentName << " has been calibrated on " << calibrationDate << endl;
}

void ElectronicDevice::displayInfo() const {
    Equipment::displayInfo();
    cout << "   [ElectronicDevice] Voltage: " << voltage
        << " | Last Calibration: " << calibrationDate << endl;
}

// ---------------- Glassware ----------------
Glassware::Glassware(int id, MyString name, MyString stat, Date lastUsed,
    bool fragile, bool disposable)
    : Equipment(id, name, stat, lastUsed), isFragile(fragile), isDisposable(disposable) {
}

void Glassware::performMaintenance() {
    cout << "Checking " << equipmentName << " for cracks/chips before reuse." << endl;
}

void Glassware::sterilize() {
    if (isDisposable) {
        cout << equipmentName << " is disposable, sterilization skipped." << endl;
        return;
    }
    Equipment::sterilize();
}

void Glassware::displayInfo() const {
    Equipment::displayInfo();
    cout << "   [Glassware] Fragile: " << (isFragile ? "Yes" : "No")
        << " | Disposable: " << (isDisposable ? "Yes" : "No") << endl;
}

// ---------------- HeavyMachinery ----------------
HeavyMachinery::HeavyMachinery(int id, MyString name, MyString stat, Date lastUsed,
    double capacity, Date serviceDate)
    : Equipment(id, name, stat, lastUsed), loadCapacity(capacity), lastServiceDate(serviceDate) {
}

void HeavyMachinery::performMaintenance() {
    cout << "Running full service routine on heavy machinery: " << equipmentName << endl;
}

void HeavyMachinery::inspect() {
    cout << equipmentName << " inspected. Load capacity: " << loadCapacity
        << " | Last service: " << lastServiceDate << endl;
}

void HeavyMachinery::displayInfo() const {
    Equipment::displayInfo();
    cout << "   [HeavyMachinery] Load Capacity: " << loadCapacity
        << " | Last Service: " << lastServiceDate << endl;
}
