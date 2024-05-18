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

//Menu options
//A MenuOptions a felhasznalo altal beadott valasztasokat fogja tarolni
struct MenuOptions {
	int mainMenuOption;		//fo menu opco
	int adminMenuOption;	//admin menu opcio
	int doctorMenuOption;	//doktor menu opcio
	int patientMenuOption;	//paciens menu opcio
	int nurseMenuOption;	//apolo menu opcio
	MenuOptions() :mainMenuOption(0), adminMenuOption(0), doctorMenuOption(0), patientMenuOption(0), nurseMenuOption(0) {}
};

//User Account
/*
* A felhasznalo negy kulonbozo fiokba jelentkezhet be.Ezt a program elejen meg nem tudjuk, hogy mibe fog ezert minden fioktipusbol letrehozunk egy nullpointert.
* Ahogy bejelentkezett egy fiokba a megfelelo fioktipus szerint egy pointeren keresztul fogunk tovabb dolgozni.
*/
struct userAccount {
	Admin* admin;		//admin pointer
	Doctor* doctor;		//doki pointer
	Nurse* nurse;		//apolo pointer
	Patient* patient;	//beteg pointer
	userAccount(Admin* ad=nullptr, Doctor* doc=nullptr, Nurse* nur= nullptr, Patient* pat= nullptr):
		admin(ad), doctor(doc), nurse(nur), patient(pat){}
};

/// @Login manager
/*
* A login manager osztaly felelos a felhasznalo belepteteseert es a megfelelo fiok osszekoteseert a jelszoval
*/
class LoginManager {
	std::istream& is;			//bemenete
	std::ostream& os;			//kimenete
	int loggedInAccountID;		//bejelentkezett fiok ID
	int loggedInAccountType;	//bejelentkezett fiok tipusa
	size_t loggedInAccountIDX;	//bejelentkezett fiok indexe
	String username;			//bejelentkezett fiok felhasznalo nev
	String password;			//bejelentkezett fiok jelszava
	bool logged;				//sikerult-e a bejelentkezes
public:
	LoginManager(std::istream& is = std::cin, std::ostream& os = std::cout, int loggedInAccountID = -1, int loggedInAccountType = -1, size_t loggedInAccountIDX = 0, const char* username = "", const char* password = "", bool logged = false) :
		is(is), os(os), loggedInAccountID(loggedInAccountID), loggedInAccountType(loggedInAccountType), loggedInAccountIDX(loggedInAccountIDX), username(username), password(password), logged(logged) {}
public:
	void getTypeAndIDX(const Array<Password>& passwords, CaesarCipher& encryptor);														//kiszedi az adatbazisbol a fiok tipusat es az indexet
	void setAccount(Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients, userAccount& user);	//beallitja az adott pointert
public:
	int getAccountType() {return loggedInAccountType;}	//visszaadja a fiok tipusat, a menu meghivasoknal van ennek fontos szerepe
};

/// @Admin manager///
/*
*	Az admin manager felele az admin menuert. A felhasznalo ha admin fiokba jelentkezett be akkor az admin menube kerul be. Az adminManager az admin menun beluli munkavegzesert felel.
*/
class AdminManager {
	std::istream& is;			//bemenet
	std::ostream& os;			//kimenet
	size_t adminDeleteOption;	//melyik paciens fiokot akarja torolni a felhasznalo
	int adminEditTypeOption;	//melyik fiokottipus szeretne a felhasznalo szerkezteni
	size_t adminEditOptionIdx;	//melyik konkret fiokot szeretne a felhasznalo szerkezteni
	String adminMedOption;		//melyik gyogyszert szeretne a felhasznalo torolni
	size_t adminVerifyOption;	//melyik admin fiokot szeretne torolni a felhasznalo
	int adminSetPatientMaxNum;	//mennyire szeretne beallitani a korlatozasokat
	String editedFirstName, editedLastName, editedEmail, editedPhone;	//fiokadat szerkeztesehez szukseges informaciok
public:
	AdminManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), adminDeleteOption(0), adminEditTypeOption(-1), adminEditOptionIdx(0), adminVerifyOption(0), adminSetPatientMaxNum(-1), editedFirstName(""), editedLastName(""), editedEmail(""), editedPhone("") {}
public:
	void adminMenu(userAccount& user,MenuOptions& ops);		//admin menu opciok
	void adminDelete(userAccount& user, Array<Patient>& patients, Array<Doctor>& doctors, Array<Password>& passwords);						//paciens fiok torlese
	void adminEditAccount(userAccount& user, Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Nurse>& nurses);	//fiok szerkeztese az adatbazisban
	void adminListAccounts(userAccount& user, Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients);//osszes fiok listazasa az adatbazisban
	void adminDeleteMedicine(Dictionary& medicines);																						//gyogyszer torlese a raktarbol
	void adminVerifyAdminAccount(userAccount& user, Array<Admin>& admins);																	//admin fiok engedelyezese
	void adminSetDoctorsLimit(userAccount& user);																							//doktorok max betegszamainak korlatozasa
	void adminDefault(MenuOptions& ops);																									//alap menu, ha rossz bemenetet adott  a felhasznalo
};

///@Doctor manager
/*
* A doktor manager felel a doktor menuert.A felhasznalo ha doktor fiokba jelentkezett be akkor a doktor menube kerul be. Az doktor manager a doktor menun beluli munkavegzesert felel.
*/
class DoctorManager {
	std::istream& is;			//bemenet
	std::ostream& os;			//kimenet	
	size_t doctorPatientIDX;	//kivalasztott beteg indexe 
	int doctorGetPatientOption;	//beteg felvetelenel kivalasztott beteg szama
	int doctorReplyKey;			//valasz a beteg szamara, mibol mennyit kell bevennie
	String doctorReplyMedicine; //valasz a beteg szamara, mit kell bevennie
public:
	DoctorManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), doctorPatientIDX(0), doctorGetPatientOption(0), doctorReplyKey(0), doctorReplyMedicine("") {}

public:
	void doctorMenu(userAccount& user, MenuOptions& ops);											//doktor menu opciok
	void doctorGetPatient(userAccount& user, Array<Doctor>& doctors, Array<Patient>& patients);		//beteg felvetele
	void doctorReplyToPatient(userAccount& user, Dictionary& medicines);							//betegnek valasz
	void doctorSeePatients(userAccount& user, Array<Patient>& patients);							//megnezheti milyen betegek vannak a rendszerben, akiknek nincs meg doktoruk
};

///@Patient manager
/*
* A patient manager felel a patient menuert.A felhasznalo ha patient fiokba jelentkezett be akkor a patient menube kerul be. Az patient manager a patient menun beluli munkavegzesert felel.
*/
class PatientManager {
	std::istream& is;		//bemenet
	std::ostream& os;		//kimenet
	String patientSympthoms;//beteg tunetei
public:
	PatientManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), patientSympthoms("") {}
public:
	void patientMenu(userAccount& user, MenuOptions& ops);	//patient alap menu
	void patientSetSymp(userAccount& user);					//panaszok beallitasa
};

///@Nurse manager
/*
* A nurse manager felel a nurse menuert.A felhasznalo ha nurse fiokba jelentkezett be akkor a nurse menube kerul be.
*/
class NurseManager {
	std::istream& is;				//bemenet
	std::ostream& os;				//kimenet
	size_t nursePatientOptionIDX;	//beteg kivalasztott indexe
	int nurseMedicineKey;			//gyogyszer kivetele a raktarbol menuopcional a gyogyszer mennyisege
	String nurseMedicineValue;		//gyogyszer kivetele a raktarbol menuopcional a gyogyszer neve
public:
	NurseManager(std::istream& input = std::cin, std::ostream& output = std::cout)
		: is(input), os(output), nursePatientOptionIDX(0), nurseMedicineKey(0), nurseMedicineValue("") {}
public:
	void nurseMenu(userAccount& user, MenuOptions& ops);						//alap menu
	void nurseGiveMedicines(userAccount& user, Array<Patient>& patients);		//betegek kiszolgalasa
	void nurseGetMedicineFromStorage(userAccount& user, Dictionary& medicines);	//gyogyszer kivetele a raktarbol
};

#endif