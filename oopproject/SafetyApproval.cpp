#include "SafetyApproval.h"

SafetyApproval::SafetyApproval(int id, Date approvalDt, MyString stat, MyString comm, int approver) {
    approvalID = id;
    approvalDate = approvalDt;
    status = stat;
    comments = comm;
    approvedBy = approver;
}

void SafetyApproval::approve() {
    status = MyString("Approved");
    cout << "Safety Approval #" << approvalID << " has been APPROVED by officer ID "
        << approvedBy << ". Comments: " << comments << endl;
}

void SafetyApproval::reject() {
    status = MyString("Rejected");
    cout << "Safety Approval #" << approvalID << " has been REJECTED by officer ID "
        << approvedBy << ". Comments: " << comments << endl;
}

MyString SafetyApproval::getStatus() const {
    return status;
}

int SafetyApproval::getApprovalID() const {
    return approvalID;
}
