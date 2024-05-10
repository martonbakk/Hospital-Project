#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "myString.h"
#include "dictionary.h"
/*
Ebben a header fájlban vannak megírva a különbözõ felhasználói fiókok osztályai. Az Account az interface
belõle származik le az összes többi fiók. Minden fitípús rendelkezik a következõ függvényekkel:Saját fiókadatok lekérése,
Saját fiók szerkeztése
*/

/// @Fiók interface ///
class Account
{
protected:
    int _accountId;     //Fiók id, ezek alapján köti össze bejelentkezési adatokat a fiók adatokkal
    String _userName;   //Felhasználónév
    String _name;       //Vezeték és keresztvén (kettõ keresztnevet nem lehet megadni a programban)
    String _mail;       //Emailcím
    String _phone;      //Telefonszám

public:
    Account(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        _accountId(id),
        _userName(uName),
        _name(Name),
        _mail(Mail),
        _phone(Phone) {}
    ~Account() {};
public:
    virtual void listAccountInformation() = 0; //Saját fiókadatok lekérése
    void editAccountInformation(const char* Name, const char* Mail, const char* Phone); //Saját fiók szerkeztése
    int getAccountID() const { return _accountId; }
public:
    friend bool operator==(const Account& lhs, const Account& rhs) {
        return (lhs._accountId == rhs._accountId);
    }
public:
    virtual void loadData(const String& ss)=0;
    virtual void sendData(std::ostream& os)=0;
    virtual void listAllOption()=0;
};



#endif