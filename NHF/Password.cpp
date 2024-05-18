#include "password.h"

#include <sstream>
#include <string>
#include <fstream>

Password& Password::operator=(const Password& rhs) {
	pwd = rhs.pwd;
	uname = rhs.uname;
	accountID = rhs.accountID;
	type = rhs.type;
	return *this;
}

bool Password::operator==(const Password& rhs) const {
	return (accountID == rhs.accountID);
}

void Password::loadData(const String& passwordINF) {
	std::stringstream ss(passwordINF.getText());
	ss >> accountID >> type >> uname >> pwd;
}

void Password::sendData(std::ostream& os) {
	os << accountID << '\n' << type << '\n' << uname << '\n' << pwd << "*\n";
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