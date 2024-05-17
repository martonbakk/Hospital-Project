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
	os << "Role: ADMIN " << _accountId << " " << _userName << " " << _name << " " << _mail << " " << _phone << " " << (_verified ? "Verified" : "Not verified") << "\n";
}

void Admin::listAllOption(std::ostream& os) {
	os << "Fiokok torlese (1)\nFiokok szerkeztese (2)\nOsszes fiok listazasa (3) \nGyogyszerek torlese a raktarbol (4) \nUj admin fiok engedelyezese (5) \nDoktorok betegeinek korlatozasa (6)\nKilepes (7)\nVALASSZON OPCIOT: ";
}

void Admin::loadData(const String& accountINF) {
	std::stringstream ss(accountINF.getText());
	String lname;
	ss>> _accountId >> _verified >> _userName >> _name >> lname >> _mail >> _phone ;
	_name += lname;
}
void Admin::sendData(std::ostream& os) {
	
	os << _accountId << '\n' << _verified << '\n' << _userName << '\n' << _name << '\n' << _mail << '\n' << _phone << "*\n";
}


void Admin::deleteMedicine(Dictionary& medicines, const char* medicine) {
	for (size_t i = 0; i < medicines.getSize(); i++){
		if (medicines[i]._value==medicine){
			medicines[i]._key = 0;
			medicines.sizeDecrement();
		}
	}
}


void Admin::listAllAccount(std::ostream& os, const Array<Patient>& patients, const Array<Nurse>& nurses, const Array<Admin>& admins, const Array<Doctor>& doctors) {
	os << "Option: Admin (1)\n";
	for (size_t i = 0; i < admins.getLen(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		admins[i].listAccountInformation(os);
	}
	os << "\nOption: Doctor (2)\n";
	for (size_t i = 0; i < doctors.getLen(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		doctors[i].listAccountInformation(os);
	}
	os << "Option: Nurse (3)\n";
	for (size_t i = 0; i < nurses.getLen(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		nurses[i].listAccountInformation(os);
	}
	os << "Option: Patient (4)\n";
	for (size_t i = 0; i < patients.getLen(); i++)
	{
		os << "Option " << i + 1 << ")\n";
		patients[i].listAccountInformation(os);
	}
}

void Admin::listAllPatientAccount(std::ostream& os, const Array<Patient>& patients) {
	for (size_t i = 0; i < patients.getLen(); i++)
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
	user._verified = true;
}

void Admin::deleteAccountfromArray(Array<Doctor>& doctors, Array<Password>& passwords,Array<Patient>& patients, Patient& element) {
	for (size_t i = 0; i < passwords.getLen(); i++){
		if (passwords[i].getID() == element.getAccountID())
			passwords.delete_element(passwords[i]);
	}
	for (size_t i = 0; i < doctors.getLen(); i++){
		doctors[i].deletePatient(element);
	}
	patients.delete_element(element);
}

