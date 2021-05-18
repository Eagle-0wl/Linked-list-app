// Linked list

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string pavard; //pavarde;
int c; //batu dydis;

////////////////////////////////////////////////////////////////
class Pirkejas
{
public:
	string pav; //pavarde;
	int nr; //batu dydis;
	Pirkejas* pkitas; //kito saraso elemento adresas
	//-------------------------------------------------------------
	Pirkejas(string pav, int nr) : pav(pav), nr(nr), pkitas(NULL) //konstruktorius
	{ }
}; //klases pabaiga

////////////////////////////////////////////////////////////////
class Dekas
{
private:
	Pirkejas* pPr; //nuoroda i pirmaji saraso elementa
	Pirkejas* pPab; //nuoroda i paskutini saraso elementa

public:

	//-------------------------------------------------------------
	Dekas() : pPr(NULL), pPab(NULL) //konstruktorius
	{ }
	//-------------------------------------------------------------
	~Dekas() //destruktorius
	{
		// (istrina visus saraso elementus)
		Pirkejas* pEsamas = pPr; //pradedama nuo saraso pradzios
		while (pEsamas != NULL) //kol pasiekiama saraso pabaiga,
		{
			Pirkejas* pLaikinas = pEsamas; //atsimenamas salinamas saraso elementas
			pEsamas = pEsamas->pkitas; //pereinama prie kito saraso elemento
			delete pLaikinas; //istrinamas pries tai atsimintas
		}
	}
	//-------------------------------------------------------------
	bool arTuscias() //pasiimame true reiksme, jeigu sarasas yra tuscias
	{
		return pPr == NULL;
	}

	//-------------------------------------------------------------
	void iterptiGalas(string pav, int nr) //iterpimas saraso pabaigoje
	{
		Pirkejas* pNewLink = new Pirkejas(pav, nr); //sukuriamas naujas saraso elementas (arba duomenu struktura)

		if (arTuscias()) //jeigu sarasas yra tuscias,
			pPr = pNewLink; //first --> newLink, jeigu sarasas tuscias, naujam elementui priskiriama pradzios rodykle
		else
			pPab->pkitas = pNewLink; //old last --> newLink

		pPab = pNewLink; //newLink <-- last
	}
	//-------------------------------------------------------------
	void salintiPirma() //pasalinamas pirmasis elementas
	{

		//(darome prielaida, kad sarasas nera tuscias)
		Pirkejas* pLaikinas = pPr; //atsimenamas pirmasis saraso elementas
		cout << pPr->pav << " " << pPr->nr << endl;
		if (pPr->pkitas == NULL) //jeigu yra tik vienas elementas,
			pPab = NULL; //NULL <-- last, pabaigos rodyklei priskiriame NULL

		pPr = pPr->pkitas; //first --> old next
		delete pLaikinas; //istrinamas saraso elementas
	}
	//-------------------------------------------------------------
	void issaugotiPirmas(string& kpavard, int& kc)//issaugomas paskutinis saraso elementas
	{

		kpavard = pPr->pav;
		kc = pPr->nr;
	}
}; //klases Dekas pabaiga

////////////////////////////////////////////////////////////////

//meniu funkcija:
void Meniu(int& pas)
{
	char a;
	cout << "[1] - Naujas pirkejas" << endl;
	cout << "[2] - Aptarnauti pirkeja " << endl;
	cout << "[3] - Kiek pirkeju parduotuveje ir kiek lauke" << endl;
	cout << "[4] - Atlaisvinti eile lauke pries darbo pabaiga" << endl;
	cout << "[5] - Isjungti programa" << endl;
	do
	{
		a = getchar();
		if ((isdigit(a) == false) && (a != '\n'))
		{
			cout << "Privalote nurodyti skaiciu" << endl;
			cout << "Bandykite dar karta:" << endl;
			cout << "\n[1] - Naujas pirkejas" << endl;
			cout << "[2] - Aptarnauti pirkeja " << endl;
			cout << "[3] - Kiek pirkeju parduotuveje ir kiek lauke" << endl;
			cout << "[4] - Atlaisvinti eile lauke pries darbo pabaiga" << endl;
			cout << "[5] - Isjungti programa" << endl;
		}
	} while (isdigit(a) == false);
	pas = (int)a - 48;
}
//darbo su meniu funkcijos, pabaiga...


void pirkejo_duomenys()
{
	cout << "Iveskite pirkejo pavarde: ";
	cin >> pavard;
	cout << endl;
	cout << "Iveskite norima batu dydi: ";
	cin >> c;
	cout << endl;
}
//duomenu priskyrimas...

bool arYraTokiuBatu() //pasiimame true reiksme, jeigu sarase yra tokio dydzio batu
{
	ifstream in("sarasas.txt");
	int m = 0;
	int z;
	while (!in.eof())
	{
		in >> z;
		if (c == z)
		{
			m++;
			break;
		}
	}
	in.close();
	if (m > 0)
		return true;
	else
		return false;
}

int main()
{
	int pas;//pas - pasirinkimas
	int kc;	//batu numerio kopija
	string kpavard;	//pavardes kopija
	int eilp = 0, eill = 0;  //  eilp - kiek zmoniu yra eileje parduotuveje    eill - kiek zmoniu eileje lauke
	Dekas pard; //sukuriamas dekas eilei parduotuveje
	Dekas lauk; //sukuriamas dekas eilei  lauke
	do
	{
		Meniu(pas);
		switch (pas)
		{
		case 1:
		{
			cout << "Pasirinkimas [1]" << endl;
			pirkejo_duomenys();
			if (arYraTokiuBatu())
			{
				if (eilp < 10)
				{
					pard.iterptiGalas(pavard, c);
					eilp++;
				}
				else if (eilp >= 10)
				{
					lauk.iterptiGalas(pavard, c);
					eill++;
				}
			}
			else
				cout << "Pirkejo negalima pastatyti i eile nes nera pasirinkto dydzio batu" << endl;
			break;
		}
		case 2:
		{
			cout << "Pasirinkimas [2]" << endl;
			if (eilp > 0)
			{
				pard.salintiPirma();
				eilp--;
				if (eilp == 7 and eill >= 3)
				{
					for (int i = 0; i < 3; i++)
					{
						lauk.issaugotiPirmas(kpavard, kc);
						pard.iterptiGalas(kpavard, kc);
						lauk.salintiPirma();
						eilp++;
						eill--;
					}
				}
				else if (eilp == 7 and eill < 3)
				{
					for (int i = 0; i < eill; i++)
					{
						lauk.issaugotiPirmas(kpavard, kc);
						pard.iterptiGalas(kpavard, kc);
						lauk.salintiPirma();
						eilp++;
						eill--;
					}
				}
			}
			else
				cout << "Parduotuveje nera neivieno kliento" << endl;
			break;
		}
		case 3:
		{
			cout << "Pasirinkimas [3]" << endl;
			cout << "Parduotuveje yra " << eilp << " pirkeju" << endl;
			cout << "Lauke yra " << eill << " pirkeju" << endl;
			break;
		}
		case 4:
		{
			cout << "Pasirinkimas [4]" << endl;
			while (eill > 0)
			{
				lauk.issaugotiPirmas(kpavard, kc);
				pard.iterptiGalas(kpavard, kc);
				lauk.salintiPirma();
				eilp++;
				eill--;
			}
			break;
		}
		case 5:
		{
			cout << "Pasirinkimas [5]" << endl;
			pard.~Dekas();
			lauk.~Dekas();
			cout << "Programa isjungiama" << endl;
			break;
		}

		default:
		{
			cout << "Tokio pasirinkimo nera ..." << endl;
			break;
		}

		}
	} while (pas != 5);

	return 0;
}
