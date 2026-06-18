#ifndef SAMPLE_H
#define SAMPLE_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
using namespace std;

class Sample {
private:
    int sampleID;
    MyString sampleName;
    MyString type;
    MyString source;
    Date collectedDate;
    MyString status;

public:
    Sample(int id, MyString name, MyString t, MyString src, Date collected, MyString stat);

    void storeSample();
    MyString getSampleDetails() const;

    int getSampleID() const;
    MyString getSampleName() const;
};

#endif
#pragma once
