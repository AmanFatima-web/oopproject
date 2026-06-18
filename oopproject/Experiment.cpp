#include "Experiment.h"

Experiment::Experiment(int id, MyString t, MyString stat, Date start, Date end, MyString n) {
    experimentID = id;
    title = t;
    status = stat;
    startDate = start;
    endDate = end;
    notes = n;
    safetyApproval = nullptr;
}

Experiment::~Experiment() {
    // composition
    for (int i = 0; i < reports.size(); i++) {
        delete reports[i];
    }
    for (int i = 0; i < samples.size(); i++) {
        delete samples[i];
    }
    if (safetyApproval != nullptr) {
        delete safetyApproval;
    }
    // scientists, equipment and chemicals are NOT deleted
}

void Experiment::assignScientist(Scientist* s) {
    scientists.push_back(s);
    cout << s->getName() << " has been assigned to experiment \"" << title << "\"" << endl;
}

void Experiment::addEquipment(Equipment* e) {
    equipmentList.push_back(e);
    cout << "Equipment \"" << e->getEquipmentName() << "\" added to experiment \""
        << title << "\"" << endl;
}

void Experiment::addChemical(Chemical* c, double qty) {
    ChemicalUsage usage;
    usage.chemical = c;
    usage.quantity = qty;
    chemicalsUsed.push_back(usage);

    double remaining = c->getQuantityInStock() - qty;
    c->setQuantityInStock(remaining);

    cout << qty << " unit(s) of \"" << c->getChemicalName()
        << "\" used in experiment \"" << title << "\"" << endl;
}

void Experiment::recordResult(MyString result) {
    notes = notes + MyString(" | Result: ") + result;
    cout << "Result recorded for experiment \"" << title << "\": " << result << endl;
}

void Experiment::reserveEquipment(Equipment* e) {
    e->setStatus(MyString("Reserved"));
    cout << "Equipment \"" << e->getEquipmentName() << "\" reserved for experiment \""
        << title << "\"" << endl;
}

void Experiment::releaseEquipment(Equipment* e) {
    e->setStatus(MyString("Available"));
    cout << "Equipment \"" << e->getEquipmentName() << "\" released from experiment \""
        << title << "\"" << endl;
}

void Experiment::addSample(Sample* s) {
    samples.push_back(s);
    cout << "Sample \"" << s->getSampleName() << "\" linked to experiment \""
        << title << "\"" << endl;
}

void Experiment::addReport(Report* r) {
    reports.push_back(r);
}

void Experiment::setSafetyApproval(SafetyApproval* approval) {
    safetyApproval = approval;
}

int Experiment::getExperimentID() const {
    return experimentID;
}

MyString Experiment::getTitle() const {
    return title;
}

MyString Experiment::getStatus() const {
    return status;
}

void Experiment::setStatus(MyString newStatus) {
    status = newStatus;
}

void Experiment::displayInfo() const {
    cout << "Experiment ID: " << experimentID
        << " | Title: " << title
        << " | Status: " << status
        << " | Start: " << startDate
        << " | End: " << endDate
        << " | Scientists: " << scientists.size()
        << " | Equipment: " << equipmentList.size()
        << " | Chemicals: " << chemicalsUsed.size()
        << " | Samples: " << samples.size()
        << " | Reports: " << reports.size() << endl;
    cout << "   Notes: " << notes << endl;
}
