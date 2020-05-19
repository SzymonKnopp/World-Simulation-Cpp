#include "trawa.h"
#include <iostream>

Trawa::Trawa(Swiat& swiat, pole_t pole) :
	Roslina(swiat, pole) {
}
Trawa::Trawa(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Roslina(swiat, pole, wiek, sila) {
}

char Trawa::gatunek() const {
	return 'T';
}

Organizm* Trawa::potomek(pole_t pole) const {
	return new Trawa(_swiat, pole);
}

