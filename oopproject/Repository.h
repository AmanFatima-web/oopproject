#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include "MyVector.h"
#include "Equipment.h"
#include "Scientist.h"
#include "Chemical.h"
using namespace std;


inline int getEntityID(Equipment* e) { return e->getEquipmentID(); }
inline int getEntityID(Scientist* s) { return s->getScientistID(); }
inline int getEntityID(Chemical* c) { return c->getChemicalID(); }
// ----------------------------
// <<template>> Repository<T>
//----------------------------
template <class T>
class Repository {
private:
    MyVector<T*> items;

public:
    Repository() {
    }

    ~Repository() {
       
        for (int i = 0; i < items.size(); i++) {
            delete items[i];
        }
    }

    void add(T* obj) {
        items.push_back(obj);
    }

    void remove(int id) {
        for (int i = 0; i < items.size(); i++) {
            if (getEntityID(items[i]) == id) {
                delete items[i];
                items.removeAt(i);
                return;
            }
        }
        cout << "Repository: no record found with ID " << id << endl;
    }

    T* search(int id) {
        for (int i = 0; i < items.size(); i++) {
            if (getEntityID(items[i]) == id) {
                return items[i];
            }
        }
        return nullptr;
    }

    MyVector<T*> getAll() {
        return items;
    }
};

#endif
#pragma once
