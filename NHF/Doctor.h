#ifndef DOCTOR_H
#define DOCTOR_H

#include "memtrace.h"

#include "Account.h"
#include "Patient.h"
#include "array.h"

class Patient;

/// @Doktor fi�k ///
class Doctor : public Account {
    static int _maxPatientNum;  //A maximum p�ciensek sz�ma
    Array<Patient*> _patients;        //A betegek akik a doktorhoz tartoznak
    int _patientNum;            //A jelenlegi betegeinek a sz�ma
public:
    Doctor(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone), _patients(0), _patientNum(0){}
    ~Doctor() { }
public:
    void listAccountInformation(std::ostream& os) override;                          //Saj�t fi�kadatok lek�r�se
    void seePatientsSympthoms(std::ostream&os, const Array<Patient>& array);          //Beteg panaszainak elolvas�sa
    void getPatient(Patient* patient);                               //Beteg felv�tele
    void listPatients(std::ostream& os);
    int listAllPatients(std::ostream& os,Array<Patient>& patients);
    void replyPatientSympthoms(const Dictionary& medicines, const DictionaryEntry& reply, int idx);   //Gy�gyszer fel�r�sa vagy elutas�t�s
public:
    static void setMaxPatientNum(int num);                          //Maximum betegsz�m be�ll�t�sa---ADMINHOZ KELL
public:
    void loadData(const String&)override;
    void sendData(std::ostream& os)override;
    void listAllOption(std::ostream& os) override;
public:
    void setPatients(Array<Patient>& patients);
    void deletePatient(Patient& patient);
};

#endif //DOCTOR_H