#pragma once

#include <iostream>
#include <windows.h>


class matrix
{
    int size;
    int* array;

public:
    matrix(int n = 0) : size(n) {
        setSizeOfArr(n);
    }

    ~matrix() {
        if (array) {
            delete array;
        }
    }

    matrix& mul(matrix& ob1, matrix& ob2);
    matrix& add(matrix& ob1, matrix& ob2);

    void calculateArray() {
        // cout << "¬ведите значени€ в массиве:" << endl;
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                // cin >> array[i * size + k];
            }
        }
    }

    void setSizeOfArr(int n) {
        size = n;
        if (array)
            delete array;
        array = new int[size * size];
    }

    int getSizeOfArr() {
        return size;
    }

    //void showArray() {
    //    for (int i = 0; i < size; i++) {
    //        for (int k = 0; k < size; k++) {
    //            cout << array[i * size + k] << " ";
    //        }
    //        cout << endl;
    //    }
    //}
};



