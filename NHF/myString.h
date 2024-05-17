#pragma once
#include <iostream>
#include "memtrace.h"

class String
{
	size_t _len;		//lezaro nullaval a String hossza
	char* _content;		//char pointer
public:
	String();
	String(const char* CONTENT);
	String(const String& str);
	~String();

public:
	//Getter fv.
	/*
	* A String _contentjet kapjuk meg vele
	*/
	char* getText() const;
	/*
	* A string _lenjet kapjuk vissza
	*/
	size_t getLen() const;

public:
	//Operatorok
	/*
	* Egyenlosegjel operator const char*-re
	* @param content - Ezkerul bele a Stringbe
	*/
	String& operator=(const char* content);

	/*
	* Plusz egyenlo operator, osszeadjuk a ket Stringet
	* A hozzafuzott es az eredeti String kozott space van
	* @param str - Ezt adjuk hozzá a Stringhez
	*/
	String& operator+=(const String& str);

	/*
	* Plusz operator, osszeadjuk a ket Stringet
	* A hozzafuzott es az eredeti String kozott space van
	* @param str - Ezt adjuk hozzá a Stringhez
	*/
	String operator+(const String& str) const;

	/*
	* Plusz operator, osszeadjuk a Stringet es a karaktertombot
	* A String es a char tomb kozott nincs space
	* @param str - Ezt adjuk hozzá a Stringhez
	*/
	String operator+(const char* str) const;

	/*
	* Egyenlosegjel operator Stringre
	* @param str - Ezt a stringet masoljuk bele a masik stringbe
	*/
	String& operator=(const String& str);

	/*
	* Egy adott karaktert dob vissza a Stringbol
	* @param i- index a karakterhez
	*/
	char& operator[](size_t i);

	/*
	* Két stringet hasonlít össze
	* @return - visszaadja, hogy egyenlõek-e
	*/
	bool operator==(const String& s1);

	/*
	* Egy char-t ad hozza a Stringhez
	* @return -visszaadja a kesz Stringet
	*/
	String& operator+=(const char& car);

	/*
	* String kiirasa
	*/
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	/*
	* Fajlbol olvasashoz szukseges fv.
	*/
	friend std::ifstream& operator>>(std::ifstream& os, String& str);
	/*
	* Standard input olvasasahoz szukseges fv.
	*/
	friend std::istream& operator>>(std::istream& os, String& str);
};