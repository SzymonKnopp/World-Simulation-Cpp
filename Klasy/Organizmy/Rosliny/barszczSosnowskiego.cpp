#include "barszczSosnowskiego.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat& swiat, pole_t pole) :
	Roslina(swiat, pole) {

	_sila = 10;
}
BarszczSosnowskiego::BarszczSosnowskiego(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Roslina(swiat, pole, wiek, sila) {
}

char BarszczSosnowskiego::gatunek() const {
	return 'B';
}

Organizm* BarszczSosnowskiego::potomek(pole_t pole) const {
	return new BarszczSosnowskiego(_swiat, pole);
}

void BarszczSosnowskiego::akcja() {
	_wiek++;
	for (int i = 0; i < 4; i++) {
		kierunek_t kierunek = static_cast<kierunek_t>(i);
		pole_t poleObok = getMiejsceObok(kierunek);
		if (!_swiat.wWymiarachSwiata(poleObok))
			continue;
		Organizm* sasiad = _swiat.getOrganizmNaPolu(poleObok);
		if (sasiad != nullptr && sasiad->getSila() < _sila)
			sasiad->zgin();
	}
}
