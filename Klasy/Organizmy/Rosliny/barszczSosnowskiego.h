#pragma once
#include "../roslina.h"

class BarszczSosnowskiego : public Roslina {
public:
	BarszczSosnowskiego(Swiat& swiat, pole_t pole);
	BarszczSosnowskiego(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;
	void akcja() override;

private:
	Organizm* potomek(pole_t pole) const override;
};

