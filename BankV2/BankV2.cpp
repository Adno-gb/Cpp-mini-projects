#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

const string filename = "cleant.txt";
const string filename2 = "users.txt";
void login();
enum enchose { add = 1, show = 2, delet = 3, update = 4, findd = 5, Transaction = 6,manengeuser=7, exxit = 8 };
enum enwde { Deposit = 1, Withdraw = 2, Trnsaction = 3, Eexit = 4 };
enum enusers{addusers=1,listusers=2,deleteusers=3,updateusers=4,findusers=5,Back=6};
enum permessions { all = -1, addClient = 1, listClient = 2, deletClient = 4, updateClient = 8, findClient = 16, Transactions = 32, mannengeuser = 64
};

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

struct stuser {
    string username = "";
    short pass = 0;
    short per = 0;
    bool trfa = false;
};

stclint cc;
stuser ll;

void forgoback() {
    cout << "For Go Back To Menu Press Any Key" << endl;
    system("pause>0");
}

void preintmenu() {
    cout << setw(80) << "=================== Bank System =====================\n";
    cout << setw(40) << "1- Add Client\n";
    cout << setw(46) << "2- Show All Clients\n";
    cout << setw(43) << "3- Delete Client\n";
    cout << setw(48) << "4- Update Client Info\n";
    cout << setw(41) << "5- Find Client\n";
    cout << setw(41) << "6- Transaction\n";
    cout << setw(41) << "7- Manage User\n";
    cout << setw(36) << "8- Logout\n";
    cout << setw(80) << "=====================================================\n";
}

void transctionmenu() {
    cout << setw(80) << "=================== Transaction Menu ====================\n";
    cout << setw(39) << "1- Deposit Money\n";
    cout << setw(40) << "2- Withdraw Money\n";
    cout << setw(37) << "3- Transaction\n";
    cout << setw(30) << "4- Exit\n";
    cout << setw(80) << "=========================================================\n";
}

void usermenu() {
    cout << setw(80) << "==================== User Menu ====================\n";
    cout << setw(41) << "1- Add Users\n";
    cout << setw(42) << "2- List Users\n";
    cout << setw(44) << "3- Delete Users\n";
    cout << setw(44) << "4- Update Users\n";
    cout << setw(42) << "5- Find Users\n";
    cout << setw(36) << "6- Back\n";
    cout << setw(80) << "===================================================\n";
}

short fnach() {
    short x;
    do {
        cout << setw(67) << "Enter Number Between 1 And 8" << endl;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            system("color C7");
            cout << "\a";
        }
        else break;
    } while (x < 1 || x>7);
    return x;
}

enchose chosfn() { return (enchose)fnach(); }

short fntch() {
    short x;
    do {
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

enwde enwfn() { return (enwde)fntch(); }

short fnusch() {
    short x;
    do {
        cout << setw(67) << "Enter Number Between 1 And 6" << endl;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            system("color C7");
            cout << "\a";
        }
        else break;
    } while (x < 1 || x>7);
    return x;
}

enusers enusfn() { return (enusers)fnusch(); }

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

void printhedrf(short i) {
    ofstream file(filename, ios::app);
    file << "|-------------|---------------|------Client " << i << "|------------|-----------------|-------------|\n";
    file << "|    Name     |   Lastname    |    Phone     |  Pincode   |  Accountnumber  |   Balance   |\n";
    file << "|-------------|---------------|--------------|------------|-----------------|-------------|\n";
}

void addcleant() {
    cout << "Enter Client Name: "; getline(cin >> ws, cc.name);
    cout << "\nEnter Client LastName: "; getline(cin, cc.lastname);
    cout << "\nEnter Client Phone: "; getline(cin, cc.phone);
    cout << "\nEnter Client PinCode: "; cin >> cc.pincode;
    cout << "\nEnter Client AccountNumber: "; cin >> cc.accountnumber;
    cout << "\nEnter Client Balance: "; cin >> cc.sold;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input!\n";
        system("color C7");
        cout << "\a";
    }
}

void printflfile() {
    ofstream file(filename, ios::app);
    file << "| " << left << setw(12) << cc.name
        << "| " << left << setw(14) << cc.lastname
        << "| " << left << setw(13) << cc.phone
        << "| " << left << setw(11) << cc.pincode
        << "| " << left << setw(16) << cc.accountnumber
        << "| " << left << setw(12) << cc.sold << "|\n";
    file << "|-------------|---------------|--------------|------------|-----------------|-------------|\n";
}

void t5baytaprintfile() {
    char da = 'y';
    static short it = 0;
    do {
        it++;
        printhedrf(it);
        system("color 07");
        cout << "==================== Add New Client ====================\n";
        addcleant();
        cout << "========================================================\n";
        printflfile();
        cout << "Do you want to add more? (Y/N): ";
        cin >> da;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            system("color C7");
            cout << "\a";
        }
    } while (da == 'y' || da == 'Y');
    cout << "=================================\n";
    forgoback();
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

bool cheacc(vector<string>& lines, int index) {
    if (index == -1) {
        cout << "Not Found!\n";
        return false;
    }
    cout << "Found:\n" << lines[index] << "\n";
    return true;
}

void deletformvector(vector<string>& lines, int index,string filllln) {
    char y;
    cout << "Are you sure you want to delete it? (Y/N): ";
    cin >> y;
    if (y == 'y' || y == 'Y') {
        lines.erase(lines.begin() + index);
        svefilefromvector(filllln,lines);
        cout << "Client deleted successfully!\n";
    }
}

void t5baytadelet() {
    system("color 07");
    system("cls");
    cout << "==================== Delete Client ====================\n";
    vector<string> lines = readfile(filename);
    string acc = enteraccountnumber();
    int idx = serechfromvector(lines, acc);
    if (cheacc(lines, idx))
        deletformvector(lines, idx,filename);
    cout << "=================================\n";
    forgoback();
}

void updateformvector(vector<string>& lines, int index, string filllln) {
    char y;
    cout << "Are you sure you want to update it? (Y/N): ";
    cin >> y;
    if (y == 'y' || y == 'Y') {
        addcleant();
        stringstream ss;
        ss << "| " << left << setw(12) << cc.name
            << "| " << left << setw(14) << cc.lastname
            << "| " << left << setw(13) << cc.phone
            << "| " << left << setw(11) << cc.pincode
            << "| " << left << setw(16) << cc.accountnumber
            << "| " << left << setw(12) << cc.sold << "|";
        lines[index] = ss.str();
        svefilefromvector(filllln,lines);
        cout << "Client updated successfully!\n";
    }
}

void t5baytaupdat() {
    system("color 07");
    system("cls");
    cout << "==================== Update Client ====================\n";
    vector<string> lines = readfile(filename);
    string acc = enteraccountnumber();
    int idx = serechfromvector(lines, acc);
    if (cheacc(lines, idx))
        updateformvector(lines, idx,filename);
    cout << "=================================\n";
    forgoback();
}

void findcl() {
    system("color 07");
    system("cls");
    cout << "==================== Find Client ====================\n";
    vector<string> lines = readfile(filename);
    string acc = enteraccountnumber();
    int idx = serechfromvector(lines, acc);
    cheacc(lines, idx);
    cout << "=================================\n";
    forgoback();
}

void updatebalncd(vector<string>& lines, int index, short ta, bool deposit) {
    stclint client;
    {
        string line = lines[index];
        vector<string> parts = splitTrim(line);
        if (parts.size() >= 6) {
            client.name = parts[0];
            client.lastname = parts[1];
            client.phone = parts[2];
            client.pincode = stoi(parts[3]);
            client.accountnumber = stoi(parts[4]);
            client.sold = stoi(parts[5]);
        }
    }
    cc.accountnumber = client.accountnumber;
    cc.oldsold = client.sold;
    cout << "Old Balance: " << client.sold << endl;
    if (deposit) {
        cc.lastDeposit = ta;
        client.sold += ta;
    }
    else {
        cc.lastWithdraw = ta;
        client.sold -= ta;
    }
    cc.sold = client.sold;
    cout << "New Balance: " << client.sold << endl;
    stringstream ss;
    ss << "| " << left << setw(12) << client.name
        << "| " << left << setw(14) << client.lastname
        << "| " << left << setw(13) << client.phone
        << "| " << left << setw(11) << client.pincode
        << "| " << left << setw(16) << client.accountnumber
        << "| " << left << setw(12) << client.sold << "|";
    lines[index] = ss.str();
    svefilefromvector(filename,lines);
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

void t5baupdat() {
    system("color 07");
    system("cls");
    cout << "==================== Update Balance ====================\n";
    vector<string> lines = readfile(filename);
    string acc = enteraccountnumber();
    int idx = serechfromvector(lines, acc);
    if (!cheacc(lines, idx)) return;
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
    string acc = enteraccountnumber();
    int idx = serechfromvector(lines, acc);
    if (!cheacc(lines, idx)) return;
    short amt = tana();
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

void showcli(string filllenmae) {
    ifstream file(filllenmae);
    if (!file.is_open()) { cout << "File not open!\n"; return; }
    string line;
    while (getline(file, line)) cout << line << endl;
}

void t5baytashow() {
    system("color 07");
    system("cls");
    showcli(filename);
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
        case Deposit: t5baupdat(); break;
        case Withdraw: t5baupdatbn(); break;
        case Trnsaction: trnsacta(); break;
        case Eexit: tr = false; break;
        }
    }
}

short permision() {
    short pr = 0;
    char yy = 'n';
    cout << "Do u want give access to All permission Y/n\n";
    while (true) {
        cin >> yy;

        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        return -1;
    cout << "Do u want give access to Add client Y/n\n";
    while (true) {
        cin >> yy;
        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        pr |= permessions::addClient;
    cout << "Do u want give access to Show client Y/n\n";
    while (true) {
        cin >> yy;
        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        pr |= permessions::listClient;
    cout << "Do u want give access to Delete client Y/n\n";
    while (true) {
        cin >> yy;
        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        pr |= permessions::deletClient;
    cout << "Do u want give access to Update client Y/n\n";
    while (true) {
        cin >> yy;
        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        pr |= permessions::updateClient;
    cout << "Do u want give access to Find client Y/n\n";
    while (true) {
        cin >> yy;
        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        pr |= permessions::findClient;
    cout << "Do u want give access to Transaction menu Y/n\n";
    while (true) {
        cin >> yy;
        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        pr |= permessions::Transactions;
    cout << "Do u want give access to Manage user Y/n\n";
    while (true) {
        cin >> yy;
        if (cin.fail() || (yy != 'y' && yy != 'Y' && yy != 'n' && yy != 'N')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            continue;
        }
        break;
    }
    if (yy == 'y' || yy == 'Y')
        pr |= permessions::mannengeuser;
    return pr;
}

void adduser() {
    short p = 0;
    while (true) {
        cout << "Enter User: ";
        cin >> ws >> ll.username; 
        cout << "Enter Password: ";
        cin >> ll.pass;            
        if (cin.fail()) {
            cin.clear();     
            cin.ignore(10000, '\n'); 
            system("color C7");
            cout << "Invalid Input!\n";
            continue; 
        }
        break;
    }
    cout << "Enter Permission: ";
    ll.per =permision();
}

void printhedrusf(short i) {
    ofstream file(filename2, ios::app);
    file << "|-------------|-----User" << i << "-----|--------------| \n";
    file << "|    User     |    Password   |  Permission  |\n";
    file << "|-------------|---------------|--------------|\n";
}

void printflfileuse() {
    ofstream file(filename2, ios::app);
    file << "| " << left << setw(12) << ll.username
        << "| " << left << setw(14) << ll.pass
        << "| " << left << setw(13) << ll.per
        << "|\n";
    file << "|-------------|---------------|--------------|\n";

}

void t5baytuse(){
    char da = 'y';
    static short it = 0;
    do {
        it++;
        printhedrusf(it);
        system("color 07");
        cout << "==================== User ====================\n";
        adduser();
        cout << "========================================================\n";
        printflfileuse();
        cout << "Do you want to add more? (Y/N): ";
        cin >> da;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Input!\n";
            system("color C7");
            cout << "\a";
        }
    } while (da == 'y' || da == 'Y');
    cout << "=================================\n";
    forgoback();

}

bool checkUserus(int index) {
    if (index == -5) {
        cout << "User and Password incorrect\n";
        cout << "\a";
        system("color C7");
        return false;
    }
    else if (index == -6) {
        cout << "User correct but password incorrect\n";
        cout << "\a";
        system("color C7");
        return false;
    }
    else if (index == -7) {
        cout << "Password correct but username incorrect\n";
        cout << "\a";
        system("color C7");
        return false;
    }
        cout << "Login successful\n";
        system("color A7");
    return true;
}
string trim(const string& s) {
    string result = s;
    while (!result.empty() && isspace(result.front())) result.erase(result.begin());
    while (!result.empty() && isspace(result.back())) result.pop_back();
    return result;
}

string getUserFromLineus(const string& line) {
    if (line.find("----") != string::npos) return "n";
    if (line.find("User") != string::npos) return "n";
    if (line.find("Password") != string::npos) return "n";
    if (line.find("|") == string::npos) return "n";
    vector<string> parts;
    stringstream ss(line);
    string segment;
    while (getline(ss, segment, '|')) {
        string clean = trim(segment);
        if (!clean.empty())
            parts.push_back(clean);
    }
    if (parts.size() >= 3)
        return parts[0];
    return "n";
}

string getPassFromLineus(const string& line) {
    if (line.find("----") != string::npos) return "n";
    if (line.find("User") != string::npos) return "n";
    if (line.find("Password") != string::npos) return "n";
    if (line.find("|") == string::npos) return "n";
    vector<string> parts;
    stringstream ss(line);
    string segment;
    while (getline(ss, segment, '|')) {
        string clean = trim(segment);
        if (!clean.empty())
            parts.push_back(clean);
    }
    if (parts.size() >= 3)
        return parts[1];

    return "n";
}

string getPermissionFromLineus(const string& line) {
    if (line.find("----") != string::npos) return "n";
    if (line.find("User") != string::npos) return "n";
    if (line.find("Password") != string::npos) return "n";
    if (line.find("|") == string::npos) return "n";
    vector<string> parts;
    stringstream ss(line);
    string segment;
    while (getline(ss, segment, '|')) {
        while (!segment.empty() && isspace(segment.front())) segment.erase(segment.begin());
        while (!segment.empty() && isspace(segment.back())) segment.pop_back();
        if (!segment.empty()) parts.push_back(segment);
    }
    if (parts.size() >= 3) {
        return parts[2];
    }
    return "n";
}

int searchUserus(const vector<string>& lines, const string& user, short pass) {
    string passStr = to_string(pass);
    for (int i = 0; i < (int)lines.size(); ++i) {
        string usr = getUserFromLineus(lines[i]);
        string pw = getPassFromLineus(lines[i]);
        if (usr != "n" && pw != "n") {
            if (usr == user && pw == passStr) {
                return i;
            }
            else if (usr == user && pw != passStr) {
                return -6;
            }
            else if (usr != user && pw == passStr) {
                return -7;
            }
        }
    }
    return -5;
}

int searchUserusy(const vector<string>& lines, const string& user, const short& pass, short& permOut) {
        string passStr = to_string(pass);
        for (int i = 0; i < (int)lines.size(); ++i) {
            string usr = getUserFromLineus(lines[i]);
            string pw = getPassFromLineus(lines[i]);
            string per = getPermissionFromLineus(lines[i]);
            if (usr != "n" && pw != "n") {
                if (usr == user && pw == passStr) {
                permOut = stoi(per);
                    return i;
                }
                else if (usr == user && pw != passStr) {
                    return -6;
                }
                else if (usr != user && pw == passStr) {
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

bool findUserusy(string& u, short& p) {
    vector<string> lines = readfile(filename2);
    short perm = 0;
    int idx = searchUserusy(lines, u, p, perm);
    if (idx >= 0) {
        ll.per = perm;
    }
    return checkUserus(idx);
}

int searchUserustan(const vector<string>& lines, const string& user) {
    for (int i = 0; i < (int)lines.size(); ++i) {
        string usr = getUserFromLineus(lines[i]);
        if (usr != "n" && usr == user) {
            return i;
        }
    }
    return -1;
}

void t5baytashowus() {
    system("color 07");
    system("cls");
    showcli(filename2);
    cout << "=================================\n";
    forgoback();
}

void t5baytadeletus() {
    system("color 07");
    system("cls");
    cout << "==================== Delete User ====================\n";
    vector<string> lines = readfile(filename2);
    string acc = enteraccountnumber();
    int idx = searchUserustan(lines, acc);
    if (cheacc(lines, idx))
        deletformvector(lines, idx,filename2);
    cout << "=================================\n";
    forgoback();
}

void updateformvectorus(vector<string>& lines, int index) {
    char y;
    cout << "Are you sure you want to update it? (Y/N): ";
    cin >> y;
    if (y == 'y' || y == 'Y') {
        adduser();
        stringstream ss;
        ss << "| " << left << setw(12) << ll.username
            << "| " << left << setw(14) << ll.pass
            << "| " << left << setw(13) << ll.per
             << "|";
        lines[index] = ss.str();
        svefilefromvector(filename2, lines);
        cout << "User updated successfully!\n";
    }
}

void t5baytaupdatus() {
    system("color 07");
    system("cls");
    cout << "==================== Update User ====================\n";
    vector<string> lines = readfile(filename2);
    string acc = enteraccountnumber();
    int idx = searchUserustan(lines, acc);
    if (cheacc(lines, idx))
        updateformvectorus(lines, idx);
    cout << "=================================\n";
    forgoback();
}

string enteraccountnumberus() {
    string accountn;
    cout << "Enter The Username: ";
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

void findus() {
    system("color 07");
    system("cls");
    cout << "==================== Find User ====================\n";
    vector<string> lines = readfile(filename2);
    string acc = enteraccountnumberus();
    int idx = searchUserustan(lines, acc);
    cheacc(lines, idx);
    cout << "=================================\n";
    forgoback();
}

void switchbinus() {
    bool tr = true;
    while (tr) {
        system("color 07");
        system("cls");
        usermenu();
        switch (enusfn()) {
        case addusers: t5baytuse();
            break;
        case listusers: t5baytashowus();
            break;
        case deleteusers: t5baytadeletus();
            break;
        case updateusers: t5baytaupdatus();
            break;
        case findusers: findus();
            break;
        case Back: tr = false; break;
        }
    }
}

void switchbin() {
    bool tr = true;
    while (tr) {
        system("color 07");
        system("cls");
        preintmenu();
        switch (chosfn()) {
        case add: if (!hasPermission(ll.per, permessions::addClient)) {
            cout << "-----------------------------------------\n";
            cout << "Access denied you cannot Add clients.\n";
            cout << "-----------------------------------------\n";
            system("color C7");
            cout << "\a";
                system("pause");
                break;
        }
        t5baytaprintfile();
        break;
        case show: if (!hasPermission(ll.per, permessions::listClient)) {
            cout << "-----------------------------------------\n";
            cout << "Access denied you cannot Show clients.\n";
            cout << "-----------------------------------------\n";
            system("color C7");
            cout << "\a";
            system("pause");
            break;
        }
            t5baytashow(); break;
        case delet: if (!hasPermission(ll.per, permessions::deletClient)) {
            cout << "-----------------------------------------\n";
            cout << "Access denied you cannot Delete clients.\n";
            cout << "-----------------------------------------\n";
            system("color C7");
            cout << "\a";
            system("pause");
            break;
        }
            t5baytadelet(); break;
        case update: if (!hasPermission(ll.per, permessions::updateClient)) {
            cout << "-----------------------------------------\n";
            cout << "Access denied you cannot Update clients.\n";
            cout << "-----------------------------------------\n";
            system("color C7");
            cout << "\a";
            system("pause");
            break;
        }
            t5baytaupdat(); break;
        case findd: if (!hasPermission(ll.per, permessions::findClient)) {
            cout << "-----------------------------------------\n";
            cout << "Access denied you cannot Find clients.\n";
            cout << "-----------------------------------------\n";
            system("color C7");
            cout << "\a";
            system("pause");
            break;
        }
            findcl(); break;
        case Transaction: if (!hasPermission(ll.per, permessions::Transactions)) {
            cout << "-----------------------------------------\n";
            cout << "Access denied you cannot Show Transaction menu.\n";
            cout << "-----------------------------------------\n";
            system("color C7");
            cout << "\a";
            system("pause");
            break;
        }
            t5baytaenchta(); break;
        case manengeuser: if (!hasPermission(ll.per, permessions::mannengeuser)) {
            cout << "-----------------------------------------\n";
            cout << "U dont have access (This is Only For Admin) \n";
            cout << "-----------------------------------------\n";
            system("color C7");
            cout << "\a";
            system("pause");
            break;
        }
            switchbinus(); break;
        case exxit: tr = false;  login();
        }
    }
}

void login() {
    system("color 07");
    system("cls");
    bool loginf =false;
    do {
        string user; short pass; 
        cout << "==================== Login Screen ====================\n";
    cout << "Enter Username: ";
    cin >> user;
    cout << "Enter Password: ";
    cin >> pass;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input!\n";
        system("color C7");
        cout << "\a";
    }
    loginf = !findUserusy(user, pass);
    } while (loginf);
    switchbin();
}

int main() {

    login();
  
    return 0;
}
