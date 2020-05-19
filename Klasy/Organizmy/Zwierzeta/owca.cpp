#include "owca.h"
#include <iostream>

Owca::Owca(Swiat& swiat, pole_t pole) :
	Zwierze(swiat, pole) {

	_sila = 4;
	_inicjatywa = 4;
}
Owca::Owca(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Zwierze(swiat, pole, wiek, sila) {

	_inicjatywa = 4;
}

char Owca::gatunek() const {
	return 'O';
}

Organizm* Owca::potomek(pole_t pole) const {
	return new Owca(_swiat, pole);
}


