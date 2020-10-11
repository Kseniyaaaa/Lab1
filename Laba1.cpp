#include <iostream>
#include <windows.h>
#include "Laba1.h"

using namespace std;

matrix& matrix::mul(matrix& ob1, matrix& ob2)
{
    this->setSizeOfArr((ob1.getSizeOfArr(), ob2.getSizeOfArr()));

    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            this->array[i * size + k] = 0;
            for (int j = 0; j < size; j++) {
                this->array[i * size + k] += ob1.array[i * size + j] * ob2.array[j * size + k];
            }
        }
    }
    return *this;
};

matrix& matrix::add(matrix& ob1, matrix& ob2)
{
    this->setSizeOfArr((ob1.getSizeOfArr(), ob2.getSizeOfArr()));
    for (int i = 0; i <= size; i++) {
        for (int k = 0; k < size; k++) {
            this->array[i + k] = ob1.array[i + k] + ob2.array[i + k];
        }
    }
    return *this;
};