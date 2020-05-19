#include "organizm.h"
#include <iostream>
#include <string>

#pragma warning(disable:4996)

Organizm::Organizm(Swiat& swiat, pole_t pole) :
	_swiat(swiat) {
	_jestZywy = true;
	_pozycja = pole;
	_wiek = 0;
	_sila = 0;
	_inicjatywa = 0;
}
Organizm::Organizm(Swiat& swiat, pole_t pole, int wiek, int sila) :
	_swiat(swiat) {
	_jestZywy = true;
	_pozycja = pole;
	_wiek = wiek;
	_sila = sila;
	_inicjatywa = 0;
}

bool Organizm::kolizja(Organizm* atakujacy) {
	return bronSie(atakujacy);
}
bool Organizm::bronSie(Organizm* atakujacy) {
	if (atakujacy->_sila >= _sila) {
		zgin();
		return true;
	}
	else return false;
}

void Organizm::zgin() {
	_jestZywy = false;
	_swiat.wyszyscPole(_pozycja);
	_swiat.zabijOrganizm(this);
	std::cout << "Na polu (" << _pozycja.x << "," << _pozycja.y << ") zgin¹³ organizm." << std::endl;
}

std::string Organizm::eksport() const {
	std::string organizm;
	char bufor[100];
	organizm += gatunek();
	organizm += ' ';
	itoa(_pozycja.x, bufor, 10);
	organizm += bufor;
	organizm += ' ';
	itoa(_pozycja.y, bufor, 10);
	organizm += bufor;
	organizm += ' ';
	itoa(_wiek, bufor, 10);
	organizm += bufor;
	organizm += ' ';
	itoa(_sila, bufor, 10);
	organizm += bufor;
	return organizm;
}

void Organizm::rysowanie() const {
	std::cout << gatunek();
}

int Organizm::getSila() {
	return _sila;
}

void Organizm::zwiekszSila() {
	_sila += 3;
}

int Organizm::getInicjatywa() {
	return _inicjatywa;
}

bool Organizm::jestZywy() {
	return _jestZywy;
}

pole_t Organizm::getMiejsceObok(kierunek_t kierunek) const {
	pole_t pozycja;
	switch (kierunek) {
	case gora:
		pozycja.x = _pozycja.x;
		pozycja.y = _pozycja.y+1;
		break;
	case prawo:
		pozycja.x = _pozycja.x+1;
		pozycja.y = _pozycja.y;
		break;
	case dol:
		pozycja.x = _pozycja.x;
		pozycja.y = _pozycja.y-1;
		break;
	default:
		pozycja.x = _pozycja.x-1;
		pozycja.y = _pozycja.y;
		break;
	}
	return pozycja;
}
