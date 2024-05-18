#include <iostream>
#include <sstream>
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
#include "menu.h"
//Teszt
#include "gtest_lite.h"
#include "memtrace.h"

using std::cout;
using std::cin;

//Leiras
/*
* A program futtatasahoz a teszt makrot  false-ra kell allitani. A tesztprogramban a feladat makroval lehet allitani mennyi tesztet futtasson
*/

#define teszt

int main() {
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

		for (size_t i = 0; i < datas.doctors.size(); i++) {
			datas.doctors[i].setPatients(datas.patients);
		}
	}
	catch (const char* ERROR) {
		cout << ERROR << '\n';
	}
#ifndef teszt
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
#ifdef teszt
	/*
	* A tesztek felepiteserol roviden: 
	* Az egyes teszt a bejelentkezest teszteli le es annak hibakezeleseit
	* A kettes tesztben a tarolok tesztjei vannak. Fajlba iras, olvasas, indexeles, uj elem hozzaadasa es ezeknek a hibaknak a kezelesei
	* A harmas tesztben a menukezelok tesztje van
	* A negyedik tesztol kezdve a fiok tipusok tesztjei vannak. Ahhoz, hogy ezeket az egyedulallo fiokokat megfeleloen tudjuk letesztelni szuksegesek a tarolo tombok. Peldail az admin torles tesztjet nem tudnank letesztelni ha nincs honnan torolni 
	*/


	#define FELADAT 7

	#if FELADAT > 1

	TEST(DictionaryTest, ConstructorEmpty) {
		Dictionary dict;
		EXPECT_EQ(0, dict.getSize());
	}ENDM

	TEST(DictionaryTest, ConstructorWithSize) {
		Dictionary dict(5);
		EXPECT_EQ(5, dict.getSize());
	}ENDM

	TEST(DictionaryTest, PushBackEmpty) {
		Dictionary dict;
		DictionaryEntry entry(1, "value");
		dict.push_back(entry);
		EXPECT_EQ(1, dict.getSize());
		EXPECT_EQ(entry.value, dict[0].value);
	}ENDM

	TEST(DictionaryTest, PushBackNonEmpty) {
		Dictionary dict(3);					 //alapbol mar volt ket tagja 0-NONE
		DictionaryEntry entry1(1, "value1");
		DictionaryEntry entry2(2, "value2");
		dict.push_back(entry1);
		dict.push_back(entry2);
		EXPECT_EQ(5, dict.getSize());
		EXPECT_EQ(entry1.key, dict[3].key);	
		EXPECT_EQ(entry2.key, dict[4].key);
	}ENDM

	TEST(DictionaryTest, ReadFileNonEmpty) {
		std::stringstream ss;
		ss << "3\nvalue 1\nvalue2 2\n value3 3"; //teszt file:elso ertek elemszam, tobbi elem: string es key
		Dictionary dict;
		dict.readFile(ss);
		EXPECT_EQ(3, dict.getSize());
	}ENDM
	
	TEST(DictionaryTest, OperatorIndex) {
		Dictionary dict;
		DictionaryEntry entry(1, "value");
		dict.push_back(entry);
		EXPECT_EQ(entry.key, dict[0].key);
		EXPECT_EQ(entry.value, dict[0].value);
	}ENDM

	TEST(ArrayTest, ConstructorEmpty) {
		Array<int> arr;
		EXPECT_EQ(0, arr.size());
	}ENDM

	TEST(ArrayTest, PushBackAndAccess) {
		Array<int> arr;
		arr.push_back(5);
		arr.push_back(10);
		EXPECT_EQ(2, arr.size());
		EXPECT_EQ(5, arr[0]);
		EXPECT_EQ(10, arr[1]);
	}ENDM

	TEST(ArrayTest, DeleteElement) {
		Array<int> arr;
		arr.push_back(5);
		arr.push_back(10);
		arr.push_back(15);
		arr.delete_element(10);
		EXPECT_EQ(2, arr.size());
		EXPECT_EQ(5, arr[0]);
		EXPECT_EQ(15, arr[1]);
	}ENDM

	TEST(ArrayTest, ReadWriteFile) {
		Array<int> arr;
		arr.push_back(5);
		arr.push_back(10);
		arr.push_back(15);

		const char* FILENAME = "test_array.txt";
		arr.writeFile(FILENAME);
		Array<int> arrFromFile;
		arrFromFile.readFile(FILENAME);

		EXPECT_EQ(3, arrFromFile.size());
		EXPECT_EQ(5, arrFromFile[0]);
		EXPECT_EQ(10, arrFromFile[1]);
		EXPECT_EQ(15, arrFromFile[2]);
	}ENDM
	#endif
	#if FELADAT > 2

	TEST(AdminTest, ListAccountInformation) {
		std::ostringstream output;
		Admin admin(true, 1, "admin", "Admin Name", "admin@example.com", "123456789");
		admin.listAccountInformation(output);
		std::string result = output.str();
		EXPECT_NE(result.find("Admin Name"), std::string::npos);
		EXPECT_NE(result.find("admin@example.com"), std::string::npos);
	}ENDM

	TEST(AdminTest, DeleteMedicine) {
		Dictionary medicines;
		medicines.push_back(DictionaryEntry(1, "Paracetamol"));
		medicines.push_back(DictionaryEntry(2, "Aspirin"));
		Admin admin(true);
		admin.deleteMedicine(medicines, "Paracetamol");
		EXPECT_EQ(1, medicines.getSize());
	}ENDM

	TEST(AdminTest, ListAllPatientAccount) {
		Array<Patient> patientsTEST;
		patientsTEST.push_back(Patient(1, "patient1", "Patient One", "patient1@example.com", "987654321"));
		patientsTEST.push_back(Patient(2, "patient2", "Patient Two", "patient2@example.com", "987654321"));
		patientsTEST.push_back(Patient(3, "patient3", "Patient Three", "patient3@example.com", "987654321"));

		std::ostringstream output;
		Admin admin(true);
		admin.listAllPatientAccount(output, patientsTEST);

		std::string result = output.str();
		EXPECT_NE(result.find("Patient One"), std::string::npos);
		EXPECT_NE(result.find("Patient Two"), std::string::npos);
		EXPECT_NE(result.find("Patient Three"), std::string::npos);
	}ENDM

	TEST(AdminTest, ListAllAccount) {
		Array<Patient> patientsTEST;
		patientsTEST.push_back(Patient(1, "patient1", "Patient One", "patient1@example.com", "987654321"));

		Array<Nurse> nursesTEST;
		nursesTEST.push_back(Nurse(1, "nurse1", "Nurse One", "nurse1@example.com", "987654321"));

		Array<Admin> adminsTEST;
		adminsTEST.push_back(Admin(true, 1, "admin", "Admin One", "admin@example.com", "123456789"));

		Array<Doctor> doctorsTEST;
		doctorsTEST.push_back(Doctor(1, "doctor1", "Doctor One", "doctor1@example.com", "987654321"));

		std::ostringstream output;
		Admin admin(true);
		admin.listAllAccount(output, patientsTEST, nursesTEST, adminsTEST, doctorsTEST);

		std::string result = output.str();
		EXPECT_NE(result.find("Patient One"), std::string::npos);
		EXPECT_NE(result.find("Nurse One"), std::string::npos);
		EXPECT_NE(result.find("Admin One"), std::string::npos);
		EXPECT_NE(result.find("Doctor One"), std::string::npos);
	}ENDM

	TEST(AdminTest, SetDoctorsMaxPatientNum) {
		Array<Doctor> doctorsTEST;
		doctorsTEST.push_back(Doctor(1, "doc1", "Doctor One", "doc1@example.com", "123456789"));
		doctorsTEST.push_back(Doctor(2, "doc2", "Doctor Two", "doc2@example.com", "987654321"));
		Admin adminTEST(true);  
		EXPECT_THROW(adminTEST.setDoctorsMaxPatientNum(-1), const char*);
	}ENDM
	#endif
	#if FELADAT > 3

	TEST(DoctorTest, Medicine ) {
		Doctor doctorTEST(1, "doctor1", "Doctor One", "doctor1@example.com", "123456789");
		Patient patient1TEST(2, "patient1", "Patient One", "patient1@example.com", "123456789");
		Patient patient2TEST(3, "patient2", "Patient Two", "patient2@example.com", "987654321");
		patient1TEST.setDoc(-1);


		Dictionary medicinesTEST;
		medicinesTEST.push_back(DictionaryEntry(1, "Aspirin"));
		medicinesTEST.push_back(DictionaryEntry(2, "Paracetamol"));

		EXPECT_THROW(Doctor::setMaxPatientNum(0), const char*);
		doctorTEST.getPatient(&patient1TEST);
		doctorTEST.getPatient(&patient2TEST);
		EXPECT_NO_THROW(doctorTEST.replyPatientSympthoms(medicinesTEST, medicinesTEST[0], 0));
		EXPECT_THROW(doctorTEST.replyPatientSympthoms(medicinesTEST, medicinesTEST[0], -1), const char*);
	}ENDM
	#endif
	#if FELADAT > 4
	TEST(PatientTest, AddAndRetrieveMedicineFromNurse) {
		Patient p;
		Dictionary nurseMedicines;
		nurseMedicines.push_back(DictionaryEntry(1, "Aspirin"));
		nurseMedicines.push_back(DictionaryEntry(2, "Codeine"));

		DictionaryEntry med1(1, "Aspirin");
		DictionaryEntry med2(2, "Codeine");

		p.medicineReply(med1);
		p.medicineReply(med2);

		p.medicineFromNurse(nurseMedicines);
		EXPECT_EQ(0, nurseMedicines[0].key); 
		EXPECT_EQ(0, nurseMedicines[1].key); 
	}ENDM
	#endif
	#if FELADAT > 5
	TEST(NurseTest, GetMedicineFromStorage) {
		Nurse n;
		Dictionary medicinesTEST;
		medicinesTEST.push_back(DictionaryEntry(1, "Aspirin"));
		medicinesTEST.push_back(DictionaryEntry(2, "Paracetamol"));
		EXPECT_THROW(n.getMedicine(medicinesTEST, 10, "Paracetamol"), const char*);
		EXPECT_NO_THROW(n.getMedicine(medicinesTEST, 1, "Paracetamol"));
		EXPECT_THROW(n.getMedicine(medicinesTEST, 1, "ASPIRINWRONG"), const char*);
	}ENDM
	#endif
	#if FELADAT > 6
	TEST(MenuTest, GetMainOps) {
		std::istringstream input("2");
		std::ostringstream output;
		Menu menu(input, output);
		EXPECT_EQ(true, menu.run());

		menu.mainMenu();
		EXPECT_EQ(2, menu.getMainOps());
		std::istringstream input2("1\njohndoe\npassword\n7");
		std::ostringstream output2;

		Menu menu2(input2, output2);
		menu2.mainMenu();
		menu2.login(datas);
		menu2.adminMenu(datas);
		EXPECT_EQ(3, menu2.getMainOps());
		EXPECT_EQ(1, menu2.getAccountType());
		EXPECT_EQ(false, menu2.run());

		std::istringstream input3("1\nkennyS\npassword\n4");
		std::ostringstream output3;
		Menu menu3(input3, output3);
		menu3.mainMenu();
		menu3.login(datas);
		menu3.doctorMenu(datas);
		EXPECT_EQ(3, menu3.getMainOps());
		EXPECT_EQ(2, menu3.getAccountType());
		EXPECT_EQ(false, menu3.run());

		std::istringstream input4("1\nbohemianb\npassword\n3");
		std::ostringstream output4;
		Menu menu4(input4, output4);
		menu4.mainMenu();
		menu4.login(datas);
		menu4.nurseMenu(datas);
		EXPECT_EQ(3, menu4.getMainOps());
		EXPECT_EQ(4, menu4.getAccountType());
		EXPECT_EQ(false, menu4.run());

		std::istringstream input5("1\nkendo\npassword\n2");
		std::ostringstream output5;
		Menu menu5(input5, output5);
		menu5.mainMenu();
		menu5.login(datas);
		menu5.patientMenu(datas);
		EXPECT_EQ(3, menu5.getMainOps());
		EXPECT_EQ(3, menu5.getAccountType());
		EXPECT_EQ(false, menu5.run());
	}ENDM
	#endif
	
#endif
#ifndef teszt
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