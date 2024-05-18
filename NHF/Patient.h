#ifndef PATIENT_H
#define PATIENT_H

#include "Account.h"
#include "Doctor.h"
#include "myString.h"
#include "memtrace.h"

class Doctor;

/// @Paciens fiók ///
/*
* A fiokhoz tartozo funkciok:
* -Tunetek leirasa
*/
class Patient :public Account {
    String sympthoms;                  //Beteg tünetei
    Dictionary medicinesToGet;         //Felirt gyogyszerek
    int docID;                         //Doktor ID-ja
    bool treated;                      //Kezelt
public:
    Patient(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN", const char* symptms = "NONE", bool treated = false, int docid = -1) :
        Account(id, uName, Name, Mail, Phone), sympthoms(symptms), medicinesToGet(), docID(docid), treated(treated) {}
public:
    void listAccountInformation(std::ostream& os) override;     //Saját fiókadatok lekérése 
public:
    void setSympthoms(const String& symp);                      //Panaszok, tünetek leírása menuopciohoz
    void setDoc(int docID) { docID = docID; }                  //A doktor betegffelvételhez kell
public:
    void medicineFromNurse(Dictionary& nurseMedicines);         //A noverek ezzel adagoljak a gyogyszert es a 
    void medicineReply(const DictionaryEntry& doctorReply);     //doktor ezzel irja fel milyen gyogyszer kell a betegnek
    void publicData(std::ostream& os);                          //nev, tunet kiirasa egy adott os-re
    int getDocID() { return docID; }                           //visszaadja, melyik doktornal van
public:
    void loadData(const String& ) override;                     //adatok betoltese egy stringrol
    void sendData(std::ostream& os)override;                    //adatok kiirasa egy adott os-re
    void listAllOption(std::ostream& os) override;              //a fiokhoz tartozo funkciok kiirasa egy adott ostreamre
};


#endif //PATIENT_H