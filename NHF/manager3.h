#ifndef MANAGER_H
#define MANAGER_H

#include "myString.h"
#include "CaesarCipher.h"
#include "Account.h"
#include "Patient.h"
#include "Nurse.h"
#include "Doctor.h"
#include "Admin.h"
#include "array.hpp"

#include <iostream>
#include <sstream>
#include <string>

class databaseManager
{
private:/// BEJELENTKEZES
	bool logged;
	int mainMenuOption;//////////
	int loggedInAccountType;
	int loggedInAccountID;
	size_t loggedInAccountIDX;
	String username;
	String password;
	String editedFirstName, editedLastName, editedEmail, editedPhone;
	
private:/// ADMIN INPUT KEZELES
	int adminMenuOption;/////////
	size_t adminDeleteOption;
	int adminEditTypeOption;
	int adminEditOptionIdx;
	String adminMedOption;
	size_t adminVerifyOption;
	int adminSetPatientMaxNum;
	
private:///DOCTOR INPUT KEZELES
	int doctorMenuOption;/////////
	int doctorPatientIDX;

	int doctorGetPatientOption;
	String doctorReplyMedicine;
	int doctorReplyKey;
	
private:///PATIENT INPUT KEZElES
	int patientMenuOption;////////
	String patientSympthoms;

private:///NURSE INPUT KEZELES
	int nurseMenuOption;/////////
	int nursePatientOptionIDX;

	int nurseMedicineKey;
	String nurseMedicineValue;
public:
	databaseManager(int mainMenuOp=-1, int accountId = -1, int accountType=-1, size_t accountIDX=0, const char* username = "", const char* password = "", const char* editedInf=""):
		mainMenuOption(mainMenuOp), loggedInAccountID(accountId), loggedInAccountType(accountType), loggedInAccountIDX(loggedInAccountIDX), username(username), password(password), logged(false){}
public:
	//Belepes
    void loginUser(Array<Password>& passwords, CaesarCipher& encryptor) {
		if(!logged){
			std::cout << "Adja meg a felhasznalo nevet:";
			std::cin >> username;
			std::cout << "Adja meg a jelszavat:";
			std::cin >> password;
			for (size_t i = 0; i < passwords.getLen(); i++)
			{
				if (passwords[i].getUserName() == username && passwords[i].getPassword() == encryptor.encode(password)) {
					loggedInAccountID = passwords[i].getID();
					loggedInAccountType = passwords[i].getAccountType();
					logged = true;
				}
			}
		}
    }

	void setAccountIndex(Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients) {
		int loggedInAccountID = this->loggedInAccountID;
		switch (AccountType(loggedInAccountType))
		{
		case ad:
			loggedInAccountIDX = admins.indexOfElement([loggedInAccountID](const Admin& admin) {
				return admin.getAccountID() == loggedInAccountID;
				});
			break;
		case doc:
			loggedInAccountIDX = doctors.indexOfElement([loggedInAccountID](const Doctor& doctor) {
				return doctor.getAccountID() == loggedInAccountID;
				});
			break;
		case pat:
			loggedInAccountIDX = patients.indexOfElement([loggedInAccountID](const Patient& patient) {
				return patient.getAccountID() == loggedInAccountID;
				});
			break;
		case nur:
			loggedInAccountIDX = nurses.indexOfElement([loggedInAccountID](const Nurse& nurse) {
				return nurse.getAccountID() == loggedInAccountID;
				});
			break;
		default:
			break;
		}
	}



	//Registracio
    void registerUser() {

    }
public:
	bool run() {
		return (mainMenuOption != 3);
	}

	void mainMenu() {
		std::cin >> mainMenuOption;
	}

	void setMainMenuOption(int option) {
		mainMenuOption = option;
	}

/// <summary>
/// AMIN DOLGOK
/// </summary>
public:
	void adminMenu(Array<Admin>& admins) {
		try {
			admins[loggedInAccountIDX].listAccountInformation();
			admins[loggedInAccountIDX].listAllOption();
		}
		catch (...) {
			std::cout << "ID ERROR\n";
		}
		std::cin >> adminMenuOption;
	}

	void adminDelete(Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Password>& passwords) {
		
		admins[loggedInAccountIDX].listAllPatientAccount(patients);
		std::cout << "VALASSZA KI MELYIK FIOKOT SZERETNE TOROLNI: ";
		std::cin >> adminDeleteOption;
		if (adminDeleteOption < patients.getLen()&&adminDeleteOption>0) {
			try {
				admins[loggedInAccountIDX].deleteAccountfromArray(doctors, passwords, patients, patients[adminDeleteOption - 1]);
			}
			catch (...) {
				std::cout << "DELETE ERROR";
			}
		}
		else {
			std::cout << "THERE IS NO OPTION LIKE THIS. RETURNING TO THE ADMIN MENU...\n";
		}
	}

	void adminEditAccount(Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Nurse>& nurses) {
		admins[loggedInAccountIDX].listAllAccount(patients, nurses, admins, doctors);
		std::cout << "VALASSZA KI MELYIK FIOKTIPUST SZERETNE SZERKEZTENI: ";
		std::cin >> adminEditTypeOption;
		if (adminEditTypeOption > 4 || adminEditTypeOption < 1) { 
			throw "THERE IS NO OPTION LIKE THIS...\n"; 
		}
		std::cout << "VALASSZA KI MELYIK FIOKOT SZERETNE SZERKEZTENI: ";
		std::cin >> adminEditOptionIdx;
		
		std::cout << "EBBEN A FORMABAN ADJA MEG AZ ADATOKAT, A FELHASZNALONEV NEM TARTALMAZHAT * ES SZOKOZ KARAKTEREKET, A NEVNEL CSAK A KERESZT ES A CSALAD NEVET ADJON, HA TOBB KERESZT NEVE VAN CSAK EGYET ADJON MEG\n(Firstname Lastname Mail Phone) : ";
		std::cin  >> editedFirstName >> editedLastName >> editedEmail >> editedPhone;
		String name;
		name = editedFirstName;
		name += editedLastName;
		switch (adminEditTypeOption)
		{
		case 1:
			if (adminEditOptionIdx > admins.getLen() || adminEditOptionIdx < 0) {
				throw "YOU MIGHT GAVE A WRONG INDEX\n";
			}
			admins[loggedInAccountIDX].editAccountfromList(admins[adminEditOptionIdx - 1],  name.getText(), editedEmail.getText(), editedPhone.getText());
			break;
		case 2:
			if (adminEditOptionIdx > doctors.getLen() || adminEditOptionIdx < 0) {
				throw "YOU MIGHT GAVE A WRONG INDEX\n";
			}
			admins[loggedInAccountIDX].editAccountfromList(doctors[adminEditOptionIdx - 1],  name.getText(), editedEmail.getText(), editedPhone.getText());
			break;
		case 3:
			if (adminEditOptionIdx > nurses.getLen() || adminEditOptionIdx < 0) {
				throw "YOU MIGHT GAVE A WRONG INDEX\n";
			}
			admins[loggedInAccountIDX].editAccountfromList(nurses[adminEditOptionIdx - 1],  name.getText(), editedEmail.getText(), editedPhone.getText());
			break;
		case 4:
			if (adminEditOptionIdx > patients.getLen() || adminEditOptionIdx < 0) {
				throw "YOU MIGHT GAVE A WRONG INDEX\n";
			}
			admins[loggedInAccountIDX].editAccountfromList(patients[adminEditOptionIdx - 1],  name.getText(), editedEmail.getText(), editedPhone.getText());
			break;
		default:
			break;
		}
	}

	void adminListAccounts(Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients) {
		admins[loggedInAccountIDX].listAllAccount(patients, nurses, admins, doctors);
	}

	void adminDeleteMedicine(Dictionary& medicines) {
		std::cout << medicines;
		std::cout << "Melyiket szeretne torolni? Adja meg a nevet: ";
		std::cin >> adminMedOption;
		for (size_t i = 0; i < medicines.getSize(); i++) {
			if (medicines[i]._value == adminMedOption.getText())
				medicines[i]._key = 0;
		}
	}

	void adminVerifyAdminAccount(Array<Admin>& admins) {
		for (size_t i = 0; i < admins.getLen(); i++) {
			std::cout << "Opcio " << i + 1 << '\n';
			admins[i].listAccountInformation();
		}
		std::cout << "Adja meg melyik admin fiokot szeretne engedelyeztetni: ";
		std::cin >> adminVerifyOption;
		try {
			admins[loggedInAccountIDX].verifyAdmins(admins[adminVerifyOption - 1]);
		}
		catch (...) {
			throw "There is no option like this\n";
		}
	}

	void adminSetDoctorsLimit(Array<Admin>& admins) {
		std::cout << "Adja meg mennyire szeretne korlatozni a betegek szamat: ";
		std::cin >> adminSetPatientMaxNum;
		admins[loggedInAccountIDX].setDoctorsMaxPatientNum(adminSetPatientMaxNum);
	}

	void adminDefault() {
		std::cout << "Nincs ilyen opcio...\nValasszon ujat: ";
		int op;
		std::cin >> op;
		setMainMenuOption(op);
	}




	int getAdminMenuOption() {
		return adminMenuOption;
	}

	size_t getAccountIndex() {
		return loggedInAccountIDX;
	}

	int getAccountType() {
		return loggedInAccountType;
	}
	
	int getMainMenuOption() {
		return mainMenuOption;
	}

/// <summary>
/// DOCTOR
/// </summary>
public:
	void doctorMenu(Array<Doctor>& doctors) {
		try {
			doctors[loggedInAccountIDX].listAccountInformation();
			doctors[loggedInAccountIDX].listAllOption();
		}
		catch (...) {
			std::cout << "ID ERROR";
		}
		std::cin >> doctorMenuOption;
	}
	int getDoctorMenuOption(){
		return doctorMenuOption;
	}

	void doctorGetPatient(Array<Doctor>& doctors, Array<Patient>& patients) {
		if (doctors[loggedInAccountIDX].listAllPatients(patients) != 0) {
			std::cout << "Valassza ki melyik beteget szeretne magahoz venni:";
			std::cin >> doctorGetPatientOption;
			try {
				doctors[loggedInAccountIDX].getPatient(&patients[doctorGetPatientOption - 1]);
			}
			catch (const char* ERROR) {
				std::cout << ERROR;
			}
		}
		else {
			std::cout << "Minden betegnek jelenleg van doktora\n";
		}
		
	}
	void doctorReplyToPatient(Array<Doctor>& doctors, Dictionary& medicines) {
		doctors[loggedInAccountIDX].listPatients();
		std::cout << "Valassza ki melyik betegnek akarja felirni a gyogyszert: ";
		std::cin >> doctorPatientIDX;
		std::cout << "Adja meg a gyogyszer nevet: ";
		std::cin >> doctorReplyMedicine;
		std::cout << "Adja meg mennyit szedjen belole: ";
		std::cin >> doctorReplyKey;
		try {
			doctors[loggedInAccountIDX].replyPatientSympthoms(medicines, DictionaryEntry(doctorReplyKey, doctorReplyMedicine.getText()), doctorPatientIDX-1);
		}
		catch (const char* ERROR) {
			std::cout << ERROR;
		}
	}

	void doctorSeePatients(Array<Doctor>& doctors, Array<Patient>& patients) {
		doctors[loggedInAccountIDX].seePatientsSympthoms(patients);
	}
/// <summary>
/// Patient
/// </summary>
public:
	void patientMenu(Array<Patient>& patients) {
		try {
			patients[loggedInAccountIDX].listAccountInformation();
			patients[loggedInAccountIDX].listAllOption();
		}
		catch (...) {
			std::cout << "ID ERROR";
		}
		std::cin >> patientMenuOption;
	}
	int getPatientMenuOption(){
		return patientMenuOption;
	}
	void patientSetSymp(Array<Patient>& patients) {
		std::cout << "Irja le milyen gondja van: ";
		std::cin >> patientSympthoms;
		patients[loggedInAccountIDX].setSympthoms(patientSympthoms);
	}
/// <summary>
/// Nurse
/// </summary>
public:
	void nurseMenu(Array<Nurse>& nurses) {
		try {
			nurses[loggedInAccountIDX].listAccountInformation();
			nurses[loggedInAccountIDX].listAllOption();
		}
		catch (...) {
			std::cout << "ID ERROR";
		}
		std::cin >> nurseMenuOption;
	}

	void nurseGiveMedicines(Array<Nurse>& nurses, Array<Patient>& patients) {
		for (size_t i = 0; i < patients.getLen(); i++)
		{
			std::cout << "Option (" << i + 1 << ")\n";
			patients[i].listAccountInformation();
		}
		std::cout << "Valasszon egy beteget: ";
		std::cin >> nursePatientOptionIDX;
		try {
			nurses[loggedInAccountIDX].medicineLog(patients[nursePatientOptionIDX - 1]);
		}
		catch (const char* ERROR) {
			std::cout << ERROR;
		}
	}
	void nurseGetMedicineFromStorage(Array<Nurse>& nurses, Dictionary& medicines) {
		std::cout << medicines;
		std::cout << "Valasszon mennyi gyogyszert szeretne kivenni, es milyet (2 Algoflex): ";
		std::cin >> nurseMedicineKey >> nurseMedicineValue;
		nurses[loggedInAccountIDX].getMedicine(medicines, nurseMedicineKey, nurseMedicineValue.getText());
	}
};
#endif