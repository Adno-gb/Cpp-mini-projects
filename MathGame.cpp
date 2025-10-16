#include <iostream>   
#include <cstdlib>    
#include <ctime>      
#include <windows.h>  
using namespace std;
enum enop{ad=1,s=2,d=3,k=4,mix=5};
enum lev{esy=1,hard=2,mid=3,mmix=4};
int RandomNumber(int From, int To)
{
        return rand() % (To - From + 1) + From;
}
enop fnrop()
{
    int x ;
    do {
        cout << "Please enter operator u want: 1=(+) | 2=(-) | 3=(*) | 4=(/) | 5=(mix)" << endl;
        cin >> x;
    } while (x < 1 || x>5);
    return (enop)x;
}
lev fnrlv()
{
    int x ;
    do {
        cout << "Please enter level u want: 1=(Easy) | 2=(Hard) | 3=(Mid) | 4=(Mix)" << endl;
        cin >> x;
    } while (x < 1 || x>4);
    return (lev)x;
}
enop reande() 
{
    return (enop)RandomNumber(1, 4);
}
lev randlv() 
{
    return (lev)RandomNumber(1, 4);
}
int tale(lev lv)
{
    switch (lv) {
    case esy:
        return  RandomNumber(1, 10);
        break;
    case hard:
        return RandomNumber(50, 100);
        break;
    case mid:
        return  RandomNumber(10, 40);
        break;
    case mmix:
        return RandomNumber(1, 100);
    }
}
int calcul(int a, int b, enop op) 
{
    switch (op) {
    case ad:
        return a+b;
        break;
    case s:
        return a-b;
        break;
    case d:
        return a*b;
        break;
    case k:
        return a/b;
        break;
    }
}
char opsymbol(enop op) 
{
    switch (op) {
    case ad:
            return '+';
            break;
    case s:
        return '-';
        break;
    case d:
        return '*';
        break;
    case k:
        return '/';
        break;
    case mix:
        return opsymbol(op);
        break;
    }
}
int entrn()
{
    int a ;
    do {
        cout << "Please enter how many questions u want from 1 to 100" << endl;
        cin >> a;
    } while (a < 1 || a>100);
    return a;
}
void stargame() 
{
    cout << "\t\t\t\t\t------------------------------------------" << endl;
    cout << "\t\t\t\t\t          Walcome to my Math Game" << endl;
    cout << "\t\t\t\t\t------------------------------------------" << endl;
    char aop = 'y';
    do {
        system("cls");
        cout << "----------------------------------------------------" << endl;
        int ba = entrn();
        cout << "----------------------------------------------------" << endl;
        for (int i = 0; i < ba; i++) {
            enop op = fnrop();
            cout << "----------------------------------------------------" << endl;
 lev  nnn = fnrlv();
 cout << "----------------------------------------------------" << endl;
 enop ta = reande();
            int a, b;
            a = tale(nnn);
            b = tale(nnn);
            if (op == mix) {
                int resul = calcul(a, b, ta);
                int retau;
                cout << "Please enter result of \n\t\t\t" << a << opsymbol( ta) << b << endl;
                cin >> retau;
                cout << "----------------------------------------------------" << endl;
                if (resul == retau) {
                    system("color A7");
                    Beep(6000, 300);
                    cout << "You are right \n----------------------------------------------------" << endl;
                }
                else{
                    cout << "You are wrong " << endl;
                    system("color C7");
                    cout << "\a";
                cout << "Right answer is " << resul << endl;
                cout << "----------------------------------------------------" << endl;
                }
            }
            else{
            int resul = calcul(a, b, op);
            int retau ;
            cout << "Please enter result of \n\t\t\t" << a << opsymbol(op) << b << endl;
            cin >> retau;
            cout << "----------------------------------------------------" << endl;
            if (resul ==retau  ){
                system("color A7");
            Beep(6000, 300);
                cout << "You are right \n----------------------------------------------------" << endl;
            }
            else {
                cout << "You are wrong " << endl;
                system("color C7");
                cout << "\a";
            cout << "Right answer is " << resul << endl;
            cout << "----------------------------------------------------" << endl;
            }
           } 
        }
cout << "Do u want to play again Y/N " << endl;
            cin >> aop;
            system("cls");
            system("color 07");
    } while (aop == 'y' || aop == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    stargame();
    return 0;
}

