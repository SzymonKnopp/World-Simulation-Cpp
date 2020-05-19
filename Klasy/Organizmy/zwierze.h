#pragma once
#include "../organizm.h"

class Zwierze : public Organizm {
public:
	Zwierze(Swiat& swiat, pole_t pole);
	Zwierze(Swiat& swiat, pole_t pole, int wiek, int sila);

	virtual char gatunek() const override = 0;

	virtual void akcja() override;

protected:
	void testujPole(pole_t pole);
	void przesunSie(pole_t nowaPozycja);

private:
	virtual void atakuj(pole_t pole);
	virtual Organizm* potomek(pole_t pole) const throw (int);
	void rozmnozSie() const;
	pole_t znajdzMiejsceDlaDziecka() const throw (int);
};

