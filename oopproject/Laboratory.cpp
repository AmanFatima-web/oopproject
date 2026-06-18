#include "Laboratory.h"

Laboratory::Laboratory(int id, MyString name, MyString loc, MyString desc) {
    labID = id;
    labName = name;
    location = loc;
    description = desc;
}

Laboratory::~Laboratory() {
   // ---------
    for (int i = 0; i < storages.size(); i++) {
        delete storages[i];
    }
   
}

void Laboratory::addStorage(Storage* s) {
    storages.push_back(s);
    s->assignToLab();
}

void Laboratory::addScientist(Scientist* s) {
    scientists.push_back(s);
    cout << s->getName() << " has joined laboratory \"" << labName << "\"" << endl;
}

void Laboratory::displayInfo() const {
    cout << "Lab ID: " << labID
        << " | Name: " << labName
        << " | Location: " << location
        << " | Storages: " << storages.size()
        << " | Scientists: " << scientists.size() << endl;
}
