#ifndef MANAGER_H
#define MANAGER_H

#include "memtrace.h"

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
	MenuOptions() :mainMenuOption(0), adminMenuOption(0), doctorMenuOption(0), patientMenuOption(0), nurseMenuOption(0) {}
};

struct userAccount {
	Admin* admin;
	Doctor* doctor;
	Nurse* nurse;
	Patient* patient;
	userAccount(Admin* ad=nullptr, Doctor* doc=nullptr, Nurse* nur= nullptr, Patient* pat= nullptr):
		admin(ad), doctor(doc), nurse(nur), patient(pat){}
};

class LoginManager {
	std::istream& is;
	std::ostream& os;
	int loggedInAccountID;
	int loggedInAccountType;
	size_t loggedInAccountIDX;
	String username;
	String password;
	bool logged;
public:
	LoginManager(std::istream& is = std::cin, std::ostream& os = std::cout, int loggedInAccountID = -1, int loggedInAccountType = -1, size_t loggedInAccountIDX = 0, const char* username = "", const char* password = "", bool logged = false) :
		is(is), os(os), loggedInAccountID(loggedInAccountID), loggedInAccountType(loggedInAccountType), loggedInAccountIDX(loggedInAccountIDX), username(username), password(password), logged(logged) {}
public:
	void getTypeAndIDX(Array<Password>& passwords, CaesarCipher& encryptor);
	void setAccount(Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients, userAccount& user);
public:
	int getAccountType() {return loggedInAccountType;}
};

class AdminManager {
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
	void adminMenu(userAccount& user,Array<Admin>& admins, MenuOptions& ops);
	void adminDelete(userAccount& user, Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Password>& passwords);
	void adminEditAccount(userAccount& user, Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Nurse>& nurses);
	void adminListAccounts(userAccount& user, Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients);
	void adminDeleteMedicine(Dictionary& medicines);
	void adminVerifyAdminAccount(userAccount& user, Array<Admin>& admins);
	void adminSetDoctorsLimit(userAccount& user, Array<Admin>& admins);
	void adminDefault(MenuOptions& ops);
};

class DoctorManager {
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
	void doctorMenu(userAccount& user, MenuOptions& ops, Array<Doctor>& doctors);
	void doctorGetPatient(userAccount& user, Array<Doctor>& doctors, Array<Patient>& patients);
	void doctorReplyToPatient(userAccount& user, Array<Doctor>& doctors, Dictionary& medicines);
	void doctorSeePatients(userAccount& user, Array<Doctor>& doctors, Array<Patient>& patients);
};

class PatientManager {
	std::istream& is;
	std::ostream& os;
	String patientSympthoms;
public:
	PatientManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), patientSympthoms("") {}
public:
	void patientMenu(userAccount& user, MenuOptions& ops, Array<Patient>& patients);
	void patientSetSymp(userAccount& user, Array<Patient>& patients);
};

class NurseManager {
	std::istream& is;
	std::ostream& os;
	size_t nursePatientOptionIDX;
	int nurseMedicineKey;
	String nurseMedicineValue;
public:
	NurseManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), nursePatientOptionIDX(0), nurseMedicineKey(0), nurseMedicineValue("") {}
public:
	void nurseMenu(userAccount& user, MenuOptions& ops, Array<Nurse>& nurses);
	void nurseGiveMedicines(userAccount& user, Array<Nurse>& nurses, Array<Patient>& patients);
	void nurseGetMedicineFromStorage(userAccount& user, Array<Nurse>& nurses, Dictionary& medicines);
};

#endif