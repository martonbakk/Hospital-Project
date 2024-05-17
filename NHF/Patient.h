#ifndef PATIENT_H
#define PATIENT_H

#include "Account.h"
#include "Doctor.h"
#include "myString.h"
#include "memtrace.h"

class Doctor;

/// @Páciens fiók ///
class Patient :public Account {
    String _sympthoms;                  //Beteg tünetei
    Dictionary _medicinesToGet;         //Felírt gyógyszerek
    int _docID;                         //Doktor ID-ja
    bool _treated;                      //Kezelt

public:
    Patient(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN", const char* symptms = "NONE", bool treated = false, int docid = -1) :
        Account(id, uName, Name, Mail, Phone), _sympthoms(symptms), _medicinesToGet(), _docID(docid), _treated(treated) {}
public:
    void listAccountInformation(std::ostream& os) override;     //Saját fiókadatok lekérése 
public:
    void setSympthoms(const String& symp);                  //Panaszok, tünetek leírása menuopciohoz
    void setDoc(int docID) { _docID = docID; }         //A doktor betegffelvételhez kell
public:
    void medicineFromNurse(Dictionary& nurseMedicines);     //A noverek ezzel adagoljak a gyogyszert es a 
    void medicineReply(const DictionaryEntry& doctorReply);  //doktor ezzel irja fel milyen gyogyszer kell a betegnek
    void publicData(std::ostream& os);
    int getDocID() { return _docID; }
public:
    void loadData(const String& ) override;
    void sendData(std::ostream& os)override;
    void listAllOption(std::ostream& os) override;
};


#endif //PATIENT_H