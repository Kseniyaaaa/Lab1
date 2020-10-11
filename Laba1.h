#pragma once

#include <iostream>
#include <windows.h>

class matrix {
    matrix& mul(matrix& ob1, matrix& ob2);
    matrix& add(matrix& ob1, matrix& ob2);
    void calculateArray();
    void setSizeOfArr(int n);
    //void showArray();
};


