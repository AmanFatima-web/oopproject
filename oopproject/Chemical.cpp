#include "Chemical.h"

// ---------------- Chemical ----------------
Chemical::Chemical(int id, MyString name, int hazard, Date expiry, double qty, MyString u) {
    chemicalID = id;
    chemicalName = name;
    hazardLevel = hazard;
    expiryDate = expiry;
    quantityInStock = qty;
    unit = u;
}

Chemical::~Chemical() {
}

int Chemical::getChemicalID() const {
    return chemicalID;
}

MyString Chemical::getChemicalName() const {
    return chemicalName;
}

double Chemical::getQuantityInStock() const {
    return quantityInStock;
}

void Chemical::setQuantityInStock(double qty) {
    quantityInStock = qty;
}

bool Chemical::isExpired(const Date& today) const {
    return expiryDate.isBefore(today);
}

void Chemical::displayInfo() const {
    cout << "Chemical ID: " << chemicalID
        << " | Name: " << chemicalName
        << " | Hazard Level: " << hazardLevel
        << " | Stock: " << quantityInStock << " " << unit
        << " | Expiry: " << expiryDate << endl;
}

// ---------------- VolatileChemical ----------------
VolatileChemical::VolatileChemical(int id, MyString name, int hazard, Date expiry, double qty,
    MyString u, double flash)
    : Chemical(id, name, hazard, expiry, qty, u), flashPoint(flash) {
}

double VolatileChemical::calculateHazardRisk() const {
    // lower flash point -> easier to ignite -> higher risk
    return (hazardLevel * 10.0) + (100.0 / (flashPoint + 1.0));
}

void VolatileChemical::displayInfo() const {
    Chemical::displayInfo();
    cout << "   [VolatileChemical] Flash Point: " << flashPoint
        << " | Hazard Risk: " << calculateHazardRisk() << endl;
}

// ---------------- BiohazardChemical ----------------
BiohazardChemical::BiohazardChemical(int id, MyString name, int hazard, Date expiry, double qty,
    MyString u, int bioLevel)
    : Chemical(id, name, hazard, expiry, qty, u), biohazardLevel(bioLevel) {
}

double BiohazardChemical::calculateHazardRisk() const {
    return (hazardLevel * 10.0) + (biohazardLevel * 15.0);
}

void BiohazardChemical::displayInfo() const {
    Chemical::displayInfo();
    cout << "   [BiohazardChemical] Biohazard Level: " << biohazardLevel
        << " | Hazard Risk: " << calculateHazardRisk() << endl;
}

// ---------------- InertChemical ----------------
InertChemical::InertChemical(int id, MyString name, int hazard, Date expiry, double qty,
    MyString u, bool reactive)
    : Chemical(id, name, hazard, expiry, qty, u), isReactive(reactive) {
}

double InertChemical::calculateHazardRisk() const {
    double risk = hazardLevel * 5.0; // generally low risk
    if (isReactive) {
        risk += 10.0;
    }
    return risk;
}

void InertChemical::displayInfo() const {
    Chemical::displayInfo();
    cout << "   [InertChemical] Reactive: " << (isReactive ? "Yes" : "No")
        << " | Hazard Risk: " << calculateHazardRisk() << endl;
}
