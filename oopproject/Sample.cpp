#include "Sample.h"

Sample::Sample(int id, MyString name, MyString t, MyString src, Date collected, MyString stat) {
    sampleID = id;
    sampleName = name;
    type = t;
    source = src;
    collectedDate = collected;
    status = stat;
}

void Sample::storeSample() {
    status = MyString("Stored");
    cout << "Sample \"" << sampleName << "\" has been stored safely." << endl;
}

MyString Sample::getSampleDetails() const {
    cout << "Sample ID: " << sampleID
        << " | Name: " << sampleName
        << " | Type: " << type
        << " | Source: " << source
        << " | Collected: " << collectedDate
        << " | Status: " << status << endl;
    return sampleName;
}

int Sample::getSampleID() const {
    return sampleID;
}

MyString Sample::getSampleName() const {
    return sampleName;
}
