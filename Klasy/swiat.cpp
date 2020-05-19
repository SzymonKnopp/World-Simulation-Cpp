#include "swiat.h"
#include <iostream>
#include <string>
#include "organizm.h"
using namespace std;

#pragma warning(disable:4996)

#define MAX_INICJATYWA 7

Swiat::Swiat(pole_t wymiary) {
	_licznikTur = 0;
	_organizmy.clear();
	_noweOrganizmy.clear();
	_martweOrganizmy.clear();
	_wymiar = wymiary;
	alokujPola();
}
Swiat::Swiat(pole_t wymiary, int licznikTur) {
	_licznikTur = licznikTur;
	_organizmy.clear();
	_noweOrganizmy.clear();
	_martweOrganizmy.clear();
	_wymiar = wymiary;
	alokujPola();
}
Swiat::~Swiat() {
	for (int x = 0; x < _wymiar.x; x++) {
		//organizmy usuniête iteruj¹c po wektorze
		delete _pola[x];
	}
	delete _pola;
	for (auto& organizm : _organizmy)
		delete organizm;
}

void Swiat::wykonajTure() {
	_licznikTur++;
	cout << "Zaczyna siê " << _licznikTur << " tura." << endl;

	int inicjatywa = MAX_INICJATYWA;
	while (true) {
		int nastepnaInicjatywa = 0;
		for (auto& organizm : _organizmy)
			if (organizm != nullptr) {
				if (organizm->getInicjatywa() == inicjatywa && organizm->jestZywy())
					organizm->akcja();
				else if (organizm->getInicjatywa() > nastepnaInicjatywa &&
					organizm->getInicjatywa() < inicjatywa)
					nastepnaInicjatywa = organizm->getInicjatywa();
			}
		if (inicjatywa == 0)
			break;
		inicjatywa = nastepnaInicjatywa;
	}

	for (auto& organizmDoUsuniecia : _martweOrganizmy)
		for (auto& organizm : _organizmy)
			if (organizm == organizmDoUsuniecia) {
				delete organizm;
				organizm = nullptr;
			}
	_martweOrganizmy.clear();

	aktywujNoweOrganizmy();
}

void Swiat::rysujSwiat() const {
	const char pustePole = ' ';
	cout << endl << '\t';
	for (int x = 0; x < _wymiar.x + 1; x++)
		cout << "# ";
	cout << "#" << endl;
	for (int y = 0; y < _wymiar.y; y++) {
		cout << "\t# ";
		for (int x = 0; x < _wymiar.x; x++) {
			if (_pola[x][y] == nullptr)
				cout << pustePole;
			else _pola[x][y]->rysowanie();
			cout << " ";
		}
		cout << "#" << endl;
	}
	cout << '\t';
	for (int x = 0; x <  _wymiar.x + 1; x++)
		cout << "# ";
	cout << "#" << endl;
}

bool Swiat::wWymiarachSwiata(pole_t pole) const {
	if (pole.x >= 0 && pole.x < _wymiar.x &&
		pole.y >= 0 && pole.y < _wymiar.y)
		return true;
	else
		return false;
}

Organizm* Swiat::getOrganizmNaPolu(pole_t pole) const {
	return (_pola[pole.x][pole.y]);
}

void Swiat::setOrganizmNaPolu(Organizm* organizm, pole_t pole) {
	_pola[pole.x][pole.y] = organizm;
}

void Swiat::wyszyscPole(pole_t pole) {
	_pola[pole.x][pole.y] = nullptr;
}

void Swiat::zabijOrganizm(Organizm* organizm) {
	_martweOrganizmy.push_back(organizm);
}

void Swiat::dodajOrganizm(Organizm* organizm, pole_t pole) {
	setOrganizmNaPolu(organizm, pole);
	_noweOrganizmy.push_back(organizm);
}

void Swiat::aktywujNoweOrganizmy() {
	for (auto& organizm : _noweOrganizmy)
		_organizmy.push_back(organizm);
	_noweOrganizmy.clear();
}

string Swiat::eksport() const{
	string swiat;
	char bufor[100];
	itoa(_wymiar.x, bufor, 10);
	swiat += bufor;
	swiat += ' ';
	itoa(_wymiar.y, bufor, 10);
	swiat += bufor;
	swiat += ' ';
	itoa(_licznikTur, bufor, 10);
	swiat += bufor;
	swiat += '\n';
	swiat += '\n';

	for (auto& organizm : _organizmy) {
		if (organizm != nullptr) {
			swiat += organizm->eksport();
			swiat += '\n';
		}
	}
	return swiat;
}

void Swiat::alokujPola() {
	_pola = new Organizm * *[_wymiar.x];
	for (int x = 0; x < _wymiar.x; x++) {
		_pola[x] = new Organizm * [_wymiar.y];
		for (int y = 0; y < _wymiar.y; y++) {
			_pola[x][y] = nullptr;
		}
	}
}
