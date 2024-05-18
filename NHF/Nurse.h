#ifndef NURSE_H
#define NURSE_H

#include "Account.h"
#include "Patient.h"

#include "memtrace.h"

/// @Nurse fiok ///
/*
* A fiokok funkcionalitasai:
* - Gyogyszerek adagolasa a betegnek – Kivesz annyi db gyogyszert a raktarból amennyit gondol, 
*   majd azt odaadja a betegnek, többet nem vehet ki a raktarbol mint amennyi elo le irva egy 
*   betegnek, több részletben is odaadhatja a betegnek 
* - Gyogyszerek kivetele a raktarbol – A raktárból kiveszi a gyogyszert
*/
class Nurse : public Account {
    Dictionary medicinesToGive;
public:
    Nurse(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        Account(id, uName, Name, Mail, Phone) {}
public:
    void listAccountInformation(std::ostream& os) override;                 //sajat fiokadatok lekerdezese
    void medicineLog(Patient& patient);                                     //gyogyszerek adagolása a betegnek 
    void getMedicine(Dictionary& medicines, int key, const char* value);    //gyogyszerek kivetele a raktarbol
public:
    void loadData(const String&)override;           //stringbol betolti a fiokadatokat
    void sendData(std::ostream& os)override;        //egy os-re kiirja a fiokadatokat
    void listAllOption(std::ostream& os) override;  //a funkcionalitasokat kiirja egy osre
};

#endif //NURSE_H