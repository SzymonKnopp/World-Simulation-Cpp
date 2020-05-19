#include "lis.h"
#include <iostream>

Lis::Lis(Swiat& swiat, pole_t pole) :
	Zwierze(swiat, pole) {
	
	_sila = 3;
	_inicjatywa = 7;
}
Lis::Lis(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Zwierze(swiat, pole, wiek ,sila) {

	_inicjatywa = 7;
}

char Lis::gatunek() const {
	return 'L';
}

Organizm* Lis::potomek(pole_t pole) const {
	return new Lis(_swiat, pole);
}

void Lis::atakuj(pole_t pole) {
	Organizm* przeciwnik = _swiat.getOrganizmNaPolu(pole);
	if (przeciwnik->getSila() > _sila) {
		std::cout << "Dobry wêch lisa na polu (" << _pozycja.x << "," << _pozycja.y << ") ostrzeg³ go przed zagro¿eniem na polu (" << pole.x << "," << pole.y << ")." << std::endl;
		return;
	}

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
