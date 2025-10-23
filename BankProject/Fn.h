#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include<fstream>
#include <iomanip>
#include <windows.h>
using namespace std;
namespace mysp {
	enum enchose { add = 1, show = 2, delet = 3, update = 4, find = 5, exit = 6 };
	struct stbank {
		string name = "";
		string lastname = "";
		string phone = "";
		string pincode = "";
		string accountnumber = "";
		string balance = "";
	};
	vector<stbank> vclient;
	void printmenu() {
		cout << setw(80) << "==================== Bank System ====================\n";
		cout << setw(40) << "1- Add Client\n";
		cout << setw(46) << "2- Show All Clients\n";
		cout << setw(43) << "3- Delete Client\n";
		cout << setw(48) << "4- Update Client Info\n";
		cout << setw(41) << "5- Find Client\n";
		cout << setw(34) << "6- Exit\n";
		cout << setw(80) << "=====================================================\n";
	};
	enchose chose() {
		short chose;
		do {
			cout << setw(74) << "Chose What Do You Want To Do [1 To 6] ?\n";
			cin >> chose;
			if (cin.fail()) { 
				cin.clear();                
				cin.ignore(10000, '\n'); 
				cout << "Worng Enter A Valid Number\n\n";
			}
			else {
				break; 
			}
		} while ( chose < 1 || chose>6);
		return (enchose)chose;
	};
	stbank fnadd( stbank& client, string ClientsFileName, vector<stbank>& vclient) {
		system("cls");
		char d = 'y';
		do {
			cout << "==================== Add New Client ====================\n";
			cout << "Enter Client Name: ";
			cin >> client.name;
			cout << "Enter Client LastName: ";
			cin >> client.lastname;
			cout << "Enter Client Phone: ";
			cin >> client.phone;
			cout << "Enter Client PinCode: ";
			cin >> client.pincode;
			cout << "Enter Client AccountNumber: ";
			cin >> client.accountnumber;
			cout << "Enter Client Balance: ";
			cin >> client.balance;
			cout << "=========================================================\n";
			cin.ignore();
			vclient.push_back(client);
			ofstream file ;
			file.open(ClientsFileName, ios::out);
			if (!file.is_open()) {
				cout << "[X] Could not open the file!" << endl;
			}
			for (int i = 0; i <vclient.size() ; i++) {
    file << "|-------------|---------------|-------Client" << i + 1 << "|------------|------------------|-------------| \n";
   file << "|";
   file << setw(5) << "    Name" << "     | ";
    file << setw(5) << "  Lastname" << "    | ";
    file << setw(5) << "    Phone" << "    | ";
    file << setw(5) << " Pincode" << "   | ";
    file << setw(5) << "  Accountnumber" << "  | ";
    file << setw(6) << "  Balance" << "   | " << endl;
    file << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
    file << "|";
    file << setw(13) << vclient[i].name << "| ";
    file << setw(14) << vclient[i].lastname << "| ";
    file << setw(13) << vclient[i].phone << "| ";
    file << setw(11) << vclient[i].pincode << "| ";
    file << setw(16) << vclient[i].accountnumber << " | ";
    file << setw(12) << vclient[i].balance << "| " << endl;
    file << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
			}
			file.close();
		cout << "Do You Want To Add Another Client? (Y/N): ";
		cin >> d;
		} while (d == 'y' || d == 'Y');
		if(d!='y') {
		cout << "For Go Back To Menu Press Any Key " << endl;
		system("pause>0");
		}
		return client;
	};
	void fordelet(stbank& client, string ClientsFileName, vector<stbank>& vclient) {
char T = 'n';
		system("cls");
		do{
			char d = 'y';
			string accountnumber;
			cout << "==================== Delete Client ====================\n";
			cout << "Do You Want Delete A Client: Y/N ";
			cin >> d;
			if (d == 'y' || d == 'Y') {
				cout << "Enter Client AccountNumber to Delete it: ";
				cin >> accountnumber;
				bool found = false;
            for (size_t i = 0; i < vclient.size(); i++) {
                if (vclient[i].accountnumber == accountnumber) {
                    vclient.erase(vclient.begin() + i);
                    cout << "Client With AccountNumber " << accountnumber << " Has Been Deleted." << endl;
                    found = true;
					ofstream file;
					file.open(ClientsFileName, ios::out);
					if (!file.is_open()) {
						cout << "[X] Could not open the file!" << endl;
					}
					for (int i = 0; i < vclient.size(); i++) {
						file << "|-------------|---------------|-------Client" << i + 1 << "|------------|------------------|-------------| \n";
						file << "|";
						file << setw(5) << "    Name" << "     | ";
						file << setw(5) << "  Lastname" << "    | ";
						file << setw(5) << "    Phone" << "    | ";
						file << setw(5) << " Pincode" << "   | ";
						file << setw(5) << "  Accountnumber" << "  | ";
						file << setw(6) << "  Balance" << "   | " << endl;
						file << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
						file << "|";
						file << setw(13) << vclient[i].name << "| ";
						file << setw(14) << vclient[i].lastname << "| ";
						file << setw(13) << vclient[i].phone << "| ";
						file << setw(11) << vclient[i].pincode << "| ";
						file << setw(16) << vclient[i].accountnumber << " | ";
						file << setw(12) << vclient[i].balance << "| " << endl;
						file << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
					}
					file.close();
                    break;
                }
            }
            if (!found) {
                cout << "Client with AccountNumber " << accountnumber << " Not Found." << endl;
            }
			}
			cout << "Do You want to Delete Another Client? (Y/N): ";
			cin >> T;
		} while (T == 'Y' || T == 'y');
		if (T != 'y' && T != 'Y') {
			cout << "For Go Back To Menu Press Any Key " << endl;
			system("pause>0");
		}
	};
	void forupdate(stbank& client, string ClientsFileName, vector<stbank>& vclient) {
		char T = 'n';
		system("cls");
		do {
			char d = 'y';
			string accountnumber;
			cout << "==================== Update Client ====================\n";
			cout << "Do You Want Update A Client: Y/N ";
			cin >> d;
			if (d == 'y' || d == 'Y') {
				cout << "Enter Client AccountNumber to Update it: ";
				cin >> accountnumber;
				bool found = false;
				for (size_t i = 0; i < vclient.size(); i++) {
					if (vclient[i].accountnumber == accountnumber) {
						found = true;
						cout << "==================== Update Client info ====================\n";
						cout << "Enter Client Name: ";
						cin >> vclient[i].name;
						cout << "Enter Client LastName: ";
						cin >> vclient[i].lastname;
						cout << "Enter Client Phone: ";
						cin >> vclient[i].phone;
						cout << "Enter Client PinCode: ";
						cin >> vclient[i].pincode;
						cout << "Enter Client AccountNumber: ";
						cin >> vclient[i].accountnumber;
						cout << "Enter Client Balance: ";
						cin >> vclient[i].balance;
						cout << "=========================================================\n";
						cin.ignore();
						ofstream file;
						file.open(ClientsFileName, ios::out);
						if (!file.is_open()) {
							cout << "[X] Could not open the file!" << endl;
						}
						for (int i = 0; i < vclient.size(); i++) {
							file << "|-------------|---------------|-------Client" << i + 1 << "|------------|------------------|-------------| \n";
							file << "|";
							file << setw(5) << "    Name" << "     | ";
							file << setw(5) << "  Lastname" << "    | ";
							file << setw(5) << "    Phone" << "    | ";
							file << setw(5) << " Pincode" << "   | ";
							file << setw(5) << "  Accountnumber" << "  | ";
							file << setw(6) << "  Balance" << "   | " << endl;
							file << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
							file << "|";
							file << setw(13) << vclient[i].name << "| ";
							file << setw(14) << vclient[i].lastname << "| ";
							file << setw(13) << vclient[i].phone << "| ";
							file << setw(11) << vclient[i].pincode << "| ";
							file << setw(16) << vclient[i].accountnumber << " | ";
							file << setw(12) << vclient[i].balance << "| " << endl;
							file << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
						}
						cout << "Client With AccountNumber " << accountnumber << " has been Updated." << endl;
						file.close();
						break;
					}
				}
				if (!found) {
					cout << "Client With AccountNumber " << accountnumber << " Not Found." << endl;
				}
			}
			cout << "Do You Want To Update Another Client? (Y/N): ";
			cin >> T;
		} while (T == 'Y' || T == 'y');
		if (T != 'y' && T != 'Y') {
			cout << "For Go Back To Menu Press Any Key " << endl;
			system("pause>0");
		}
	}
	void findclient(stbank& client, string ClientsFileName, vector<stbank>& vclient) {
		char T = 'n';
		system("cls");
		do {
			char d = 'y';
			string accountnumber;
			cout << "==================== Find Client ====================\n";
				cout << "Enter Client AccountNumber to Find iT: ";
				cin >> accountnumber;
				bool found = false;
				for (size_t i = 0; i < vclient.size(); i++) {
					if (vclient[i].accountnumber == accountnumber) {
						found = true;
						ifstream file;
						file.open(ClientsFileName);
						if (!file.is_open()) {
							cout << "[X] Could Not Open The File!" << endl;
						}
						cout << "|-------------|---------------|-------Client" << i + 1 << "|------------|------------------|-------------| \n";
						cout << "|";
						cout << setw(5) << "    Name" << "     | ";
						cout << setw(5) << "  Lastname" << "    | ";
						cout << setw(5) << "    Phone" << "    | ";
						cout << setw(5) << " Pincode" << "   | ";
						cout << setw(5) << "  Accountnumber" << "  | ";
						cout << setw(6) << "  Balance" << "   | " << endl;
						cout << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
						cout << "|";
						cout << setw(13) << vclient[i].name << "| ";
						cout << setw(14) << vclient[i].lastname << "| ";
						cout << setw(13) << vclient[i].phone << "| ";
						cout << setw(11) << vclient[i].pincode << "| ";
						cout << setw(16) << vclient[i].accountnumber << " | ";
						cout << setw(12) << vclient[i].balance << "| " << endl;
						cout << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
						cout << "Client With AccountNumber " << accountnumber << " has Been Find it." << endl;
						file.close();
						break;
					}
				}
				if (!found) {
					cout << "Client With AccountNumber " << accountnumber << " Not Found." << endl;
				}
			cout << "Do You Want To Find Another Client? (Y/N): ";
			cin >> T;
		} while (T == 'Y' || T == 'y');
		if (T != 'y' && T != 'Y') {
			cout << "For Go Back To Menu Press Any Key " << endl;
			system("pause>0");
		}
	}
	void fnshowall(stbank client, string ClientsFileName, vector<stbank>& vclient) {
		system("cls");
		char d = 'y';
		ifstream file;
		file.open(ClientsFileName);
		if (!file.is_open()) {
		cout << "[X] Could Not Open The File!" << endl;
		}
		while (!file.eof()) {
			file>> client.name;
			file>> client.lastname;
			file>>client.phone;
			file>> client.pincode;
			file >> client.accountnumber;
			file>> client.balance;
		}
		file.close();
		if (client.name != "")
			for (size_t i = 0; i < vclient.size(); i++) {
				cout << "|-------------|---------------|-------Client" << i+1 << "|------------|------------------|-------------| \n";
				cout << "|";
				cout << setw(5) << "    Name" << "     | ";
				cout << setw(5) << "  Lastname" << "    | ";
				cout << setw(5) << "    Phone" << "    | ";
				cout << setw(5) << " Pincode" << "   | ";
				cout << setw(5) << "  Accountnumber" << "  | ";
				cout << setw(6) << "  Balance" << "   | " << endl;
				cout << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
				cout << "|";
				cout << setw(13) << vclient[i].name << "| ";
				cout << setw(14) << vclient[i].lastname << "| ";
				cout << setw(13) << vclient[i].phone << "| ";
				cout << setw(11) << vclient[i].pincode << "| ";
				cout << setw(16) << vclient[i].accountnumber << " | ";
				cout << setw(12) << vclient[i].balance << "| " << endl;
				cout << "|-------------|---------------|--------------|------------|------------------|-------------|\n";
				}
		cout << "For Go Back To Menu Press Any Key " << endl;
		system("pause>0");		
	};
	void fnshow(string ClientsFileName) {
		stbank client;
		enchose chos{};
		while(chos!=exit){
			system("cls");
		printmenu();
		chos = chose();
		if (chos == add) {
			fnadd( client, ClientsFileName, vclient);	
		}
		 if (chos==show) {
			fnshowall(client, ClientsFileName, vclient);
		}
		 if (chos == delet) {
			 fordelet(client,ClientsFileName,vclient);
		 }
		 if (chos == update) {
			 forupdate(client, ClientsFileName, vclient);
		 }
		 if (chos == find) {
			 findclient(client, ClientsFileName, vclient);
		 }
	}
	};
}
