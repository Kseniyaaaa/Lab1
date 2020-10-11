#include <iostream>
#include <windows.h>
#include "Laba1.h"

using namespace std;

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
        cout << "Введите значения в массиве:" << endl;
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                cin >> array[i * size + k];
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

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    matrix obj1, obj2, obj3, obj4;
    cout << "Размерность первого массива: ";
    cin >> n;
    obj1.setSizeOfArr(n);
    obj1.calculateArray();
    cout << "Размерность второго массива: ";
    cin >> n;
    obj2.setSizeOfArr(n);
    obj2.calculateArray();
    cout << endl << " Первый массив: " << endl;
   // obj1.showArray();
    cout << endl << " Второй массив: " << endl;
   // obj2.showArray();
    obj3.setSizeOfArr((obj1.getSizeOfArr(), obj2.getSizeOfArr()));
    cout << endl << " Умножение массивов: " << endl;
    //obj3.mul(obj1, obj2).showArray();
    cout << endl << " Сложение массивов: " << endl;
    //obj4.add(obj1, obj2).showArray();
    cout << endl;
    system("pause");
}