#pragma once

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Storage
{
protected:
	vector<T>* items;

public:
	Storage<T>();
	void add(T* item);
	void remove(int i);
	vector<T>* getAll();
};


template<typename T>
inline Storage<T>::Storage()
{
	cout << "constructor 2\n";
	this->items = new vector<T>();
}


template<typename T>
void Storage<T>::add(T* item)
{
	this->items->push_back(*item);
}


template<typename T>
void Storage<T>::remove(int i)
{
	if (i >= 0 && i < this->items->size())
	{
		this->items->erase(this->items->begin() + i);
		return;
	}

	throw "Такой записи нет.";
}


template<typename T>
vector<T>* Storage<T>::getAll()
{
	return this->items;
}