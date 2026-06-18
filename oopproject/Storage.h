#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include "MyString.h"
#include "Chemical.h"
#include "MyVector.h"
using namespace std;

class Storage {
private:
    int storageID;
    MyString storageName;
    MyString type;        //  Cabinet, Fridge,FumeHood
    MyString location;

    MyVector<Chemical*> chemicals; // chemicals kept in this storage 

public:
    Storage(int id, MyString name, MyString t, MyString loc);

    void assignToLab();
    void assignChemical(Chemical* c);
    MyString getStorageDetails() const;

    int getStorageID() const;
};

#endif
#pragma once
