#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
using namespace std;

bool eNumar(string s);                  //functia aceasta am facut-o pentru a verifica ca datele introduse in fisier sa fie numere
float sColoana(string s, float suma);           //calculez suma numerelor de pe coloana
int Zecimale(string s, int zec);            //imi calculeaza numarul maxim de zecimale din numerele de la fiecare coloana

bool eNumar(string prop)                    //verific ca stringurile din fisier sa fie numere
{
    for (int i = 0; i < prop.size(); i++)        //iau fiecare litera a stringului
    {
    	if (((prop[i] >= '0' && prop[i] <= '9') || prop[i] == '.') == false)         //si verific ca litera sa fie un numar
        {
            return false;                       //daca nu e numar imi returneaza fals
        }
    }
    return true;        //in caz opus imi returneaza adevarat
}

float sColoana (string s, float suma)       //calculez suma de pe coloana
{

        float numar = stof(s);
        return suma + numar;

}

int Zecimale(string s, int zec)         //numar cate zecimale au numerele
{
    int numar = 0;                          //am initializat acest numar cu 0 pentru a putea verifica fiecare zecimala din numar
                                            //astfel, pot vedea numarul care are cele mai multe zecimale pe coloana
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '.')                    //in cazul in care stringul ajunge la virgula
        {
            for (int j = i; j < s.size(); j++)
                numar = numar + 1;                 //sa imi numere care numere sunt dupa acea virgula
        }
    if (numar > zec)                        //in caz ca numarul de zecimare este mai mare decat nr de zecimale actuale
        return numar;                       //sa mi modifice numarul de zecimale actuale
    else return zec;                        //altfel numarul de zecimale nu se modifica
}

int main()
{
	int contor = 0,             //acesta imi numara coloanele de numere
		x_zec = 0,              //acesta nr de zecimale dintr-un numar de pe coloana x
		y_zec = 0;              //acesta de pe coloana y
	float col_x = 0,                //suma de pe coloana x
		col_y = 0,                //suma de pe coloana y
		w2 = 0,
		w1 = 0,
		s1 = 0,                   //suma de la numarator
		s2 = 0;                   //suma de la numitor
	ifstream fo;
	string Years;
	string Exp;
	string line_x;              //numerele de pe coloana x
	string line_y;              //numere de pe coloana y
								//am ales sa le iau drept stringuri ca sa pot sa le citesc de pe coloane
	fo.open("Salary_Data.csv");
	if (!fo) cout << "Eroare";      // verific ca fisierul sa se poata deschida
	getline(fo, Years, ' ');              //citesc prima linie din fisier
	getline(fo, Exp, '\n');
	while (getline(fo, line_x, ' ') &&           //atata timp cat sunt date imi executa
		getline(fo, line_y, '\n'))                 //am ales sa despart datele prin virgula pentru a putea fi scrise fiecare in coloana lor in excel
	{
		if (eNumar(line_x) && eNumar(line_y))   //omit stringurile care nu sunt numere si trec mai departe in program
		{
			col_x = sColoana(line_x, col_x);            //calculez suma pe coloana x
			col_y = sColoana(line_y, col_y);            //aici pe coloana  y
			contor = contor + 1;                    //si numar cate coloane are fisierul cu numere
		}
	}
	cout << "Totalul pe coloane: " << col_x << " " << col_y << endl;                        //am dorit sa afisez totalul pentru cele doua coloane
	float med_x = col_x / contor;                 //calculez media pentru fiecare coloana
	float med_y = col_y / contor;
	cout << "Media pe coloane: " << med_x << " " << med_y << endl;                              //si o afisez
	fo.close();                                     //apoi inchid fisierul pentru a putea relua datele

	fo.open("Salary_Data.csv");                     //in continuare deschid fisierul si repet procesul de citire
	getline(fo, Years, ' ');
	getline(fo, Exp, '\n');
	while (getline(fo, line_x, ' ') &&
		getline(fo, line_y, '\n'))
	{
		if (eNumar(line_x) && eNumar(line_y))
		{
			x_zec = Zecimale(line_x, x_zec);           //aici am dorit sa calculez numarul de zecimale pentru fiecare coloana
			y_zec = Zecimale(line_y, y_zec);
			float x = stof(line_x);                     //convertesc stringurile in float pentru cele doua coloane
			float y = stof(line_y);
			s1 = s1 + ((x - med_x) * (y - med_y));      //calculez suma de la numarator
			s2 = s2 + ((x - med_x) * (x - med_x));      //calculez suma de la numitor
		}
	}
	w2 = s1 / s2;                       //aflu cu cele 2 sume w2
	w1 = med_y - w2 * med_x;            //apoi w1
	int a;                                          //initializez numarul conclusiv de zecimal
	if (x_zec > y_zec)          //compar numarul de zecimale ale celor 2
		a = x_zec;                  //si atribui valorile finale de zecimale
	else a = y_zec;
	cout << setprecision(a) << "w2 este: " << w2 << endl;   //astfel acesta imi afiseaza rezultatul in functie de numarul total de zecimale din fisier
	cout << setprecision(a) << "w1 este: " << w1 << endl;
}
