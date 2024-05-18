#ifndef PASSWORD_H
#define PASSWORD_H

#include "myString.h"
#include "memtrace.h"

enum AccountType {
	ad = 1,
	doc = 2,
	pat = 3,
	nur = 4
};

/// @Password ///
/*
* A jelszo osztaly. 
*/
struct Password {
	String pwd;
	String uname;
	int accountID;
	int type;
public:
	Password(int id = 0, int type = 0, const char* uname = "UNKNOWN", const char* pwd = "UNKNOWN") :pwd(pwd), uname(uname), accountID(id), type(type) {}
	void loadData(const String& passwordINF);		//adatok betoltese egy stringrol
	void sendData(std::ostream& os);				//adatok kiirasa egy os-re
	bool operator==(const Password& rhs) const;		//osszehasonlito operator
	Password& operator=(const Password& rhs);		//egyenloseg operator
public:
	friend std::ifstream& operator>>(std::ifstream& is, Password& member);	//inserter operator fajlbol olvasashoz
	friend std::ofstream& operator<<(std::ofstream& is, Password& member);	//kiiro operator a fajlba irashoz
};

#endif