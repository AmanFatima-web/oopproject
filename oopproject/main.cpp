#include <iostream>
#include "MyString.h"
#include "Date.h"
#include "Equipment.h"
#include "Chemical.h"
#include "Scientist.h"
#include "Sample.h"
#include "Report.h"
#include "SafetyApproval.h"
#include "Storage.h"
#include "Laboratory.h"
#include "Experiment.h"
#include "Project.h"
#include "Repository.h"

using namespace std;

// ===================================================================
//                      INPUT HELPER FUNCTIONS
// ===================================================================
// 
// 

int readInt(const char* prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a whole number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n'); 
    return value;
}

double readDouble(const char* prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    return value;
}

MyString readString(const char* prompt) {
    cout << prompt;
    MyString s;
    cin >> s; 
    return s;
}

bool readYesNo(const char* prompt) {
    MyString s = readString(prompt);
    if (s.length() > 0 && (s[0] == 'y' || s[0] == 'Y')) {
        return true;
    }
    return false;
}

Date readDate(const char* label) {
    cout << label << endl;
    int d = readInt("  Day: ");
    int m = readInt("  Month: ");
    int y = readInt("  Year: ");
    return Date(d, m, y);
}

// ===================================================================
//                      SMALL LOOKUP HELPER
// ===================================================================
// Laboratory and Project don't expose ID getters in the UML diagram,
// so they are picked by list position. Experiment DOES expose
// getExperimentID(), so it is looked up by its real ID.

Experiment* findExperimentByID(MyVector<Experiment*>& experiments, int id) {
    for (int i = 0; i < experiments.size(); i++) {
        if (experiments[i]->getExperimentID() == id) {
            return experiments[i];
        }
    }
    return nullptr;
}

// ===================================================================
//                      SCIENTIST MANAGEMENT
// ===================================================================
void scientistMenu(Repository<Scientist>& repo) {
    int choice;
    do {
        cout << "\n--- Scientist Management ---" << endl;
        cout << "1. Add Scientist" << endl;
        cout << "2. View All Scientists" << endl;
        cout << "3. Search Scientist by ID" << endl;
        cout << "4. Remove Scientist by ID" << endl;
        cout << "5. Back to Main Menu" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Scientist ID: ");
            MyString name = readString("Enter Name: ");
            MyString qual = readString("Enter Qualification: ");
            int exp = readInt("Enter Years of Experience: ");

            cout << "Select Role:\n 1. LabTechnician\n 2. SafetyOfficer\n 3. PrincipalInvestigator" << endl;
            int roleChoice = readInt("Enter choice: ");

            Scientist* s = nullptr;
            if (roleChoice == 1) {
                MyString dept = readString("Enter Department: ");
                s = new LabTechnician(id, name, qual, exp, MyString("LabTechnician"), dept);
            }
            else if (roleChoice == 2) {
                MyString cert = readString("Enter Certification: ");
                s = new SafetyOfficer(id, name, qual, exp, MyString("SafetyOfficer"), cert);
            }
            else if (roleChoice == 3) {
                MyString spec = readString("Enter Specialization: ");
                s = new PrincipalInvestigator(id, name, qual, exp, MyString("PrincipalInvestigator"), spec);
            }
            else {
                cout << "Invalid role choice. Scientist not added." << endl;
            }

            if (s != nullptr) {
                repo.add(s);
                cout << "Scientist added successfully!" << endl;
            }
        }
        else if (choice == 2) {
            MyVector<Scientist*> all = repo.getAll();
            if (all.isEmpty()) {
                cout << "No scientists registered yet." << endl;
            }
            else {
                for (int i = 0; i < all.size(); i++) {
                    all[i]->displayInfo();
                }
            }
        }
        else if (choice == 3) {
            int id = readInt("Enter Scientist ID to search: ");
            Scientist* found = repo.search(id);
            if (found != nullptr) {
                found->displayInfo();
            }
            else {
                cout << "No scientist found with ID " << id << endl;
            }
        }
        else if (choice == 4) {
            int id = readInt("Enter Scientist ID to remove: ");
            repo.remove(id);
        }
        else if (choice != 5) {
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 5);
}

// ===================================================================
//                      EQUIPMENT MANAGEMENT
// ===================================================================
void equipmentMenu(Repository<Equipment>& repo) {
    int choice;
    do {
        cout << "\n--- Equipment Management ---" << endl;
        cout << "1. Add Equipment" << endl;
        cout << "2. View All Equipment" << endl;
        cout << "3. Search Equipment by ID" << endl;
        cout << "4. Remove Equipment by ID" << endl;
        cout << "5. Perform Maintenance" << endl;
        cout << "6. Sterilize Equipment" << endl;
        cout << "7. Back to Main Menu" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Equipment ID: ");
            MyString name = readString("Enter Equipment Name: ");
            MyString status = readString("Enter Status (e.g. Available): ");
            Date lastUsed = readDate("Enter Last Used Date:");

            cout << "Select Equipment Type:\n 1. ElectronicDevice\n 2. Glassware\n 3. HeavyMachinery" << endl;
            int typeChoice = readInt("Enter choice: ");

            Equipment* e = nullptr;
            if (typeChoice == 1) {
                MyString volt = readString("Enter Voltage (e.g. 220V): ");
                Date calibDate = readDate("Enter Calibration Date:");
                e = new ElectronicDevice(id, name, status, lastUsed, volt, calibDate);
            }
            else if (typeChoice == 2) {
                bool fragile = readYesNo("Is it fragile? (y/n): ");
                bool disposable = readYesNo("Is it disposable? (y/n): ");
                e = new Glassware(id, name, status, lastUsed, fragile, disposable);
            }
            else if (typeChoice == 3) {
                double capacity = readDouble("Enter Load Capacity: ");
                Date serviceDate = readDate("Enter Last Service Date:");
                e = new HeavyMachinery(id, name, status, lastUsed, capacity, serviceDate);
            }
            else {
                cout << "Invalid type choice. Equipment not added." << endl;
            }

            if (e != nullptr) {
                repo.add(e);
                cout << "Equipment added successfully!" << endl;
            }
        }
        else if (choice == 2) {
            MyVector<Equipment*> all = repo.getAll();
            if (all.isEmpty()) {
                cout << "No equipment registered yet." << endl;
            }
            else {
                for (int i = 0; i < all.size(); i++) {
                    all[i]->displayInfo();
                }
            }
        }
        else if (choice == 3) {
            int id = readInt("Enter Equipment ID to search: ");
            Equipment* found = repo.search(id);
            if (found != nullptr) {
                found->displayInfo();
            }
            else {
                cout << "No equipment found with ID " << id << endl;
            }
        }
        else if (choice == 4) {
            int id = readInt("Enter Equipment ID to remove: ");
            repo.remove(id);
        }
        else if (choice == 5) {
            int id = readInt("Enter Equipment ID: ");
            Equipment* found = repo.search(id);
            if (found != nullptr) {
                found->performMaintenance();
            }
            else {
                cout << "No equipment found with ID " << id << endl;
            }
        }
        else if (choice == 6) {
            int id = readInt("Enter Equipment ID: ");
            Equipment* found = repo.search(id);
            if (found != nullptr) {
                found->sterilize();
            }
            else {
                cout << "No equipment found with ID " << id << endl;
            }
        }
        else if (choice != 7) {
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 7);
}

// ===================================================================
//                      CHEMICAL MANAGEMENT
// ===================================================================
void chemicalMenu(Repository<Chemical>& repo) {
    int choice;
    do {
        cout << "\n--- Chemical Management ---" << endl;
        cout << "1. Add Chemical" << endl;
        cout << "2. View All Chemicals" << endl;
        cout << "3. Search Chemical by ID" << endl;
        cout << "4. Remove Chemical by ID" << endl;
        cout << "5. Calculate Hazard Risk" << endl;
        cout << "6. Back to Main Menu" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Chemical ID: ");
            MyString name = readString("Enter Chemical Name: ");
            int hazard = readInt("Enter Hazard Level (1-5): ");
            Date expiry = readDate("Enter Expiry Date:");
            double qty = readDouble("Enter Quantity in Stock: ");
            MyString unit = readString("Enter Unit (e.g. ml, g): ");

            cout << "Select Chemical Type:\n 1. VolatileChemical\n 2. BiohazardChemical\n 3. InertChemical" << endl;
            int typeChoice = readInt("Enter choice: ");

            Chemical* c = nullptr;
            if (typeChoice == 1) {
                double flash = readDouble("Enter Flash Point: ");
                c = new VolatileChemical(id, name, hazard, expiry, qty, unit, flash);
            }
            else if (typeChoice == 2) {
                int bioLevel = readInt("Enter Biohazard Level: ");
                c = new BiohazardChemical(id, name, hazard, expiry, qty, unit, bioLevel);
            }
            else if (typeChoice == 3) {
                bool reactive = readYesNo("Is it reactive? (y/n): ");
                c = new InertChemical(id, name, hazard, expiry, qty, unit, reactive);
            }
            else {
                cout << "Invalid type choice. Chemical not added." << endl;
            }

            if (c != nullptr) {
                repo.add(c);
                cout << "Chemical added successfully!" << endl;
            }
        }
        else if (choice == 2) {
            MyVector<Chemical*> all = repo.getAll();
            if (all.isEmpty()) {
                cout << "No chemicals registered yet." << endl;
            }
            else {
                for (int i = 0; i < all.size(); i++) {
                    all[i]->displayInfo();
                }
            }
        }
        else if (choice == 3) {
            int id = readInt("Enter Chemical ID to search: ");
            Chemical* found = repo.search(id);
            if (found != nullptr) {
                found->displayInfo();
            }
            else {
                cout << "No chemical found with ID " << id << endl;
            }
        }
        else if (choice == 4) {
            int id = readInt("Enter Chemical ID to remove: ");
            repo.remove(id);
        }
        else if (choice == 5) {
            int id = readInt("Enter Chemical ID: ");
            Chemical* found = repo.search(id);
            if (found != nullptr) {
                cout << "Hazard Risk: " << found->calculateHazardRisk() << endl;
            }
            else {
                cout << "No chemical found with ID " << id << endl;
            }
        }
        else if (choice != 6) {
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 6);
}

// ===================================================================
//                      LABORATORY MANAGEMENT
// ===================================================================
void laboratoryMenu(MyVector<Laboratory*>& labs, Repository<Scientist>& scientistRepo,
    Repository<Chemical>& chemicalRepo) {
    int choice;
    do {
        cout << "\n--- Laboratory Management ---" << endl;
        cout << "1. Create Laboratory" << endl;
        cout << "2. View All Laboratories" << endl;
        cout << "3. Add Storage to a Laboratory" << endl;
        cout << "4. Add Scientist to a Laboratory" << endl;
        cout << "5. Back to Main Menu" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Lab ID: ");
            MyString name = readString("Enter Lab Name: ");
            MyString loc = readString("Enter Location: ");
            MyString desc = readString("Enter Description: ");
            Laboratory* lab = new Laboratory(id, name, loc, desc);
            labs.push_back(lab);
            cout << "Laboratory created successfully!" << endl;
        }
        else if (choice == 2) {
            if (labs.isEmpty()) {
                cout << "No laboratories created yet." << endl;
            }
            else {
                for (int i = 0; i < labs.size(); i++) {
                    cout << "[" << (i + 1) << "] ";
                    labs[i]->displayInfo();
                }
            }
        }
        else if (choice == 3) {
            if (labs.isEmpty()) {
                cout << "No laboratories available. Create one first." << endl;
            }
            else {
                for (int i = 0; i < labs.size(); i++) {
                    cout << "[" << (i + 1) << "] ";
                    labs[i]->displayInfo();
                }
                int pick = readInt("Select Laboratory number: ");
                if (pick >= 1 && pick <= labs.size()) {
                    int sid = readInt("Enter Storage ID: ");
                    MyString sname = readString("Enter Storage Name: ");
                    MyString stype = readString("Enter Storage Type (e.g. Cabinet, Fridge): ");
                    MyString sloc = readString("Enter Storage Location: ");
                    Storage* storage = new Storage(sid, sname, stype, sloc);

                    bool addMoreChem = readYesNo("Assign a chemical to this storage now? (y/n): ");
                    while (addMoreChem) {
                        int cid = readInt("Enter Chemical ID: ");
                        Chemical* chem = chemicalRepo.search(cid);
                        if (chem != nullptr) {
                            storage->assignChemical(chem);
                        }
                        else {
                            cout << "No chemical found with ID " << cid << endl;
                        }
                        addMoreChem = readYesNo("Assign another chemical? (y/n): ");
                    }

                    labs[pick - 1]->addStorage(storage);
                }
                else {
                    cout << "Invalid selection." << endl;
                }
            }
        }
        else if (choice == 4) {
            if (labs.isEmpty()) {
                cout << "No laboratories available. Create one first." << endl;
            }
            else {
                for (int i = 0; i < labs.size(); i++) {
                    cout << "[" << (i + 1) << "] ";
                    labs[i]->displayInfo();
                }
                int pick = readInt("Select Laboratory number: ");
                if (pick >= 1 && pick <= labs.size()) {
                    int scid = readInt("Enter Scientist ID to add: ");
                    Scientist* sci = scientistRepo.search(scid);
                    if (sci != nullptr) {
                        labs[pick - 1]->addScientist(sci);
                    }
                    else {
                        cout << "No scientist found with ID " << scid << endl;
                    }
                }
                else {
                    cout << "Invalid selection." << endl;
                }
            }
        }
        else if (choice != 5) {
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 5);
}

// ===================================================================
//                      PROJECT MANAGEMENT
// ===================================================================
void projectMenu(MyVector<Project*>& projects) {
    int choice;
    do {
        cout << "\n--- Project Management ---" << endl;
        cout << "1. Create Project" << endl;
        cout << "2. View All Projects" << endl;
        cout << "3. Start a Project" << endl;
        cout << "4. Complete a Project" << endl;
        cout << "5. Back to Main Menu" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Project ID: ");
            MyString name = readString("Enter Project Name: ");
            MyString desc = readString("Enter Description: ");
            Date start = readDate("Enter Start Date:");
            Date end = readDate("Enter End Date:");
            Project* p = new Project(id, name, desc, start, end, MyString("Planned"));
            projects.push_back(p);
            cout << "Project created successfully!" << endl;
        }
        else if (choice == 2) {
            if (projects.isEmpty()) {
                cout << "No projects created yet." << endl;
            }
            else {
                for (int i = 0; i < projects.size(); i++) {
                    cout << "[" << (i + 1) << "] ";
                    projects[i]->displayInfo();
                }
            }
        }
        else if (choice == 3) {
            if (projects.isEmpty()) {
                cout << "No projects available." << endl;
            }
            else {
                for (int i = 0; i < projects.size(); i++) {
                    cout << "[" << (i + 1) << "] ";
                    projects[i]->displayInfo();
                }
                int pick = readInt("Select Project number: ");
                if (pick >= 1 && pick <= projects.size()) {
                    projects[pick - 1]->startProject();
                }
                else {
                    cout << "Invalid selection." << endl;
                }
            }
        }
        else if (choice == 4) {
            if (projects.isEmpty()) {
                cout << "No projects available." << endl;
            }
            else {
                for (int i = 0; i < projects.size(); i++) {
                    cout << "[" << (i + 1) << "] ";
                    projects[i]->displayInfo();
                }
                int pick = readInt("Select Project number: ");
                if (pick >= 1 && pick <= projects.size()) {
                    projects[pick - 1]->completeProject();
                }
                else {
                    cout << "Invalid selection." << endl;
                }
            }
        }
        else if (choice != 5) {
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 5);
}

// ===================================================================
//                      EXPERIMENT MANAGEMENT
// ===================================================================
void experimentMenu(MyVector<Experiment*>& experiments, MyVector<Project*>& projects,
    Repository<Scientist>& scientistRepo, Repository<Equipment>& equipmentRepo,
    Repository<Chemical>& chemicalRepo) {
    int choice;
    do {
        cout << "\n--- Experiment Management ---" << endl;
        cout << "1. Create Experiment" << endl;
        cout << "2. View All Experiments" << endl;
        cout << "3. Assign Scientist to Experiment" << endl;
        cout << "4. Add Equipment to Experiment" << endl;
        cout << "5. Add Chemical Usage to Experiment" << endl;
        cout << "6. Scientist Approve & Start Experiment" << endl;
        cout << "7. Record Result" << endl;
        cout << "8. Release Equipment" << endl;
        cout << "9. Add Sample to Experiment" << endl;
        cout << "10. Set Safety Approval for Experiment" << endl;
        cout << "11. Generate Report for Experiment" << endl;
        cout << "12. Display Experiment Info" << endl;
        cout << "13. Back to Main Menu" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Experiment ID: ");
            MyString title = readString("Enter Experiment Title: ");
            Date start = readDate("Enter Start Date:");
            Date end = readDate("Enter End Date:");
            MyString notes = readString("Enter Initial Notes: ");

            Experiment* exp = new Experiment(id, title, MyString("Planned"), start, end, notes);
            experiments.push_back(exp);
            cout << "Experiment created successfully!" << endl;

            if (!projects.isEmpty()) {
                bool addToProj = readYesNo("Add this experiment to a project now? (y/n): ");
                if (addToProj) {
                    for (int i = 0; i < projects.size(); i++) {
                        cout << "[" << (i + 1) << "] ";
                        projects[i]->displayInfo();
                    }
                    int pick = readInt("Select Project number: ");
                    if (pick >= 1 && pick <= projects.size()) {
                        projects[pick - 1]->addExperiment(exp);
                    }
                    else {
                        cout << "Invalid selection, experiment not linked to any project." << endl;
                    }
                }
            }
        }
        else if (choice == 2) {
            if (experiments.isEmpty()) {
                cout << "No experiments created yet." << endl;
            }
            else {
                for (int i = 0; i < experiments.size(); i++) {
                    experiments[i]->displayInfo();
                }
            }
        }
        else if (choice == 3) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int scid = readInt("Enter Scientist ID to assign: ");
                Scientist* sci = scientistRepo.search(scid);
                if (sci != nullptr) {
                    exp->assignScientist(sci);
                }
                else {
                    cout << "No scientist found with ID " << scid << endl;
                }
            }
        }
        else if (choice == 4) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int eqid = readInt("Enter Equipment ID to add: ");
                Equipment* eq = equipmentRepo.search(eqid);
                if (eq != nullptr) {
                    exp->addEquipment(eq);
                    exp->reserveEquipment(eq);
                }
                else {
                    cout << "No equipment found with ID " << eqid << endl;
                }
            }
        }
        else if (choice == 5) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int cid = readInt("Enter Chemical ID to use: ");
                Chemical* chem = chemicalRepo.search(cid);
                if (chem != nullptr) {
                    double qty = readDouble("Enter quantity used: ");
                    exp->addChemical(chem, qty);
                }
                else {
                    cout << "No chemical found with ID " << cid << endl;
                }
            }
        }
        else if (choice == 6) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int scid = readInt("Enter approving Scientist ID: ");
                Scientist* sci = scientistRepo.search(scid);
                if (sci != nullptr) {
                    bool approved = sci->approveUsage(exp);
                    if (approved) {
                        sci->startExperiment(exp);
                    }
                }
                else {
                    cout << "No scientist found with ID " << scid << endl;
                }
            }
        }
        else if (choice == 7) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                MyString result = readString("Enter Result: ");
                exp->recordResult(result);
            }
        }
        else if (choice == 8) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int eqid = readInt("Enter Equipment ID to release: ");
                Equipment* eq = equipmentRepo.search(eqid);
                if (eq != nullptr) {
                    exp->releaseEquipment(eq);
                }
                else {
                    cout << "No equipment found with ID " << eqid << endl;
                }
            }
        }
        else if (choice == 9) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int sampleId = readInt("Enter Sample ID: ");
                MyString sname = readString("Enter Sample Name: ");
                MyString stype = readString("Enter Sample Type: ");
                MyString source = readString("Enter Sample Source: ");
                Date collected = readDate("Enter Collected Date:");
                Sample* sample = new Sample(sampleId, sname, stype, source, collected, MyString("Collected"));
                sample->storeSample();
                exp->addSample(sample);
            }
        }
        else if (choice == 10) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int approvalId = readInt("Enter Safety Approval ID: ");
                Date approvalDate = readDate("Enter Approval Date:");
                MyString comments = readString("Enter Comments: ");
                int approverID = readInt("Enter Approving Safety Officer ID: ");

                SafetyApproval* approval = new SafetyApproval(approvalId, approvalDate,
                    MyString("Pending"), comments, approverID);
                bool isApproved = readYesNo("Approve this safety check? (y/n): ");
                if (isApproved) {
                    approval->approve();
                }
                else {
                    approval->reject();
                }

                exp->setSafetyApproval(approval);
            }
        }
        else if (choice == 11) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp == nullptr) {
                cout << "No experiment found with ID " << eid << endl;
            }
            else {
                int reportId = readInt("Enter Report ID: ");
                MyString type = readString("Enter Report Type: ");
                MyString summary = readString("Enter Summary: ");
                MyString result = readString("Enter Result (Pass/Fail/etc): ");
                int genBy = readInt("Enter Generating Scientist ID: ");
                Date genDate = readDate("Enter Generated Date:");

                Report* report = new Report(reportId, type, summary, result, genBy, genDate);

                bool addEq = readYesNo("Link equipment to this report? (y/n): ");
                while (addEq) {
                    int eqid = readInt("Enter Equipment ID: ");
                    Equipment* eq = equipmentRepo.search(eqid);
                    if (eq != nullptr) {
                        report->addRelatedEquipment(eq);
                    }
                    else {
                        cout << "No equipment found with ID " << eqid << endl;
                    }
                    addEq = readYesNo("Link another equipment? (y/n): ");
                }

                report->generateReport();
                bool publish = readYesNo("Publish this report now? (y/n): ");
                if (publish) {
                    report->publishReport();
                }

                exp->addReport(report);
            }
        }
        else if (choice == 12) {
            int eid = readInt("Enter Experiment ID: ");
            Experiment* exp = findExperimentByID(experiments, eid);
            if (exp != nullptr) {
                exp->displayInfo();
            }
            else {
                cout << "No experiment found with ID " << eid << endl;
            }
        }
        else if (choice != 13) {
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 13);
}

// ===================================================================
//                              MAIN
// ===================================================================
int main() {
    cout << "=========================================" << endl;
    cout << "   SCIENCE LABORATORY MANAGEMENT SYSTEM   " << endl;
    cout << "=========================================" << endl;

    // ---------- Repositories (the "databases" for these object types) ----------
    Repository<Scientist> scientistRepo;
    Repository<Equipment> equipmentRepo;
    Repository<Chemical> chemicalRepo;

    // ---------- Master lists for Laboratory / Project / Experiment ----------
    MyVector<Laboratory*> labs;
    MyVector<Project*> projects;
    MyVector<Experiment*> experiments;

    int choice;
    do {
        cout << "\n================ MAIN MENU ================" << endl;
        cout << "1. Scientist Management" << endl;
        cout << "2. Equipment Management" << endl;
        cout << "3. Chemical Management" << endl;
        cout << "4. Laboratory Management" << endl;
        cout << "5. Project Management" << endl;
        cout << "6. Experiment Management" << endl;
        cout << "7. Exit" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            scientistMenu(scientistRepo);
        }
        else if (choice == 2) {
            equipmentMenu(equipmentRepo);
        }
        else if (choice == 3) {
            chemicalMenu(chemicalRepo);
        }
        else if (choice == 4) {
            laboratoryMenu(labs, scientistRepo, chemicalRepo);
        }
        else if (choice == 5) {
            projectMenu(projects);
        }
        else if (choice == 6) {
            experimentMenu(experiments, projects, scientistRepo, equipmentRepo, chemicalRepo);
        }
        else if (choice != 7) {
            cout << "Invalid choice, try again." << endl;
        }

    } while (choice != 7);

    cout << "\n----- Cleaning up and exiting -----" << endl;

    for (int i = 0; i < experiments.size(); i++) {
        delete experiments[i];
    }


    for (int i = 0; i < projects.size(); i++) {
        delete projects[i];
    }

    for (int i = 0; i < labs.size(); i++) {
        delete labs[i];
    }

    

    cout << "Goodbye!" << endl;
    return 0;
}
