#include "Doctor.h"
#include "Patient.h"

/// <summary>
/// Doktor osztaly fuggvenyei
/// </summary>
void Doctor::listAccountInformation(std::ostream& os) {
	os << "Role: DOCTOR " << _accountId << " " << _userName << " " << _name << " " << _mail << " " << _phone << "\n"
		<< "You can have " << _maxPatientNum - _patientNum << " more Patients. Your current patients:\n";
	for (int i = 0; i < _patientNum; i++)
	{
		_patients[i]->publicData();
	}
	if (_patientNum==0)
	{
		os << "You have no patients\n\n";
	}
}

void Doctor::listPatients(std::ostream& os) {
	for (int i = 0; i < _patientNum; i++){
		std::cout << "Option: (" << i + 1 << ")\n";
		_patients[i]->listAccountInformation(os);
	}
	if (_patientNum == 0)
	{
		std::cout << "You have no patients\n\n";
	}
}

int Doctor::listAllPatients(Array<Patient>& patients) {
	int db = 0;
	for (size_t i = 0; i < patients.getLen(); i++)
	{
		if (patients[i].getDocID() == -1) {
			patients[i].publicData();
			db++;
		}
	}
	return db;
}

void Doctor::listAllOption(std::ostream& os) {
	os << "Beteg panaszainak elolvasasa (1)\nBeteg felvetele (2)\nGyogyszer felirasa mar felvett betegeknek (3)\nKilepes (4)\nVALASSZON OPCIOT: ";
}

void Doctor::setPatients(Array<Patient>& patients) {
	int j = 0;
	for (size_t i = 0; i < patients.getLen(); i++){
		if (patients[i].getDocID() == _accountId) {
			_patients.push_back(&patients[i]);
		}
	}
}

void Doctor::loadData(const String&accountINF) {
	std::stringstream ss(accountINF.getText());
	String lname;
	ss >>_accountId >> _patientNum >> _userName >> _name >> lname >> _mail >> _phone;
	_name += lname;
}
void Doctor::sendData(std::ostream& os) {
	os<<_accountId<<'\n'<<_patientNum<<'\n' << _userName << '\n' << _name << '\n' << _mail << '\n' << _phone << "*\n";
}

void Doctor::seePatientsSympthoms(const Array<Patient>& patients) {
	for (size_t i = 0; i < patients.getLen(); i++)
	{
		patients[i].publicData();
	}
}

void Doctor::getPatient(Patient* patient) {
	if (_patientNum + 1 > _maxPatientNum)
		throw "DOCTOR: YOU HAVE REACHED THE PATIENT LIMIT";
	if (patient->getDocID() != -1)
		throw "This patient already have a doctor";
	patient->setDoc(_accountId);
	_patients.push_back(patient);
}

void Doctor::replyPatientSympthoms(const Dictionary& medicines,const DictionaryEntry& reply, int idx) {
	bool medicineOnStorage = false;
	bool enough = false;
	for (size_t i = 0; i < medicines.getSize(); i++)
	{
		if (medicines[i]._value == reply._value) {
			medicineOnStorage = true;
			if (medicines[i]._key >= reply._key) {
				enough = true;
			}
		}
	}
	if(medicineOnStorage&&enough){
		_patients[idx]->medicineReply(reply);
	}
	else if (!enough&&medicineOnStorage) {
		throw "THERE IS NO ENOUGH MEDICINE";
	}
	else {
		throw "THERE IS NO MEDICINE YOU ARE LOOKING FOR";
	}
}

void Doctor::setMaxPatientNum(int num) {
	_maxPatientNum = num;
}

int Doctor::_maxPatientNum = 5;

void Doctor::deletePatient(Patient& pat) {
	for (size_t j = 0; j < _patients.size(); j++)
	{
		if (_patients[j]->getAccountID() == pat.getAccountID()) {
			_patientNum--;
		}
	}
}