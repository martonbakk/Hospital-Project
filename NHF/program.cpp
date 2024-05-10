#include <iostream>
//Tarolok
#include "myString.h"
#include "dictionary.h"
#include "array.hpp"
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
//Teszt
#include "gtest_lite.h"

using std::cout;
using std::cin;

/*
* TO DO: 
* - A doktornak ki kell irni a max patient num szamat fileba
* - A tesztek torzseinek megirasa 
* - A dictionary valamiert a vegere neha odarak egy 4 4-es rekordot a fajlba
* - A try catch-ek berakasa a fuggvenyekbe ahol meg nem tortent meg es ahol lehet
* - Az input es output fixalasa a teszthez
* - Clean code... Kommentek megirasa, a fuggvenyek tagolasa logikusan, az input kezelo osztalyok rendszerezese, igeny szerint tobb fajlba bontasa, szemetek kiszurese
*/

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
	Dictionary medicines;
	Array<Admin>admins;
	Array<Doctor>doctors;
	Array<Patient>patients;
	Array<Nurse>nurses;
	Array<Password>passwords;
	///Felhasznalo
	LoginManager user;
	///Menu kezelok
	MenuOptions menuOPS;
	AdminManager adManager;
	DoctorManager docManager;
	NurseManager nurManager;
	PatientManager patManager;
	///Jelszo titkositas
	CaesarCipher encryptor(3);
	try {
		//--FAJLBOL OLVASAS--
		medicines.readFile(fs, "medicines.txt");
		passwords.readFile("pwd.txt");
		admins.readFile("admin.txt");
		doctors.readFile("doctor.txt");
		patients.readFile("patient.txt");
		nurses.readFile("nurse.txt");

		for (size_t i = 0; i < doctors.getLen(); i++) {
			doctors[i].setPatients(patients);
		}
	}
	catch (const char* ERROR) {
		cout << ERROR << '\n';
	}
#endif 
#if PROGRAM&&!TESZT
	//PROGRAM
	cout << "KORHAZI ADATBAZIS KEZELO PROGRAM\nBejelentkezes (1)\nRegisztacio (2)\nKilepes (3)\nVALASSZON OPCIOT: ";
	cin >> menuOPS.mainMenuOption;
	while (menuOPS.mainMenuOption != 3)
	{
		switch (menuOPS.mainMenuOption)
		{
		case 1:
			user.loginUser(passwords, encryptor);
			try {
				user.setAccountIndex(admins, doctors, nurses, patients);
			}
			catch (const char* ERROR) {
				std::cout << ERROR;
			}
			switch (AccountType(user.getAccountType()))
			{
			case ad:
				adManager.adminMenu(admins, user, menuOPS);
				switch (menuOPS.adminMenuOption)
				{
				case 1://Fiokok torlese
					try {
						adManager.adminDelete(user, admins, patients, doctors, passwords);
					}
					catch (const char* ERROR) { std::cout << ERROR; }
					break;
				case 2://Fiokok szerkeztese
					try {
						adManager.adminEditAccount(user, admins, patients, doctors, nurses);
					}
					catch (const char* ERROR) { std::cout << ERROR; }
					break;
				case 3://Osszes fiok listazasa
					adManager.adminListAccounts(user, admins, doctors, nurses, patients);
					break;
				case 4://Gyogyszerek torlese a raktarbol
					adManager.adminDeleteMedicine(medicines);
					break;
				case 5://Uj admin fiok engedelyezese
					try {
						adManager.adminVerifyAdminAccount(user, admins);
					}
					catch (const char* ERROR) { std::cout << ERROR; }
					break;
				case 6://Doktorok betegeinek korlatozasa
					adManager.adminSetDoctorsLimit(user, admins);	/// NINCS KIIRVA A FAJLBA MEG!!!!!!!!!!!!!!!!!!!!!!!!!
					break;
				case 7://Kilepes
					menuOPS.mainMenuOption=3;
					break;
				default:
					cout << "Nincs ilyen opcio...\nValasszon ujat: ";
					int op;
					cin >> op;
					menuOPS.mainMenuOption = op;
					break;
				}
				break;
			case doc:
				docManager.doctorMenu(user, menuOPS,doctors);
				switch (menuOPS.doctorMenuOption)
				{
				case 1://Beteg panaszainak elolvasasa
					docManager.doctorSeePatients(user, doctors, patients);
					break;
				case 2://Beteg felvetele
					docManager.doctorGetPatient(user, doctors, patients);
					break;
				case 3://Gyogyszer felirasa mar felvett betegeknek
					docManager.doctorReplyToPatient(user, doctors, medicines);
					break;
				case 4://Kilepes
					menuOPS.mainMenuOption = 3;
					break;
				default:
					cout << "Nincs ilyen opcio...\nValasszon ujat: ";
					int op;
					cin >> op;
					menuOPS.mainMenuOption = op;
					break;
				}
				break;
			case pat:
				patManager.patientMenu(user, menuOPS, patients);
				switch (menuOPS.patientMenuOption) {
				case 1:
					patManager.patientSetSymp(user, patients);
					break;
				case 2:
					menuOPS.mainMenuOption = 3;
					break;
				default:
					cout << "Nincs ilyen opcio...\nValasszon ujat: ";
					int op;
					cin >> op;
					menuOPS.mainMenuOption = op;
					break;
				}
				break;
			case nur:
				nurManager.nurseMenu(user, menuOPS, nurses);
				switch (menuOPS.nurseMenuOption)
				{
				case 1://Gyogyszerek adagolasa a betegnek
					nurManager.nurseGiveMedicines(user, nurses, patients);
					break;
				case 2://Gyogyszerek kivetele a raktarbol
					nurManager.nurseGetMedicineFromStorage(user, nurses, medicines);
					break;
				case 3://Kilepes
					menuOPS.mainMenuOption = 3;
					break;
				default:
					cout << "Nincs ilyen opcio...\nValasszon ujat: ";
					int op;
					cin >> op;
					menuOPS.mainMenuOption = op;
					break;
				}
				break;
			default:
				cout << "Nem sikerult bejelentkeznie...\nKilepeshez nyomja meg a harmast\nUjboli probalkozashoz nyomja meg az egyest: ";
				int opt;
				cin >> opt;
				menuOPS.mainMenuOption=opt;
				break;
			}
			break;
		case 2:
			
			break;
		default:
			cout << "Nincs ilyen opcio...\nVALASSZON OPCIOT: ";
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
		medicines.writeFile("medicines.txt");
		passwords.writeFile("pwd.txt");
		admins.writeFile("admin.txt");
		doctors.writeFile("doctor.txt");
		patients.writeFile("patient.txt");
		nurses.writeFile("nurse.txt");
	}
	catch (const char* ERROR) {
		cout << ERROR << '\n';
	}
#endif
	return 0;
}
