#ifndef CHEMICAL_H
#define CHEMICAL_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
using namespace std;

// ---------------- Chemical (abstract base class) ----------------
class Chemical {
protected:
    int chemicalID;
    MyString chemicalName;
    int hazardLevel;
    Date expiryDate;
    double quantityInStock;
    MyString unit;

public:
    Chemical(int id, MyString name, int hazard, Date expiry, double qty, MyString u);
    virtual ~Chemical();

    // pure virtual -> every type of chemical calculates risk differently
    virtual double calculateHazardRisk() const = 0;

    int getChemicalID() const;
    MyString getChemicalName() const;
    double getQuantityInStock() const;
    void setQuantityInStock(double qty);
    bool isExpired(const Date& today) const;

    virtual void displayInfo() const;
};

// ---------------- VolatileChemical ----------------
class VolatileChemical : public Chemical {
private:
    double flashPoint;

public:
    VolatileChemical(int id, MyString name, int hazard, Date expiry, double qty, MyString u,
        double flash);

    double calculateHazardRisk() const override;
    void displayInfo() const override;
};

// ---------------- BiohazardChemical ----------------
class BiohazardChemical : public Chemical {
private:
    int biohazardLevel;

public:
    BiohazardChemical(int id, MyString name, int hazard, Date expiry, double qty, MyString u,
        int bioLevel);

    double calculateHazardRisk() const override;
    void displayInfo() const override;
};

// ---------------- InertChemical ----------------
class InertChemical : public Chemical {
private:
    bool isReactive;

public:
    InertChemical(int id, MyString name, int hazard, Date expiry, double qty, MyString u,
        bool reactive);

    double calculateHazardRisk() const override;
    void displayInfo() const override;
};

#endif
#pragma once
