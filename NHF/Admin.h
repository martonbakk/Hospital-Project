#ifndef ADMIN_H
#define ADMIN_H

#include "memtrace.h"

#include "Account.h"
#include "Doctor.h"
#include "Patient.h"
#include "Nurse.h"
#include "array.h"
#include "password.h"


class Admin;

/// @Admin fiok ///
/*
* Az admin fiok a kovetkezo funkcionalitassal rendelkezik:
* -Paciens fokok torlese, szerkeztese – Szerkez /Torli az adatbazisbol a fiokot 
* -Összes fiok listazasa – Megnezhe az osszes regisztralt fiokot az adatbazisban 
* -Gyógyszer törlése a raktarbol – Gyogyszereket kitorli az adatbazisbol 
* -Uj admin fiok engedelyezese – Uj admin fiokot engedelyeztethet 
* -Doktorok maximum betegeinek korlatozasa – Szerkezthe a limitet a doktor fioknal (csak nagyobb szamot adhat meg)
*/
class Admin :public Account {
    bool verified;     //ellett-e fogadva a fiók másik Admin által
public:
    Admin(bool accept = false, int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone), verified(accept) {}
public:
    void listAccountInformation(std::ostream& os) override;             //Sajat fiókadatok lekerese
public:
    void deleteMedicine(Dictionary& medicines, const char* medicine);               //Gyogyszer torlese a raktarbol
    void listAllPatientAccount(std::ostream& os, const Array<Patient>& patients);   //Kiirja az osszes paciens fiokot
    void listAllAccount(std::ostream& os, const Array<Patient>& patients, const Array<Nurse>& nurses, const Array<Admin>& admins, const Array<Doctor>& doctors); //Osszes fiok kilistazasa
    void setDoctorsMaxPatientNum(int num);                   //Maximum betegszam beallitasa
    void verifyAdmins(Admin& user);                          //Uj admin fiok engedelyezese
public:
    void loadData(const String& accountINF)override;         //Betolti a fiokatadok egy stringbol       
    void sendData(std::ostream& os)override;                 //Kiirja a fiokadatokat egy ostreamre
    void listAllOption(std::ostream& os) override;           //Kiirja az osszes funkcionalitast amit a user elerhet
    bool verifiedYet()const { return verified; }             //Visszaadja, hogy már el lett-e fogadva
public:
    void deleteAccountfromArray(Array<Doctor>& doctors, Array<Password>& passwords, Array<Patient>& patients, Patient& account);    //Paciens fiok torlese az adatbazisbol
    template<class T>
    void editAccountfromList(T& account, const char* Name, const char* Mail, const char* Phone) {   //Fiok szerkeztese az adatbazisban
        account.editAccountInformation(Name, Mail, Phone);
    }

};

#endif //ADMIN_H