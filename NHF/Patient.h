#ifndef PATIENT_H
#define PATIENT_H

#include "Account.h"
#include "Doctor.h"
#include "myString.h"

class Doctor;

/// @P�ciens fi�k ///
class Patient :public Account {
    String _sympthoms;                  //Beteg t�netei
    Dictionary _medicinesToGet;         //Fel�rt gy�gyszerek
    int _docID;                         //Doktor ID-ja
    bool _treated;                      //Kezelt

public:
    Patient(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN", const char* symptms = "NONE", bool treated = false, int docid = -1) :
        Account(id, uName, Name, Mail, Phone), _sympthoms(symptms), _medicinesToGet(), _docID(docid), _treated(treated) {}
public:
    void listAccountInformation() override;     //Saj�t fi�kadatok lek�r�se 
public:
    void setSympthoms(const String& symp);                  //Panaszok, t�netek le�r�sa
    void setTreated(bool treat);                            //Beall�tja, hogy kezeltek-e mar
    void setDoc(const Doctor& doc);                         //Beallitja a doktort
    void setMedicines(const Dictionary& medicines);         //Beallitja a felirt gyogyszereket
public:
    Dictionary& patientNeededMedicines() { return _medicinesToGet; }  //A noverek ezzel adagoljak a gyogyszert
    String getSympthoms() { return _sympthoms; }
    int getDocID() { return _docID; }
public:
    void loadData(const String& ) override;
    void sendData(std::ostream& os)override;
    void listAllOption() override;
    String getName() { return _name; }
};


#endif //PATIENT_H