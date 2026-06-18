#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "Equipment.h"
#include "MyVector.h"
using namespace std;

class Report {
private:
    int reportID;
    MyString reportType;
    MyString summary;
    MyString result;
    int generatedBy;     
    Date generatedDate;

    MyVector<Equipment*> relatedEquipment; 
    bool published;

public:
    Report(int id, MyString type, MyString sum, MyString res, int genBy, Date genDate);

    void addRelatedEquipment(Equipment* e);

    void generateReport();
    void publishReport();

    int getReportID() const;
    MyString getReportType() const;
};

#endif
#pragma once
