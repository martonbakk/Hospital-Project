#include "Nurse.h"

/// <summary>
/// Nurse osztaly fuggvenyei
/// </summary>
void Nurse::listAccountInformation() {
	std::cout << "Role: NURSE Username: " << _userName << " Full-name: " << _name
		<< " Mail: " << _mail << " Phonenumber: " << _phone << '\n';
	if (_medicinesToGive.getSize() == 0) {
		std::cout << "No medicine to give\n";
	}
	else {
		std::cout << "The following medicines need to be served:\n" << _medicinesToGive<<'\n';
	}
}

void Nurse::listAllOption() {
	std::cout << "Gyogyszer adagolasa a betegeknek (1)\nGyogyszer kivetele a raktarbol(2)\nKilepes (3)\nVALASSZON OPCIOT: ";
}

void Nurse::loadData(const String& accountINF) {
	std::stringstream ss(accountINF.getText());
	String lname;
	char ch;
	String med = "";
	ss >> _accountId;
	while (ss.get(ch) && ch != '}')
	{
		if (ch != '{')
			med += ch;
	}
	std::stringstream ss2(med.getText());
	_medicinesToGive.readFile(ss2);
	ss >> _userName >> _name >> lname >> _mail >> _phone;
	_name += lname;
}

void Nurse::sendData(std::ostream& os) {
	os << _accountId << '\n';
	os << "{" << _medicinesToGive.getSize() << ' ';
	for (size_t i = 0; i < _medicinesToGive.getSize(); i++)
	{
		os << _medicinesToGive[i]._value << " " << _medicinesToGive[i]._key << " ";
	}
	os << "}\n" << _userName << '\n' << _name << '\n' << _mail << '\n' << _phone << "*\n";
}



void Nurse::medicineLog(Patient& patient) {
	for (size_t i = 0; i < _medicinesToGive.getSize(); i++) {
		for (size_t j = 0; j < patient.patientNeededMedicines().getSize(); j++)
		{
			if (_medicinesToGive[i]._value == patient.patientNeededMedicines()[j]._value) //Ha van a novernel olyan ami a betegnek kell
			{
				if (_medicinesToGive[i]._key - patient.patientNeededMedicines()[j]._key >= 0)
				{
					int temp = patient.patientNeededMedicines()[j]._key;
					patient.patientNeededMedicines()[j]._key -= _medicinesToGive[i]._key;
					_medicinesToGive[i]._key -= temp;
				}
				else {
					patient.patientNeededMedicines()[j]._key -= _medicinesToGive[i]._key;
					_medicinesToGive[i]._key = 0;
				}
			}
		}
	}
}

void Nurse::getMedicine(Dictionary& medicines, int key, const char* value) {
	bool gotMed=false;
	for (size_t i = 0; i < medicines.getSize(); i++) {
		if (medicines[i]._value == value) {
			if (medicines[i]._key - key < 0) {
				throw "THERE IS NO ENOUGH MEDICINE IN THE STORE";
			}
			else {
				medicines[i]._key -= key;
				_medicinesToGive.push_back(DictionaryEntry(key, value));
				gotMed = true;
			}
		}
	}
	if (!gotMed) throw "THERE IS NO PROPER MEDICIN YOU ARE LOOKING FOR";
}


std::ifstream& operator>>(std::ifstream& is, Nurse& member) {
	String data;
	char ch;
	while (is.get(ch) && ch != '*') {
		data += ch;
	}
	member.loadData(data);
	return is;
}

std::ofstream& operator<<(std::ofstream& os, Nurse& member) {
	member.sendData(os);
	return os;
}