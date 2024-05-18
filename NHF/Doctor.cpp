#include "Doctor.h"
#include "Patient.h"

/// <summary>
/// Doktor osztaly fuggvenyei
/// </summary>
void Doctor::listAccountInformation(std::ostream& os) {
	os << "Role: DOCTOR " << accountId << " " << userName << " " << name << " " << mail << " " << phone << "\n"
		<< "You can have " << maxPatientNum - patientNum << " more Patients. Your current patients:\n";
	for (int i = 0; i < patientNum; i++){
		patients[i]->publicData(os);
	}
	if (patientNum==0){
		os << "You have no patients\n\n";
	}
}

void Doctor::listPatients(std::ostream& os) {
	for (int i = 0; i < patientNum; i++){
		std::cout << "Option: (" << i + 1 << ")\n";
		patients[i]->listAccountInformation(os);
	}
	if (patientNum == 0){
		std::cout << "You have no patients\n\n";
	}
}

int Doctor::listAllPatients(std::ostream& os, Array<Patient>& patients) {
	int db = 0;
	for (size_t i = 0; i < patients.size(); i++){
		if (patients[i].getDocID() == -1) {
			patients[i].publicData(os);
			db++;
		}
	}
	return db;
}

void Doctor::listAllOption(std::ostream& os) {
	os << "Beteg panaszainak elolvasasa (1)\nBeteg felvetele (2)\nGyogyszer felirasa mar felvett betegeknek (3)\nKilepes (4)\nVALASSZON OPCIOT: ";
}

void Doctor::setPatients(Array<Patient>& patientsarr) {
	for (size_t i = 0; i < patientsarr.size(); i++){
		if (patientsarr[i].getDocID() == accountId) {
			patients.push_back(&patientsarr[i]);
		}
	}
}

void Doctor::loadData(const String&accountINF) {
	std::stringstream ss(accountINF.getText());
	String lname;
	ss >>accountId >> patientNum >> userName >> name >> lname >> mail >> phone;
	name += lname;
}
void Doctor::sendData(std::ostream& os) {
	os<<accountId<<'\n'<<patientNum<<'\n' << userName << '\n' << name << '\n' << mail << '\n' <<phone << "*\n";
}

void Doctor::seePatientsSympthoms(std::ostream& os, const Array<Patient>& patients) {
	for (size_t i = 0; i < patients.size(); i++){
		patients[i].publicData(os);
	}
}

void Doctor::getPatient(Patient* patient) {
	if (patientNum + 1 > maxPatientNum)
		throw "DOCTOR: YOU HAVE REACHED THE PATIENT LIMIT";
	if (patient->getDocID() != -1)
		throw "This patient already have a doctor";
	patient->setDoc(accountId);
	patients.push_back(patient);
}

void Doctor::replyPatientSympthoms(const Dictionary& medicines,const DictionaryEntry& reply, int idx) {
	bool medicineOnStorage = false;
	bool enough = false;
	for (size_t i = 0; i < medicines.getSize(); i++){
		if (medicines[i].value == reply.value) {
			medicineOnStorage = true;
			if (medicines[i].key >= reply.key) {
				enough = true;
			}
		}
	}
	if(medicineOnStorage&&enough){
		patients[idx]->medicineReply(reply);
	}
	else if (!enough&&medicineOnStorage) {
		throw "THERE IS NO ENOUGH MEDICINE";
	}
	else {
		throw "THERE IS NO MEDICINE YOU ARE LOOKING FOR";
	}
}

void Doctor::setMaxPatientNum(int num) {
	if (num < maxPatientNum) 
		throw "ERROR: WHILE SETTING THE PATIENT NUM: YOU CANT GIVE A LOWER NUMBER";
	maxPatientNum = num;
}

int Doctor::maxPatientNum = 5;

void Doctor::deletePatient(Patient& pat) {
	for (size_t j = 0; j < patients.size(); j++){
		if (patients[j]->getAccountID() == pat.getAccountID()) {
			patientNum--;
		}
	}
}