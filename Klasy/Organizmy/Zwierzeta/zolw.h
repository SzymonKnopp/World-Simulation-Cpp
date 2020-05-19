#pragma once
#include "../zwierze.h"

class Zolw : public Zwierze {
public:
	Zolw(Swiat& swiat, pole_t pole);
	Zolw(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;
	void akcja() override;
	bool kolizja(Organizm* atakujacy) override;

private:
	Organizm* potomek(pole_t pole) const override;
};