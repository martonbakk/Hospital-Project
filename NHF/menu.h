#ifndef MENU_H
#define MENU_H

#include "myString.h"
#include "CaesarCipher.h"
#include "Account.h"
#include "Patient.h"
#include "Nurse.h"
#include "Doctor.h"
#include "Admin.h"
#include "array.h"
#include "manager.h"
#include "CaesarCipher.h"

#include "memtrace.h"

#include <iostream>
#include <sstream>
#include <string>


struct Data {
    Dictionary medicines;
    Array<Admin>admins;
    Array<Doctor>doctors;
    Array<Patient>patients;
    Array<Nurse>nurses;
    Array<Password>passwords;
};

class Menu{
    std::istream& is;
    std::ostream& os;
    CaesarCipher encryptor;   
    userAccount user;
    MenuOptions menuOPS;
    LoginManager userLogin;
    AdminManager adManager; 
    DoctorManager docManager;
    NurseManager nurManager;
    PatientManager patManager;
    String userName, password, firstName, lastName, email, phone;
public:
    Menu(std::istream& input = std::cin, std::ostream& output = std::cout, int cipher=3):
        is(input), os(output), encryptor(cipher), userLogin(input, output), adManager(input, output), docManager(input, output), nurManager(input, output), patManager(input, output){}
    void login(Data& datas);
    void adminMenu(Data& datas);
    void doctorMenu(Data& datas);
    void patientMenu(Data& datas);
    void nurseMenu(Data& datas);
    void registration(Data& datas);
    void mainMenu();
    void loginError();
public:
    bool run() { return (menuOPS.mainMenuOption != 3); }
    int getMainOps() { return menuOPS.mainMenuOption; }
    int getAccountType() { return userLogin.getAccountType(); }
};
#endif 