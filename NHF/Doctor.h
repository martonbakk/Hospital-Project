#ifndef DOCTOR_H
#define DOCTOR_H

#include "Account.h"
#include "Patient.h"
#include "array.hpp"

class Patient;

/// @Doktor fiók ///
class Doctor : public Account {
    static int _maxPatientNum;  //A maximum páciensek száma
    Patient** _patients;        //A betegek akik a doktorhoz tartoznak
    int _patientNum;            //A jelenlegi betegeinek a száma
public:
    Doctor(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone), _patients(0), _patientNum(0){}
    ~Doctor() { delete[] _patients; }
public:
    String getName() { return _name; }
    int& getPatientNum() { return _patientNum; }
    Patient** getPatients(){ return _patients; }
public:
    void listAccountInformation() override;                         //Saját fiókadatok lekérése
    void seePatientsSympthoms(const Array<Patient>& array);                                    //Beteg panaszainak elolvasása
    void getPatient(Patient* patient);                               //Beteg felvétele
    void listPatients();
    int listAllPatients(Array<Patient>& patients);
    void replyPatientSympthoms(const Dictionary& medicines, const DictionaryEntry& reply, int idx);   //Gyógyszer felírása vagy elutasítás
public:
    static void setMaxPatientNum(int num);                          //Maximum betegszám beállítása---ADMINHOZ KELL
public:
    void loadData(const String&)override;
    void sendData(std::ostream& os)override;
    void listAllOption() override;
public:
    void setPatients(Array<Patient>& patients);
public:
    friend std::ifstream& operator>>(std::ifstream& is, Doctor& member);
    friend std::ofstream& operator<<(std::ofstream& is, Doctor& member);
};

#endif //DOCTOR_H