#pragma once
#include "../zwierze.h"

class Wilk : public Zwierze {
public:
	Wilk(Swiat& swiat, pole_t pole);
	Wilk(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;

private:
	Organizm* potomek(pole_t pole) const override;
};

