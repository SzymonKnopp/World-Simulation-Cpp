#include "antylopa.h"
#include <iostream>

Antylopa::Antylopa(Swiat& swiat, pole_t pole) :
	Zwierze(swiat, pole) {

	_sila = 4;
	_inicjatywa = 4;
}
Antylopa::Antylopa(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Zwierze(swiat, pole, wiek, sila) {

	_inicjatywa = 4;
}

char Antylopa::gatunek() const {
	return 'A';
}

Organizm* Antylopa::potomek(pole_t pole) const {
	return new Antylopa(_swiat, pole);
}

void Antylopa::akcja() {
	if (!_jestZywy)
		return;
	kierunek_t kierunekRuchu = static_cast<kierunek_t>(rand() % 4);
	pole_t nowaPozycja = getMiejsceDwaPolaDalej(kierunekRuchu);
	testujPole(nowaPozycja);
}

bool Antylopa::kolizja(Organizm* atakujacy) {
	if (ucieczka())
		return true;
	return bronSie(atakujacy);
}


pole_t Antylopa::getMiejsceDwaPolaDalej(kierunek_t kierunek) const {
	pole_t pozycja;
	switch (kierunek) {
	case gora:
		pozycja.x = _pozycja.x;
		pozycja.y = _pozycja.y + 2;
		break;
	case prawo:
		pozycja.x = _pozycja.x + 2;
		pozycja.y = _pozycja.y;
		break;
	case dol:
		pozycja.x = _pozycja.x;
		pozycja.y = _pozycja.y - 2;
		break;
	default:
		pozycja.x = _pozycja.x - 2;
		pozycja.y = _pozycja.y;
		break;
	}
	return pozycja;
}

bool Antylopa::ucieczka() {
	if (rand() % 2 == 0)
		return false;
	pole_t nowePole;
	try {
		nowePole = znajdzWolnePoleDwaDalej();
		przesunSie(nowePole);
		std::cout << "Antylopa na polu (" << _pozycja.x << "," << _pozycja.y << ")" << " uciek³a od konfliktu" << std::endl;
		return true;
	}
	catch (...) {
		std::cout << "Antylopa na polu (" << _pozycja.x << "," << _pozycja.y << ") nie znalaz³a pola na które mo¿e uciec!" << std::endl;
		return false;
	}
	
}

pole_t Antylopa::znajdzWolnePoleDwaDalej() const {
	int kierunekInt = rand() % 4;
	for (int i = 0; i < 4; i++) {
		pole_t poleDlaDziecka = getMiejsceObok(static_cast<kierunek_t>(kierunekInt + i));
		if (_swiat.wWymiarachSwiata(poleDlaDziecka) &&
			_swiat.getOrganizmNaPolu(poleDlaDziecka) == nullptr)
			return poleDlaDziecka;
	}
	throw - 1; //nie znaleziono pola na ucieczkê
}
