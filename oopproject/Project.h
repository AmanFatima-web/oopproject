#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "MyVector.h"
#include "Experiment.h"
using namespace std;

class Project {
private:
    int projectID;
    MyString projectName;
    MyString description;
    Date startDate;
    Date endDate;
    MyString status;

    MyVector<Experiment*> experiments; // aggregation 

public:
    Project(int id, MyString name, MyString desc, Date start, Date end, MyString stat);

    void addExperiment(Experiment* e);
    void startProject();
    void completeProject();

    void displayInfo() const;
};

#endif
#pragma once
