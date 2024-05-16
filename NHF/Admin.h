#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"

#include "Doctor.h"
#include "Patient.h"
#include "Nurse.h"
#include "array.h"
#include "password.h"


class Admin;

/// @Admin fiók ///
class Admin :public Account {
    bool _verified;     //ellett-e fogadva a fiók másik Admin által
public:
    Admin(bool accept = false, int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone), _verified(accept) {}
public:
    void listAccountInformation() override;                             //Saját fiókadatok lekérése
public:
    void deleteMedicine(Dictionary& medicines, const char* medicine);   //Gyógyszer törlése a raktárból
    void listAllPatientAccount(const Array<Patient>& patients);
    void listAllAccount(const Array<Patient>& patients, const Array<Nurse>& nurses, const Array<Admin>& admins, const Array<Doctor>& doctors); //Összes fiók kilistázása
    void setDoctorsMaxPatientNum(int num);                              //Maximum betegszám beállítása
    void verifyAdmins(Admin& user);                                     //Új admin fiók engedélyezése
public:
    void loadData(const String& accountINF)override;
    void sendData(std::ostream& os)override;
    void listAllOption() override;
public:
    //Fiók törlése az adatbázisbõl
    void deleteAccountfromArray(Array<Doctor>& doctors, Array<Password>& passwords, Array<Patient>& patients, Patient& account);
    //Fiók szerkeztése az adatbázisban
    template<class T>
    void editAccountfromList(T& account, const char* Name, const char* Mail, const char* Phone) {
        account.editAccountInformation(Name, Mail, Phone);
    }

};

#endif //ADMIN_H