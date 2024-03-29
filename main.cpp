/*============================================================================*/
/* Name        : KolkoIKrzyzyk.cpp	                       		      */
/* Author      : Robert							      */
/* Version     : 1.0.0 alpha						      */
/* Copyright   : Your copyright notice			 		      */
/* Description : Kolko i krzyzyk in C++, Ansi-style			      */
/*============================================================================*/

#include <iostream>
#include <cstdlib>

using namespace std;

char o=79;				//O w ASCII
char x=88;				//X w ASCII
char spacja=32;			//spacja w ASCII
int komp[2];			//wybor komputera

//rysuje plansze pod wymiar
void rysuj(char** plansza, int rozmiar);
//wykonuje ruch (i komputer i gracz)
void ruch(char** plansza, int rozmiar, char gracz, int ilosc);
//sprawdza czy wygrana
char wygrana(char** plansza, int rozmiar, char gracz, int ilosc);
//sprawdza czy remis(uzywac jak wygrana zwraca spacja)
bool remis(char** plansza, int rozmiar);
//szuka ruchu dla komputera
void komputer(char** plansza, int rozmiar, int ilosc);
//minimax
int minimax(char** plansza, int rozmiar, int ilosc, char gracz, int glebokosc);

int main()
{
	char** plansza;
	int rozmiar=0;
	int ilosc=0;
	char gracz=o;

	do{
		cout << "Podaj rozmiar planszy: ";
		cin >> rozmiar;
		if(rozmiar<3)
		{
			cout << "!!! MINIMALNY ROZMIAR PLANSZY WYNOSI 3 !!!" << endl << endl;
		}

	}while(rozmiar<3);

	do{
		cout << "Podaj ilosc symboli w rzedzie do wygrania: ";
		cin >> ilosc;
		if(ilosc<3)
		{
			cout << "!!! MINIMALNA WARTOSC DO WYGRANEJ WYNOSI 3 !!!" << endl << endl;
		}

	}while(ilosc<3);

	plansza=new char*[rozmiar];				//alokacja planszy
	for(int i=0;i<rozmiar;++i)
	{
		plansza[i]=new char[rozmiar];
	}

	for(int i=0;i<rozmiar;i++)				//uzupelniamy plansze spacjami
	{
		for(int j=0;j<rozmiar;++j)
		{
			plansza[i][j]=spacja;
		}
	}

	rysuj(plansza,rozmiar);
	for(unsigned int i=0;i<rozmiar*rozmiar;++i)
	{
		ruch(plansza,rozmiar,gracz,ilosc);
		rysuj(plansza,rozmiar);
		if(wygrana(plansza,rozmiar,gracz,ilosc)==gracz)
		{
			if(gracz==x)
			{
				cout << " WYGRYWA KOMPUTER " << endl;
			}
			else
			{
				cout << " WYGRYWASZ " << endl;
			}
			return 0;
		}
		if(gracz==x)
		{
			gracz=o;
		}
		else
		{
			gracz=x;
		}
	}
/*
	ruch(plansza,rozmiar,x);
	rysuj(plansza,rozmiar);
	ruch(plansza,rozmiar,x);
	rysuj(plansza,rozmiar);
	ruch(plansza,rozmiar,x);
	rysuj(plansza,rozmiar);
	ruch(plansza,rozmiar,x);
	rysuj(plansza,rozmiar);

	char wynik=wygrana(plansza, rozmiar, x,ilosc);
	cout << wynik << endl;*/

	cout << " REMIS " << endl;
	return 0;
}

//rysuje plansze pod wymiar
void rysuj(char** plansza, int rozmiar)
{
	cout << "    ";
	for(int j=0;j<rozmiar;++j)
	{
		cout << " " << j+1 << "  ";
	}
	cout << endl;
	cout << "   +";
	for(int j=0;j<rozmiar;++j)
	{
		cout << "---+";
	}
	cout << endl;
	for(int i=0;i<rozmiar;++i)
	{
		char c =i+65;
		cout << " "<< c << " |";
		for(int j=0;j<rozmiar;++j)
		{
			cout << " " << plansza[i][j] << " |";
		}
		cout << endl << "   +";
		for(int j=0;j<rozmiar;++j)
		{
			cout << "---+";
		}
		cout << endl;
	}
}

//wykonuje ruch (i komputera i gracza)
void ruch(char** plansza, int rozmiar,char gracz,int ilosc)
{
	char r[2];
	bool test=false;

	if(gracz==o) //ruch gracza
	{
		do{
			cout << "Podaj pole: ";
			cin >> r[0] >> r[1];
			int w=r[0]-64;					//przeliczanie z ascii
			int k=r[1]-48;
			if(w>0&&w<=rozmiar&&k>0&&k<=rozmiar)
			{
				if(plansza[w-1][k-1]==spacja)
				{
					test=true;
					plansza[w-1][k-1]=gracz;
				}
				else
				{
					cout << "!!! TO POLE JEST JUZ ZAJETE !!!" << endl << endl;
				}
			}
			else
			{
				cout << "!!! PODANE POLE NIE ZNAJDUJE SIE NA PLANSZY !!!" << endl << endl;
			}
		}while(test==false);
	}
	else //ruch komputera
	{
		komputer(plansza,rozmiar,ilosc);
		int w=komp[0];
		int k=komp[1];
		plansza[w][k]=gracz;
		char a=w+65;
		char b=k+49;
		cout << a << b << endl;//wyswietla ruch komputera w sposob zrozumialy dla gracza
	}
}

//sprwadza czy wygrana gracza
char wygrana(char** plansza, int rozmiar, char gracz, int ilosc)
{
	int licznik=0;
	bool wygrana=false;
	int skos=rozmiar-ilosc;

	//sprawdzamy wiersze
	if(wygrana==false)
	{
		for(int i=0;i<rozmiar;++i)
		{
			for(int j=0;j<rozmiar;++j)
			{
				if(plansza[i][j]==gracz)
				{
					licznik++;
					if(licznik>=ilosc)
					{
						wygrana=true;
						break;
					}
				}
				else
				{
					licznik=0;
				}
			}
			if(wygrana==true)
			{
				break;
			}
			else
			{
				licznik=0;
			}
		}
	}

	//Sprawdzamy kolumny
	if(wygrana==false)
	{
		for(int i=0;i<rozmiar;++i)
		{
			for(int j=0;j<rozmiar;++j)
			{
				if(plansza[j][i]==gracz)
				{
					licznik++;
					if(licznik>=ilosc)
					{
						wygrana=true;
						break;
					}
				}
				else
				{
					licznik=0;
				}
			}
			if(wygrana==true)
			{
				break;
			}
			else
			{
				licznik=0;
			}
		}
	}

	//Sprawdzamy skos lewo-prawo gora
	if(wygrana==false)
	{
		for(int i=0;i<=skos;++i)
		{
			int w=0;
			int k=i;

			while(w<rozmiar&&k<rozmiar)
			{
				if(plansza[w][k]==gracz)
				{
					licznik++;
					if(licznik>=ilosc)
					{
						wygrana=true;
						break;
					}
				}
				else
				{
					licznik=0;
				}
				k++;
				w++;
			}
			if(wygrana==true)
			{
				break;
			}
			else
			{
				licznik=0;
			}
		}
	}

	//Sprawdzamy skos lewo-prawo dol
	if(wygrana==false)
	{
		for(int i=1;i<=skos;++i)
		{
			int w=i;
			int k=0;

			while(w<rozmiar&&k<rozmiar)
			{
				if(plansza[w][k]==gracz)
				{
					licznik++;
					if(licznik>=ilosc)
					{
						wygrana=true;
						break;
					}
				}
				else
				{
					licznik=0;
				}
				k++;
				w++;
			}
			if(wygrana==true)
			{
				break;
			}
			else
			{
				licznik=0;
			}
		}
	}

	//Sprawdzamy skos prawo-lewo gora
	if(wygrana==false)
	{
		for(int i=rozmiar-1;i>=skos;--i)
		{
			int w=0;
			int k=i;

			while(w<rozmiar&&k>=0)
			{
				if(plansza[w][k]==gracz)
				{
					licznik++;
					if(licznik>=ilosc)
					{
						wygrana=true;
						break;
					}
				}
				else
				{
					licznik=0;
				}
				k--;
				w++;
			}
			if(wygrana==true)
			{
				break;
			}
			else
			{
				licznik=0;
			}
		}
	}

	//Sprawdzamy skos prawo-lewo dol
	if(wygrana==false)
	{
		for(int i=1;i<=skos;++i)
		{
			int w=i;
			int k=rozmiar-1;

			while(w<rozmiar&&k>=0)
			{
				if(plansza[w][k]==gracz)
				{
					licznik++;
					if(licznik>=ilosc)
					{
						wygrana=true;
						break;
					}
				}
				else
				{
					licznik=0;
				}
				k--;
				w++;
			}
			if(wygrana==true)
			{
				break;
			}
			else
			{
				licznik=0;
			}
		}
	}

	if(wygrana==true)
	{
		return gracz;
	}
	return spacja;
}

//sprawdza czy remis (uzywac tylko jak wygrana zwraca spacje)
bool remis(char** plansza, int rozmiar)
{
	for (int i=0;i<rozmiar;++i)
	{
		for(int j=0; j<rozmiar;++j)
		{
			if(plansza[i][j]==spacja)
			{
				return false;
			}
		}
	}
	return true;
}

//szuka optymalnego ruchu dla komputera
void komputer(char** plansza, int rozmiar, int ilosc)
{
	int m, mmx;

	mmx=-(rozmiar*rozmiar+1);
	for(int i=0;i<rozmiar;++i)
	{
		for(int j=0; j<rozmiar;++j)
		{
			if(plansza[i][j]==spacja)
			{
				plansza[i][j]=x;
				m=minimax(plansza, rozmiar, ilosc, x,0);
				plansza[i][j]=spacja;
				if(m>mmx)
				{
					mmx=m;
					komp[0]=i;
					komp[1]=j;
				}
			}
		}
	}
}

//minimax
int minimax(char** plansza, int rozmiar, int ilosc, char gracz,int glebokosc)
{

	int m, mmx=0;
	if(glebokosc<=4){ //glebokosc przeszukania ograniczona do 4
	char wygrany=wygrana(plansza,rozmiar,gracz,ilosc);
	if(wygrany==x)
	{
		return 1+glebokosc;
	}
	else if(wygrany==o)
	{
		return -1-glebokosc;
	}
	else
	{
		if(remis(plansza,rozmiar)==true)
		{
			return 0;
		}
	}


	if(gracz==x)//zamiana graczy
	{
		gracz=o;
	}
	else
	{
		gracz=x;
	}

	if(gracz==o) //okreslamy czy liczymy max czy min
	{
		mmx=rozmiar*rozmiar+1;
	}
	else
	{
		mmx=-(rozmiar*rozmiar+1);
	}

	for(int i=0;i<rozmiar;++i)
	{
		for(int j=0;j<rozmiar;++j)
		{
			if(plansza[i][j]==spacja)
			{
				plansza[i][j]=gracz;
				m=minimax(plansza,rozmiar,ilosc,gracz,glebokosc+1); //rekurencja (nie dalej niz 4)
				plansza[i][j]=spacja;
				if(((gracz == o) && (m < mmx)) || ((gracz == x) && (m > mmx))) //czy ta opcja lepsza od poprzednich
				{
					mmx=m;
				}
			}
		}
	}}
	return mmx; //zwrot najlepszej opcji

}
