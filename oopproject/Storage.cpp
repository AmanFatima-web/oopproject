#include "Storage.h"

Storage::Storage(int id, MyString name, MyString t, MyString loc) {
    storageID = id;
    storageName = name;
    type = t;
    location = loc;
}

void Storage::assignToLab() {
    cout << "Storage \"" << storageName << "\" has been assigned to the laboratory." << endl;
}

void Storage::assignChemical(Chemical* c) {
    chemicals.push_back(c);
    cout << "Chemical \"" << c->getChemicalName() << "\" assigned to storage \""
        << storageName << "\"" << endl;
}

MyString Storage::getStorageDetails() const {
    cout << "Storage ID: " << storageID
        << " | Name: " << storageName
        << " | Type: " << type
        << " | Location: " << location
        << " | Chemicals stored: " << chemicals.size() << endl;
    return storageName;
}

int Storage::getStorageID() const {
    return storageID;
}
