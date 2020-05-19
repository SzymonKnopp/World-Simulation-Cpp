#pragma once
#include "../zwierze.h"

class Lis : public Zwierze {
public:
	Lis(Swiat& swiat, pole_t pole);
	Lis(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;
	void atakuj(pole_t pole) override;

private:
	Organizm* potomek(pole_t pole) const override;
};

