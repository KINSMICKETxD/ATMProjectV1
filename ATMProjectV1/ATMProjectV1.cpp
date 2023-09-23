#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

enum eClientChoices { QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5 };
enum eWithdrawChoice {twenty = 1,fifteen,oneHundred,twoHundred,fourHundred,sixHundred,
    eightHundred,oneThousand,Exit};
const string clientFile = "clients.txt";
struct stClient
{
    string accountNumber;
    string pinCode;
    string clientName;
    string phoneNumber;
    int balance;
    bool markForDelete = false;

};
stClient currentClient;
void showATMMainMenueScreen();
void printLoginScreenHeader() {
    cout << "_______________________\n";
    cout << "   Login Screen\n";
    cout << "_______________________\n";
}
vector<string> splitString(string s1, string delim) {
    vector<string> vResult;
    short pos = 0;
    string word;
    while ((pos = s1.find(delim)) != std::string::npos) {
        word = s1.substr(0, pos);
        if (word != "") {
            vResult.push_back(word);
        }
        s1.erase(0, pos + delim.length());
    }
    if (s1 != "") {
        vResult.push_back(s1);
    }
    return vResult;
}
stClient LineDataToClientRecord(string line) {
    stClient client;
    vector<string> vLine = splitString(line, "#//#");
    client.accountNumber = vLine[0];
    client.pinCode = vLine[1];
    client.clientName = vLine[2];
    client.phoneNumber = vLine[3];
    client.balance = stoi(vLine[4]);
    return client;
}
vector<stClient> LoadClientsDataFromFile(string fileName) {
    stClient client;
    vector<stClient> vClients;
    string line;
    fstream file(fileName, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            client = LineDataToClientRecord(line);
            vClients.push_back(client);
        }
        file.close();
    }
    return vClients;
}
void readClientAccountNumberAndPinCode(string& pinCode, string& accountNumber) {
    cout << "Enter Account Number? ";
    cin >> accountNumber;
    cout << "Enter pinCode? ";
    cin >> pinCode;
}
bool findClientByAccountNumberAndPinCode(string pinCode, string accountNumber,stClient& currentClient) {
    vector<stClient> vClients = LoadClientsDataFromFile(clientFile);
    for (stClient client : vClients) {
        if (client.accountNumber == accountNumber && client.pinCode == pinCode) {
            currentClient = client;
            return true;
        }
    }
    return false;
}
eClientChoices readClientChoice() {
    short choice = 0;
    cout << "Choose what do you want to do? [1 to 5]? ";
    cin >> choice;
    return (eClientChoices)choice;
}
void printATMMainMenueScreenHeader() {
    system("cls");
    cout << "=============================================";
    cout << "\n           ATM Main Menu Screen";
    cout << "\n=============================================";
    cout << "\n\t[1] Quick Withdraw.";
    cout << "\n\t[2] Normal WithDraw.";
    cout << "\n\t[3] Deposit.";
    cout << "\n\t[4] Check Balance.";
    cout << "\n\t[5] Logout.";
    cout << "\n=============================================" << endl;
}
void goBackToMainMenueScreen() {
    cout << "\n\nPress Any key to go back to main Menue.....";
    system("pause>0");
    showATMMainMenueScreen();
}
void printQuickWithdrawScreenHeader() {
    cout << "=============================================";
    cout << "\n              Quick Withdraw";
    cout << "\n=============================================";
    cout << "\n\t[1] 20 \t\t[2] 50";
    cout << "\n\t[3] 100\t\t[4] 200";
    cout << "\n\t[5] 400\t\t[6] 600";
    cout << "\n\t[7] 800\t\t[8] 1000";
    cout << "\n\t[9] Exit.";
    cout << "\n=============================================" << endl;
}
short currentClientBalance() {
    return currentClient.balance;
}
bool checkIfClientCanWithDraw(int ammount) {
    if (ammount <= currentClientBalance()) {
        return true;
    }
    else {
        return false;
    }
}
string convertAClientToDataLine(stClient client, string delim) {
    string s;
    s += client.accountNumber + delim + client.pinCode + delim + client.clientName + delim +
        client.phoneNumber + delim + to_string(client.balance);
    return s;
}
void saveAllClientsToFile(vector<stClient> vClients) {
    fstream file(clientFile, ios::out);
    if (file.is_open()) {
        for (stClient client : vClients) {
            file << convertAClientToDataLine(client, "#//#") << endl;
        }
    }
}
void saveCurrentClientToFile(stClient currentClient) {
    vector<stClient> vClients = LoadClientsDataFromFile(clientFile);
    for (stClient& client : vClients) {
        if (client.accountNumber == currentClient.accountNumber) {
            client.balance = currentClient.balance;
        }
    }
    saveAllClientsToFile(vClients);
    
}
void withDrawTheAmount(int ammount) {
    char answer = 'n';
    if (checkIfClientCanWithDraw(ammount)) {
        cout << "\n\nare you sure you want to performe this transation y/n? ";
        cin >> answer;
        if (toupper(answer) == 'Y') {
            currentClient.balance -= ammount;
            saveCurrentClientToFile(currentClient);
            cout << "Done Succfully.new Balance is: " << currentClient.balance;
        }
    }
    else {
        cout << "You can't withdraw this ammount, your balance is " << currentClient.balance;
    }
}
eWithdrawChoice readWithdrawChoice() {
    short choice;
    cout << "Choose what to withdraw from[1 to 8]? ";
    cin >> choice;
    return eWithdrawChoice(choice);
}

void performeQuickWithdraw(eWithdrawChoice withdrawChoice) {
    switch (withdrawChoice)
    {
    case twenty:
        withDrawTheAmount(20);
        goBackToMainMenueScreen();
        break;
    case fifteen:
        withDrawTheAmount(50);
        goBackToMainMenueScreen();
        break;
    case oneHundred:
        withDrawTheAmount(100);
        goBackToMainMenueScreen();
        break;
    case twoHundred:
        withDrawTheAmount(200);
        goBackToMainMenueScreen();
        break;
    case fourHundred:
        withDrawTheAmount(400);
        goBackToMainMenueScreen();
        break;
    case sixHundred:
        withDrawTheAmount(600);
        goBackToMainMenueScreen();
        break;
    case eightHundred:
        withDrawTheAmount(800);
        goBackToMainMenueScreen();
        break;
    case oneThousand:
        withDrawTheAmount(1000);
        goBackToMainMenueScreen();
        break;
    case Exit:
        goBackToMainMenueScreen();
        goBackToMainMenueScreen();
        break;
    default:
        break;
    }
}
void showQuickWithdrawScreen() {
    printQuickWithdrawScreenHeader();
    cout <<"Your balance is : "<< currentClientBalance() << endl;
    performeQuickWithdraw(readWithdrawChoice());
}
void performeClientChoice(eClientChoices clientChoice) {
    vector<stClient> vClients = LoadClientsDataFromFile(clientFile);
    switch (clientChoice)
    {
    case QuickWithdraw:
        system("cls");
        showQuickWithdrawScreen();
        goBackToMainMenueScreen();
        break;
    case NormalWithdraw:
        system("cls");
        //showNormalWithdrawScreen();
        goBackToMainMenueScreen();
        break;
    case Deposit:
        system("cls");
       // showDepositScreen();
        goBackToMainMenueScreen();
        break;
    case CheckBalance:
        system("cls");
      //  showCheckBalanceScreen();
        goBackToMainMenueScreen();
        break;
    case Logout:
        system("cls");
        goBackToMainMenueScreen();
        break;
    default:
        break;
    }
}
void showATMMainMenueScreen() {
    printATMMainMenueScreenHeader();
    performeClientChoice(readClientChoice());
}
void login() {
    bool loginFailed = false;
    string pinCode;
    string accountNumber;
    do {
        system("cls");
        printLoginScreenHeader();
        readClientAccountNumberAndPinCode(pinCode, accountNumber);
        loginFailed = !findClientByAccountNumberAndPinCode(pinCode, accountNumber, currentClient);
    } while (loginFailed);

}


int main()
{
    vector<stClient> vClients = LoadClientsDataFromFile(clientFile);
    currentClient = vClients[6];
    showQuickWithdrawScreen();
}
