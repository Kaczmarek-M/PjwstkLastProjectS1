//projekt nr.59 Michal Kaczmarek

#include "pch.h"
#define _USE_MATH_DEFINE
#include <time.h>
#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <conio.h>



void gotoxy(int x, int y);
int wherex();
int wherey();
void HideCursor();
using namespace std;

const char Esq = 27;
void wstep(int x, int y);
void wyswietlanie(int rozmiar, char znak, int x, int y);
void poruszanie(char znak, int rozmiar, int &x, int &y, int &right, int &bottom, int &max, int &zmiana, char &wybor);
void wczytajRozmiar(int &rozmiar);
void wczytajZnak(char &znak);
void info(int x, int y);
void figura();
void program();
void powtorka();

int _tmain(int argc, _TCHAR* argv[])
{
	program();
	return 0;
}
void program()
{
	int max = 25;                             // max rozmiar figury
	int zmiana;	                              // zmienna odpowiadajaca za zmiane w funkcji poruszanie
	char wybor, znak, z;
	int x = wherex();						  // przypisanie warotosci zmiennej x				
	int y = wherey();                         // przypisanie wartosci zmiennej y
	int rozmiar = 0;                          // zmienna rozmiaru figury
	int right = 0, bottom = 0;                // zmienne rozmiaru ekranu konsoli

	wstep(x, y);                           // informacja dla uzytkownika
	wczytajRozmiar(rozmiar);           // wczytywanie danych od uzytkownika
	do
	{
		wczytajZnak(znak);
		poruszanie(znak, rozmiar, x, y, right, bottom, max, zmiana, wybor);   // funkcja poruszania figury
		powtorka();
		_getch();
		z = _getch();
		system("cls");
		_getch();
	} while (z == 't' || z == 'T');                                              // kontynuacja lub zakonczenie programu
}
void powtorka()
{
	system("cls");
	gotoxy(4, 2);
	cout << "jezeli chcesz zmienic znak ASCII nacisnij t" << endl;
	gotoxy(4, 3);
	cout << "jezeli chcesz zakonczyc program nacisnij dowolny klawisz ";
}
void wstep(int x, int y)                                                        // funkcja informacyjna
{
	gotoxy(34, 2);
	cout << " Witamy w programie rysowania znakiem ASCII " << endl;
	gotoxy(51, 5);
	cout << " FIGURA";
	figura();
	gotoxy(44, 20);
	cout << " Program udostepnia :";
	gotoxy(35, 22);
	cout << " - wybor poczatkowego rozmiaru figury" << endl;
	gotoxy(35, 23);
	cout << " - wybor znaku ASCII" << endl;
	gotoxy(35, 24);
	cout << " - poruszanie figura po ekranie" << endl;
	gotoxy(35, 25);
	cout << " - powiekszanie i zmniejszanie figury" << endl;
	gotoxy(35, 27);
	cout << " nacisnij dowolny klawisz aby rozpoczac";
	HideCursor();
	_getch();
	system("cls");
	info(x, y);                                                        // dodatkowe informacje o programie
	_getch();

}
void wczytajRozmiar(int &rozmiar)                             // wczytywanie rozmiaru od uzytkownika
{
	for (int i = 0; i < 1; i++)
	{
		system("cls");                           // czyszcze ekran                         
		gotoxy(4, 2);                            // podaje miejsce w konsoli gdzie ma wyswietlic napis
		cout << "Podaj rozmiar figury : ";
		cin >> rozmiar;							 // zapisuje rozmiar figury
		HideCursor();

		if (rozmiar < 3 || rozmiar > 25)         // sprawdzam czy podany rozmiar jest prawidlowy
		{
			i--;
			system("cls");
			gotoxy(4, 2);
			cout << "nieodpowiedni rozmiar, prosze podac wielkosc jeszcze raz";
			Sleep(3000);
		}
	}
}
void wczytajZnak(char &znak)                     // wczytywanie znaku od uzytkownika
{
	gotoxy(4, 3);
	cout << "Podaj znak : ";
	cin >> znak;								 // zapisuje znak ktorym bedzie figura sie wyswietlala
	gotoxy(4, 5);
	cout << "nacisnij dowolny klawisz aby kontynulowac";
	HideCursor();
}
void info(int x, int y)                       // funkcja dodatkowych informacji
{
	gotoxy(4, 2);
	cout << "Dodatkowe informacje :";
	gotoxy(4, 4);
	cout << "- min. rozmiar figury = 3";
	gotoxy(4, 5);
	cout << "- max. rozmiar figury = 25";
	gotoxy(4, 6);
	cout << "- jezeli chcesz zmienic znak ASCII nacisnij ESC podczas dzialania programu";
	gotoxy(4, 7);
	cout << "- w lewym gornym rogu znajduje sie informacja o aktualnym rozmiarze konsoli ";
	gotoxy(6, 8);
	cout << "x-szeroksc, y-wysokosc,r-rozmiar";
	gotoxy(4, 10);
	cout << "- aby przejsc do wczytywania danych nacisnij dowolny klawisz";
	_getch();
	HideCursor();
}
void figura()                  // wyswitlanie figury do funkcji dane
{
	char figura[9][6] = {
		{'k',' ',' ',' ',' ','k'},
		{'k',' ',' ',' ','k',' '},
		{'k',' ',' ','k',' ',' '},
		{'k',' ','k',' ',' ',' '},
		{'k','k',' ',' ',' ',' '},
		{'k',' ','k',' ',' ',' '},
		{'k',' ',' ','k',' ',' '},
		{'k',' ',' ',' ','k',' '},
		{'k',' ',' ',' ',' ','k'},
	};
	cout << "\n\n\n";
	for (int k = 0; k < 1; k++)
	{

		for (int i = 0; i < 9; i++)
		{
			cout << "\t\t\t\t\t\t    ";
			for (int j = 0; j < 6; j++)
			{
				cout << figura[i][j];
			}
			cout << endl;
		}
	}
}
void poruszanie(char znak, int rozmiar, int &x, int &y, int &right, int &bottom, int &max, int &zmiana, char &wybor)
{
	system("cls");
	gotoxy(4, 2);
	cout << "aby kontynulowac nacisnij jeden z klawiszy kontroli nad figura";
	do
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		right = csbi.srWindow.Right;											// pobieram z konsoli aktualny x
		bottom = csbi.srWindow.Bottom;											// pobieram z konsoli aktualny y						

		wybor = _getch();
		switch (wybor)								// w zaleznosci jaki znak zostanie uzyty przez uzytkownika wywola sie odpowiedni case
		{
		case '+':                                   // powiekszanie figury
		{
			rozmiar++;
			zmiana = 1;
			if (rozmiar < 3 || rozmiar > max)		// jesli rozmiar bedzie nieodpowiedni figura nie zmieni wielkosci
			{
				rozmiar--;
				zmiana = 0;
			}
			else if (y < rozmiar - 1 || x >= right - ((rozmiar / 2) + 1))  // jesli figura bedzie sie stykac z dolna lub prawa krawedzia konsoli to figura
																		   // nie powiekszy sie
			{
				rozmiar--;
				zmiana = 0;
			}
			if (y < 2 + rozmiar && x < 6)
			{
				rozmiar--;
				zmiana = 0;
			}
			break;
		}
		case '-':									// pomniejszanie figury i warunki
		{
			rozmiar--;
			zmiana = 1;
			if (rozmiar < 3 || rozmiar > max)
			{
				rozmiar++;
				zmiana = 0;
			}
			if (y < 3 + rozmiar && x < 6)
			{
				zmiana = 0;
			}
			break;
		}
		case 72:                                   // poruszanie figury w gore
		{
			y--;
			zmiana = 1;
			if (y < rozmiar - 1)
			{
				y++;
				zmiana = 0;
			}
			if (y < 2 + rozmiar && x < 6)
			{
				y++;
				zmiana = 0;
			}
			break;
		}
		case 80:								  // poruszanie w dol	
		{
			y++;
			zmiana = 1;
			if (y == bottom + 1)
			{
				y--;
				zmiana = 0;
			}
			break;
		}
		case 75:								// porusznie w lewo
		{
			x--;
			zmiana = 1;
			if (x < 0)
			{
				x++;
				zmiana = 0;
			}
			if (x < 6 && y < 2 + rozmiar)
			{
				x++;
				zmiana = 0;
			}
			break;
		}
		case 77:                                // poruszanie w prawo
		{
			x++;
			zmiana = 1;
			if (x > right - ((rozmiar / 2) + 1) && rozmiar % 2 == 0)
			{
				x--;
				zmiana = 0;
			}
			else if (x > right - ((rozmiar / 2) + 2) && rozmiar % 2 != 0)
			{
				x--;
				zmiana = 0;
			}

		}
		}
		if (zmiana)                          // jezeli zmiana rowna sie 1 to zmien
		{
			wyswietlanie(rozmiar, znak, x, y);
			zmiana = 0;
			gotoxy(0, 0);
			cout << "x= " << right << endl;   // wyswietlanie dodatkowych informacji w lewym gornym narozniku
			cout << "y= " << bottom << endl;
			cout << "r= " << rozmiar;
			void rysuj();
		}
	} while (wybor != 27);                                // zakoncz funkcje poruszanie
}
void wyswietlanie(int rozmiar, char znak, int x, int y)   // wyswietlanie figury
{
	system("cls");
	for (int i = 0; i < rozmiar; i++)
	{
		gotoxy(x, y);
		y--;
		cout << znak;
		for (int j = rozmiar / 2; j < rozmiar; j++)
		{
			if (j == i || j == rozmiar - i - 1)
			{
				cout << znak;
			}
			else
				cout << " ";
		}
		cout << endl;

	}
	HideCursor();
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int wherex()
{

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X = 0;

}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y = 29;
}
void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
