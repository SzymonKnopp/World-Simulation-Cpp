#pragma once
#include "../zwierze.h"
class Owca : public Zwierze {
public:
	Owca(Swiat& swiat, pole_t pole);
	Owca(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;

private:
	Organizm* potomek(pole_t pole) const override;
};

