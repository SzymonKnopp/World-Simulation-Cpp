#pragma once
#include "../organizm.h"

class Roslina : public Organizm {
public:
	Roslina(Swiat& swiat, pole_t pole);
	Roslina(Swiat& swiat, pole_t pole, int wiek, int sila);

	virtual char gatunek() const override = 0;

	virtual void akcja() override;

protected:
	void rozprzestrzenSie() const;

private:
	virtual Organizm* potomek(pole_t pole) const throw (int);
};

