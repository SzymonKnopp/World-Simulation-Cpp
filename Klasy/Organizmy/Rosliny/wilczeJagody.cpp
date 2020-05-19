#include "wilczeJagody.h"
#include <iostream>

WilczeJagody::WilczeJagody(Swiat& swiat, pole_t pole) :
	Roslina(swiat, pole) {

	_sila = 99;
}
WilczeJagody::WilczeJagody(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Roslina(swiat, pole, wiek, sila) {
}

char WilczeJagody::gatunek() const {
	return 'J';
}

Organizm* WilczeJagody::potomek(pole_t pole) const {
	return new WilczeJagody(_swiat, pole);
}
