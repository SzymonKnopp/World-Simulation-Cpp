#include "kontroler.h"
#include <iostream>
#include <conio.h>
#include <fstream>

#include "Organizmy/Zwierzeta/antylopa.h"
#include "Organizmy/Rosliny/barszczSosnowskiego.h"
#include "Organizmy/Zwierzeta/czlowiek.h"
#include "Organizmy/Rosliny/guarana.h"
#include "Organizmy/Zwierzeta/lis.h"
#include "Organizmy/Rosliny/mlecz.h"
#include "Organizmy/Zwierzeta/owca.h"
#include "Organizmy/Rosliny/trawa.h"
#include "Organizmy/Rosliny/wilczeJagody.h"
#include "Organizmy/Zwierzeta/wilk.h"
#include "Organizmy/Zwierzeta/zolw.h"

using namespace std;

Kontroler::~Kontroler() {
	delete _swiat;
}

void Kontroler::przygotujSwiat() {
	cout << "Podaj wymiar 'x' œwiata: ";
	cin >> _wymiarySwiata.x;
	cout << "Podaj wymiar 'y' œwiata: ";
	cin >> _wymiarySwiata.y;

	cout << "Podaj poziom zape³nienia œwiata organizmami <0,10>: ";
	cin >> _poziomZapelnieniaSwiata;
	system("cls");

	_swiat = new Swiat(_wymiarySwiata);

	zapelnijSwiat();
}

void Kontroler::wczytajSwiat() throw (int){
	cout << "Podaj nazwe zapisu (bez '.save'): ";
	string nazwa;
	cin >> nazwa;
	fstream plik;
	plik.open(nazwa + ".save", ios::in);
	if (!plik.is_open())
		throw -1;

	pole_t wymiary;
	int licznikTur;
	plik >> wymiary.x >> wymiary.y >> licznikTur;
	_swiat = new Swiat(wymiary, licznikTur);
	wczytajOrganizmy(plik);
}

void Kontroler::przeprowadzSymulacje() {
	cout << "Autor: Szymon Knopp, 175550" << endl;
	_swiat->rysujSwiat();
	cout << endl << "\t -- Log wydarzeñ --" << endl;
	wypiszKomunikat();
	przetworzInput();
	system("cls");
	while (true) {
		cout << "Autor: Szymon Knopp, 175550" << endl;
		_swiat->rysujSwiat();
		cout << endl << "\t -- Log wydarzeñ --" << endl;
		_swiat->wykonajTure();
		_swiat->rysujSwiat();
		if (!_czlowiek->jestZywy()) {
			cout << endl << "Cz³owiek zgin¹³, koniec gry!" << endl;
			return;
		}
		wypiszKomunikat();
		przetworzInput();
		system("cls");
	}
}


void Kontroler::zapiszSwiat() const throw (int) {
	cout << "Podaj nazwê zapisu: ";
	string nazwa;
	cin >> nazwa;
	fstream plik;
	plik.open(nazwa + ".save", ios::out);
	if (!plik.is_open()) {
		cout << "Nie uda³o siê stworzyæ zapisu! Kontynuowanie symulacji..." << endl;
		throw - 1;
	}
	else {
		plik << _swiat->eksport() << "\nX";
		cout << "Zapisano swiat w pliku '" << nazwa << ".save'." << endl;
		plik.close();
	}
}

void Kontroler::zapelnijSwiat() {
	pole_t pozycjaCzlowieka = losowaPozycjaWSwiecie();
	Czlowiek* czlowiek = new Czlowiek(*_swiat, pozycjaCzlowieka);
	_czlowiek = czlowiek;
	_swiat->dodajOrganizm(czlowiek, pozycjaCzlowieka);

	for (int y = 0; y < _wymiarySwiata.y; y++) {
		for (int x = 0; x < _wymiarySwiata.x; x++) {
			if (!(y == pozycjaCzlowieka.y && x == pozycjaCzlowieka.x) &&
				(rand() % 10) + 1 <= _poziomZapelnieniaSwiata)
					zapelnijPole({ x,y });
		}
	}
	_swiat->aktywujNoweOrganizmy();
}

pole_t Kontroler::losowaPozycjaWSwiecie() {
	pole_t pole;
	pole.x = rand() % _wymiarySwiata.x;
	pole.y = rand() % _wymiarySwiata.y;
	return pole;
}

void Kontroler::zapelnijPole(pole_t pole) {
	Organizm* organizm = losowyOrganizm(pole);
	_swiat->dodajOrganizm(organizm, pole);
}

Organizm* Kontroler::losowyOrganizm(pole_t pole) {
	const char* gatunki = "ABGLMOTJWZ";
	int wybrany = rand() % (strlen(gatunki) - 1);
	return nowyOrganizm(gatunki[wybrany], pole);
}

void Kontroler::wypiszKomunikat() const{
	if (_czlowiek->czyZdolnoscAktywowana())
		cout << endl << "Nieœmiertelnoœæ aktywna jeszcze przez " << _czlowiek->getIleTurZdolnosci() << " tur." << endl
		<< "Strza³ki - ruch cz³owiekiem | s - zapisanie œwiata" << endl;
	else
		cout << endl << "Strza³ki - ruch cz³owiekiem | spacja - nieœmiertelnoœæ | s - zapisanie œwiata" << endl;
	if (_czlowiek->czyZdolnoscAktywowana())
		cout << "AKTWYNA NIEŒMIERTELNOŒÆ" << endl;
}

void Kontroler::przetworzInput() const {
	_getch();
	char input = _getch();
	if (input == 's') {
		zapiszSwiat();
		wypiszKomunikat();
		przetworzInput();
	}
	else {
		_czlowiek->setInput(input);
	}
}

void Kontroler::wczytajOrganizmy(fstream& plik) {
	while (true) {
		char gatunek;
		plik >> gatunek;
		if (gatunek == 'X')
			break;

		pole_t pozycja;
		int wiek, sila;
		plik >> pozycja.x >> pozycja.y >> wiek >> sila;
		if(gatunek == '@'){ //cz³owiek
			Czlowiek* czlowiek;
			int specjalnaZdolnoscInt, timerZdolnosci;
			plik >> specjalnaZdolnoscInt >> timerZdolnosci;
			bool specjalnaZdolnosc = specjalnaZdolnoscInt == 1 ? true : false;
			czlowiek = new Czlowiek(*_swiat, pozycja, wiek, sila, specjalnaZdolnosc, timerZdolnosci);
			_czlowiek = czlowiek;
			_swiat->dodajOrganizm(czlowiek, pozycja);
		}
		else {
			Organizm* organizm;
			organizm = nowyOrganizm(gatunek, pozycja, wiek, sila);
			_swiat->dodajOrganizm(organizm, pozycja);
		}
	}
}

Organizm* Kontroler::nowyOrganizm(char gatunek, pole_t pole) const {
	switch (gatunek) {
	case 'A':
		return new Antylopa(*_swiat, pole);
	case 'B':
		return new BarszczSosnowskiego(*_swiat, pole);
	case 'G':
		return new Guarana(*_swiat, pole);
	case 'L':
		return new Lis(*_swiat, pole);
	case 'M':
		return new Mlecz(*_swiat, pole);
	case 'O':
		return new Owca(*_swiat, pole);
	case 'T':
		return new Trawa(*_swiat, pole);
	case 'J':
		return new WilczeJagody(*_swiat, pole);
	case 'W':
		return new Wilk(*_swiat, pole);
	case 'Z':
		return new Zolw(*_swiat, pole);
	default:
		return nullptr;
	}
}

Organizm* Kontroler::nowyOrganizm(char gatunek, pole_t pole, int wiek, int sila) const {
	switch (gatunek) {
	case 'A':
		return new Antylopa(*_swiat, pole, wiek, sila);
	case 'B':
		return new BarszczSosnowskiego(*_swiat, pole, wiek, sila);
	case 'G':
		return new Guarana(*_swiat, pole, wiek, sila);
	case 'L':
		return new Lis(*_swiat, pole, wiek, sila);
	case 'M':
		return new Mlecz(*_swiat, pole, wiek, sila);
	case 'O':
		return new Owca(*_swiat, pole, wiek, sila);
	case 'T':
		return new Trawa(*_swiat, pole, wiek, sila);
	case 'J':
		return new WilczeJagody(*_swiat, pole, wiek, sila);
	case 'W':
		return new Wilk(*_swiat, pole, wiek, sila);
	case 'Z':
		return new Zolw(*_swiat, pole, wiek, sila);
	default:
		return nullptr;
	}
}

