#include "Patient.h"
#include "Doctor.h"

/// <summary>
/// Patient osztaly fuggvenyei
/// </summary>
void Patient::listAccountInformation() {
	std::cout << "Role: PATIENT Username: " << _userName << " Full-name: " << _name
		<< " Mail: " << _mail << " Phonenumber: " << _phone;
	if (!_treated) {
		std::cout << "\nYour currently reported sympthoms: " << _sympthoms << "\nMedicines you will get:\n" << _medicinesToGet << '\n';
	}
	else {
		std::cout << "\nYou are treated!\n";
	}
}

void Patient::listAllOption() {
	std::cout << "Panaszok, tunetek leirasa (1)\nKilepes (2)\nValasszon opciot: ";
}

void Patient::loadData(const String& accountINF) {
	std::stringstream ss(accountINF.getText());
	String lname;
	char ch;
	String med="";
	ss >> _accountId;
	_sympthoms = "";
	while (ss.get(ch) && ch != '}')
	{
		if(ch!='{'&&ch!='\n')
			_sympthoms += ch;
	}
	while (ss.get(ch) && ch != '}')
	{
		if (ch != '{')
			med += ch;
	}
	std::stringstream ss2(med.getText());
	_medicinesToGet.readFile(ss2);
	ss >> _docID >> _treated >> _userName >> _name >> lname >> _mail >> _phone;
	_name += lname;
}


void Patient::sendData(std::ostream& os) {
	os << _accountId << "\n{" << _sympthoms << "}";
	os << "\n{" << _medicinesToGet.getSize() << ' ';
	for (size_t i = 0; i < _medicinesToGet.getSize(); i++)
	{
		os << _medicinesToGet[i]._value << " " << _medicinesToGet[i]._key<<" ";
	}
	os<<"}\n" << _docID << '\n' << _treated << '\n' << _userName << '\n' << _name << '\n' << _mail << '\n' << _phone << "* \n";
}


void Patient::setSympthoms(const String& symp) {
	_sympthoms = symp;
}

void Patient::setTreated(bool treat) {
	_treated = treat;
	_sympthoms = "";
}

void Patient::setDoc(const Doctor& doc) {
	_docID = doc.getAccountID();
}

void Patient::setMedicines(const Dictionary& medicines) {
	_medicinesToGet = medicines;
}


std::ifstream& operator>>(std::ifstream& is, Patient& member) {
	String data;
	char ch;
	while (is.get(ch) && ch != '*') {
		data += ch;
	}
	member.loadData(data);
	return is;
}

std::ofstream& operator<<(std::ofstream& os, Patient& member) {
	member.sendData(os);
	return os;
}