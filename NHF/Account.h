#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "myString.h"
#include "dictionary.h"
/*
Ebben a header f�jlban vannak meg�rva a k�l�nb�z� felhaszn�l�i fi�kok oszt�lyai. Az Account az interface
bel�le sz�rmazik le az �sszes t�bbi fi�k. Minden fit�p�s rendelkezik a k�vetkez� f�ggv�nyekkel:Saj�t fi�kadatok lek�r�se,
Saj�t fi�k szerkezt�se
*/

/// @Fi�k interface ///
class Account
{
protected:
    int _accountId;     //Fi�k id, ezek alapj�n k�ti �ssze bejelentkez�si adatokat a fi�k adatokkal
    String _userName;   //Felhaszn�l�n�v
    String _name;       //Vezet�k �s keresztv�n (kett� keresztnevet nem lehet megadni a programban)
    String _mail;       //Emailc�m
    String _phone;      //Telefonsz�m

public:
    Account(int id = -1, const char* uName = "UNKNOWN", const char* Name = "UNKNOWN", const char* Mail = "UNKNOWN", const char* Phone = "UNKNOWN") :
        _accountId(id),
        _userName(uName),
        _name(Name),
        _mail(Mail),
        _phone(Phone) {}
    ~Account() {};
public:
    virtual void listAccountInformation() = 0; //Saj�t fi�kadatok lek�r�se
    void editAccountInformation(const char* Name, const char* Mail, const char* Phone); //Saj�t fi�k szerkezt�se
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