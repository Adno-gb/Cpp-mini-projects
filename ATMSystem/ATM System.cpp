#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

const string filename = "Clients.txt";

enum enwde { QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5 };
enum pri { kha = 1, mya = 2, khmsa = 3, alf = 4};

void login();

struct stclint {
    string name = "";
    string lastname = "";
    string phone = "";
    short pincode = 0;
    short accountnumber = 0;
    short sold = 0;
    short oldsold = 0;
    short lastDeposit = 0;
    short lastWithdraw = 0;
};
stclint cc;

void forgoback() {
    cout << "For Go Back To Menu Press Any Key" << endl;
    system("pause>0");
}

void transctionmenu() {
    cout << setw(80) << "=================== Transaction Menu ====================\n";
    cout << setw(40) << "1- Quick Withdraw\n";
    cout << setw(41) << "2- Normal Withdraw\n";
    cout << setw(33) << "3- Deposit\n";
    cout << setw(39) << "4- Check Balance\n";
    cout << setw(32) << "5- Logout\n";
    cout << setw(80) << "=========================================================\n";
}

short fntch() {
    short x;
    do {
        cout << setw(67) << "Enter Number Between 1 And 5" << endl;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            system("color C7");
            cout << "\a";
        }
        else break;
    } while (x < 1 || x>4);
    return x;
}

enwde enwfn() { return (enwde)fntch(); }

short fntchp() {
    short x;
    do {
        cout << setw(37) << "Select Withdrawal Amount Do u Want: \n";
        cout << setw(39) << "|50 |" << setw(6) << "100|\n";
        cout << setw(39) << "|500 |" << setw(7) << "1000|\n";
        cout << setw(67) << "Enter Number Between 1 And 4" << endl;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            system("color C7");
            cout << "\a";
        }
        else break;
    } while (x < 1 || x>4);
    return x;
}

pri prifn() { return (pri)fntchp(); }

vector<string> readfile(string fileename) {
    vector<string> lines;
    ifstream file(fileename);
    if (!file.is_open()) {
        cout << "File not found!\n";
        return lines;
    }
    string line;
    while (getline(file, line)) lines.push_back(line);
    return lines;
}

void svefilefromvector(string fileename, const vector<string>& lline) {
    ofstream file(fileename);
    for (const string& l : lline) file << l << endl;
}

vector<string> splitTrim(const string& line) {
    vector<string> parts;
    string token;
    stringstream ss(line);
    while (getline(ss, token, '|')) {
        size_t start = 0;
        while (start < token.size() && isspace((unsigned char)token[start])) ++start;
        size_t end = token.size();
        while (end > start && isspace((unsigned char)token[end - 1])) --end;
        if (end > start) parts.push_back(token.substr(start, end - start));
    }
    return parts;
}

int getAccountFromLine(const string& line) {
    if (line.find("----") != string::npos) return -1;
    if (line.find("Name") != string::npos) return -1;
    if (line.find("Client") != string::npos) return -1;

    vector<string> parts = splitTrim(line);
    if (parts.size() >= 5) {
        try {
            return stoi(parts[4]);
        }
        catch (...) {
            return -1;
        }
    }
    return -1;
}

int serechfromvector(const vector<string>& lines, const string& accountNumber) {
    int accToFind;
    try {
        accToFind = stoi(accountNumber);
    }
    catch (...) {
        return -1;
    }
    for (int i = 0; i < (int)lines.size(); ++i) {
        int acc = getAccountFromLine(lines[i]);
        if (acc != -1 && acc == accToFind) return i;
    }
    return -1;
}

string enteraccountnumber() {
    string accountn;
    cout << "Enter The Account Number: ";
    cin >> accountn;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input!\n";
        system("color C7");
        cout << "\a";
    }
    return accountn;
}

bool cheacc( int index) {
    if (index == -1) {
        cout << "Not Found!\n";
        system("color C7");
        cout << "\a";
   forgoback();
        return false;
    }
    return true;
}

void updatebalncd(vector<string>& lines, int index, short ta, bool deposit) {
    string line = lines[index];
    vector<string> parts = splitTrim(line);
    if (parts.size() < 6) {
        cout << "Error reading client data\n";
        return;
    }
    stclint client;
    client.name = parts[0];
    client.lastname = parts[1];
    client.phone = parts[2];
    client.pincode = stoi(parts[3]);
    client.accountnumber = stoi(parts[4]);
    client.sold = stoi(parts[5]);
    cc.name = client.name;
    cc.lastname = client.lastname;
    cc.phone = client.phone;
    cc.pincode = client.pincode;
    cc.accountnumber = client.accountnumber;
    cc.oldsold = client.sold;

    if (deposit) {
        cc.lastDeposit = ta;
        client.sold += ta;
    }
    else {
        if (client.sold < ta) {
            system("color C7");
            cout << "\a";
            cout << "You don't have enough money to withdraw!\n";
            cc.lastWithdraw = 0;
            return;
        }
        cc.lastWithdraw = ta;
        client.sold -= ta;
    }
    cc.sold = client.sold;
    stringstream ss;
    ss << "| " << left << setw(12) << cc.name
        << "| " << left << setw(14) << cc.lastname
        << "| " << left << setw(13) << cc.phone
        << "| " << left << setw(11) << cc.pincode
        << "| " << left << setw(17) << cc.accountnumber
        << "| " << left << setw(12) << client.sold << "|";
    lines[index] = ss.str();
    svefilefromvector(filename, lines);
    cout << "Balance updated successfully!\n";
}

short taza() {
    short i = 0;
    cout << "Enter Deposit Amount: ";
    cin >> i;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input!\n";
        system("color C7");
        cout << "\a";
    }
    return i;
}

short tana() {
    short i = 0;
    cout << "Enter Withdrawal Amount: ";
    cin >> i;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input!\n";
        system("color C7");
        cout << "\a";
    }
    return i;
}

short tanat() {
    short i = 0;
    switch (prifn()) {
    case kha:return i = 50; break;
    case mya:return i = 100; break;
    case khmsa:return i = 500; break;
    case alf: return i = 1000; break;
    }
    return i;
}

void t5baupdat() {
    system("color 07");
    system("cls");
    cout << "==================== Update Balance ====================\n";
    vector<string> lines = readfile(filename);
    int idx = serechfromvector(lines, to_string(cc.accountnumber));
    if (!cheacc( idx)) return;
    short amt = taza();
    updatebalncd(lines, idx, amt, true);
    cout << "=================================\n";
    forgoback();
}

void t5baupdatbn() {
    system("color 07");
    system("cls");
    cout << "==================== Update Balance ====================\n";
    vector<string> lines = readfile(filename);
    int idx = serechfromvector(lines, to_string(cc.accountnumber));
    if (!cheacc( idx)) return;
    short amt = tana();
    updatebalncd(lines, idx, amt, false);
    cout << "=================================\n";
    forgoback();
}

void t5baupdatbnt() {
    system("color 07");
    system("cls");
    cout << "==================== Update Balance ====================\n";
    vector<string> lines = readfile(filename);
   
    int idx = serechfromvector(lines, to_string(cc.accountnumber));
    if (!cheacc(idx)) return;
    short amt = tanat();
    updatebalncd(lines, idx, amt, false);
    cout << "=================================\n";
    forgoback();
}

void tatb3() {
    cout << "Account Number : " << cc.accountnumber << endl;
    cout << "Old Balance    : " << cc.oldsold << endl;
    cout << "Last Deposit   : " << cc.lastDeposit << endl;
    cout << "Last Withdraw  : " << cc.lastWithdraw << endl;
    cout << "New Balance    : " << cc.sold << endl;
}

void trnsacta() {
    system("color 07");
    system("cls");
    cout << "==================== Transaction Summary ====================\n";
    tatb3();
    cout << "=================================\n";
    forgoback();
}

void t5baytaenchta() {
    bool tr = true;
    while (tr) {
        system("color 07");
        system("cls");
        transctionmenu();
        switch (enwfn()) {
        case QuickWithdraw: t5baupdatbnt(); break;
        case NormalWithdraw: t5baupdatbn(); break;
        case Deposit: t5baupdat(); break;
        case CheckBalance: trnsacta(); break;
        case Logout: tr = false; login();
        }
    }
}

bool checkUserus(int index) {
    if (index == -5) {
        cout << "Accountnumber and Pincode incorrect\n";
        cout << "\a";
        system("color C7");
        return false;
    }
    else if (index == -6) {
        cout << "Accountnumber correct but Pincode incorrect\n";
        cout << "\a";
        system("color C7");
        return false;
    }
    else if (index == -7) {
        cout << "Pincode correct but Accountnumber incorrect\n";
        cout << "\a";
        system("color C7");
        return false;
    }
    cout << "Login successful\n";
    system("color A7");
    return true;
}


int getpinFromLine(const string& line) {
    if (line.find("----") != string::npos) return -1;
    if (line.find("Name") != string::npos) return -1;
    if (line.find("Client") != string::npos) return -1;

    vector<string> parts = splitTrim(line);
    if (parts.size() >= 5) {
        try {
            return stoi(parts[3]);
        }
        catch (...) {
            return -1;
        }
    }
    return -1;
}

int searchUserusy(const vector<string>& lines, const short& user, const short& pass) {
    for (int i = 0; i < (int)lines.size(); ++i) {
        short usr = getAccountFromLine(lines[i]);
        short pw = getpinFromLine(lines[i]);
        if (usr != -1 && pw != -1) {
            if (usr == user && pw == pass) {
                return i;
            }
            else if (usr == user && pw != pass) {
                return -6;
            }
            else if (usr != user && pw == pass) {
                return -7;
            }
        }
    }
    return -5;
}

bool hasPermission(short userPerm, short requiredPerm) {
    if (userPerm == -1) return true;
    return (userPerm & requiredPerm) == requiredPerm;
}

bool findUserusy(short& u, short& p) {
    vector<string> lines = readfile(filename);
    short perm = 0;
    int idx = searchUserusy(lines, u, p);
 
    return checkUserus(idx);
}

int searchUserustan(const vector<string>& lines, const short& user) {
    for (int i = 0; i < (int)lines.size(); ++i) {
        short usr = getAccountFromLine(lines[i]);
        if (usr != -1 && usr == user) {
            return i;
        }
    }
    return -1;
}

void login() {
    system("color 07");
    system("cls");
    bool loginf = false;
    do {
        short pass;
        cout << "==================== Login Screen ====================\n";
        short us = stoi(enteraccountnumber());
        cc.accountnumber = us;
            
        cout << "Enter Pincode: ";
        cin >> pass;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            system("color C7");
            cout << "\a";
        }
        loginf = !findUserusy(us, pass);
    } while (loginf);
    t5baytaenchta();
}

    int main()
    {
        login();
        system("pause>0");
    }

