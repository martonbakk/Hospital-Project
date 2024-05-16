#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"

#include "Doctor.h"
#include "Patient.h"
#include "Nurse.h"
#include "array.h"
#include "password.h"


class Admin;

/// @Admin fi�k ///
class Admin :public Account {
    bool _verified;     //ellett-e fogadva a fi�k m�sik Admin �ltal
public:
    Admin(bool accept = false, int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone), _verified(accept) {}
public:
    void listAccountInformation() override;                             //Saj�t fi�kadatok lek�r�se
public:
    void deleteMedicine(Dictionary& medicines, const char* medicine);   //Gy�gyszer t�rl�se a rakt�rb�l
    void listAllPatientAccount(const Array<Patient>& patients);
    void listAllAccount(const Array<Patient>& patients, const Array<Nurse>& nurses, const Array<Admin>& admins, const Array<Doctor>& doctors); //�sszes fi�k kilist�z�sa
    void setDoctorsMaxPatientNum(int num);                              //Maximum betegsz�m be�ll�t�sa
    void verifyAdmins(Admin& user);                                     //�j admin fi�k enged�lyez�se
public:
    void loadData(const String& accountINF)override;
    void sendData(std::ostream& os)override;
    void listAllOption() override;
public:
    //Fi�k t�rl�se az adatb�zisb�l
    void deleteAccountfromArray(Array<Doctor>& doctors, Array<Password>& passwords, Array<Patient>& patients, Patient& account);
    //Fi�k szerkezt�se az adatb�zisban
    template<class T>
    void editAccountfromList(T& account, const char* Name, const char* Mail, const char* Phone) {
        account.editAccountInformation(Name, Mail, Phone);
    }

};

#endif //ADMIN_H