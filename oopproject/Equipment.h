#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
using namespace std;

// ---------------- Equipment (abstract base class) ----------------
class Equipment {
protected:
    int equipmentID;
    MyString equipmentName;
    MyString status;             
    bool isContaminated;
    MyString sterilizationStatus;
    Date lastUsedDate;

public:
    Equipment(int id, MyString name, MyString stat, Date lastUsed);
    virtual ~Equipment();

   
    virtual void performMaintenance() = 0;

    virtual void sterilize();              
    virtual bool checkAvailability() const; 

    int getEquipmentID() const;
    MyString getEquipmentName() const;
    MyString getStatus() const;
    void setStatus(const MyString& newStatus);
    bool getIsContaminated() const;

    virtual void displayInfo() const; 
};

// ---------------- ElectronicDevice ----------------
class ElectronicDevice : public Equipment {
private:
    MyString voltage;
    Date calibrationDate;

public:
    ElectronicDevice(int id, MyString name, MyString stat, Date lastUsed,
        MyString volt, Date calibDate);

    void performMaintenance() override;
    void calibrate();
    void displayInfo() const override;
};

// ---------------- Glassware ----------------
class Glassware : public Equipment {
private:
    bool isFragile;
    bool isDisposable;

public:
    Glassware(int id, MyString name, MyString stat, Date lastUsed,
        bool fragile, bool disposable);

    void performMaintenance() override;
    void sterilize() override;
    void displayInfo() const override;
};

// ---------------- HeavyMachinery ----------------
class HeavyMachinery : public Equipment {
private:
    double loadCapacity;
    Date lastServiceDate;

public:
    HeavyMachinery(int id, MyString name, MyString stat, Date lastUsed,
        double capacity, Date serviceDate);

    void performMaintenance() override;
    void inspect();
    void displayInfo() const override;
};

#endif
#pragma once
