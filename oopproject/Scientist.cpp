#include "Scientist.h"
#include "Experiment.h"   

// ---------------- Scientist ----------------
Scientist::Scientist(int id, MyString n, MyString qual, int expYears, MyString r) {
    scientistID = id;
    name = n;
    qualification = qual;
    experienceYears = expYears;
    role = r;
}

Scientist::~Scientist() {
}

int Scientist::getScientistID() const {
    return scientistID;
}

MyString Scientist::getName() const {
    return name;
}

MyString Scientist::getRole() const {
    return role;
}

void Scientist::displayInfo() const {
    cout << "Scientist ID: " << scientistID
        << " | Name: " << name
        << " | Role: " << role
        << " | Experience: " << experienceYears << " years" << endl;
}

// ---------------- LabTechnician ----------------
LabTechnician::LabTechnician(int id, MyString n, MyString qual, int expYears, MyString r,
    MyString dept)
    : Scientist(id, n, qual, expYears, r), department(dept) {
}

bool LabTechnician::approveUsage(Experiment* exp) {
    cout << name << " (LabTechnician) reviewed experiment \"" << exp->getTitle()
        << "\" for basic equipment readiness. Approved." << endl;
    return true;
}

void LabTechnician::startExperiment(Experiment* exp) {
    cout << name << " (LabTechnician) is setting up and starting experiment \""
        << exp->getTitle() << "\"" << endl;
    exp->setStatus(MyString("In Progress"));
}

void LabTechnician::prepareLab() {
    cout << name << " is preparing the " << department << " lab for the next experiment." << endl;
}

void LabTechnician::displayInfo() const {
    Scientist::displayInfo();
    cout << "   [LabTechnician] Department: " << department << endl;
}

// ---------------- SafetyOfficer ----------------
SafetyOfficer::SafetyOfficer(int id, MyString n, MyString qual, int expYears, MyString r,
    MyString cert)
    : Scientist(id, n, qual, expYears, r), certification(cert) {
}

bool SafetyOfficer::approveUsage(Experiment* exp) {
    cout << name << " (SafetyOfficer) checked safety requirements for \"" << exp->getTitle()
        << "\". Approved." << endl;
    return true;
}

void SafetyOfficer::startExperiment(Experiment* exp) {
    cout << name << " (SafetyOfficer) confirms safety clearance, experiment \""
        << exp->getTitle() << "\" may proceed." << endl;
    exp->setStatus(MyString("In Progress"));
}

bool SafetyOfficer::checkCompliance(Experiment* exp) {
    cout << name << " is checking compliance for experiment \"" << exp->getTitle()
        << "\" (Certification: " << certification << ")" << endl;
    return true;
}

void SafetyOfficer::displayInfo() const {
    Scientist::displayInfo();
    cout << "   [SafetyOfficer] Certification: " << certification << endl;
}

// ---------------- PrincipalInvestigator ----------------
PrincipalInvestigator::PrincipalInvestigator(int id, MyString n, MyString qual, int expYears,
    MyString r, MyString spec)
    : Scientist(id, n, qual, expYears, r), specialization(spec) {
}

bool PrincipalInvestigator::approveUsage(Experiment* exp) {
    cout << name << " (PrincipalInvestigator) reviewed experiment \"" << exp->getTitle()
        << "\" against project goals. Approved." << endl;
    return true;
}

void PrincipalInvestigator::startExperiment(Experiment* exp) {
    cout << name << " (PrincipalInvestigator) officially starts experiment \""
        << exp->getTitle() << "\"" << endl;
    exp->setStatus(MyString("In Progress"));
}

void PrincipalInvestigator::authorize(Experiment* exp) {
    cout << name << " has authorized experiment \"" << exp->getTitle()
        << "\" in the field of " << specialization << endl;
}

void PrincipalInvestigator::displayInfo() const {
    Scientist::displayInfo();
    cout << "   [PrincipalInvestigator] Specialization: " << specialization << endl;
}
