#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <iostream>
#include "MyString.h"
using namespace std;

class Experiment; // forward declaration (Experiment.h includes Scientist.h, not the other way)

// ---------------- Scientist (abstract base class) ----------------
class Scientist {
protected:
    int scientistID;
    MyString name;
    MyString qualification;
    int experienceYears;
    MyString role;

public:
    Scientist(int id, MyString n, MyString qual, int expYears, MyString r);
    virtual ~Scientist();

    // pure virtual -> each role decides usage approval / experiment start differently
    virtual bool approveUsage(Experiment* exp) = 0;
    virtual void startExperiment(Experiment* exp) = 0;

    int getScientistID() const;
    MyString getName() const;
    MyString getRole() const;

    virtual void displayInfo() const;
};

// ---------------- LabTechnician ----------------
class LabTechnician : public Scientist {
private:
    MyString department;

public:
    LabTechnician(int id, MyString n, MyString qual, int expYears, MyString r, MyString dept);

    bool approveUsage(Experiment* exp) override;
    void startExperiment(Experiment* exp) override;
    void prepareLab();
    void displayInfo() const override;
};

// ---------------- SafetyOfficer ----------------
class SafetyOfficer : public Scientist {
private:
    MyString certification;

public:
    SafetyOfficer(int id, MyString n, MyString qual, int expYears, MyString r, MyString cert);

    bool approveUsage(Experiment* exp) override;
    void startExperiment(Experiment* exp) override;
    bool checkCompliance(Experiment* exp);
    void displayInfo() const override;
};

// ---------------- PrincipalInvestigator ----------------
class PrincipalInvestigator : public Scientist {
private:
    MyString specialization;

public:
    PrincipalInvestigator(int id, MyString n, MyString qual, int expYears, MyString r,
        MyString spec);

    bool approveUsage(Experiment* exp) override;
    void startExperiment(Experiment* exp) override;
    void authorize(Experiment* exp);
    void displayInfo() const override;
};

#endif
#pragma once
