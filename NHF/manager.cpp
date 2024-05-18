#include "manager.h"

void LoginManager::getTypeAndIDX(Array<Password>& passwords, CaesarCipher& encryptor) {
    if (!logged) {
        os << "Adja meg a felhasznalo nevet:";
        is >> username;
        os << "Adja meg a jelszavat:";
        is >> password;
        for (size_t i = 0; i < passwords.getLen(); i++) {
            if (passwords[i].getUserName() == username && passwords[i].getPassword() == encryptor.encode(password)) {
                loggedInAccountID = passwords[i].getID();
                loggedInAccountType = passwords[i].getAccountType();
                logged = true;
            }
        }
    }
}

void LoginManager::setAccount(Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients, userAccount& user) {
    int loggedInAccountID = this->loggedInAccountID;
    switch (AccountType(loggedInAccountType))
    {
    case ad:
        loggedInAccountIDX = admins.indexOfElement([loggedInAccountID](const Admin& admin) {
            return admin.getAccountID() == loggedInAccountID;
            });
        user.admin = &admins[loggedInAccountIDX];
        break;
    case doc:
        loggedInAccountIDX = doctors.indexOfElement([loggedInAccountID](const Doctor& doctor) {
            return doctor.getAccountID() == loggedInAccountID;
            });
        user.doctor = &doctors[loggedInAccountIDX];
        break;
    case pat:
        loggedInAccountIDX = patients.indexOfElement([loggedInAccountID](const Patient& patient) {
            return patient.getAccountID() == loggedInAccountID;
            });
        user.patient = &patients[loggedInAccountIDX];
        break;
    case nur:
        loggedInAccountIDX = nurses.indexOfElement([loggedInAccountID](const Nurse& nurse) {
            return nurse.getAccountID() == loggedInAccountID;
            });
        user.nurse = &nurses[loggedInAccountIDX];
        break;
    default:
        break;
    }
}


//Admin manager
void AdminManager::adminMenu(userAccount& user, Array<Admin>& admins, MenuOptions& ops) {
    try {
        user.admin->listAccountInformation(os);
       user.admin->listAllOption(os);
    }
    catch (...) {
        os << "ID ERROR\n";
    }
    is >> ops.adminMenuOption;
}

void AdminManager::adminDelete(userAccount& user, Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Password>& passwords) {

    user.admin->listAllPatientAccount(os, patients);
    os << "VALASSZA KI MELYIK FIOKOT SZERETNE TOROLNI: ";
    is >> adminDeleteOption;
    if (adminDeleteOption <= patients.getLen() && adminDeleteOption>0) {
        try {
            os << adminDeleteOption;
            user.admin->deleteAccountfromArray(doctors, passwords, patients, patients[adminDeleteOption - 1]);
        }
        catch (...) {
            os << "DELETE ERROR";
        }
    }
    else {
        os << "THERE IS NO OPTION LIKE THIS. RETURNING TO THE ADMIN MENU...\n";
    }
}

void AdminManager::adminEditAccount(userAccount& user, Array<Admin>& admins, Array<Patient>& patients, Array<Doctor>& doctors, Array<Nurse>& nurses) {
    user.admin->listAllAccount(os, patients, nurses, admins, doctors);
    os << "VALASSZA KI MELYIK FIOKTIPUST SZERETNE SZERKEZTENI: ";
    is >> adminEditTypeOption;
    if (adminEditTypeOption > 4 || adminEditTypeOption < 1) {
        throw "THERE IS NO OPTION LIKE THIS...\n";
    }
    os << "VALASSZA KI MELYIK FIOKOT SZERETNE SZERKEZTENI: ";
    is >> adminEditOptionIdx;

    os << "EBBEN A FORMABAN ADJA MEG AZ ADATOKAT, A FELHASZNALONEV NEM TARTALMAZHAT * ES SZOKOZ KARAKTEREKET, A NEVNEL CSAK A KERESZT ES A CSALAD NEVET ADJON, HA TOBB KERESZT NEVE VAN CSAK EGYET ADJON MEG\n(Firstname Lastname Mail Phone) : ";
    is >> editedFirstName >> editedLastName >> editedEmail >> editedPhone;
    String name;
    name = editedFirstName;
    name += editedLastName;
    switch (adminEditTypeOption)
    {
    case 1:
        if (adminEditOptionIdx > admins.getLen() || adminEditOptionIdx < 0) {
            throw "YOU MIGHT GAVE A WRONG INDEX\n";
        }
        user.admin->editAccountfromList(admins[adminEditOptionIdx - 1], name.getText(), editedEmail.getText(), editedPhone.getText());
        break;
    case 2:
        if (adminEditOptionIdx > doctors.getLen() || adminEditOptionIdx < 0) {
            throw "YOU MIGHT GAVE A WRONG INDEX\n";
        }
        user.admin->editAccountfromList(doctors[adminEditOptionIdx - 1], name.getText(), editedEmail.getText(), editedPhone.getText());
        break;
    case 3:
        if (adminEditOptionIdx > nurses.getLen() || adminEditOptionIdx < 0) {
            throw "YOU MIGHT GAVE A WRONG INDEX\n";
        }
        user.admin->editAccountfromList(nurses[adminEditOptionIdx - 1], name.getText(), editedEmail.getText(), editedPhone.getText());
        break;
    case 4:
        if (adminEditOptionIdx > patients.getLen() || adminEditOptionIdx < 0) {
            throw "YOU MIGHT GAVE A WRONG INDEX\n";
        }
        user.admin->editAccountfromList(patients[adminEditOptionIdx - 1], name.getText(), editedEmail.getText(), editedPhone.getText());
        break;
    default:
        break;
    }
}

void AdminManager::adminListAccounts(userAccount& user, Array<Admin>& admins, Array<Doctor>& doctors, Array<Nurse>& nurses, Array<Patient>& patients) {
    user.admin->listAllAccount(os, patients, nurses, admins, doctors);
}

void AdminManager::adminDeleteMedicine(Dictionary& medicines) {
    os << medicines;
    os << "Melyiket szeretne torolni? Adja meg a nevet: ";
    is >> adminMedOption;
    for (size_t i = 0; i < medicines.getSize(); i++) {
        if (medicines[i]._value == adminMedOption.getText())
            medicines[i]._key = 0;
    }
}

void AdminManager::adminVerifyAdminAccount(userAccount& user, Array<Admin>& admins) {
    for (size_t i = 0; i < admins.getLen(); i++) {
        os << "Opcio " << i + 1 << '\n';
        admins[i].listAccountInformation(os);
    }
    os << "Adja meg melyik admin fiokot szeretne engedelyeztetni: ";
    is >> adminVerifyOption;
    try {
        user.admin->verifyAdmins(admins[adminVerifyOption - 1]);
    }
    catch (...) {
        throw "There is no option like this\n";
    }
}

void AdminManager::adminSetDoctorsLimit(userAccount& user, Array<Admin>& admins) {
    os << "Adja meg mennyire szeretne korlatozni a betegek szamat: ";
    is >> adminSetPatientMaxNum;
    try {
        user.admin->setDoctorsMaxPatientNum(adminSetPatientMaxNum);
    }
    catch (const char* ERROR) {
        os << ERROR;
    }
   
}

void AdminManager::adminDefault(MenuOptions& ops) {
    os << "Nincs ilyen opcio...\nValasszon ujat: ";
    int op;
    is >> op;
    ops.mainMenuOption = op;
}


//Doctor Manager
void DoctorManager::doctorMenu(userAccount& user, MenuOptions& ops, Array<Doctor>& doctors) {
    try {
        user.doctor->listAccountInformation(os);
        user.doctor->listAllOption(os);
    }
    catch (...) {
        os << "ID ERROR";
    }
    is >> ops.doctorMenuOption;
}

void DoctorManager::doctorGetPatient(userAccount& user, Array<Doctor>& doctors, Array<Patient>& patients) {
    if (user.doctor->listAllPatients(os, patients) != 0) {
        os << "Valassza ki melyik beteget szeretne magahoz venni:";
        is >> doctorGetPatientOption;
        try {
            user.doctor->getPatient(&patients[doctorGetPatientOption - 1]);
        }
        catch (const char* ERROR) {
            os << ERROR;
        }
    }
    else {
        os << "Minden betegnek jelenleg van doktora\n";
    }
}

void DoctorManager::doctorReplyToPatient(userAccount& user, Array<Doctor>& doctors, Dictionary& medicines) {
    user.doctor->listPatients(os);
    os << "Valassza ki melyik betegnek akarja felirni a gyogyszert: ";
    is >> doctorPatientIDX;
    os << "Adja meg a gyogyszer nevet: ";
    is >> doctorReplyMedicine;
    os << "Adja meg mennyit szedjen belole: ";
    is >> doctorReplyKey;
    try {
        user.doctor->replyPatientSympthoms(medicines, DictionaryEntry(doctorReplyKey, doctorReplyMedicine.getText()), doctorPatientIDX - 1);
    }
    catch (const char* ERROR) {
        os << ERROR;
    }
}

void DoctorManager::doctorSeePatients(userAccount& user, Array<Doctor>& doctors, Array<Patient>& patients) {
    user.doctor->seePatientsSympthoms(os, patients);
}

//Patient Manager
void PatientManager::patientMenu(userAccount& user, MenuOptions& ops, Array<Patient>& patients) {
    try {
        user.patient->listAccountInformation(os);
        user.patient->listAllOption(os);
    }
    catch (...) {
        os << "ID ERROR";
    }
    is >> ops.patientMenuOption;
}

void PatientManager::patientSetSymp(userAccount& user, Array<Patient>& patients) {
    os << "Irja le milyen gondja van: ";
    is >> patientSympthoms; 
    char ch;
    while (is.get(ch)&&ch!='\n'){
        patientSympthoms += ch;
    }
    user.patient->setSympthoms(patientSympthoms);
}


//Nurse
void NurseManager::nurseMenu(userAccount& user, MenuOptions& ops, Array<Nurse>& nurses) {
    try {
        user.nurse->listAccountInformation(os);
        user.nurse->listAllOption(os);
    }
    catch (...) {
        os << "ID ERROR";
    }
    is >> ops.nurseMenuOption;
}

void NurseManager::nurseGiveMedicines(userAccount& user, Array<Nurse>& nurses, Array<Patient>& patients) {
    for (size_t i = 0; i < patients.getLen(); i++)
    {
        os << "Option (" << i + 1 << ")\n";
        patients[i].listAccountInformation(os);
    }
    os << "Valasszon egy beteget: ";
    is >> nursePatientOptionIDX;
    try {
        user.nurse->medicineLog(patients[nursePatientOptionIDX - 1]);
    }
    catch (const char* ERROR) {
        os << ERROR;
    }
}

void NurseManager::nurseGetMedicineFromStorage(userAccount& user, Array<Nurse>& nurses, Dictionary& medicines) {
    os << medicines;
    os << "Valasszon mennyi gyogyszert szeretne kivenni, es milyet (2 Algoflex): ";
    is >> nurseMedicineKey >> nurseMedicineValue;
    user.nurse->getMedicine(medicines, nurseMedicineKey, nurseMedicineValue.getText());
}