#ifndef ARRAY_H
#define ARRAY_H

#include "memtrace.h"

#include "Account.h"

#include <iostream>
#include <fstream>
#include <string>

///@Dinamikus tomb///
/*
* A program STL tarolokat nem hasznal. Az adatok tarolasat ez az osztaly valositja meg reszben. A dinamikus tomb hasznalhato Admin, Doctor, Patient es Nurse osztalyokkal, tovabba
* kompatibilis minden alap valtozoval is (pl.:int). Az Array osztaly funkcionalitasai hasonlitanak az std::vector-hoz. Iteratora a tombnek nincs, cimzo operatora viszont van. A tomb 
* adatait ezzel az operatorral lehet elerni. 
*/
template<class T>
class Array{
	size_t len;		//A tarolo hozza
	T* data;		//A tomb amiben az adatokat taroljuk
public:
	Array(size_t len=0):len(len), data(new T[len]){}	//konstruktor
	~Array();											//destruktor
public:
	void push_back(const T& element);			//hatulra berakra
	void delete_element(const T& element);		//kitorol egy elemet
	T& operator[](size_t i) const;				//visszaadja a tomb i. tagjat			
	Array& operator=(const Array& rhs);			//Masolo operator
	void readFile(const char* FILENAME);		//Fajlbol olvasas
	void writeFile(const char* FILENAME);		//Fajlba iras
	size_t size()const { return len; }			//Visszaadja a tomb hosszat
public:
	template<typename P>
	size_t indexOfElement(P pred) const;		//Visszaadja az indxet annak az elemnek amire teljesul a predikatum
};

template<class T>
template<typename P>
size_t Array<T>::indexOfElement(P pred) const{
	for (size_t i = 0; i < len; i++){
		if (pred(data[i]))
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
		of << len << '\n';
		for (size_t i = 0; i < len; i++) {
			of<< data[i]<<' ';
		}
	}
	else {
		throw "ARRAY: CAN NOT OPEN FILE TO WRITE";
	}
}

template<class T>
Array<T>& Array<T>::operator=(const Array& rhs) {
	len = rhs.len;
	delete[] data;
	data = new T[len];
	for (size_t i = 0; i < len; i++) {
		data[i] = rhs.data[i];
	}
	return *this;
}

template<class T>
Array<T>::~Array() {
	delete[] data;
}

template<class T>
void Array<T>::push_back(const T& element) {
	T* newArray = new T[len + 1];
	for (size_t i = 0; i < len; i++) {
		
		newArray[i] = data[i];
	}
	newArray[len++] = element;
	delete[] data;
	data = newArray;
}

template<class T>
void Array<T>::delete_element(const T& element) {
	size_t newSize = 0;
	T* newArray = new T[len - 1];
	bool deleted = false;
	for (size_t i = 0; i < len; i++) {
		if (element == data[i]){
			deleted = true;
		}
		else {
			newArray[newSize++] = data[i];
		}
	}
	if (deleted) {
		len--;
		delete[] data;
		data = newArray;
	}
}

template<class T>
T& Array<T>::operator[](size_t i) const{
	if (len == 0)
		throw "DINARRAY: THE ARRAY IS EMPTY";
		
	if (i >= len)
		throw "DINARRAY: INDEX ERROR";

	return data[i];
}

#endif //ARRAY_H