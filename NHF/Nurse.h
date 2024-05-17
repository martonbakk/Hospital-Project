#ifndef NURSE_H
#define NURSE_H

#include "Account.h"
#include "Patient.h"

#include "memtrace.h"

/// @�pol� fi�k ///
class Nurse : public Account {
    Dictionary _medicinesToGive;
public:
    Nurse(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone) {}
public:
    void listAccountInformation(std::ostream& os) override;                                 //Saj�t fi�kadatok lek�r�se
    void medicineLog(Patient& patient);                                     //Gy�gyszerek adagol�sa a betegnek 
    void getMedicine(Dictionary& medicines, int key, const char* value);    //Gy�gyszerek kiv�tele a rakt�rb�l
public:
    void loadData(const String&)override;
    void sendData(std::ostream& os)override;
    void listAllOption(std::ostream& os) override;
};

#endif //NURSE_H