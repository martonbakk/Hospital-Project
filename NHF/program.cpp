#include <iostream>
//String
#include "myString.h"
//Tarolok
#include "dictionary.h"
#include "array.h"
//Fiokok
#include "Account.h"
#include "Patient.h"
#include "Nurse.h"
#include "Doctor.h"
#include "Admin.h"
//Jelszo
#include "password.h"
#include "CaesarCipher.h"
//Inputkezelo
#include "manager.h"
#include "Menu.h"
//Teszt
#include "gtest_lite.h"
#include "memtrace.h"

using std::cout;
using std::cin;

//Leiras
/*
* A program futtatasahoz a PROGRAM makrot true-ra a TESZT makrot pedig false-ra kell allitani. A teszt futtatasahoz a PROGRAM makrot false-ra a TESZT makrot pedig true-ra kell allitani.
* A teszt 6 reszre van bonta. Ezeket piramis szeruen is le lehet futtatni. A teszteknek jelenleg a vazai vannak csak megirva.
*/

#define PROGRAM true
#define TESZT false

int main() {
#if !TESZT&&PROGRAM
	std::ifstream fs;
	///Tarolok
	Data datas;
	///Menu 
	Menu program;
	try {
		//--FAJLBOL OLVASAS--
		datas.medicines.readFile(fs, "medicines.txt");
		datas.passwords.readFile("pwd.txt");
		datas.admins.readFile("admin.txt");
		datas.doctors.readFile("doctor.txt");
		datas.patients.readFile("patient.txt");
		datas.nurses.readFile("nurse.txt");

		for (size_t i = 0; i < datas.doctors.getLen(); i++) {
			datas.doctors[i].setPatients(datas.patients);
		}
	}
	catch (const char* ERROR) {
		cout << ERROR << '\n';
	}
#endif 
#if PROGRAM&&!TESZT
	//PROGRAM
	program.mainMenu();
	while (program.run()){
		switch (program.getMainOps()){
		case 1:	
			program.login(datas);
			switch (AccountType(program.getAccountType())){
			case ad:
				program.adminMenu(datas);
				break;
			case doc:
				program.doctorMenu(datas);
				break;
			case pat:
				program.patientMenu(datas);
				break;
			case nur:
				program.nurseMenu(datas);
				break;
			default:
				program.loginError();
				break;
			}
			break;
		case 2:
			program.registration(datas);
			break;
		default:
			break;
		}
	}
#endif

#if TESZT
	/*
	* A tesztek felepiteserol roviden: 
	* Az egyes teszt a bejelentkezest teszteli le es annak hibakezeleseit
	* A kettes tesztben a tarolok tesztjei vannak. Fajlba iras, olvasas, indexeles, uj elem hozzaadasa es ezeknek a hibaknak a kezelesei
	* A harmas tesztben a menukezelok tesztje van
	* A negyedik tesztol kezdve a fiok tipusok tesztjei vannak. Ahhoz, hogy ezeket az egyedulallo fiokokat megfeleloen tudjuk letesztelni szuksegesek a tarolo tombok. Peldail az admin torles tesztjet nem tudnank letesztelni ha nincs honnan torolni 
	*/
#define FELADAT 7
	
#if FELADAT==1
	//Login teszt
	LoginManager user;
	TEST(){

	}ENDM
#endif
#if FELADAT>1
	//Tarolok teszt
	Dictionary medicines;
	Array<Admin>admins;
	Array<Doctor>doctors;
	Array<Patient>patients;
	Array<Nurse>nurses;
	Array<Password>passwords;
	TEST(Dictionary) {

	}ENDM
	TEST(Array<Admin>) {

	}ENDM
	TEST(Array<Password>) {

	}ENDM
#endif
#if FELADAT>2
	//Menu kezelok teszt
	MenuOptions menuOPS;
	AdminManager adManager;
	DoctorManager docManager;
	NurseManager nurManager;
	PatientManager patManager;
	TEST(MenuOptions) {

	}ENDM
	TEST(AdminManager) {

	}ENDM
	TEST(DoctorManager) {

	}ENDM
	TEST(NurseManager) {

	}ENDM
	TEST(PatientManager) {

	}ENDM
#endif
#if FELADAT>3
	//Patient teszt
	Patient teszt;
	TEST() {

	}ENDM
#endif
#if FELADAT>4
	//Nurse teszt
	Nurse teszt;
	TEST() {

	}ENDM
#endif
#if FELADAT>5
	//Admin teszt
	Admin teszt;
	TEST() {

	}ENDM
#endif
#if FELADAT>6
	//Doctor teszt
	Doctor teszt;
	TEST() {

	}ENDM
#endif
#endif

#if !TESZT&&PROGRAM
	/*
	* A teszt soran nem akarjuk, hogy a teszt eredmenyek kiirodjanak azokba a fajlokba amiket a tenyleges program
	* fog hasznalni. A fajlba irashoz lesz teszt.
	*/
	try {
		//--FAJLBA IRAS--
		datas.medicines.writeFile("medicines.txt");
		datas.passwords.writeFile("pwd.txt");
		datas.admins.writeFile("admin.txt");
		datas.doctors.writeFile("doctor.txt");
		datas.patients.writeFile("patient.txt");
		datas.nurses.writeFile("nurse.txt");
	}
	catch (const char* ERROR) {
		cout << ERROR << '\n';
	}
#endif
	return 0;
}
