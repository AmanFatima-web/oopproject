#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "MyVector.h"
#include "Scientist.h"
#include "Equipment.h"
#include "Chemical.h"
#include "Report.h"
#include "Sample.h"
#include "SafetyApproval.h"
using namespace std;


struct ChemicalUsage {
    Chemical* chemical;
    double quantity;
};

class Experiment {
private:
    int experimentID;
    MyString title;
    MyString status;
    Date startDate;
    Date endDate;
    MyString notes;
    // aggregation 
    MyVector<Scientist*> scientists;        // aggregation
    MyVector<Equipment*> equipmentList;     // aggregation
    MyVector<ChemicalUsage> chemicalsUsed;  // aggregation (with quantity)
    MyVector<Report*> reports;              // composition -> owned by the experiment
    MyVector<Sample*> samples;              // composition -> owned by the experiment
    SafetyApproval* safetyApproval;         // association (1 to 1)

public:
    Experiment(int id, MyString t, MyString stat, Date start, Date end, MyString n);
    ~Experiment(); 

    void assignScientist(Scientist* s);
    void addEquipment(Equipment* e);
    void addChemical(Chemical* c, double qty);
    void recordResult(MyString result);
    void reserveEquipment(Equipment* e);
    void releaseEquipment(Equipment* e);

    
    void addSample(Sample* s);
    void addReport(Report* r);
    void setSafetyApproval(SafetyApproval* approval);

    int getExperimentID() const;
    MyString getTitle() const;
    MyString getStatus() const;
    void setStatus(MyString newStatus);

    void displayInfo() const;
};

#endif
#pragma once
