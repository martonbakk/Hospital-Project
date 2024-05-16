#ifndef MANAGER_H
#define MANAGER_H

#include "myString.h"
#include "CaesarCipher.h"
#include "Account.h"
#include "Patient.h"
#include "Nurse.h"
#include "Doctor.h"
#include "Admin.h"
#include "array.h"

#include <iostream>
#include <sstream>
#include <string>


struct MenuOptions {
	int mainMenuOption;
	int adminMenuOption;
	int doctorMenuOption;
	int patientMenuOption;
	int nurseMenuOption;
	MenuOptions():mainMenuOption(0), adminMenuOption(0), doctorMenuOption(0), patientMenuOption(0), nurseMenuOption(0){}
};



class LoginManager {
private:
	std::istream& is;
	std::ostream& os;
	int loggedInAccountID;
    int loggedInAccountType;
    size_t loggedInAccountIDX;
    String username;
    String password;
	bool logged;
public:
	LoginManager(std::istream& is = std::cin, std::ostream& os = std::cout, int loggedInAccountID = -1, int loggedInAccountType = -1, size_t loggedInAccountIDX = 0, const char* username = "", const char* password = "", bool logged=false) :
		is(is), os(os), loggedInAccountID(loggedInAccountID), loggedInAccountType(loggedInAccountType), loggedInAccountIDX(loggedInAccountIDX), username(username), password(password), logged(logged) {}

	void loginUser(Array<Password>& passwords, CaesarCipher& encryptor);

	void setAccountIndex(Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients);

	size_t getloggedInAccountIDX() {
		return loggedInAccountIDX;
	}
	int getAccountType() {
		return loggedInAccountType;
	}
};

class AdminManager {
private:
	std::istream& is;
	std::ostream& os;
    size_t adminDeleteOption;
    int adminEditTypeOption;
    size_t adminEditOptionIdx;
    String adminMedOption;
    size_t adminVerifyOption;
    int adminSetPatientMaxNum;
	String editedFirstName, editedLastName, editedEmail, editedPhone;

public:
	AdminManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), adminDeleteOption(0), adminEditTypeOption(-1), adminEditOptionIdx(0), adminVerifyOption(0), adminSetPatientMaxNum(-1), editedFirstName(""), editedLastName(""), editedEmail(""), editedPhone("") {}
public:
	void adminMenu(Array<Admin>& admins, LoginManager& user, MenuOptions& ops);

	void adminDelete(LoginManager& user, Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Password>& passwords);

	void adminEditAccount(LoginManager& user, Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Nurse>& nurses);

	void adminListAccounts(LoginManager& user, Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients);

	void adminDeleteMedicine(Dictionary& medicines);

	void adminVerifyAdminAccount(LoginManager& user, Array<Admin>& admins);

	void adminSetDoctorsLimit(LoginManager& user, Array<Admin>& admins);

	void adminDefault(MenuOptions& ops);

};

class DoctorManager {
private:
	std::istream& is;
	std::ostream& os;
    size_t doctorPatientIDX;
    int doctorGetPatientOption;
	int doctorReplyKey;
    String doctorReplyMedicine;
  

public:
	DoctorManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), doctorPatientIDX(0), doctorGetPatientOption(0), doctorReplyKey(0), doctorReplyMedicine("") {}

public:
	void doctorMenu(LoginManager& user, MenuOptions& ops, Array<Doctor>& doctors);

	void doctorGetPatient(LoginManager& user, Array<Doctor>& doctors, Array<Patient>& patients);

	void doctorReplyToPatient(LoginManager& user, Array<Doctor>& doctors, Dictionary& medicines);

	void doctorSeePatients(LoginManager& user, Array<Doctor>& doctors, Array<Patient>& patients);
};

class PatientManager {
private:
	std::istream& is;
	std::ostream& os;
    String patientSympthoms;

public:
	PatientManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), patientSympthoms("") {}
public:
	void patientMenu(LoginManager& user, MenuOptions& ops, Array<Patient>& patients);

	void patientSetSymp(LoginManager& user, Array<Patient>& patients);
};

class NurseManager {
private:
	std::istream& is;
	std::ostream& os;
    size_t nursePatientOptionIDX;
    int nurseMedicineKey;
    String nurseMedicineValue;

public:
	NurseManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), nursePatientOptionIDX(0), nurseMedicineKey(0), nurseMedicineValue("") {}
public:
	void nurseMenu(LoginManager& user, MenuOptions& ops, Array<Nurse>& nurses);

	void nurseGiveMedicines(LoginManager& user, Array<Nurse>& nurses, Array<Patient>& patients);

	void nurseGetMedicineFromStorage(LoginManager& user, Array<Nurse>& nurses, Dictionary& medicines);
};

#endif
