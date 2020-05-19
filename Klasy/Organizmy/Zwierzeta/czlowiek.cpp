#include "czlowiek.h"
#include <iostream>

#pragma warning(disable:4996)

#define DLUGOSC_ZDOLNOSCI 5
#define GORA 72
#define DOL 80
#define LEWO 75
#define PRAWO 77

Czlowiek::Czlowiek(Swiat& swiat, pole_t pole) :
	Zwierze(swiat, pole) {

	_sila = 5;
	_inicjatywa = 4;
	_specjalnaZdolnosc = false;
	_timerZdolnosci = 0;
	_input = NULL;
}
Czlowiek::Czlowiek(Swiat& swiat, pole_t pole, int wiek, int sila, bool specjalnaZdolnosc, int timerZdolnosci) :
	Zwierze(swiat, pole, wiek, sila) {

	_inicjatywa = 4;
	_specjalnaZdolnosc = specjalnaZdolnosc;
	_timerZdolnosci = timerZdolnosci;
	_input = NULL;
}

char Czlowiek::gatunek() const {
	return '@';
}

void Czlowiek::akcja() {
	if (!_jestZywy)
		return;
	ustawSpecjalnaZdolnosc();

	kierunek_t kierunekRuchu;
	switch (_input) {
	case GORA:
		kierunekRuchu = dol; // kierunek w osi y obrócony, bo rysowane od y=0 (u góry)
		break;
	case PRAWO:
		kierunekRuchu = prawo;
		break;
	case DOL:
		kierunekRuchu = gora;
		break;
	case LEWO:
		kierunekRuchu = lewo;
		break;
	default:
		return;
	}
	pole_t nowaPozycja = getMiejsceObok(kierunekRuchu);
	testujPole(nowaPozycja);
}

void Czlowiek::zgin() {
	if (_specjalnaZdolnosc)
		return;

	_jestZywy = false;
	_swiat.wyszyscPole(_pozycja);
	//_swiat.zabijOrganizm(this); // cz³owiek nie jest usuwany, ¿eby mo¿na by³o sprawdziæ warunek zakoñczenia
	std::cout << "Na polu (" << _pozycja.x << "," << _pozycja.y << ") zgin¹³ organizm." << std::endl;
}

int Czlowiek::getIleTurZdolnosci() {
	return _timerZdolnosci;
}

void Czlowiek::setInput(int input) {
	_input = input;
}

bool Czlowiek::czyZdolnoscAktywowana() {
	return _specjalnaZdolnosc;
}

std::string Czlowiek::eksport() const {
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
	organizm += ' ';
	if (_specjalnaZdolnosc)
		organizm += '1';
	else
		organizm += '0';
	organizm += ' ';
	itoa(_timerZdolnosci, bufor, 10);
	organizm += bufor;
	organizm += '\n';
	return organizm;
}

void Czlowiek::ustawSpecjalnaZdolnosc() {
	static bool cooldown = false;
	if (_timerZdolnosci > 0)
		_timerZdolnosci--;
	
	if (_timerZdolnosci == 0) {
		if (!cooldown && _specjalnaZdolnosc) {
			_timerZdolnosci = DLUGOSC_ZDOLNOSCI;
			_specjalnaZdolnosc = false;
			cooldown = true;
		}
		else if (cooldown) {
			cooldown = false;
		}
		else if (_input == ' ') {
			_timerZdolnosci = DLUGOSC_ZDOLNOSCI;
			_specjalnaZdolnosc = true;
		}
	}
}

void Czlowiek::atakuj(pole_t pole) {
	Organizm* przeciwnik = _swiat.getOrganizmNaPolu(pole);
	bool wygral = przeciwnik->kolizja(this);
	if (wygral) {
		przeciwnik = _swiat.getOrganizmNaPolu(pole);
		if (przeciwnik == nullptr)
			przesunSie(pole);
	}
	else {
		zgin();
	}
}

