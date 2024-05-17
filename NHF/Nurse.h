#ifndef NURSE_H
#define NURSE_H

#include "Account.h"
#include "Patient.h"

#include "memtrace.h"

/// @Ápoló fiók ///
class Nurse : public Account {
    Dictionary _medicinesToGive;
public:
    Nurse(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone) {}
public:
    void listAccountInformation(std::ostream& os) override;                                 //Saját fiókadatok lekérése
    void medicineLog(Patient& patient);                                     //Gyógyszerek adagolása a betegnek 
    void getMedicine(Dictionary& medicines, int key, const char* value);    //Gyógyszerek kivétele a raktárból
public:
    void loadData(const String&)override;
    void sendData(std::ostream& os)override;
    void listAllOption(std::ostream& os) override;
};

#endif //NURSE_H