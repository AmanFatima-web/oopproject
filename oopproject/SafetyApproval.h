#ifndef SAFETYAPPROVAL_H
#define SAFETYAPPROVAL_H

#include <iostream>
#include "MyString.h"
#include "Date.h"
using namespace std;

class SafetyApproval {
private:
    int approvalID;
    Date approvalDate;
    MyString status;       // contain any status like pending ,approved or rejected
    MyString comments;
    int approvedBy;          // SafetyOfficerID

public:
    SafetyApproval(int id, Date approvalDt, MyString stat, MyString comm, int approver);

    void approve();
    void reject();

    MyString getStatus() const;
    int getApprovalID() const;
};

#endif
#pragma once
