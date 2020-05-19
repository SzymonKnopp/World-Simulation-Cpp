#include "wilk.h"
#include <iostream>

Wilk::Wilk(Swiat& swiat, pole_t pole) :
	Zwierze(swiat, pole) {
	
	_sila = 9;
	_inicjatywa = 5;
}
Wilk::Wilk(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Zwierze(swiat, pole, wiek, sila) {

	_inicjatywa = 5;
}

char Wilk::gatunek() const {
	return 'W';
}

Organizm* Wilk::potomek(pole_t pole) const
{
	return new Wilk(_swiat, pole);
}


