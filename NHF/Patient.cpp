#include "Patient.h"
#include "Doctor.h"

/// <summary>
/// Patient osztaly fuggvenyei
/// </summary>
void Patient::listAccountInformation(std::ostream& os) {
	os << "Role: PATIENT Username: " << userName << " Full-name: " << name
		<< " Mail: " << mail << " Phonenumber: " <<phone;
	if (!treated) {
		os << "\nYour currently reported sympthoms: " << sympthoms << "\nMedicines you will get:\n" << medicinesToGet << '\n';
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
	ss >> accountId;
	sympthoms = "";
	while (ss.get(ch) && ch != '}')
	{
		if(ch!='{'&&ch!='\n')
			sympthoms += ch;
	}
	while (ss.get(ch) && ch != '}')
	{
		if (ch != '{')
			med += ch;
	}
	std::stringstream ss2(med.getText());
	medicinesToGet.readFile(ss2);
	ss >> docID >> treated >> userName >> name >> lname >> mail >> phone;
	name += lname;
}


void Patient::sendData(std::ostream& os) {
	os << accountId << "\n{" << sympthoms << "}";
	os << "\n{" << medicinesToGet.getSize() << ' ';
	for (size_t i = 0; i < medicinesToGet.getSize(); i++)
	{
		os << medicinesToGet[i].value << " " << medicinesToGet[i].key<<" ";
	}
	os<<"}\n" << docID << '\n' << treated << '\n' << userName << '\n' << name << '\n' << mail << '\n' << phone << "* \n";
}


void Patient::setSympthoms(const String& symp) {
	sympthoms = symp;
}



void Patient::publicData(std::ostream& os) {
	os << name << ":\n";
	os<< sympthoms << '\n';
}

void Patient::medicineFromNurse(Dictionary& nurseMedicine) {
	for (size_t i = 0; i < nurseMedicine.getSize(); i++) {
		for (size_t j = 0; j < medicinesToGet.getSize(); j++)
		{
			if (nurseMedicine[i].value == medicinesToGet[j].value) //Ha van a novernel olyan ami a betegnek kell
			{
				if (nurseMedicine[i].key - medicinesToGet[j].key >= 0)
				{
					int temp = medicinesToGet[j].key;
					medicinesToGet[j].key -= nurseMedicine[i].key;
					nurseMedicine[i].key -= temp;
				}
				else {
					medicinesToGet[j].key -= nurseMedicine[i].key;
					nurseMedicine[i].key = 0;
				}
			}
		}
	}
}

void Patient::medicineReply(const DictionaryEntry& doctorReply) {
	medicinesToGet.push_back(doctorReply);
}