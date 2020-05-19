#include "guarana.h"

Guarana::Guarana(Swiat& swiat, pole_t pole) :
	Roslina(swiat, pole) {
}
Guarana::Guarana(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Roslina(swiat, pole, wiek, sila) {
}

char Guarana::gatunek() const {
	return 'G';
}

Organizm* Guarana::potomek(pole_t pole) const {
	return new Guarana(_swiat, pole);
}

bool Guarana::kolizja(Organizm* atakujacy) {
	zgin();
	atakujacy->zwiekszSila();
	return true;
}
