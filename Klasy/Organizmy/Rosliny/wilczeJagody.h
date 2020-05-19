#pragma once
#include "../roslina.h"

class WilczeJagody : public Roslina {
public:
	WilczeJagody(Swiat& swiat, pole_t pole);
	WilczeJagody(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;

private:
	Organizm* potomek(pole_t pole) const override;
};

