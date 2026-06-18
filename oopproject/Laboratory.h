#ifndef LABORATORY_H
#define LABORATORY_H

#include <iostream>
#include "MyString.h"
#include "Storage.h"
#include "Scientist.h"
#include "MyVector.h"
using namespace std;

class Laboratory {
private:
    int labID;
    MyString labName;
    MyString location;
    MyString description;

    MyVector<Storage*> storages;     // composition -----  Lab owns its storage units
    MyVector<Scientist*> scientists; // aggregation ----- scientists just work here

public:
    Laboratory(int id, MyString name, MyString loc, MyString desc);
    ~Laboratory(); // --------composition

    void addStorage(Storage* s);
    void addScientist(Scientist* s);

    void displayInfo() const;
};

#endif
#pragma once
