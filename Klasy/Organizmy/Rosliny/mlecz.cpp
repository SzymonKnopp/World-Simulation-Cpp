#include "mlecz.h"
#include <iostream>

Mlecz::Mlecz(Swiat& swiat, pole_t pole) :
	Roslina(swiat, pole) {
}
Mlecz::Mlecz(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Roslina(swiat, pole, wiek, sila) {
}

char Mlecz::gatunek() const {
	return 'M';
}

Organizm* Mlecz::potomek(pole_t pole) const {
	return new Mlecz(_swiat, pole);
}

void Mlecz::akcja() {
	_wiek++;
	for (int i = 0; i < 3; i++) {
		rozprzestrzenSie();
	}
}
