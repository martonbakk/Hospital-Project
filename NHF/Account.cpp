#include "Account.h"

void Account::editAccountInformation(const char* Name, const char* Mail, const char* Phone) {
        _name = Name;
        _mail = Mail;
        _phone = Phone;
}