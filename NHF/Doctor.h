#ifndef DOCTOR_H
#define DOCTOR_H

#include "memtrace.h"

#include "Account.h"
#include "Patient.h"
#include "array.h"

class Patient;

/// @Doktor fiok ///
/*
* A fiokhoz tartozo funkcionalitasok:
*- Beteg felvetele – Magához rendelhe a beteget akinek kesobb gyogyszert irhat ki 
*- Gyogyszer felirasa a betegeknek vagy elutasitas – Felír egy gyogyszert es mennyiseget 
*- Betegek panaszainak elolvasasa 
*/
class Doctor : public Account {
    static int maxPatientNum;  //A maximum paciensek szama
    Array<Patient*> patients;  //A betegek akik a doktorhoz tartoznak
    int patientNum;            //A jelenlegi betegeinek a szama
public:
    Doctor(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone), patients(0), patientNum(0){}
    ~Doctor() { }
public:
    void listAccountInformation(std::ostream& os) override;                             //Sajat fiókadatok lekerese
    void seePatientsSympthoms(std::ostream&os, const Array<Patient>& array);            //Beteg panaszainak elolvasasa
    void getPatient(Patient* patient);                                          //Beteg felvetele
    void listPatients(std::ostream& os);                                        //A megadott ostreamre kiirja a pacienseit
    int listAllPatients(std::ostream& os,const Array<Patient>& patients);       //A megadott ostreamre kiirja az osszes pacienst
    void replyPatientSympthoms(const Dictionary& medicines, const DictionaryEntry& reply, int idx);   //Gyogyszer felírasa vagy elutasítás
public:
    static void setMaxPatientNum(int num);                //Maximum betegszám beallítasa, ezt hasznalja az admin
public:
    void loadData(const String&)override;                 //A stringrol betolti az adatait
    void sendData(std::ostream& os)override;              //Egy adott ostreamre kiirja az adatait
    void listAllOption(std::ostream& os) override;        //Kiirja a fiokhoz tartozo funkciokat
public:
    void setPatients(const Array<Patient>& patientsarr);  //A pacienseit beallitja a doktornak
    void deletePatient(const Patient& patient);           //Torli az adott pacienset a  sajat betegei kozul
};

#endif //DOCTOR_H