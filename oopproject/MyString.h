#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

class MyString {
private:
    char* data;   
    int len;     

    int calcLength(const char* text) const; 

public:
    MyString();                      
    MyString(const char* text);       
    MyString(const MyString& other);  // copy constructor
    ~MyString();                      // destructor

    MyString& operator=(const MyString& other);
    MyString operator+(const MyString& other) const;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;

    char operator[](int index) const;

    int length() const;
    const char* c_str() const;
    bool isEmpty() const;

    friend ostream& operator<<(ostream& out, const MyString& str);
    friend istream& operator>>(istream& in, MyString& str);
};

#endif
