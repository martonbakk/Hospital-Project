#include "Admin.h"
#include "Doctor.h"
#include "Patient.h"
#include "Nurse.h"
#include "array.h"
#include "password.h"

#include <string>

/// <summary>
/// Admin osztaly fuggvenyei
/// </summary>
void Admin::listAccountInformation(std::ostream& os) {
	os << "Role: ADMIN " << accountId << " " << userName << " " << name << " " << mail << " " << phone << " " << (verified ? "Verified" : "Not verified") << "\n";
}

void Admin::listAllOption(std::ostream& os) {
	os << "Fiokok torlese (1)\nFiokok szerkeztese (2)\nOsszes fiok listazasa (3) \nGyogyszerek torlese a raktarbol (4) \nUj admin fiok engedelyezese (5) \nDoktorok betegeinek korlatozasa (6)\nKilepes (7)\nVALASSZON OPCIOT: ";
}

void Admin::loadData(const String& accountINF) {
	std::stringstream ss(accountINF.getText());
	String lname;
	ss>> accountId >> verified >> userName >> name >> lname >> mail >> phone ;
	name += lname;
}
void Admin::sendData(std::ostream& os) {
	
	os << accountId << '\n' << verified << '\n' << userName << '\n' << name << '\n' << mail << '\n' << phone << "*\n";
}


void Admin::deleteMedicine(Dictionary& medicines, const char* medicine) {
	for (size_t i = 0; i < medicines.getSize(); i++){
		if (medicines[i].value==medicine){
			medicines[i].key = 0;
			medicines.sizeDecrement();
		}
	}
}


void Admin::listAllAccount(std::ostream& os, const Array<Patient>& patients, const Array<Nurse>& nurses, const Array<Admin>& admins, const Array<Doctor>& doctors) {
	os << "Option: Admin (1)\n";
	for (size_t i = 0; i < admins.size(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		admins[i].listAccountInformation(os);
	}
	os << "\nOption: Doctor (2)\n";
	for (size_t i = 0; i < doctors.size(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		doctors[i].listAccountInformation(os);
	}
	os << "Option: Nurse (3)\n";
	for (size_t i = 0; i < nurses.size(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		nurses[i].listAccountInformation(os);
	}
	os << "Option: Patient (4)\n";
	for (size_t i = 0; i < patients.size(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		patients[i].listAccountInformation(os);
	}
}

void Admin::listAllPatientAccount(std::ostream& os, const Array<Patient>& patients) {
	for (size_t i = 0; i < patients.size(); i++)
	{
		os << "Opcio " << i+1<<'\n';
		patients[i].listAccountInformation(os);
	}
}

void Admin::setDoctorsMaxPatientNum(int num) {
	if (num > 1)
		Doctor::setMaxPatientNum(num);
	else
		throw "ADMIN: SET DOC MAX PATIENT";
}

void  Admin::verifyAdmins(Admin& user) {
	user.verified = true;
}

void Admin::deleteAccountfromArray(Array<Doctor>& doctors, Array<Password>& passwords,Array<Patient>& patients, Patient& element) {
	for (size_t i = 0; i < passwords.size(); i++){
		if (passwords[i].accountID == element.getAccountID())
			passwords.delete_element(passwords[i]);
	}
	for (size_t i = 0; i < doctors.size(); i++){
		doctors[i].deletePatient(element);
	}
	patients.delete_element(element);
}

