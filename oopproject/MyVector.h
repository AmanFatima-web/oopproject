#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
using namespace std;
//
// Simple custom dynamic array (template).
//

template <class T>
class MyVector {
private:
    T* items;       
    int count;        
    int capacity;     

    void resize() {
        capacity = capacity * 2;
        T* newItems = new T[capacity];
        for (int i = 0; i < count; i++) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
    }

public:
    MyVector() {
        capacity = 4;
        count = 0;
        items = new T[capacity];
    }

    MyVector(const MyVector& other) {
        capacity = other.capacity;
        count = other.count;
        items = new T[capacity];
        for (int i = 0; i < count; i++) {
            items[i] = other.items[i];
        }
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] items;
        capacity = other.capacity;
        count = other.count;
        items = new T[capacity];
        for (int i = 0; i < count; i++) {
            items[i] = other.items[i];
        }
        return *this;
    }

    ~MyVector() {
        delete[] items;
    }

    void push_back(const T& value) {
        if (count >= capacity) {
            resize();
        }
        items[count] = value;
        count++;
    }

   
    void removeAt(int index) {
        if (index < 0 || index >= count) {
            return;
        }
        for (int i = index; i < count - 1; i++) {
            items[i] = items[i + 1];
        }
        count--;
    }

    T& operator[](int index) {
        return items[index];
    }

    const T& operator[](int index) const {
        return items[index];
    }

    int size() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }
};

#endif
#pragma once
