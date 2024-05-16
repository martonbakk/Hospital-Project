#ifndef ARRAY_H
#define ARRAY_H

#include "Account.h"

#include <iostream>
#include <fstream>
#include <string>


template<class T>
class Array{
	size_t _len;
	T* _array;

public:
	Array(size_t len=0):_len(len),_array(new T[_len]){}	//konstruktor
	~Array();											//destruktor
public:
	void push_back(const T& element);					//hatulra berakra
	void delete_element(const T& element);				//kitorol egy elemet
	T& operator[](size_t i) const;						//visszaadja a tomb i. tagjat
	size_t getLen() const { return _len; }
	Array& operator=(const Array& rhs);
	void readFile(const char* FILENAME);
	void writeFile(const char* FILENAME);
public:
	template<typename P>
	size_t indexOfElement(P pred);
};

template<class T>
template<typename P>
size_t Array<T>::indexOfElement(P pred) {
	for (size_t i = 0; i < _len; i++)
	{
		if (pred(_array[i]))
			return i;
	}
	return -1;
}

template<class T>
void Array<T>::readFile(const char* FILENAME) {
	std::ifstream fs;
	fs.open(FILENAME);
	if (fs.is_open()) {
		int db=0;
		fs >> db;
		for (int i = 0; i < db; i++)
		{
			T member;
			fs>>member;
			push_back(member);
		}
	}
	else {
		throw "ARRAY: CAN NOT OPEN FILE TO READ";
	}
	fs.close();
}

template<class T>
void Array<T>::writeFile(const char* FILENAME) {
	std::ofstream of(FILENAME);
	if (of.is_open())
	{
		of << _len << '\n';
		for (size_t i = 0; i < _len; i++) {
			of<<_array[i];
		}
	}
	else {
		throw "ARRAY: CAN NOT OPEN FILE TO WRITE";
	}
}

template<class T>
Array<T>& Array<T>::operator=(const Array& rhs) {
	_len = rhs._len;
	delete[] _array;
	_array = new T[_len];
	for (size_t i = 0; i < _len; i++) {
		_array[i] = rhs._array[i];
	}
	return *this;
}

template<class T>
Array<T>::~Array() {
	delete[] _array;
}

template<class T>
void Array<T>::push_back(const T& element) {
	T* newArray = new T[_len + 1];
	for (size_t i = 0; i < _len; i++) {
		
		newArray[i] = _array[i];
	}
	newArray[_len++] = element;
	delete[] _array;
	_array = newArray;
}

template<class T>
void Array<T>::delete_element(const T& element) {
	size_t newSize = 0;
	T* newArray = new T[_len - 1];
	bool deleted = false;
	for (size_t i = 0; i < _len; i++) {
		if (element == _array[i]){
			deleted = true;
		}
		else {
			newArray[newSize++] = _array[i];
		}
	}
	if (deleted) {
		_len--;
		delete[] _array;
		_array = newArray;
	}
}

template<class T>
T& Array<T>::operator[](size_t i) const{
	if (_len == 0)
		throw "DINARRAY: THE ARRAY IS EMPTY";
		
	if (i >= _len)
		throw "DINARRAY: INDEX ERROR";

	return _array[i];
}

#endif //ARRAY_H