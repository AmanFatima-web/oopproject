#include "Date.h"

Date::Date() {
    day = 1;
    month = 1;
    year = 2026;
}

Date::Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

void Date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

bool Date::isBefore(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::isAfter(const Date& other) const {
    if (year != other.year) return year > other.year;
    if (month != other.month) return month > other.month;
    return day > other.day;
}

void Date::display() const {
    cout << day << "-" << month << "-" << year;
}

ostream& operator<<(ostream& out, const Date& d) {
    out << d.day << "-" << d.month << "-" << d.year;
    return out;
}
