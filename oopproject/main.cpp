#include <iostream>
using namespace std;



class MyString {
private:
    char* str;
    int length;

  
    int customStrLen(const char* s) {
        int len = 0;
        while (s[len] != '\0') {
            len++;
        }
        return len;
    }

    void customStrCpy(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    
    bool customStrCmp(const char* s1, const char* s2) const {
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0') {
            if (s1[i] != s2[i]) return false;
            i++;
        }
        return (s1[i] == s2[i]);
    }

public:
 
    MyString() {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }


    MyString(const char* val) {
        if (val == nullptr) {
            length = 0;
            str = new char[1];
            str[0] = '\0';
        }
        else {
            length = customStrLen(val);
            str = new char[length + 1];
            customStrCpy(str, val);
        }
    }

 
    MyString(const MyString& source) {
        length = source.length;
        str = new char[length + 1];
        customStrCpy(str, source.str);
    }

    MyString& operator=(const MyString& rhs) {
        if (this == &rhs) return *this;
        delete[] str;
        length = rhs.length;
        str = new char[length + 1];
        customStrCpy(str, rhs.str);
        return *this;
    }

   
    bool operator==(const char* rhs) const {
        return customStrCmp(this->str, rhs);
    }


    const char* getCStr() const {
        return str;
    }


    ~MyString() {
        delete[] str;
    }
};


class Equipment {
protected:
    int equipmentID;
    MyString equipmentName;
    MyString status;
    bool isContaminated;
    MyString calibrationStatus;
    MyString lastUsedDate;

public:
    Equipment(int id, MyString name, MyString stat, bool contam, MyString calib, MyString date)
        : equipmentID(id), equipmentName(name), status(stat), isContaminated(contam), calibrationStatus(calib), lastUsedDate(date) {
    }

    virtual void performMaintenance() = 0;

    void sterilize() {
        isContaminated = false;
        status = MyString("Sterilized");
        cout << equipmentName.getCStr() << " (ID: " << equipmentID << ") has been sterilized.\n";
    }

    bool checkAvailability() {
        return (status == "Available" && !isContaminated);
    }

    virtual ~Equipment() {}
};

// 
// 3. CHILD CLASSES (INHERITANCE)
// 

// Class A: GlasswareAndDevice
class GlasswareAndDevice : public Equipment {
private:
    MyString volume;
    bool isReusable;

public:
    GlasswareAndDevice(int id,
        MyString name, MyString stat, bool contam, MyString calib, MyString date, MyString vol, bool reusable)
        : Equipment(id, name, stat, contam, calib, date), volume(vol), isReusable(reusable) {
    }

    void performMaintenance() override {
        cout << "Washing and autoclaving glassware: " << equipmentName.getCStr() << "\n";
    }

    void calibrate() {
        calibrationStatus = MyString("Calibrated");
        cout << equipmentName.getCStr() << " volume calibration completed.\n";
    }
};


class Instrument : public Equipment {
private:
    bool isCalibrated;

public:
    Instrument(int id, MyString name, MyString stat, bool contam, MyString calib, MyString date, bool calibrated)
        : Equipment(id, name, stat, contam, calib, date), isCalibrated(calibrated) {
    }

    void performMaintenance() override {
        cout << "Re-calibrating electronic sensors of " << equipmentName.getCStr() << "\n";
        isCalibrated = true;
        calibrationStatus = MyString("Certified");
    }
};


class HeavyMachinery : public Equipment {
private:
    double loadCapacity;
    bool requiresFuel;

public:
    HeavyMachinery(int id, MyString name, MyString stat, bool contam, MyString calib, MyString date, double capacity, bool fuel)
        : Equipment(id, name, stat, contam, calib, date), loadCapacity(capacity), requiresFuel(fuel) {
    }

    void performMaintenance() override {
        cout << "Checking hydraulic fluids and mechanical parts for " << equipmentName.getCStr() << "\n";
        status = MyString("Operational");
    }

    void inspect() {
        cout << "Inspecting " << equipmentName.getCStr() << ". Load capacity: " << loadCapacity << " tons.\n";
    }
};
int main(){
    {
        GlasswareAndDevice g1(
            1,
            "Beaker",
            "Available",
            false,
            "Not Calibrated",
            "2025-05-01",
            "500ml",
            true
        );
        g1.performMaintenance();
        g1.calibrate();
    }
    return 0;
    }