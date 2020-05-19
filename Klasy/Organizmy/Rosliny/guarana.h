#pragma once
#include "../roslina.h"

class Guarana : public Roslina {
public:
	Guarana(Swiat& swiat, pole_t pole);
	Guarana(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;
	bool kolizja(Organizm* atakujacy) override;

private:
	Organizm* potomek(pole_t pole) const override;
};

