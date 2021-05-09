#include <iostream>
#include <string>
#include <unistd.h> //for 2 sec pausing

using namespace std;

//Constants 
#define MAX_USERS 100
#define MAX_DOCTORS 100
#define MAX_PATIENT 100
#define MAX_DIAGNOSIS 100
#define MAX_MEDICINE 100
#define MAX_TEST 100
#define MAX_INVOICES 100
#define MAX_ENTRIES 100

//Global variables
int docIndex = 0, docID = 101, docLoginIndex = 0; //doctors global variables
int uIndex = 0, userID = 201; //users global variables
int tIndex = 0, testID = 301; // tests global variable
int tranIndex = 0, transactID = 401; // patient global variables
int mIndex = 0, medicineID = 501; // medicines global variable
int mSIndex = 0, saleID = 601; // sales global variable
int iIndex = 0, invoiceID = 701; // invoices global variable
int dIndex = 0, diagnosisID = 901; // diagnosis global variable
int pIndex = 0, patientID = 1001; // patient global variables
bool start = true; //temp global variables for ruff work

//using typedef for creating a short name for long datatypes
typedef unsigned long long int storeAmount;

//All Functions Defination
int mainMenu();
void loginNow(string typeOfUser);
void doctorLogin();
void changePassword();
void aboutAuthor();

//Admin Function Usage
void adminDashboard();
void addUserMenu();
void addNewDoctor();
void addNewUser(string userType);
void displayUserMenu();
void displayUsers();
void displayDoctors();
void pharmacyInfo();
void labInfo();
void accountInfo();

//Doctor Function Usage
void doctorDashboard();
void addNewPatient();
void displayPatient();
void addNewDiagnosis();
void fullPatientInfo();

//Pharmacist Function Usage
void pharmacistDashboard();
void addNewMedicine();
void displayMedicine();
void addMedicineSale();
void soldMedicine();

//Lab Tech Functions Usage
void labTechDashboard();
void addNewTest();
void displayTest();

//Cashier Funtions Usage
void cashierDashboard();
void addHospitalCharges();
void displayHospitalCharges();
void generateInvoice();
void displayInvoice();
void patientInvoice(int invoiceIndex, int patientIndex);

//Accountant Functions Usage
void accountantDashboard();
void addTransaction(string tranType);
void profitLoss();
void balanceSheet();

//pre-loading data functions
void preLoadingData();
void loadUsers();
void loadLoginCredetials();
void loadDoctors();
void loadPatients();
void loadDiagnosis();
void loadMedicines();
void loadSoldMedicines();
void loadTests();
void loadAccounts();

//Miscellaneous functions
int checkPatientExists(); //gettting current patient index
void clearTerminal(); //clearing above terminal commands
int getMenuChoices(int min, int max, string message); //getting & validting choices 
int getInt(string message);  // getting int values
string getString(string message); // geting string values
storeAmount getDouble(string message); // getting & validting values

//Structures

struct Login
{
    string adminPassword, labTechPassword, pharmacistPassword, 
    cashierPassword, accountantPassword, doctorPassword[MAX_DOCTORS];
    int currentDoctor;
    bool loginStatus;
};
struct Login checkLogin;

struct User
{
    string uFName,uLName, userType;
    int uID, userAge;
    storeAmount userSalary;
};
struct User newUser[MAX_USERS];

struct Doctor
{
    string docFName, docLName, docSpeciality;
    int docID, docAge;
    storeAmount docSalary;
};
struct Doctor newDoc[MAX_DOCTORS];

struct Patient
{
    string pFName, pLName, pAddress, pSex, pBG;
    int patientID, pAge;
    storeAmount medicineBill, testBill, diagnosisBill, 
    hospitalBill, otherCharges;
};
struct Patient newPatient[MAX_PATIENT];

struct Diagnosis
{
    string dSymptoms, dDiagnosis, dMedicines, dLabTest;
    int patientID, diagID;
    storeAmount totalAmount;
};
struct Diagnosis newDiagnosis[MAX_DIAGNOSIS];

struct Medicine
{
    string mName, mCompany, mExpiryDate;
    int mID, stock;
    storeAmount totalAmount;
};
struct Medicine newMedicine[MAX_MEDICINE];

struct MedicineSale
{
    string mName;
    int saleID, patientID, medicineID, saleQty;
    storeAmount totalAmount;
};
struct MedicineSale newSale[MAX_MEDICINE];

struct LabTech
{
    string testName;
    int tID, patientID;
    storeAmount totalAmount;
};
struct LabTech newTest[MAX_TEST];

struct Invoice
{
    string patientName;
    int inID, patientID;
    storeAmount hospitalTotal, medicineTotal, testTotal, diagnosisTotal, 
    otherCharges, baseTotal ,taxTotal, totalBillAmount;
};
struct Invoice newInvoice[MAX_INVOICES];

struct Transactions
{
    string typeOfTran, tranName;
    int tranID;
    storeAmount tranAmount;
};
struct Transactions newEntry[MAX_ENTRIES];

struct BalanceSheet
{
    string netMsg;
    storeAmount totalPatientBills, totalIncome, incomeSideTotal, totalDoctorSalary, 
    totalOtherSalary, totalExpenses, expenseSideTotal, diffrence;
};
struct BalanceSheet totalBalance;

int main()
{
    if(start){
        preLoadingData(); //Pre loading data
        start = false;
    }

    int  mainMenuChoice;

    mainMenuChoice = mainMenu(); // Loading main menu

    switch (mainMenuChoice)
    {
        case 1:
            if(checkLogin.loginStatus){
                adminDashboard();
            }
            loginNow("admin");
            break;
        case 2:
            if(checkLogin.loginStatus){
                doctorDashboard();
            }
            doctorLogin();
            break;
        case 3:
            if(checkLogin.loginStatus){
                pharmacistDashboard();
            }
            loginNow("pharmacist");
            break;
        case 4:
            if(checkLogin.loginStatus){
                labTechDashboard();
            }
            loginNow("labTech");
            break;
        case 5:
            if(checkLogin.loginStatus){
                cashierDashboard();
            }
            loginNow("cashier");
            break;
        case 6: 
            if(checkLogin.loginStatus){
                accountantDashboard();
            }
            loginNow("accountant");
            break;
        case 7:
            aboutAuthor();
            break;
        case 8:
            exit(0);
            break;
        default:
            cout << "System Breach" << endl;
            break;
    }
}

int mainMenu()
{
    //clearTerminal();

    int choice = 0;

    //Main Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 Welcome to ISI Hospital                                     **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 Please select your role                                     **************" << endl;
    cout << "**************                                 -----------------------                                     **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Admin's    Dashboard                                    **************" << endl;
    cout << "**************                                 2.  Doctor's   Dashboard                                    **************" << endl;
    cout << "**************                                 3.  Pharmacist Dashboard                                    **************" << endl;
    cout << "**************                                 4.  Lab Tech   Dashboard                                    **************" << endl;
    cout << "**************                                 5.  Cashier    Dashboard                                    **************" << endl;
    cout << "**************                                 6.  Accountant Dashboard                                    **************" << endl;
    cout << "**************                                 7.  About Author                                            **************" << endl;
    cout << "**************                                 8.  Quit                                                    **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,8,"Enter your choice -> ");

    if(choice==8){
        cout << "*************************************************************************************************************************" << endl;
        cout << "**************                    Logging off from ISI Hospital Management System...                       **************" << endl;
        cout << "*************************************************************************************************************************" << endl;
    }
    cout << endl << endl;

    return choice;
}

void aboutAuthor()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      ISI Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                   Designed & Coded By                                       **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                     Sr. No.        Student ID           Student Name                        **************" << endl;
    cout << "**************                    --------       ------------         --------------                       **************" << endl;
    cout << "**************                        1.            2031023        Mohammad Sahil Achhava                  **************" << endl;
    cout << "**************                        2.            2031141              Dhruv Shah                        **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    
    cout << "Press enter key to go back to main dashboard...." << endl;

    system("read");
    main();
}

void adminDashboard()
{
    clearTerminal();

    int choice = 0;

    //Admin Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 Administrator Dashboard                                     **************" << endl;
    cout << "**************                                --------------------------                                   **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Add New User                                            **************" << endl;
    cout << "**************                                 2.  Display Users                                           **************" << endl;
    cout << "**************                                 3.  Display Pharmacy Info                                   **************" << endl;
    cout << "**************                                 4.  Display Lab Info                                        **************" << endl;
    cout << "**************                                 5.  Display Accounts Info                                   **************" << endl;
    cout << "**************                                 6.  Logout                                                  **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,6,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            addUserMenu();
            break;
        case 2:
            displayUserMenu();
            break;
        case 3:
            pharmacyInfo();
            break;
        case 4:
            labInfo();
            break;
        case 5:
            accountInfo();
            break;
        case 6:
            checkLogin.loginStatus = false;
            main();
            break;
        default:
            break;
    }
}

//User Modules
void addUserMenu()
{
    clearTerminal();

    int choice = 0;

    //Admin Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                Select Type of User to add                                   **************" << endl;
    cout << "**************                               ----------------------------                                  **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Add New Doctor                                          **************" << endl;
    cout << "**************                                 2.  Add Lab Technician                                      **************" << endl;
    cout << "**************                                 3.  Add Pharmacist                                          **************" << endl;
    cout << "**************                                 4.  Add Cashier                                             **************" << endl;
    cout << "**************                                 5.  Add Accountant                                          **************" << endl;
    cout << "**************                                 6.  Back to menu                                            **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,6,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            addNewDoctor();
            break;
        case 2:
            addNewUser("Lab Technician");
            break;
        case 3:
            addNewUser("Pharmacist");
            break;
        case 4:
            addNewUser("Cashier");
            break;
        case 5:
            addNewUser("Accountant");
            break;
        case 6:
            adminDashboard();
            break;
        default:
            break;
    }

}

void addNewUser(string userType)
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Add "<< userType <<"                                          **************" << endl;
    cout << "**************                                   ------------------                                        **************" << endl;
    getString("");
    cout << endl;
    newUser[uIndex].uFName = getString("Enter First Name -> ");
    cout << endl;
    newUser[uIndex].uLName = getString("Enter Last Name -> ");
    cout << endl;
    newUser[uIndex].userAge = getInt("Enter Age        ->");
    cout << endl;
    newUser[uIndex].userSalary = getDouble("Enter Salary     -> ");
    cout << endl;
    newUser[uIndex].uID = userID;
    newUser[uIndex].userType = userType;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newUser[uIndex].uFName << " " << newUser[uIndex].uLName <<" added as a " << newUser[uIndex].userType << "           " << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to admin dashboard, please wait....." << endl;

    uIndex = uIndex + 1; //incrementing index manually
    userID = userID + 1; //incrementing docID manually
    sleep(2); //pausing code before going back
    adminDashboard(); //going back to admin dashboard
}  

void displayUserMenu()
{
    clearTerminal();

    int choice = 0;

    //Admin Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                             Select Type of User to show Info                                **************" << endl;
    cout << "**************                               ----------------------------                                  **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Show All Doctors                                        **************" << endl;
    cout << "**************                                 2.  Show Other Users                                        **************" << endl;
    cout << "**************                                 3.  Back to menu                                            **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,3,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            displayDoctors();
            break;
        case 2:
            displayUsers();
            break;
        case 3:
            adminDashboard();
            break;
        default:
            break;
    }
}

void displayUsers()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    All Users Details                                        **************" << endl;
    cout << "**************                                   --------------------                                      **************" << endl;
    cout << "                     ID        F.Name       L.Name           Age          Type                 Salary                    " << endl;

    for(int i = 0; i < uIndex; i++)
    {
        cout << "                    "
         << newUser[i].uID
         <<"       "<< newUser[i].uFName 
         <<"       "<< newUser[i].uLName 
         <<"            "<< newUser[i].userAge 
         <<"              "<< newUser[i].userType 
         <<"            "<< newUser[i].userSalary 
         <<"                       " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to admin dashboard...." << endl;

    system("read");
    adminDashboard();
}

//Doctor Modules

void addNewDoctor()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Add New Doctor                                          **************" << endl;
    cout << "**************                                   ------------------                                        **************" << endl;
    getString("");
    cout << endl;
    newDoc[docIndex].docFName = getString("Enter First Name -> ");
    cout << endl;
    newDoc[docIndex].docLName = getString("Enter Last  Name -> ");
    cout << endl;
    newDoc[docIndex].docSpeciality = getString("Enter Speciality -> ");
    cout << endl;
    newDoc[docIndex].docAge = getInt("Enter Age        -> ");
    cout << endl;
    newDoc[docIndex].docSalary = getDouble("Enter Salary     -> ");
    cout << endl;
    newDoc[docIndex].docID = docID;
    checkLogin.doctorPassword[docLoginIndex] = "doc123";
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newDoc[docIndex].docFName << " " << newDoc[docIndex].docLName <<" added as a " << newDoc[docIndex].docSpeciality << " doctor           " << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to admin dashboard, please wait....." << endl;

    docIndex = docIndex + 1; //incrementing index manually
    docID = docID + 1; //incrementing docID manually
    sleep(2); //pausing code before going back
    adminDashboard(); //going back to admin dashboard
}

void displayDoctors()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    All Doctor Details                                       **************" << endl;
    cout << "**************                                   --------------------                                      **************" << endl;
    cout << "                     ID        F.Name       L.Name           Age          Speciality           Salary                    " << endl;

    for(int i = 0; i < docIndex; i++)
    {
        cout << "                    "
         << newDoc[i].docID
         <<"       "<< newDoc[i].docFName 
         <<"       "<< newDoc[i].docLName 
         <<"            "<< newDoc[i].docAge 
         <<"              "<< newDoc[i].docSpeciality 
         <<"            "<< newDoc[i].docSalary 
         <<"                       " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;

    cout << "Press enter key to go back to admin dashboard...." << endl;

    system("read");
    adminDashboard();
}

void pharmacyInfo()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    All Medicine Details                                     **************" << endl;
    cout << "**************                                   -----------------------                                   **************" << endl;
    cout << "                ID                M.Name                C.Name             Quantity             Amount                   " << endl;

    for(int i = 0; i < mIndex; i++)
    {
        cout << "                " << newMedicine[i].mID
         <<"             "<< newMedicine[i].mName 
         <<"                "<< newMedicine[i].mCompany 
         <<"                "<< newMedicine[i].stock 
         <<"             "<< newMedicine[i].totalAmount 
         <<"                                     " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to admin dashboard...." << endl;

    system("read");
    adminDashboard();
}

void labInfo()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     All Test Details                                        **************" << endl;
    cout << "**************                                    ------------------                                       **************" << endl;
    cout << "                  T.ID                P.ID                T.Name                     Amount                              " << endl;

    for(int i = 0; i < tIndex; i++)
    {
        cout << "                  " << newTest[i].tID
        <<"                "<< newTest[i].patientID 
        <<"                "<< newTest[i].testName 
        <<"                     "<< newTest[i].totalAmount 
        <<"                              " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to administrator dashboard...." << endl;

    system("read");
    adminDashboard();
}

void accountInfo()
{
    profitLoss();
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      Balance Sheet                                          **************" << endl;
    cout << "**************                                     ----------------                                        **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************              All Incomes                    |                 All Expense                   **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************  Patient's Bills               $ " << totalBalance.totalPatientBills << "   |  Doctor's Salary                $ " << totalBalance.totalDoctorSalary << "    **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "**************  All Other Income              $ " << totalBalance.totalIncome << "   |  All Other Salaries             $ " << totalBalance.totalOtherSalary << "    **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "**************                                             |  All Other Expenses             $ " << totalBalance.totalExpenses << "    **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************  Total Income                               |  Total Expenses                               **************" << endl; 
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************                            ISI Hospital's Net " << totalBalance.netMsg << " is: $ " << totalBalance.diffrence << "                          **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;    
    cout << "Press enter key to go back to administrator dashboard...." << endl;

    system("read");
    adminDashboard();
}

void doctorDashboard()
{
    clearTerminal();

    int choice = 0;

    //Doctor Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                   Doctor's Dashboard                                        **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Add New Patient                                         **************" << endl;
    cout << "**************                                 2.  Add Diagnosis                                           **************" << endl;
    cout << "**************                                 3.  Display Patient                                         **************" << endl;
    cout << "**************                                 4.  Full Patient Info                                       **************" << endl;
    cout << "**************                                 5.  Change Password                                         **************" << endl;
    cout << "**************                                 6.  Logout                                                 **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,6,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            addNewPatient();
            break;
        case 2:
            addNewDiagnosis();
            break;
        case 3:
            displayPatient();
            break;
        case 4: 
            fullPatientInfo();
            break;
        case 5:
            changePassword();
            break;
        case 6: 
            checkLogin.loginStatus = false;
            main();
            break;
        default:
            break;
    }
}

// Patient Modules
void addNewPatient()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Add New Patient                                         **************" << endl;
    cout << "**************                                    ------------------                                       **************" << endl;
    getString("");
    cout << endl;
    newPatient[pIndex].pFName = getString("Enter First Name   -> ");
    cout << endl;
    newPatient[pIndex].pLName = getString("Enter Last  Name   -> ");
    cout << endl;
    newPatient[pIndex].pAddress = getString("Enter Address      -> ");
    cout << endl;
    newPatient[pIndex].pSex = getString("Enter Sex          -> ");
    cout << endl;
    newPatient[pIndex].pAge = getInt("Enter Age          -> ");
    cout << endl;
    newPatient[pIndex].pBG = getString("Enter Blood Group  -> ");
    cout << endl;
    newPatient[pIndex].patientID = patientID;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newPatient[pIndex].pFName << " " << newPatient[pIndex].pLName <<" added as a patient           " << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to doctor dashboard, please wait....." << endl;

    pIndex = pIndex + 1; //incrementing index manually
    patientID = patientID + 1; //incrementing patientID manually
    sleep(2); //pausing code before going back
    doctorDashboard(); //going back to doctor dashboard
}

void displayPatient()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    All Patient Details                                      **************" << endl;
    cout << "**************                                  -----------------------                                    **************" << endl;
    cout << "                ID        F.Name       L.Name       Age       Sex      Blood.G       Address                             " << endl;

    for(int i = 0; i < pIndex; i++)
    {
        cout << "                " << newPatient[i].patientID
         <<"     "<< newPatient[i].pFName 
         <<"       "<< newPatient[i].pLName 
         <<"         "<< newPatient[i].pAge 
         <<"        "<< newPatient[i].pSex 
         <<"         "<< newPatient[i].pBG 
         <<"           "<< newPatient[i].pAddress 
         <<"                             " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to doctor dashboard...." << endl;

    system("read");
    doctorDashboard();
}

//Diagnosis Modules

void addNewDiagnosis()
{
    int currentPatientIndex = checkPatientExists();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      Patient Details                                        **************" << endl;
    cout << "**************                                  -----------------------                                    **************" << endl;
    cout << "                ID        F.Name       L.Name       Age       Sex      Blood.G       Address      D.Bill                                 " << endl;
    cout << "                " << newPatient[currentPatientIndex].patientID <<"     "<< newPatient[currentPatientIndex].pFName 
         <<"       "<< newPatient[currentPatientIndex].pLName <<"         "<< newPatient[currentPatientIndex].pAge 
         <<"        "<< newPatient[currentPatientIndex].pSex <<"         "<< newPatient[currentPatientIndex].pBG 
         <<"           "<< newPatient[currentPatientIndex].pAddress <<"           "<< newPatient[currentPatientIndex].diagnosisBill 
         <<"                                 " << endl << endl;
    cout << "**************                                     Add New Diagnosis                                         **************" << endl;
    cout << "**************                                    -------------------                                        **************" << endl;
    getString("");
    cout << endl;
    newDiagnosis[dIndex].dSymptoms = getString("Enter Symptoms    -> ");
    cout << endl;
    newDiagnosis[dIndex].dDiagnosis = getString("Enter Diagnosis   -> ");
    cout << endl;
    newDiagnosis[dIndex].dMedicines = getString("Enter Medicines   -> ");
    cout << endl;
    newDiagnosis[dIndex].dLabTest = getString("Enter Lab Test    -> ");
    cout << endl;
    newDiagnosis[dIndex].totalAmount = getDouble("Enter Bill Amt    -> ");
    cout << endl;
    newDiagnosis[dIndex].diagID = diagnosisID;
    newDiagnosis[dIndex].patientID = newPatient[currentPatientIndex].patientID;
    newPatient[currentPatientIndex].diagnosisBill += newDiagnosis[dIndex].totalAmount;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newPatient[currentPatientIndex].pFName << " " << newPatient[currentPatientIndex].pLName <<"'s " << newDiagnosis[dIndex].dDiagnosis <<  " Diagnosis added           " << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to doctor dashboard, please wait....." << endl;

    dIndex = dIndex + 1; //incrementing index manually
    diagnosisID = diagnosisID + 1; //incrementing diagnosisID manually
    sleep(2); //pausing code before going back
    doctorDashboard(); //going back to doctor dashboard
}

void fullPatientInfo()
{
    int currentPatientIndex = checkPatientExists();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      Patient Details                                        **************" << endl;
    cout << "**************                                  -----------------------                                    **************" << endl;
    cout << "                ID        F.Name       L.Name       Age       Sex      Blood.G       Address      D.Bill                 " << endl;
    cout << "                " << newPatient[currentPatientIndex].patientID <<"     "<< newPatient[currentPatientIndex].pFName 
         <<"       "<< newPatient[currentPatientIndex].pLName <<"         "<< newPatient[currentPatientIndex].pAge 
         <<"        "<< newPatient[currentPatientIndex].pSex <<"         "<< newPatient[currentPatientIndex].pBG 
         <<"           "<< newPatient[currentPatientIndex].pAddress <<"      "<< newPatient[currentPatientIndex].diagnosisBill 
         <<"                                 " << endl << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Diagnosis Details                                       **************" << endl;
    cout << "**************                                    -------------------                                      **************" << endl;
    cout << "                ID        Symptoms       Diagnosis       Medicines       Lab Test              T.Bill                    " << endl;
    
    int flag = false;
    for(int i = 0; i < dIndex; i++)
    {
        if(newPatient[currentPatientIndex].patientID == newDiagnosis[i].patientID){
            cout << "                " << newDiagnosis[i].diagID <<"        "<< newDiagnosis[i].dSymptoms 
            <<"           "<< newDiagnosis[i].dDiagnosis <<"          "<< newDiagnosis[i].dMedicines 
            <<"           "<< newDiagnosis[i].dLabTest <<"                   "<< newDiagnosis[i].totalAmount 
            <<"                                                       " << endl << endl;
            flag = true;
        }
    }

    if(flag==false){
        cout << "**************                                                                                             **************" << endl;
        cout << "**************                                  No Diagnosis done yet.                                     **************" << endl;
        cout << "**************                                                                                             **************" << endl;
        cout << "*************************************************************************************************************************" << endl;
        cout << "*************************************************************************************************************************" << endl;
    }else{
        cout << "**************                                                                                             **************" << endl;
        cout << "**************                                                                                             **************" << endl;
        cout << "*************************************************************************************************************************" << endl;
        cout << "*************************************************************************************************************************" << endl;
    }
    cout << "Press enter key to go back to doctor dashboard...." << endl;

    system("read");
    doctorDashboard();
}

void changePassword()
{
    clearTerminal();
    string oldPassword, newPassword, confirmNewPassword;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Change Password                                         **************" << endl;
    cout << "**************                                    ------------------                                       **************" << endl;
    getString("");
    cout << endl;
    int tryCount = 3;
    while(true){
        oldPassword = getString("Enter Current Password   -> ");
        cout << endl;
        if(oldPassword != checkLogin.doctorPassword[checkLogin.currentDoctor] && tryCount != 1){
            cout << "                          Please enter valid old password. (" << tryCount << " Try reamaning)" << endl << endl;
            tryCount = tryCount - 1;
        }else if(oldPassword == checkLogin.doctorPassword[checkLogin.currentDoctor]){
            break;
        }else{
            cout << "Redirecting, You exceeded the maximum password attempts, please try again after sometimes" << endl << endl;
            sleep(1); //pausing code before going back
            doctorDashboard(); //going back to dashboard
        }
    }
    while(true){
        newPassword = getString("New Password   -> ");
        cout << endl;
        confirmNewPassword = getString("Confirm Password      -> ");
        cout << endl;
        if(newPassword != confirmNewPassword){
            cout << "                          Password Not matched, try again" << endl << endl;
        }else{
            break;
        }
    }
    checkLogin.doctorPassword[checkLogin.currentDoctor] = newPassword;
    checkLogin.loginStatus = false;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        New Password Updated, Please login again                                         " << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to main dashboard, please wait....." << endl;
    
    sleep(2); //pausing code before going back
    main(); //going back to doctor dashboard
}

void pharmacistDashboard()
{
    clearTerminal();

    int choice = 0;

    //Pharmacist Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                  Pharmacist's Dashboard                                     **************" << endl;
    cout << "**************                                 ------------------------                                    **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Add New Medicine                                        **************" << endl;
    cout << "**************                                 2.  Display Medicine                                        **************" << endl;
    cout << "**************                                 3.  Add Medicine Sale                                       **************" << endl;
    cout << "**************                                 4.  Display Sold Medicine                                   **************" << endl;
    cout << "**************                                 5.  Logout                                                  **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,5,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            addNewMedicine();
            break;
        case 2:
            displayMedicine();
            break;
        case 3:
            addMedicineSale();
            break;
        case 4:
            soldMedicine();
            break;
        case 5: 
            checkLogin.loginStatus = false;
            main();
            break;
        default:
            break;
    }
}

//Medicine Modules
void addNewMedicine()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Add New Medicine                                        **************" << endl;
    cout << "**************                                   --------------------                                      **************" << endl;
    getString("");
    cout << endl;
    newMedicine[mIndex].mName = getString("Enter Medicine Name   -> ");
    cout << endl;
    newMedicine[mIndex].mCompany = getString("Enter Company Name   -> ");
    cout << endl;
    newMedicine[mIndex].mExpiryDate = getString("Enter Expiry      -> ");
    cout << endl;
    newMedicine[mIndex].totalAmount = getInt("Enter Amount          -> ");
    cout << endl;
    newMedicine[mIndex].stock = getInt("Enter Stock          -> ");
    cout << endl;
    newMedicine[mIndex].mID = medicineID;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newMedicine[mIndex].mName <<" added           " << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to pharmacist dashboard, please wait....." << endl;

    mIndex = mIndex + 1; //incrementing index manually
    medicineID = medicineID + 1; //incrementing medicineID manually
    sleep(2); //pausing code before going back
    pharmacistDashboard(); //going back to doctor dashboard
}

void displayMedicine()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    All Medicine Details                                     **************" << endl;
    cout << "**************                                   -----------------------                                   **************" << endl;
    cout << "                ID                M.Name                C.Name             Quantity             Amount                   " << endl;

    for(int i = 0; i < mIndex; i++)
    {
        cout << "                " << newMedicine[i].mID
         <<"             "<< newMedicine[i].mName 
         <<"                "<< newMedicine[i].mCompany 
         <<"                "<< newMedicine[i].stock 
         <<"             "<< newMedicine[i].totalAmount 
         <<"                                     " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to pharmacist dashboard...." << endl;

    system("read");
    pharmacistDashboard();
}

void addMedicineSale()
{
    clearTerminal();

    int patientIndex, medicineIndex;
    bool flag = false;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Add New Medicine Sale                                   **************" << endl;
    cout << "**************                                   -------------------------                                 **************" << endl;
    do{
        newSale[mSIndex].patientID = getInt("Enter Patient ID -> ");
        cout << endl;
        for(int i = 0; i < pIndex; i++){
            if(newPatient[i].patientID == newSale[mSIndex].patientID){
                patientIndex = i;
                flag = true;
                break;
            }
        }
        if(!flag){
            cout << "                          Please enter valid patient ID." << endl << endl;
        }
    }while(!flag);
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      Patient Details                                        **************" << endl;
    cout << "**************                                  -----------------------                                    **************" << endl;
    cout << "                ID        F.Name       L.Name       Age       Sex      Blood.G       Address      M.Bill                 " << endl;
    cout << "                " << newPatient[patientIndex].patientID <<"     "<< newPatient[patientIndex].pFName 
         <<"       "<< newPatient[patientIndex].pLName <<"         "<< newPatient[patientIndex].pAge 
         <<"        "<< newPatient[patientIndex].pSex <<"         "<< newPatient[patientIndex].pBG 
         <<"           "<< newPatient[patientIndex].pAddress <<"      "<< newPatient[patientIndex].medicineBill 
         <<"                                 " << endl << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Select Medicine                                         **************" << endl;
    cout << "**************                                    ------------------                                       **************" << endl;
    for(int i = 0; i < mIndex; i++)
    {
        cout << "                               " << i+1 << "." << newMedicine[i].mName << endl;
    }
    cout << endl;
    medicineIndex = getMenuChoices(1, mIndex, "Select Medicine to Sale ->");
    medicineIndex -= 1; 
    cout << endl;

    do{
        string msg = "Enter Total Qty (Current Stock: " + to_string(newMedicine[medicineIndex].stock) + ") ->";
        newSale[mSIndex].saleQty = getMenuChoices(1,newMedicine[medicineIndex].stock, msg);
        cout << endl;
        if(newMedicine[medicineIndex].stock > newSale[mSIndex].saleQty){
            break;
        }else{
            cout << "                               " << newMedicine[medicineIndex].mName 
            << " stock is " << newMedicine[medicineIndex].stock  << endl;
        }
    }while(true);

    newSale[mSIndex].saleID = saleID;
    newSale[mSIndex].mName = newMedicine[medicineIndex].mName;
    newSale[mSIndex].totalAmount = newSale[mSIndex].saleQty * newMedicine[medicineIndex].totalAmount;
    newMedicine[medicineIndex].stock -= newSale[mSIndex].saleQty;
    newPatient[patientIndex].medicineBill += newSale[mSIndex].totalAmount;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newMedicine[medicineIndex].mName <<" sold to " << newPatient[patientIndex].pFName 
    << " in $" << newSale[mSIndex].totalAmount << "." << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to pharmacist dashboard, please wait....." << endl;

    mSIndex = mSIndex + 1; //incrementing index manually
    saleID = saleID + 1; //incrementing saleID manually
    sleep(2); //pausing code before going back
    pharmacistDashboard(); //going back to doctor dashboard
}

void soldMedicine()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    All Order Details                                        **************" << endl;
    cout << "**************                                   -------------------                                       **************" << endl;
    cout << "                S.ID                P.ID                M.Name             Quantity            Amount                    " << endl;

    for(int i = 0; i < mSIndex; i++)
    {
        cout << "                " << newSale[i].saleID
        <<"              "<< newSale[i].patientID 
        <<"             "<< newSale[i].mName 
        <<"                "<< newSale[i].saleQty 
        <<"             "<< newSale[i].totalAmount 
        <<"                                     " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to pharmacist dashboard...." << endl;

    system("read");
    pharmacistDashboard();
}

//Lab Tech Modules
void labTechDashboard()
{
    clearTerminal();

    int choice = 0;

    //Lab Tech Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                  Lab Tech's Dashboard                                       **************" << endl;
    cout << "**************                                 ----------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Add New Test                                            **************" << endl;
    cout << "**************                                 2.  Display Tests                                           **************" << endl;
    cout << "**************                                 3.  Logout                                                  **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,3,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            addNewTest();
            break;
        case 2:
            displayTest();
            break;
        case 3: 
            checkLogin.loginStatus = false;
            main();
            break;
        default:
            break;
    }
}

void addNewTest()
{
    clearTerminal();

    int patientIndex;
    bool flag = false;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                       Add New Lab Test                                      **************" << endl;
    cout << "**************                                     --------------------                                    **************" << endl;
    do{
        newTest[tIndex].patientID = getInt("Enter Patient ID -> ");
        cout << endl;
        for(int i = 0; i < pIndex; i++){
            if(newPatient[i].patientID == newTest[tIndex].patientID){
                patientIndex = i;
                flag = true;
                break;
            }
        }
        if(!flag){
            cout << "                          Please enter valid patient ID." << endl << endl;
        }
    }while(!flag);
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      Patient Details                                        **************" << endl;
    cout << "**************                                  -----------------------                                    **************" << endl;
    cout << "                ID        F.Name       L.Name       Age       Sex      Blood.G       Address      Lab.Bill               " << endl;
    cout << "                " << newPatient[patientIndex].patientID <<"     "<< newPatient[patientIndex].pFName 
         <<"       "<< newPatient[patientIndex].pLName <<"         "<< newPatient[patientIndex].pAge 
         <<"        "<< newPatient[patientIndex].pSex <<"         "<< newPatient[patientIndex].pBG 
         <<"           "<< newPatient[patientIndex].pAddress <<"      "<< newPatient[patientIndex].testBill 
         <<"                                 " << endl << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << endl;
    getString("");
    cout << endl;
    newTest[tIndex].testName = getString("Enter Test Name ->");
    cout << endl;
    newTest[tIndex].totalAmount = getDouble("Enter Amount -> ");
    cout << endl;
    newTest[tIndex].tID = testID;
    newPatient[patientIndex].testBill += newTest[tIndex].totalAmount;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newTest[tIndex].testName <<" of " << newPatient[patientIndex].pFName 
    << " in $" << newTest[tIndex].totalAmount << "." << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to pharmacist dashboard, please wait....." << endl;

    tIndex = tIndex + 1; //incrementing index manually
    testID = testID + 1; //incrementing testID manually
    sleep(2); //pausing code before going back
    labTechDashboard(); //going back to dashboard
}

void displayTest()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     All Test Details                                        **************" << endl;
    cout << "**************                                    ------------------                                       **************" << endl;
    cout << "                  T.ID                P.ID                T.Name                     Amount                              " << endl;

    for(int i = 0; i < tIndex; i++)
    {
        cout << "                  " << newTest[i].tID
        <<"                "<< newTest[i].patientID 
        <<"                "<< newTest[i].testName 
        <<"                     "<< newTest[i].totalAmount 
        <<"                              " << endl;
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to lab tech dashboard...." << endl;

    system("read");
    labTechDashboard();
}

//Cashier Modules

void cashierDashboard()
{
    clearTerminal();

    int choice = 0;

    //Lab Tech Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                   Cashier's Dashboard                                       **************" << endl;
    cout << "**************                                  ----------------------                                     **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Add Hospital Charges                                    **************" << endl;
    cout << "**************                                 2.  Show Hospital Charges                                   **************" << endl;
    cout << "**************                                 3.  Generate Patient Invoice                                **************" << endl;
    cout << "**************                                 4.  Display Patient Invoice                                 **************" << endl;
    cout << "**************                                 5.  Logout                                                  **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,5,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            addHospitalCharges();
            break;
        case 2:
            displayHospitalCharges();
            break;
        case 3:
            generateInvoice();
            break;
        case 4:
            displayInvoice();
            break;
        case 5: 
            checkLogin.loginStatus = false;
            main();
            break;
        default:
            break;
    }
}

void addHospitalCharges()
{
    clearTerminal();

    int patientIndex, pID;
    bool flag = false;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     Add Hospital Charges                                    **************" << endl;
    cout << "**************                                    ----------------------                                   **************" << endl;
    
    do{
        pID = getInt("Enter Patient ID -> ");
        cout << endl;
        for(int i = 0; i < pIndex; i++){
            if(newPatient[i].patientID == pID){
                patientIndex = i;
                flag = true;
                break;
            }
        }
        if(!flag){
            cout << "                          Please enter valid patient ID." << endl << endl;
        }
    }while(!flag);

    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      Patient Details                                        **************" << endl;
    cout << "**************                                  -----------------------                                    **************" << endl;
    cout << "                ID        F.Name       L.Name       Age       Sex      Blood.G       Address      H.Charge                               " << endl;
    cout << "                " << newPatient[patientIndex].patientID <<"     "<< newPatient[patientIndex].pFName 
         <<"       "<< newPatient[patientIndex].pLName <<"         "<< newPatient[patientIndex].pAge 
         <<"        "<< newPatient[patientIndex].pSex <<"         "<< newPatient[patientIndex].pBG 
         <<"           "<< newPatient[patientIndex].pAddress <<"      "<< newPatient[patientIndex].hospitalBill 
         <<"                                 " << endl << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << endl;
    newPatient[patientIndex].hospitalBill += getInt("Enter Hospital Charges -> ");
    cout << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newPatient[patientIndex].pFName << " " << newPatient[patientIndex].pLName 
    << "'s Hospital charge of $" << newPatient[patientIndex].hospitalBill << " Added." << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to cashier dashboard, please wait....." << endl;

    sleep(2); //pausing code before going back
    cashierDashboard(); //going back to dashboard
}

void displayHospitalCharges()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                  All Hospital Charges                                       **************" << endl;
    cout << "**************                                 ----------------------                                      **************" << endl;
    cout << "                  P.ID                P.Name                H.Charges                     O.Charges                      " << endl;

    for(int i = 0; i < pIndex; i++)
    {
        if(newPatient[i].hospitalBill != 0)
        {
            cout << "                  " << newPatient[i].patientID
            <<"                "<< newPatient[i].pFName << " " <<  newPatient[i].pLName 
            <<"            "<< newPatient[i].hospitalBill 
            <<"                     "<< newPatient[i].otherCharges 
            <<"                              " << endl;
        }
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to cashier dashboard...." << endl;

    system("read");
    cashierDashboard();
}

void generateInvoice()
{
    clearTerminal();

    int patientIndex, pID;
    float taxPercentage;
    bool flag = false;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    Generate New Invoice                                     **************" << endl;
    cout << "**************                                   ----------------------                                    **************" << endl;
    
    do{
        pID = getInt("Enter Patient ID -> ");
        cout << endl;
        for(int i = 0; i < pIndex; i++){
            if(newPatient[i].patientID == pID){
                patientIndex = i;
                flag = true;
                break;
            }
        }
        if(!flag){
            cout << "                          Please enter valid patient ID." << endl << endl;
        }
    }while(!flag);

    if(newPatient[patientIndex].hospitalBill <= 0){
        cout << "                          Please enter hospital charges first, to generate invoice." << endl << endl;
        sleep(1); //pausing code 
        cout << "Redirecting you to cashier dashboard....." << endl << endl;
        sleep(2); //pausing code before going back
        cashierDashboard(); //going back to dashboard
    }

    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                   Patient Bill Details                                      **************" << endl;
    cout << "**************                                  -----------------------                                    **************" << endl;
    cout << "               ID        P.Name       H.Charges       D.Bill       Med.Bill       Test Bill     Other.Charges            " << endl;
    cout << "               " << newPatient[patientIndex].patientID <<"      "<< newPatient[patientIndex].pFName 
        << " " << newPatient[patientIndex].pLName
        <<"    "<< newPatient[patientIndex].hospitalBill <<"       "<< newPatient[patientIndex].diagnosisBill 
        <<"       "<< newPatient[patientIndex].medicineBill <<"       "<< newPatient[patientIndex].testBill 
        <<"     "<< newPatient[patientIndex].otherCharges <<"                                 " << endl << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << endl;
    newPatient[patientIndex].otherCharges = getInt("Enter Any Other Charges (If have) -> ");
    cout << endl;
    taxPercentage = getInt("Enter Tax Percentage (without % sign) -> ");
    cout << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newPatient[patientIndex].pFName << " " << newPatient[patientIndex].pLName 
    << "'s Other charges of $" << newPatient[patientIndex].otherCharges << " also added." << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    //Generating Invoice Code
    cout << "Generating Invoice, Please wait......" << endl << endl;
    newInvoice[iIndex].inID = invoiceID;
    newInvoice[iIndex].patientID = newPatient[patientIndex].patientID;
    newInvoice[iIndex].patientName = newPatient[patientIndex].pFName + " " + newPatient[patientIndex].pLName;
    newInvoice[iIndex].diagnosisTotal = newPatient[patientIndex].diagnosisBill;
    newInvoice[iIndex].medicineTotal = newPatient[patientIndex].medicineBill;
    newInvoice[iIndex].testTotal = newPatient[patientIndex].testBill;
    newInvoice[iIndex].hospitalTotal = newPatient[patientIndex].hospitalBill;
    newInvoice[iIndex].otherCharges = newPatient[patientIndex].otherCharges;
    newInvoice[iIndex].baseTotal = newPatient[patientIndex].diagnosisBill + newPatient[patientIndex].medicineBill + newPatient[patientIndex].testBill
    + newPatient[patientIndex].hospitalBill + newPatient[patientIndex].otherCharges;
    newInvoice[iIndex].taxTotal = newInvoice[iIndex].baseTotal * (taxPercentage / 100);
    newInvoice[iIndex].totalBillAmount = newInvoice[iIndex].baseTotal + newInvoice[iIndex].taxTotal;
    sleep(1); //pausing code for generating invoice
    cout << "Invoice Generated Successfully, Redirecting you to cashier dashboard, please wait....." << endl << endl;
 
    iIndex = iIndex + 1;
    invoiceID = invoiceID + 1;
    sleep(2); //pausing code before going back
    cashierDashboard(); //going back to dashboard
}

void displayInvoice()
{
    clearTerminal();

    int patientIndex, invoiceIndex, pID;
    bool flag = false, invoiceFlag = false;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                       Display Invoice                                       **************" << endl;
    cout << "**************                                      ------------------                                     **************" << endl;
    do{
        pID = getInt("Enter Patient ID -> ");
        cout << endl;
        for(int i = 0; i < pIndex; i++){
            if(newPatient[i].patientID == pID){
                patientIndex = i;
                flag = true;
                break;
            }
        }
        if(!flag){
            cout << "                          Please enter valid patient ID." << endl << endl;
        }
    }while(!flag);

    for(int i = 0; i < iIndex; i++)
    {
        if(newInvoice[i].patientID == newPatient[patientIndex].patientID){
            invoiceIndex = i;
            invoiceFlag = true;
            break;
        }
    }

    if(invoiceFlag){
        patientInvoice(invoiceIndex, patientIndex);
    }else{
        cout << "                          " << newPatient[patientIndex].pFName << " " << newPatient[patientIndex].pLName 
        << " have no invoice, please generate invoice first." << endl << endl;
    }

    cout << "Redirecting to cashier dashboard....." << endl << endl;

    sleep(2); //pausing code before going back
    cashierDashboard(); //going back to dashboard
}

void patientInvoice(int invoiceIndex, int patientIndex)
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                   Invoice No: #" << newInvoice[invoiceIndex].inID << "                                          **************" << endl;
    cout << "**************                                 ----------------------                                      **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*****                                             Patient ID: #" << newPatient[patientIndex].patientID << "                                                 *****" << endl;
    cout << "*****                                            -----------------                                                  *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*****  Patient Full Name: " << newPatient[patientIndex].pFName << " " << newPatient[patientIndex].pLName << "                                                                             *****" << endl;
    cout << "*****  Address: " << newPatient[patientIndex].pAddress << "                                                                                               *****" << endl;
    cout << "*****  Age: " << newPatient[patientIndex].pAge << "                                                                                                      *****" << endl;
    cout << "*****  Sex: " << newPatient[patientIndex].pSex << "                                                                                                       *****" << endl;
    cout << "*****  Blood Group: " << newPatient[patientIndex].pBG << "                                                                                              *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*****                                              Invoice Details                                                  *****" << endl;
    cout << "*****                                             -----------------                                                 *****" << endl;
    cout << "*****     Description                                                                                Amount         *****" << endl;
    cout << "*****     -----------                                                                                ------         *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*****  1. Diagnosis Charges                                                                         $" << newInvoice[invoiceIndex].diagnosisTotal << "         *****" << endl;
    cout << "*****  2. Hospital  Charges                                                                         $" << newInvoice[invoiceIndex].hospitalTotal << "         *****" << endl;
    cout << "*****  3. Medicine  Charges                                                                         $" << newInvoice[invoiceIndex].medicineTotal << "         *****" << endl;
    cout << "*****  4. Lab Test  Charges                                                                         $" << newInvoice[invoiceIndex].testTotal << "         *****" << endl;
    cout << "*****  5. Other     Charges                                                                         $" << newInvoice[invoiceIndex].otherCharges << "         *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*****                                                                                               --------------  *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*****                                                                                 Base Total   $" << newInvoice[invoiceIndex].baseTotal << "         *****" << endl;
    cout << "*****                                                                                 Total  Tax   $" << newInvoice[invoiceIndex].taxTotal << "         *****" << endl;
    cout << "*****                                                                                              ------------     *****" << endl;
    cout << "*****                                                                                 Final Total  $" << newInvoice[invoiceIndex].totalBillAmount << "         *****" << endl;
    cout << "*****                                                                                                               *****" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*****                                      Thank you for choosing ISI Hospital.                                     *****" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Press enter key to go back to cashier dashboard...." << endl;

    system("read");
    cashierDashboard();
}

//Accountant Modules

void accountantDashboard()
{
    clearTerminal();

    int choice = 0;

    //Accountant Menu 
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 Accountant's Dashboard                                      **************" << endl;
    cout << "**************                                -------------------------                                    **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                 1.  Add Income                                              **************" << endl;
    cout << "**************                                 2.  Add Expenses                                            **************" << endl;
    cout << "**************                                 3.  Balance Sheet                                           **************" << endl;
    cout << "**************                                 4.  Logout                                                  **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << endl << endl;

    choice = getMenuChoices(1,4,"Enter your choice -> ");
    
    cout << endl << endl;

    switch (choice)
    {
        case 1:
            addTransaction("Income");
            break;
        case 2:
            addTransaction("Expense");
            break;
        case 3:
            profitLoss();
            balanceSheet();
            break;
        case 4: 
            checkLogin.loginStatus = false;
            main();
            break;
        default:
            break;
    }
}

void addTransaction(string tranType)
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    if(tranType=="Income"){
    cout << "**************                                      Add New Income                                         **************" << endl;
    }else{
    cout << "**************                                      Add New Expense                                        **************" << endl;
    }
    cout << "**************                                     -----------------                                       **************" << endl;
    getString("");
    cout << endl;
    newEntry[tranIndex].tranName = getString(tranType + " for ("+tranType+" Purpose) -> ");
    cout << endl;
    newEntry[tranIndex].tranAmount = getInt("Enter "+tranType+" Amount -> ");
    cout << endl;
    newEntry[tranIndex].typeOfTran = tranType;
    newEntry[tranIndex].tranID = transactID;
    cout << "*************************************************************************************************************************" << endl;
    cout << "                                        "<< newEntry[tranIndex].tranName << " of $" << newEntry[tranIndex].tranAmount << " added." << endl;
    cout << "*************************************************************************************************************************" << endl << endl;
    cout << "Redirecting you to accountant dashboard, please wait....." << endl;

    tranIndex = tranIndex + 1; //incrementing index manually
    transactID = transactID + 1; //incrementing transactID manually
    sleep(2); //pausing code before going back
    accountantDashboard(); //going back to dashboard
}

void profitLoss()
{
    cout << "Calculating total profit & loss, please wait....." << endl << endl;
    sleep(1); //pausing code 

    //Calculating Patients Total bills
    for(int i = 0; i < iIndex; i++){
        totalBalance.totalPatientBills += newInvoice[i].totalBillAmount;
    }

    //Calculating Income and Expenses
    for(int i = 0; i < tranIndex; i++){
        if(newEntry[i].typeOfTran == "Income"){
            totalBalance.totalIncome += newEntry[i].tranAmount;
        }else{
            totalBalance.totalExpenses += newEntry[i].tranAmount;
        }
    }

    //Calculating doctor's salary
    for(int i = 0; i < dIndex; i++){
        totalBalance.totalDoctorSalary += newDoc[i].docSalary;
    }

    //Calculating other users salary
    for(int i = 0; i < uIndex; i++){
        totalBalance.totalOtherSalary += newUser[i].userSalary;
    }

    //adding both side income and expenses
    totalBalance.incomeSideTotal = totalBalance.totalPatientBills + totalBalance.totalIncome;
    totalBalance.expenseSideTotal = totalBalance.totalDoctorSalary + totalBalance.totalExpenses + totalBalance.totalOtherSalary;

    //finding diffrence
    totalBalance.diffrence = totalBalance.incomeSideTotal - totalBalance.expenseSideTotal;

    //Specifying Profit or Loss
    if(totalBalance.diffrence < 0){
        totalBalance.netMsg = "Loss";
    }else{
        totalBalance.netMsg = "Profit";
    }

    cout << "Profit & Loss calculated, showing balance sheet now....." << endl << endl;
    sleep(1); //pausing code 
}

void balanceSheet()
{
    clearTerminal();

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                      Balance Sheet                                          **************" << endl;
    cout << "**************                                     ----------------                                        **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************              All Incomes                    |                 All Expense                   **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************  Patient's Bills               $ " << totalBalance.totalPatientBills << "   |  Doctor's Salary                $ " << totalBalance.totalDoctorSalary << "    **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "**************  All Other Income              $ " << totalBalance.totalIncome << "   |  All Other Salaries             $ " << totalBalance.totalOtherSalary << "    **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "**************                                             |  All Other Expenses             $ " << totalBalance.totalExpenses << "    **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "**************                                             |                                               **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************  Total Income                               |  Total Expenses                               **************" << endl; 
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "**************                            ISI Hospital's Net " << totalBalance.netMsg << " is: $ " << totalBalance.diffrence << "                          **************" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;    
    cout << "Press enter key to go back to accountant dashboard...." << endl;

    system("read");
    accountantDashboard();
}

//Login Module

void loginNow(string typeOfUser)
{
    clearTerminal();
    string password;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    Login Authentication                                     **************" << endl;
    cout << "**************                                   ----------------------                                    **************" << endl;
    getString("");
    cout << endl;
    if(typeOfUser == "admin"){
        int tryCount = 3;
        while(true){
            password = getString("Enter Admin Password -> ");
            if(checkLogin.adminPassword != password && tryCount != 1){
                tryCount = tryCount - 1;
                cout << "                          Please enter valid admin password. (" << tryCount << " Try reamaning)" << endl << endl;
            }else if(checkLogin.adminPassword == password){
                cout << "Login Successful, Redirecting you to admin dashboard, please wait....." << endl;
                checkLogin.loginStatus = true;
                sleep(1); //pausing code before going back
                adminDashboard(); //going back to dashboard
            }else{
                cout << "Redirecting, You exceeded the maximum password attempts, please try again after sometimes" << endl << endl;
                sleep(1); //pausing code before going back
                main(); //going back to dashboard
            }
        }
    }else if(typeOfUser == "pharmacist"){
        int tryCount = 3;
        while(true){
            password = getString("Enter Pharmacist Password -> ");
            if(checkLogin.pharmacistPassword != password && tryCount != 1){
                tryCount = tryCount - 1;
                cout << "                          Please enter valid pharmacist password. (" << tryCount << " Try reamaning)" << endl << endl;
            }else if(checkLogin.pharmacistPassword == password){
                cout << "Login Successful, Redirecting you to pharmacist dashboard, please wait....." << endl;
                checkLogin.loginStatus = true;
                sleep(1); //pausing code before going back
                pharmacistDashboard(); //going back to dashboard
            }else{
                cout << "Redirecting, You exceeded the maximum password attempts, please try again after sometimes" << endl << endl;
                sleep(1); //pausing code before going back
                main(); //going back to dashboard
            }
        }
    }else if(typeOfUser == "labTech"){
        int tryCount = 3;
        while(true){
            password = getString("Enter Lab Tech Password -> ");
            if(checkLogin.labTechPassword != password && tryCount != 1){
                tryCount = tryCount - 1;
                cout << "                          Please enter valid lab tech password. (" << tryCount << " Try reamaning)" << endl << endl;
            }else if(checkLogin.labTechPassword == password){
                cout << "Login Successful, Redirecting you to lab tech dashboard, please wait....." << endl;
                checkLogin.loginStatus = true;
                sleep(1); //pausing code before going back
                labTechDashboard(); //going back to dashboard
            }else{
                cout << "Redirecting, You exceeded the maximum password attempts, please try again after sometimes" << endl << endl;
                sleep(1); //pausing code before going back
                main(); //going back to dashboard
            }
        }
    }else if(typeOfUser == "cashier"){
        int tryCount = 3;
        while(true){
            password = getString("Enter Cashier Password -> ");
            if(checkLogin.cashierPassword != password && tryCount != 1){
                tryCount = tryCount - 1;
                cout << "                          Please enter valid Cashier password. (" << tryCount << " Try reamaning)" << endl << endl;
            }else if(checkLogin.cashierPassword == password){
                cout << "Login Successful, Redirecting you to Cashier's dashboard, please wait....." << endl;
                checkLogin.loginStatus = true;
                sleep(1); //pausing code before going back
                cashierDashboard(); //going back to dashboard
            }else{
                cout << "Redirecting, You exceeded the maximum password attempts, please try again after sometimes" << endl << endl;
                sleep(1); //pausing code before going back
                main(); //going back to dashboard
            }
        }
    }else if(typeOfUser == "accountant"){
        int tryCount = 3;
        while(true){
            password = getString("Enter Accountant Password -> ");
            if(checkLogin.accountantPassword != password && tryCount != 1){
                tryCount = tryCount - 1;
                cout << "                          Please enter valid Accountant password. (" << tryCount << " Try reamaning)" << endl << endl;
            }else if(checkLogin.accountantPassword == password){
                cout << "Login Successful, Redirecting you to Accountant's dashboard, please wait....." << endl;
                checkLogin.loginStatus = true;
                sleep(1); //pausing code before going back
                accountantDashboard(); //going back to dashboard
            }else{
                cout << "Redirecting, You exceeded the maximum password attempts, please try again after sometimes" << endl << endl;
                sleep(1); //pausing code before going back
                main(); //going back to dashboard
            }
        }
    }
}

void doctorLogin()
{
    clearTerminal();
    string password;
    int docID, docIndex;
    bool flag = false;

    cout << "*************************************************************************************************************************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                     ISI  Hospital                                           **************" << endl;
    cout << "**************                                    Montreal, Canada                                         **************" << endl;
    cout << "**************                                  ---------------------                                      **************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "*************************************************************************************************************************" << endl;
    cout << "**************                                                                                             **************" << endl;
    cout << "**************                                    Login Authentication                                     **************" << endl;
    cout << "**************                                   ----------------------                                    **************" << endl;
    do{
        docID = getInt("Enter Doctor ID -> ");
        cout << endl;
        for(int i = 0; i < pIndex; i++){
            if(newDoc[i].docID == docID){
                docIndex = i;
                flag = true;
                break;
            }
        }
        if(!flag){
            cout << "                          Please enter valid doctor ID." << endl << endl;
        }
    }while(!flag);
    getString("");
    cout << endl;
    int tryCount = 3;
    while(true){
        password = getString("Enter Your Password -> ");
        if(checkLogin.doctorPassword[docIndex] != password && tryCount != 1){
            tryCount = tryCount - 1;
            cout << "                          Please enter valid doctor password. (" << tryCount << " Try reamaning)" << endl << endl;
        }else if(checkLogin.doctorPassword[docIndex] == password){
            cout << "Login Successful, Redirecting you to doctor dashboard, please wait....." << endl;
            checkLogin.currentDoctor = docIndex;
            checkLogin.loginStatus = true;
            sleep(1); //pausing code before going back
            doctorDashboard(); //going back to dashboard
        }else{
            cout << "Redirecting, You exceeded the maximum password attempts, please try again after sometimes" << endl << endl;
            sleep(1); //pausing code before going back
            main(); //going back to dashboard
        }
    }
}

/*

Other Functions Section for system to run smoothly

*/

// Preloading Data Section
void preLoadingData()
{
    loadUsers(); //loading pre-loaded users data
    loadLoginCredetials(); //loading login credentials
    loadDoctors(); //loading pre-loaded doctors data
    loadPatients(); //loading pre-loaded patients data
    loadDiagnosis(); //loading pre-loaded diagnosis data
    loadMedicines(); //loading pre-loaded medicine data
    loadSoldMedicines(); //loading pre-loaded sales medicine data
    loadTests(); //loading pre-loaded test data
    loadAccounts(); //loading pre-loaded accounts data
}

void loadUsers()
{
    //Lab Technician
    newUser[uIndex].uID = userID;
    newUser[uIndex].uFName = "Michael";
    newUser[uIndex].uLName = "Joyce";
    newUser[uIndex].userAge = 32;
    newUser[uIndex].userSalary = 80000;
    newUser[uIndex].userType = "Lab Technician";
    userID = userID + 1;
    uIndex = uIndex + 1;

    //Pharmacist
    newUser[uIndex].uID = userID;
    newUser[uIndex].uFName = "Gamil";
    newUser[uIndex].uLName = "Azim";
    newUser[uIndex].userAge = 63;
    newUser[uIndex].userSalary = 110000;
    newUser[uIndex].userType = "Pharmacist";
    userID = userID + 1;
    uIndex = uIndex + 1;

    //Cashier
    newUser[uIndex].uID = userID;
    newUser[uIndex].uFName = "Harman";
    newUser[uIndex].uLName = "Singh";
    newUser[uIndex].userAge = 28;
    newUser[uIndex].userSalary = 75000;
    newUser[uIndex].userType = "Cashier";
    userID = userID + 1;
    uIndex = uIndex + 1;

    //Accountant
    newUser[uIndex].uID = userID;
    newUser[uIndex].uFName = "Surya";
    newUser[uIndex].uLName = "Reddy";
    newUser[uIndex].userAge = 27;
    newUser[uIndex].userSalary = 82000;
    newUser[uIndex].userType = "Accountant";
    userID = userID + 1;
    uIndex = uIndex + 1;
}

void loadDoctors()
{
    //Doctor 1
    newDoc[docIndex].docID = docID;
    newDoc[docIndex].docFName = "Sahil";
    newDoc[docIndex].docLName = "Achhava";
    newDoc[docIndex].docSpeciality = "Heart";
    newDoc[docIndex].docAge = 23;
    newDoc[docIndex].docSalary = 400000;
    docID = docID + 1;
    docIndex = docIndex + 1;

    //Doctor 2
    newDoc[docIndex].docID = docID;
    newDoc[docIndex].docFName = "Nirav";
    newDoc[docIndex].docLName = "Chaudhari";
    newDoc[docIndex].docSpeciality = "Brain";
    newDoc[docIndex].docAge = 23;
    newDoc[docIndex].docSalary = 450000;
    docID = docID + 1;
    docIndex = docIndex + 1;

    //Doctor 3
    newDoc[docIndex].docID = docID;
    newDoc[docIndex].docFName = "Harshil";
    newDoc[docIndex].docLName = "Patel";
    newDoc[docIndex].docSpeciality = "Eye";
    newDoc[docIndex].docAge = 23;
    newDoc[docIndex].docSalary = 210000;
    docID = docID + 1;
    docIndex = docIndex + 1;

    //Doctor 4
    newDoc[docIndex].docID = docID;
    newDoc[docIndex].docFName = "Sruthi";
    newDoc[docIndex].docLName = "Nair";
    newDoc[docIndex].docSpeciality = "Kidney";
    newDoc[docIndex].docAge = 26;
    newDoc[docIndex].docSalary = 250000;
    docID = docID + 1;
    docIndex = docIndex + 1;

    //Doctor 5
    newDoc[docIndex].docID = docID;
    newDoc[docIndex].docFName = "Vijeta";
    newDoc[docIndex].docLName = "Kumari";
    newDoc[docIndex].docSpeciality = "Cardiologist";
    newDoc[docIndex].docAge = 28;
    newDoc[docIndex].docSalary = 175000;
    docID = docID + 1;
    docIndex = docIndex + 1;
}

void loadPatients()
{
    //Patient 1
    newPatient[pIndex].patientID = patientID;
    newPatient[pIndex].pFName = "Harpreet";
    newPatient[pIndex].pLName = "Dhillon";
    newPatient[pIndex].pAddress = "Anand";
    newPatient[pIndex].pSex = "M";
    newPatient[pIndex].pAge = 23;
    newPatient[pIndex].pBG = "O+";
    pIndex = pIndex + 1;
    patientID = patientID + 1;

    //Patient 2
    newPatient[pIndex].patientID = patientID;
    newPatient[pIndex].pFName = "Namita";
    newPatient[pIndex].pLName = "Bhoj";
    newPatient[pIndex].pAddress = "Vadodra";
    newPatient[pIndex].pSex = "F";
    newPatient[pIndex].pAge = 26;
    newPatient[pIndex].pBG = "B-";
    pIndex = pIndex + 1;
    patientID = patientID + 1;

    //Patient 3
    newPatient[pIndex].patientID = patientID;
    newPatient[pIndex].pFName = "Dhruv";
    newPatient[pIndex].pLName = "Shah";
    newPatient[pIndex].pAddress = "Bhavnagar";
    newPatient[pIndex].pSex = "M";
    newPatient[pIndex].pAge = 23;
    newPatient[pIndex].pBG = "A+";
    pIndex = pIndex + 1;
    patientID = patientID + 1; 

    //Patient 4
    newPatient[pIndex].patientID = patientID;
    newPatient[pIndex].pFName = "Aakash";
    newPatient[pIndex].pLName = "Singh";
    newPatient[pIndex].pAddress = "Bhavnagar";
    newPatient[pIndex].pSex = "M";
    newPatient[pIndex].pAge = 23;
    newPatient[pIndex].pBG = "B+";
    pIndex = pIndex + 1;
    patientID = patientID + 1; 
 
    //Patient 5
    newPatient[pIndex].patientID = patientID;
    newPatient[pIndex].pFName = "Anmol";
    newPatient[pIndex].pLName = "Kaur";
    newPatient[pIndex].pAddress = "Chandigarh";
    newPatient[pIndex].pSex = "F";
    newPatient[pIndex].pAge = 25;
    newPatient[pIndex].pBG = "A";
    pIndex = pIndex + 1;
    patientID = patientID + 1; 
}

void loadDiagnosis()
{
    //Diagnosis 1
    newDiagnosis[dIndex].patientID = 1001;
    newDiagnosis[dIndex].diagID = diagnosisID;
    newDiagnosis[dIndex].dSymptoms = "Chest pain";
    newDiagnosis[dIndex].dDiagnosis = "Cardiomyopathy";
    newDiagnosis[dIndex].dMedicines = "Statins";
    newDiagnosis[dIndex].dLabTest = "Chest X-ray";
    newDiagnosis[dIndex].totalAmount = 2550000;
    newPatient[0].diagnosisBill += newDiagnosis[dIndex].totalAmount;
    diagnosisID = diagnosisID + 1;
    dIndex = dIndex + 1;

    //Diagnosis 2
    newDiagnosis[dIndex].patientID = 1002;
    newDiagnosis[dIndex].diagID = diagnosisID;
    newDiagnosis[dIndex].dSymptoms = "Heart Attack";
    newDiagnosis[dIndex].dDiagnosis = "Cardiovascular";
    newDiagnosis[dIndex].dMedicines = "Warfarin";
    newDiagnosis[dIndex].dLabTest = "Chest X-ray";
    newDiagnosis[dIndex].totalAmount = 2240000;
    newPatient[1].diagnosisBill += newDiagnosis[dIndex].totalAmount;
    diagnosisID = diagnosisID + 1;
    dIndex = dIndex + 1;

    //Diagnosis 3
    newDiagnosis[dIndex].patientID = 1003;
    newDiagnosis[dIndex].diagID = diagnosisID;
    newDiagnosis[dIndex].dSymptoms = "Hemorrhagic stoke";
    newDiagnosis[dIndex].dDiagnosis = "Brain Hemrage";
    newDiagnosis[dIndex].dMedicines = "Corticosteroids";
    newDiagnosis[dIndex].dLabTest = "CT / MRI";
    newDiagnosis[dIndex].totalAmount = 3575000;
    newPatient[2].diagnosisBill += newDiagnosis[dIndex].totalAmount;
    diagnosisID = diagnosisID + 1;
    dIndex = dIndex + 1;

    //Diagnosis 4
    newDiagnosis[dIndex].patientID = 1004;
    newDiagnosis[dIndex].diagID = diagnosisID;
    newDiagnosis[dIndex].dSymptoms = "Difficulty Breathing";
    newDiagnosis[dIndex].dDiagnosis = "COVID";
    newDiagnosis[dIndex].dMedicines = "SARS-CoV";
    newDiagnosis[dIndex].dLabTest = "Viral Test";
    newDiagnosis[dIndex].totalAmount = 1145000;
    newPatient[3].diagnosisBill += newDiagnosis[dIndex].totalAmount;
    diagnosisID = diagnosisID + 1;
    dIndex = dIndex + 1;

    //Diagnosis 5
    newDiagnosis[dIndex].patientID = 1005;
    newDiagnosis[dIndex].diagID = diagnosisID;
    newDiagnosis[dIndex].dSymptoms = "Nausea";
    newDiagnosis[dIndex].dDiagnosis = "Kidney failure";
    newDiagnosis[dIndex].dMedicines = "Captopril";
    newDiagnosis[dIndex].dLabTest = "Blood Test";
    newDiagnosis[dIndex].totalAmount = 550000;
    newPatient[4].diagnosisBill += newDiagnosis[dIndex].totalAmount;
    diagnosisID = diagnosisID + 1;
    dIndex = dIndex + 1;
}

void loadMedicines()
{
    //Medicine 1
    newMedicine[mIndex].mID = medicineID;
    newMedicine[mIndex].mName = "Statins";
    newMedicine[mIndex].mCompany = "Atorvastatin";
    newMedicine[mIndex].mExpiryDate = "08/2022";
    newMedicine[mIndex].totalAmount = 450000;
    newMedicine[mIndex].stock = 100;
    medicineID = medicineID + 1;
    mIndex = mIndex + 1;

    //Medicine 2
    newMedicine[mIndex].mID = medicineID;
    newMedicine[mIndex].mName = "Warfarin";
    newMedicine[mIndex].mCompany = "Atorvastatin";
    newMedicine[mIndex].mExpiryDate = "11/2021";
    newMedicine[mIndex].totalAmount = 345000;
    newMedicine[mIndex].stock = 100;
    medicineID = medicineID + 1;
    mIndex = mIndex + 1;

    //Medicine 3
    newMedicine[mIndex].mID = medicineID;
    newMedicine[mIndex].mName = "Corticosteroids";
    newMedicine[mIndex].mCompany = "Bethamethasone";
    newMedicine[mIndex].mExpiryDate = "05/2024";
    newMedicine[mIndex].totalAmount = 555000;
    newMedicine[mIndex].stock = 100;
    medicineID = medicineID + 1;
    mIndex = mIndex + 1;

    //Medicine 4
    newMedicine[mIndex].mID = medicineID;
    newMedicine[mIndex].mName = "SARS-CoV";
    newMedicine[mIndex].mCompany = "Pfizer Inc";
    newMedicine[mIndex].mExpiryDate = "02/2025";
    newMedicine[mIndex].totalAmount = 145000;
    newMedicine[mIndex].stock = 100;
    medicineID = medicineID + 1;
    mIndex = mIndex + 1;

    //Medicine 5
    newMedicine[mIndex].mID = medicineID;
    newMedicine[mIndex].mName = "Captopril";
    newMedicine[mIndex].mCompany = "Lupin Laboratories";
    newMedicine[mIndex].mExpiryDate = "07/2023";
    newMedicine[mIndex].totalAmount = 75000;
    newMedicine[mIndex].stock = 100;
    medicineID = medicineID + 1;
    mIndex = mIndex + 1;
}

void loadSoldMedicines()
{
    //Medicine Sales 1
    newSale[mSIndex].saleID = saleID;
    newSale[mSIndex].patientID = 1001;
    newSale[mSIndex].mName = "Statins";
    newSale[mSIndex].saleQty = 2;
    newSale[mSIndex].medicineID = 501;
    newSale[mSIndex].totalAmount = newMedicine[0].totalAmount * newSale[mSIndex].saleQty;
    newMedicine[0].stock -= newSale[mSIndex].saleQty;
    newPatient[0].medicineBill += newSale[mSIndex].totalAmount;
    mSIndex = mSIndex + 1;
    saleID = saleID + 1;

    //Medicine Sales 2
    newSale[mSIndex].saleID = saleID;
    newSale[mSIndex].patientID = 1002;
    newSale[mSIndex].mName = "Warfarin";
    newSale[mSIndex].saleQty = 3;
    newSale[mSIndex].medicineID = 502;
    newSale[mSIndex].totalAmount = newMedicine[1].totalAmount * newSale[mSIndex].saleQty;
    newMedicine[1].stock -= newSale[mSIndex].saleQty;
    newPatient[1].medicineBill += newSale[mSIndex].totalAmount;
    mSIndex = mSIndex + 1;
    saleID = saleID + 1;

    //Medicine Sales 3
    newSale[mSIndex].saleID = saleID;
    newSale[mSIndex].patientID = 1003;
    newSale[mSIndex].mName = "Corticosteroids";
    newSale[mSIndex].saleQty = 1;
    newSale[mSIndex].medicineID = 503;
    newSale[mSIndex].totalAmount = newMedicine[2].totalAmount * newSale[mSIndex].saleQty;
    newMedicine[2].stock -= newSale[mSIndex].saleQty;
    newPatient[2].medicineBill += newSale[mSIndex].totalAmount;
    mSIndex = mSIndex + 1;
    saleID = saleID + 1;

    //Medicine Sales 4
    newSale[mSIndex].saleID = saleID;
    newSale[mSIndex].patientID = 1004;
    newSale[mSIndex].mName = "SARS-CoV";
    newSale[mSIndex].saleQty = 5;
    newSale[mSIndex].medicineID = 504;
    newSale[mSIndex].totalAmount = newMedicine[3].totalAmount * newSale[mSIndex].saleQty;
    newMedicine[3].stock -= newSale[mSIndex].saleQty;
    newPatient[3].medicineBill += newSale[mSIndex].totalAmount;
    mSIndex = mSIndex + 1;
    saleID = saleID + 1;

    //Medicine Sales 5
    newSale[mSIndex].saleID = saleID;
    newSale[mSIndex].patientID = 1004;
    newSale[mSIndex].mName = "Captopril";
    newSale[mSIndex].saleQty = 4;
    newSale[mSIndex].medicineID = 505;
    newSale[mSIndex].totalAmount = newMedicine[4].totalAmount * newSale[mSIndex].saleQty;
    newMedicine[4].stock -= newSale[mSIndex].saleQty;
    newPatient[4].medicineBill += newSale[mSIndex].totalAmount;
    mSIndex = mSIndex + 1;
    saleID = saleID + 1;
}

void loadTests()
{
    //Test 1
    newTest[tIndex].tID = testID;
    newTest[tIndex].patientID = 1001;
    newTest[tIndex].testName = "Chest X-ray";
    newTest[tIndex].totalAmount = 45000;
    newPatient[0].testBill += newTest[tIndex].totalAmount;
    tIndex = tIndex + 1;
    testID = testID + 1;

    //Test 2
    newTest[tIndex].tID = testID;
    newTest[tIndex].patientID = 1002;
    newTest[tIndex].testName = "Chest X-ray";
    newTest[tIndex].totalAmount = 45000;
    newPatient[1].testBill += newTest[tIndex].totalAmount;
    tIndex = tIndex + 1;
    testID = testID + 1;

    //Test 3
    newTest[tIndex].tID = testID;
    newTest[tIndex].patientID = 1003;
    newTest[tIndex].testName = "CT / MRI";
    newTest[tIndex].totalAmount = 235000;
    newPatient[2].testBill += newTest[tIndex].totalAmount;
    tIndex = tIndex + 1;
    testID = testID + 1;

    //Test 4
    newTest[tIndex].tID = testID;
    newTest[tIndex].patientID = 1004;
    newTest[tIndex].testName = "Viral Test";
    newTest[tIndex].totalAmount = 25500;
    newPatient[3].testBill += newTest[tIndex].totalAmount;
    tIndex = tIndex + 1;
    testID = testID + 1;

    //Test 5
    newTest[tIndex].tID = testID;
    newTest[tIndex].patientID = 1005;
    newTest[tIndex].testName = "Blood Test";
    newTest[tIndex].totalAmount = 12400;
    newPatient[4].testBill += newTest[tIndex].totalAmount;
    tIndex = tIndex + 1;
    testID = testID + 1;
}

void loadAccounts()
{
    //Income 1
    newEntry[tranIndex].tranID = transactID;
    newEntry[tranIndex].tranName = "Gamil NGO Donation";
    newEntry[tranIndex].typeOfTran = "Income";
    newEntry[tranIndex].tranAmount = 2100000;
    tranIndex = tranIndex + 1;
    transactID = transactID + 1;

    //Income 2
    newEntry[tranIndex].tranID = transactID;
    newEntry[tranIndex].tranName = "Trust Donation";
    newEntry[tranIndex].typeOfTran = "Income";
    newEntry[tranIndex].tranAmount = 1700000;
    tranIndex = tranIndex + 1;
    transactID = transactID + 1;

    //Expense 1
    newEntry[tranIndex].tranID = transactID;
    newEntry[tranIndex].tranName = "Maintainance";
    newEntry[tranIndex].typeOfTran = "Expense";
    newEntry[tranIndex].tranAmount = 1000000;
    tranIndex = tranIndex + 1;
    transactID = transactID + 1;

    //Expense 2
    newEntry[tranIndex].tranID = transactID;
    newEntry[tranIndex].tranName = "Cleaning";
    newEntry[tranIndex].typeOfTran = "Expense";
    newEntry[tranIndex].tranAmount = 500000;
    tranIndex = tranIndex + 1;
    transactID = transactID + 1;
}

void loadLoginCredetials()
{
    checkLogin.adminPassword = "admin123";
    checkLogin.pharmacistPassword = "pharma123";
    checkLogin.labTechPassword = "lab123";
    checkLogin.cashierPassword = "cash123";
    checkLogin.accountantPassword = "account123";
    checkLogin.loginStatus = false;

    //Doctor Passwords
    checkLogin.doctorPassword[docLoginIndex] = "sahil123";
    docLoginIndex = docLoginIndex + 1;
    checkLogin.doctorPassword[docLoginIndex] = "nirav123";
    docLoginIndex = docLoginIndex + 1;
    checkLogin.doctorPassword[docLoginIndex] = "harshil123";
    docLoginIndex = docLoginIndex + 1;
    checkLogin.doctorPassword[docLoginIndex] = "sruthi123";
    docLoginIndex = docLoginIndex + 1;
    checkLogin.doctorPassword[docLoginIndex] = "vijeta123";
    docLoginIndex = docLoginIndex + 1;
}

// Miscellaneous Functions

void clearTerminal(){
    system("clear");
}

int checkPatientExists()
{
    int pID = 0, currentPatientIndex = 0;
    pID = getInt("Enter Patient ID -> ");
    
    bool isExists = false;
    for(int i = 0; i < pIndex; i++){
        if(newPatient[i].patientID == pID){
            currentPatientIndex = i;
            isExists = true;
        }
    }

    if(!isExists){
        cout << "                          Please enter valid patient ID." << endl << endl;
    }else{
        clearTerminal();
    }
    return currentPatientIndex;
}

int getMenuChoices(int min, int max, string message)
{
    int number;
    do{
        cout << "                          " << message << " ";
        cin >> number;

        if(cin.fail() || cin.peek() != '\n'){
            cin.clear();
            cin.ignore(512, '\n');
            cout << "                          Please enter integer between "<< min <<" to " << max << " only." << endl << endl;
        }else if(number < min || number > max){
            cout << "                          Please enter integer between "<< min <<" to " << max << " only." << endl << endl;
        }else if(number < 0){
            cout << "                          Please enter positive integer only." << endl << endl;
        }else{
            break;
        }

    }while(true);
    return number;
}

int getInt(string message)
{
    int number;
    do{
        cout << "                          " << message << " "; 
        cin >> number;

        if(cin.fail() || cin.peek() != '\n'){
            cin.clear();
            cin.ignore(512, '\n');
            cout << "                          Please enter integer only." << endl << endl;
        }else if(number < 0){
            cout << "                          Please enter positive integer only." << endl << endl;
        }else{
            break;
        }

    }while(true);
    return number;
}

storeAmount getDouble(string message)
{
    storeAmount number;
    do{
        cout << "                          " << message << " "; 
        cin >> number;

        if(cin.fail() || cin.peek() != '\n'){
            cin.clear();
            cin.ignore(512, '\n');
            cout << "                          Please enter floating point numbers. (Ex. 1000.10)" << endl << endl;
        }else if(number < 0){
            cout << "                          Please enter positive floating point numbers. (Ex. 1000.10) only." << endl << endl;
        }else{
            break;
        }
    }while(true);
    return number;
}

string getString(string message)
{
    string str;
    cout << "                          " << message << " ";
    getline(cin, str);
    return str;
}