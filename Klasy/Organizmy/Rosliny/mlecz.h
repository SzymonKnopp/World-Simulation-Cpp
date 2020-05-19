#pragma once
#include "../roslina.h"

class Mlecz : public Roslina {
public:
	Mlecz(Swiat& swiat, pole_t pole);
	Mlecz(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;
	void akcja() override;

private:
	Organizm* potomek(pole_t pole) const override;
};

