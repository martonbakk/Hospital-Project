#include "Patient.h"
#include "Doctor.h"

/// <summary>
/// Patient osztaly fuggvenyei
/// </summary>
void Patient::listAccountInformation(std::ostream& os) {
	os << "Role: PATIENT Username: " << _userName << " Full-name: " << _name
		<< " Mail: " << _mail << " Phonenumber: " << _phone;
	if (!_treated) {
		os << "\nYour currently reported sympthoms: " << _sympthoms << "\nMedicines you will get:\n" << _medicinesToGet << '\n';
	}
	else {
		os << "\nYou are treated!\n";
	}
}

void Patient::listAllOption(std::ostream& os) {
	os << "Panaszok, tunetek leirasa (1)\nKilepes (2)\nValasszon opciot: ";
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



void Patient::publicData() {
	std::cout << _name << ":\n";
	std::cout << _sympthoms << '\n';
}

void Patient::medicineFromNurse(Dictionary& nurseMedicine) {
	for (size_t i = 0; i < nurseMedicine.getSize(); i++) {
		for (size_t j = 0; j < _medicinesToGet.getSize(); j++)
		{
			if (nurseMedicine[i]._value == _medicinesToGet[j]._value) //Ha van a novernel olyan ami a betegnek kell
			{
				if (nurseMedicine[i]._key - _medicinesToGet[j]._key >= 0)
				{
					int temp = _medicinesToGet[j]._key;
					_medicinesToGet[j]._key -= nurseMedicine[i]._key;
					nurseMedicine[i]._key -= temp;
				}
				else {
					_medicinesToGet[j]._key -= nurseMedicine[i]._key;
					nurseMedicine[i]._key = 0;
				}
			}
		}
	}
}

void Patient::medicineReply(const DictionaryEntry& doctorReply) {
	_medicinesToGet.push_back(doctorReply);
}