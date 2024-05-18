#include "Nurse.h"

/// <summary>
/// Nurse osztaly fuggvenyei
/// </summary>
void Nurse::listAccountInformation(std::ostream& os) {
	os << "Role: NURSE Username: " << userName << " Full-name: " << name
		<< " Mail: " << mail << " Phonenumber: " << phone << '\n';
	if (medicinesToGive.getSize() == 0) {
		os << "No medicine to give\n";
	}
	else {
		os << "The following medicines need to be served:\n" << medicinesToGive<<'\n';
	}
}

void Nurse::listAllOption(std::ostream& os) {
	os << "Gyogyszer adagolasa a betegeknek (1)\nGyogyszer kivetele a raktarbol(2)\nKilepes (3)\nVALASSZON OPCIOT: ";
}

void Nurse::loadData(const String& accountINF) {
	std::stringstream ss(accountINF.getText());
	String lname;
	char ch;
	String med = "";
	ss >> accountId;
	while (ss.get(ch) && ch != '}')
	{
		if (ch != '{')
			med += ch;
	}
	std::stringstream ss2(med.getText());
	medicinesToGive.readFile(ss2);
	ss >> userName >> name >> lname >> mail >> phone;
	name += lname;
}

void Nurse::sendData(std::ostream& os) {
	os << accountId << '\n';
	os << "{" << medicinesToGive.getSize() << ' ';
	for (size_t i = 0; i < medicinesToGive.getSize(); i++)
	{
		os << medicinesToGive[i].value << " " << medicinesToGive[i].key << " ";
	}
	os << "}\n" << userName << '\n' << name << '\n' << mail << '\n' << phone << "*\n";
}



void Nurse::medicineLog(Patient& patient) {
	patient.medicineFromNurse(medicinesToGive);
}

void Nurse::getMedicine(Dictionary& medicines, int key, const char* value) {
	bool gotMed=false;
	for (size_t i = 0; i < medicines.getSize(); i++) {
		if (medicines[i].value == value) {
			if (medicines[i].key - key < 0) {
				throw "THERE IS NO ENOUGH MEDICINE IN THE STORE";
			}
			else {
				medicines[i].key -= key;
				medicinesToGive.push_back(DictionaryEntry(key, value));
				gotMed = true;
			}
		}
	}
	if (!gotMed) throw "THERE IS NO PROPER MEDICIN YOU ARE LOOKING FOR";
}
