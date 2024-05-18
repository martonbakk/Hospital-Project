#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "myString.h"
#include "dictionary.h"
#include "memtrace.h"

/// @Fiok interface ///
/*
*Ebben a header fájlban vannak megírva a különbözõ felhasználói fiókok osztályai. Az Account az interface
*belõle származik le az összes többi fiók. Minden fitípús rendelkezik a következõ függvényekkel:Saját fiókadatok lekérése,
*Saját fiók szerkeztése
*/
class Account
{
protected:
    int accountId;     //Fiok id, ezek alapján köti ossze bejelentkezési adatokat a fiok adatokkal
    String userName;   //Felhasználonev
    String name;       //Vezetek es keresztven (ketto keresztnevet nem lehet megadni a programban)
    String mail;       //Emailcim
    String phone;      //Telefonszam

public:
    Account(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        accountId(id),
        userName(uName),
        name(Name),
        mail(Mail),
        phone(Phone) {}
    ~Account() {};
public:
    virtual void listAccountInformation(std::ostream& os) = 0;                          //Sajat fiokadatok lekerese
    void editAccountInformation(const char* Name, const char* Mail, const char* Phone); //Sajat fiok szerkeztese
    int getAccountID() const { return accountId; }                                     //visszaadja a fok id-jet
public:
    friend bool operator==(const Account& lhs, const Account& rhs) {         //visszaadja, hogy ket fiok megegyezik-e ezt a fiok id alapjan lehet osszehasonlitani
        return (lhs.accountId == rhs.accountId);
    }
public:
    virtual void loadData(const String& ss)=0;           //beolvassa egy stringbol az adatokat es beletolti a fiokba
    virtual void sendData(std::ostream& os)=0;           //kiirja egy ostreamre a az adatait
    virtual void listAllOption(std::ostream& os)=0;      //a fiokokhoz tartozo menu funkciok kiirasaert felel ez a fuggveny
public:
    friend std::ifstream& operator>>(std::ifstream& is, Account& member);   //inserter operator, a fajlbol olvasasnal van erre szukseg
    friend std::ofstream& operator<<(std::ofstream& is, Account& member);   //kiira egy ostreamre a fiok adatait, a fajlba irasnal van erre szukseg
};



#endif