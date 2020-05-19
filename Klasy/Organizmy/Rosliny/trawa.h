#pragma once
#include "../roslina.h"

class Trawa : public Roslina {
public:
	Trawa(Swiat& swiat, pole_t pole);
	Trawa(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;

private:
	Organizm* potomek(pole_t pole) const override;
};

