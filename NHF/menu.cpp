#include "Menu.h"


void Menu::login(Data& datas){
	userLogin.getTypeAndIDX(datas.passwords, encryptor);
	userLogin.setAccount(datas.admins, datas.doctors, datas.nurses, datas.patients, user);
}

void Menu::adminMenu(Data& datas) {
	adManager.adminMenu(user, datas.admins, menuOPS);
	switch (menuOPS.adminMenuOption)
	{
	case 1://Fiokok torlese
		adManager.adminDelete(user, datas.admins, datas.patients, datas.doctors, datas.passwords);
		break;
	case 2://Fiokok szerkeztese
		try {
			adManager.adminEditAccount(user, datas.admins, datas.patients, datas.doctors, datas.nurses);
		}
		catch (const char* ERROR) { std::cout << ERROR; }
		break;
	case 3://Osszes fiok listazasa
		adManager.adminListAccounts(user, datas.admins, datas.doctors, datas.nurses, datas.patients);
		break;
	case 4://Gyogyszerek torlese a raktarbol
		adManager.adminDeleteMedicine(datas.medicines);
		break;
	case 5://Uj admin fiok engedelyezese
		adManager.adminVerifyAdminAccount(user, datas.admins);
		break;
	case 6://Doktorok betegeinek korlatozasa
		adManager.adminSetDoctorsLimit(user, datas.admins);
		break;
	case 7://Kilepes
		menuOPS.mainMenuOption = 3;
		break;
	default:
		os << "Nincs ilyen opcio...\nValasszon ujat: ";
		int op;
		is >> op;
		menuOPS.mainMenuOption = op;
		break;
	}
}

void Menu::doctorMenu(Data& datas) {
	docManager.doctorMenu(user, menuOPS, datas.doctors);
	switch (menuOPS.doctorMenuOption)
	{
	case 1://Beteg panaszainak elolvasasa
		docManager.doctorSeePatients(user, datas.doctors, datas.patients);
		break;
	case 2://Beteg felvetele
		docManager.doctorGetPatient(user, datas.doctors, datas.patients);
		break;
	case 3://Gyogyszer felirasa mar felvett betegeknek
		docManager.doctorReplyToPatient(user, datas.doctors, datas.medicines);
		break;
	case 4://Kilepes
		menuOPS.mainMenuOption = 3;
		break;
	default:
		os << "Nincs ilyen opcio...\nValasszon ujat: ";
		int op;
		is >> op;
		menuOPS.mainMenuOption = op;
		break;
	}
}

void Menu::patientMenu(Data& datas) {
	patManager.patientMenu(user, menuOPS, datas.patients);
	switch (menuOPS.patientMenuOption) {
	case 1:
		patManager.patientSetSymp(user, datas.patients);
		break;
	case 2:
		menuOPS.mainMenuOption = 3;
		break;
	default:
		os << "Nincs ilyen opcio...\nValasszon ujat: ";
		int op;
		is >> op;
		menuOPS.mainMenuOption = op;
		break;
	}
}

void Menu::nurseMenu(Data& datas) {
	nurManager.nurseMenu(user, menuOPS, datas.nurses);
	switch (menuOPS.nurseMenuOption)
	{
	case 1://Gyogyszerek adagolasa a betegnek
		nurManager.nurseGiveMedicines(user, datas.nurses, datas.patients);
		break;
	case 2://Gyogyszerek kivetele a raktarbol
		nurManager.nurseGetMedicineFromStorage(user, datas.nurses, datas.medicines);
		break;
	case 3://Kilepes
		menuOPS.mainMenuOption = 3;
		break;
	default:
		os << "Nincs ilyen opcio...\nValasszon ujat: ";
		int op;
		is >> op;
		menuOPS.mainMenuOption = op;
		break;
	}
}

void Menu::loginError() {
	os << "Nem sikerult bejelentkeznie...\nKilepeshez nyomja meg a harmast\nUjboli probalkozashoz nyomja meg az egyest: ";
	int opt;
	is >> opt;
	menuOPS.mainMenuOption = opt;
}

void Menu::mainMenu() {
	os << "KORHAZI ADATBAZIS KEZELO PROGRAM\nBejelentkezes (1)\nRegisztacio (2)\nKilepes (3)\nVALASSZON OPCIOT: ";
	is >> menuOPS.mainMenuOption;
}

void Menu::registration(Data& datas) {

}