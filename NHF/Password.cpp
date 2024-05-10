#include "password.h"

#include <sstream>
#include <string>
#include <fstream>

Password& Password::operator=(const Password& rhs) {
	_pwd = rhs._pwd;
	_uname = rhs._uname;
	_accountID = rhs._accountID;
	_type = rhs._type;
	return *this;
}

bool Password::operator==(const Password& rhs) const {
	return (_accountID == rhs._accountID);
}

void Password::loadData(const String& passwordINF) {
	std::stringstream ss(passwordINF.getText());
	int type;
	ss >> _accountID >> type >> _uname >> _pwd;
	_type = AccountType(type);
}

void Password::sendData(std::ostream& os) {
	os << _accountID << '\n' << _type << '\n' << _uname << '\n' << _pwd << "*\n";
}

std::ifstream& operator>>(std::ifstream& is, Password& member) {
	String data;
	char ch;
	while (is.get(ch) && ch != '*') {
		data += ch;
	}
	member.loadData(data);
	return is;
}

std::ofstream& operator<<(std::ofstream& os, Password& member) {
	member.sendData(os);
	return os;
}