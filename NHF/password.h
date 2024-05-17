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

class Password {
	String _pwd;
	String _uname;
	int _accountID;
	AccountType _type;
public:
	Password(int id = 0, int type = 0, const char* uname = "UNKNOWN", const char* pwd = "UNKNOWN") :_pwd(pwd), _uname(uname), _accountID(id), _type(AccountType(type)) {}
	int getID() { return _accountID; }
	String getUserName() { return _uname; }
	String getPassword() { return _pwd; }
	int getAccountType() { return _type; }
	void loadData(const String& passwordINF);
	void sendData(std::ostream& os);
	bool operator==(const Password& rhs) const;
	Password& operator=(const Password& rhs);
public:
	friend std::ifstream& operator>>(std::ifstream& is, Password& member);
	friend std::ofstream& operator<<(std::ofstream& is, Password& member);
};

#endif