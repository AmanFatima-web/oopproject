#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

// Simple date class storing day, month and year.
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();                              // defaults to 01-01-2026
    Date(int d, int m, int y);

    void setDate(int d, int m, int y);
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool isBefore(const Date& other) const;   // true if this date < other
    bool isAfter(const Date& other) const;    // true if this date > other

    void display() const;  // prints as dd-mm-yyyy

    friend ostream& operator<<(ostream& out, const Date& d);
};

#endif
#pragma once
