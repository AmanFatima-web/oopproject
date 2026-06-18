#include<iostream>
#include "MyString.h"

int MyString::calcLength(const char* text) const {
    int count = 0;
    while (text[count] != '\0') {
        count++;
    }
    return count;
}

MyString::MyString() {
    len = 0;
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const char* text) {
    if (text == nullptr) {
        len = 0;
        data = new char[1];
        data[0] = '\0';
        return;
    }
    len = calcLength(text);
    data = new char[len + 1];
    for (int i = 0; i < len; i++) {
        data[i] = text[i];
    }
    data[len] = '\0';
}

MyString::MyString(const MyString& other) {
    len = other.len;
    data = new char[len + 1];
    for (int i = 0; i < len; i++) {
        data[i] = other.data[i];
    }
    data[len] = '\0';
}

MyString::~MyString() {
    delete[] data;
}

MyString& MyString::operator=(const MyString& other) {
    if (this == &other) {
        return *this;
    }
    delete[] data;
    len = other.len;
    data = new char[len + 1];
    for (int i = 0; i < len; i++) {
        data[i] = other.data[i];
    }
    data[len] = '\0';
    return *this;
}

MyString MyString::operator+(const MyString& other) const {
    char* combined = new char[len + other.len + 1];
    for (int i = 0; i < len; i++) {
        combined[i] = data[i];
    }
    for (int i = 0; i < other.len; i++) {
        combined[len + i] = other.data[i];
    }
    combined[len + other.len] = '\0';

    MyString result(combined);
    delete[] combined;
    return result;
}

bool MyString::operator==(const MyString& other) const {
    if (len != other.len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

char MyString::operator[](int index) const {
    if (index < 0 || index >= len) {
        return '\0';
    }
    return data[index];
}

int MyString::length() const {
    return len;
}

const char* MyString::c_str() const {
    return data;
}

bool MyString::isEmpty() const {
    return len == 0;
}

ostream& operator<<(ostream& out, const MyString& str) {
    out << str.data;
    return out;
}

istream& operator>>(istream& in, MyString& str) {
    char buffer[500];
    in.getline(buffer, 500);
    str = MyString(buffer);
    return in;
}
int main() {
    return 0;
}