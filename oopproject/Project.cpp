#include "Project.h"

Project::Project(int id, MyString name, MyString desc, Date start, Date end, MyString stat) {
    projectID = id;
    projectName = name;
    description = desc;
    startDate = start;
    endDate = end;
    status = stat;
}

void Project::addExperiment(Experiment* e) {
    experiments.push_back(e);
    cout << "Experiment \"" << e->getTitle() << "\" added to project \""
        << projectName << "\"" << endl;
}

void Project::startProject() {
    status = MyString("Active");
    cout << "Project \"" << projectName << "\" has started." << endl;
}

void Project::completeProject() {
    status = MyString("Completed");
    cout << "Project \"" << projectName << "\" has been marked as completed." << endl;
}

void Project::displayInfo() const {
    cout << "Project ID: " << projectID
        << " | Name: " << projectName
        << " | Status: " << status
        << " | Experiments: " << experiments.size() << endl;
}
