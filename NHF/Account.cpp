#include "Account.h"

void Account::editAccountInformation(const char* Name, const char* Mail, const char* Phone) {
        name = Name;
        mail = Mail;
        phone = Phone;
}

std::ifstream& operator>>(std::ifstream& is, Account& member) {
	String data;
	char ch;
	while (is.get(ch) && ch != '*') {
		data += ch;
	}
	member.loadData(data);
	return is;
}

std::ofstream& operator<<(std::ofstream& os, Account& member) {
	member.sendData(os);
	return os;
}