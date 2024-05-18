#ifndef MENU_H
#define MENU_H

#include "myString.h"
#include "CaesarCipher.h"
#include "Account.h"
#include "Patient.h"
#include "Nurse.h"
#include "Doctor.h"
#include "Admin.h"
#include "array.h"
#include "manager.h"
#include "CaesarCipher.h"

#include "memtrace.h"

#include <iostream>
#include <sstream>
#include <string>

//Data
/* Mivel heterogen kollekciot nem lehetett implementalni mert az ososztalynak kevesebb fuggvenye van mint a leszarmaztatottaknak ezert
* negy kulonbozo tombot kellet letrehozni. A Data ezeket foglalja egybe. Tovabba, hogy az adatokat egy helyen tartsuk akkor a gyogyszerek es 
* a jelszavak tombot is bekerultek ide.
*/
struct Data {
    Dictionary medicines;       //gyogyszerek     
    Array<Admin>admins;         //adminok
    Array<Doctor>doctors;       //doktorok
    Array<Patient>patients;     //paciensek
    Array<Nurse>nurses;         //apolok
    Array<Password>passwords;   //jelszavak
};


/// @Menu ///
/*
* A menu osztaly foglalja ossze a menu managereket. A menu osztalyban hivodnakmeg a managerek megfelelo funkcioi.
*/
class Menu{ 
    std::istream& is;           //bemenet
    std::ostream& os;           //kimenet
    CaesarCipher encryptor;     //titkosito
    userAccount user;           //felahasznalo altal bejelentkezett fiok
    MenuOptions menuOPS;        //menu opciok
    LoginManager userLogin;     //bejelentkezesert felelos manager
    AdminManager adManager;     //admin muveleketert felelos manager
    DoctorManager docManager;   //doktor muveletekert felelos manager
    NurseManager nurManager;    //nurse muveletekert felelos manager
    PatientManager patManager;  //patient muveletekert feleos manager
    String userName, password, firstName, lastName, email, phone;   //regisztraciohoz szukseges adatok
public:
    Menu(std::istream& input = std::cin, std::ostream& output = std::cout, int cipher=3):
        is(input), os(output), encryptor(cipher), userLogin(input, output), adManager(input, output), docManager(input, output), nurManager(input, output), patManager(input, output){}
    void login(Data& datas);        //bejelentkezes
    void adminMenu(Data& datas);    //admin menu
    void doctorMenu(Data& datas);   //doktor menu
    void patientMenu(Data& datas);  //paciens menu
    void nurseMenu(Data& datas);    //apolo menu
    void registration(Data& datas); //regisztracio
    void mainMenu();                //fomenu
    void loginError();              //bejelentkezes hiba
public:
    bool run() { return (menuOPS.mainMenuOption != 3); }        //program futasanak eldontesere kell
    int getMainOps() { return menuOPS.mainMenuOption; }         //visszaadja a fomenu opciot
    int getAccountType() { return userLogin.getAccountType(); } //visszaadja a bejelentkezett fiok tipusat
};
#endif 