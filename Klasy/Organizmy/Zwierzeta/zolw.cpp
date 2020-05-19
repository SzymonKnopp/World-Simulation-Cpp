#include "zolw.h"
#include <iostream>

Zolw::Zolw(Swiat& swiat, pole_t pole) :
	Zwierze(swiat, pole) {
	
	_sila = 2;
	_inicjatywa = 1;
}
Zolw::Zolw(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Zwierze(swiat, pole, wiek, sila) {

	_inicjatywa = 1;
}

char Zolw::gatunek() const {
	return 'Z';
}

Organizm* Zolw::potomek(pole_t pole) const {
	return new Zolw(_swiat, pole);
}

void Zolw::akcja() {
	if (!_jestZywy)
		return;

	if (rand() % 4 != 0)
		return;

	kierunek_t kierunekRuchu = static_cast<kierunek_t>(rand() % 4);
	pole_t nowaPozycja = getMiejsceObok(kierunekRuchu);
	testujPole(nowaPozycja);
}

bool Zolw::kolizja(Organizm* atakujacy) {
	if (atakujacy->getSila() >= _sila) {
		if (atakujacy->getSila() < 5) {
			std::cout << "Atak na ¿ó³wia na polu (" << _pozycja.x << "," << _pozycja.y << ") zosta³ odparty." << std::endl;
			return true;
		}
		zgin();
		return true;
	}
	else return false;
}
