//------------------------------------------//
#include <iostream>   
#include <cstdlib>    
#include <ctime>      
#include <windows.h>  
using namespace std;
//------------------------------------------// 
enum enplayrch { ajra = 1, wara = 2, mias = 3 };
enum enchkonlir { palyer = 1, cm = 2, dr = 3 };
//------------------------------------//
struct stta5wpalyer {
	enplayrch pch;
	enplayrch playo;
};
struct m3lola3ba {
	short ranodnum = 0;
	short plw = 0;
	short cmw = 0;
	short drw = 0;
	enchkonlir chkonlir = enchkonlir::dr;
};
//------------------------------------//
int randomnum(int from, int to) {
	return rand() % (to - from + 1) + from;
}
short howmanyround() {
	short rounds;
	do {
		cout << "Enter number of rounds to play (1-10): ";
		cin >> rounds;
	} while (rounds < 1 || rounds > 10);
	return rounds;
}
enplayrch readplayrch() {
	short playrch = 0;
	do {
		cout << "----------------------------------------------------------" << endl;
		cout << "Enter your choice (1 for Ajra, 2 for Wara, 3 for Mias): ";
		cin >> playrch;
		cout << "----------------------------------------------------------" << endl;
	} while (playrch < ajra || playrch > mias);
	return (enplayrch)playrch;
}
enplayrch cmplayrch() {
	return (enplayrch)randomnum(1, 3);
}
string swtoname(enplayrch playrch) {
	switch (playrch) {
	case ajra: return "Ajra";
	case wara: return "Wara";
	case mias: return "Mias";
	}
	return "";
}
stta5wpalyer fnta3() {
	stta5wpalyer a;
	a.playo = readplayrch();
	a.pch = cmplayrch();
	return a;
}
enchkonlir checkonlir(enplayrch palyer, enplayrch cm) {
	enchkonlir ta3o;
	if (palyer == cm) return enchkonlir::dr;
	switch (palyer)
	{
	case ajra:
		if (cm == wara && palyer == ajra)
			return enchkonlir::cm;
		break;
	case wara:
		if (cm == mias && palyer ==wara )
			return enchkonlir::cm;
		break;
	case mias:
		if (cm ==  ajra&& palyer == mias)
			return enchkonlir::cm;
		break;
	default:
		break;
	}
	return enchkonlir::palyer;
}
//------------------------------------------//
void roundresult(stta5wpalyer palyer, m3lola3ba& m3l) {

	cout << "Player chose: " << swtoname(palyer.playo) << endl;

	cout << "Computer chose: " << swtoname(palyer.pch) << endl;

	m3l.chkonlir = checkonlir(palyer.playo, palyer.pch);

	switch (m3l.chkonlir)
	{
	case enchkonlir::palyer:
		cout << "Player wins" << endl;
		system("color A7");
		Beep(6000, 300);
		m3l.plw++;
		break;
	case enchkonlir::cm:
		cout << "Computer wins this round!" << endl;
		system("color C7");
		cout << "\a";
		m3l.cmw++;
		break;
	case enchkonlir::dr:
		cout << "This round is a draw!" << endl;
		system("color E0");
		Beep(440, 200);
		m3l.drw++;
		break;
	}
}
//------------------------------------------//
void stargame() {
	char a = 'Y';
	system("cls");
	cout << "\t\t\t\t\t-------------------" << endl;
	cout << "\t\t\t\t\t Welcome to my game " << endl;
	cout << "\t\t\t\t\t-------------------" << endl;
	do
	{

		short raond = howmanyround();
		m3lola3ba m3l;
		for (int i = 1; i <= raond; i++) {
			m3l.ranodnum = i;
			cout << "Round " << m3l.ranodnum << " of " << raond << endl;
			roundresult(fnta3(), m3l);
			cout << "-----------------------------------" << endl;
			cout << "player wins: " << m3l.plw << endl;
			cout << "computer wins: " << m3l.cmw << endl;
			cout << "draws: " << m3l.drw << endl;
			cout << "-----------------------------------" << endl;


		}
		cout << "you wanna play again? (Y or N): ";
		cin >> a;
		system("cls");
		system("color 07");
	} while (a == 'Y' || a == 'y');
}
//------------------------------------------//
int main()
{
	srand((unsigned)time(NULL));
	stargame();
}