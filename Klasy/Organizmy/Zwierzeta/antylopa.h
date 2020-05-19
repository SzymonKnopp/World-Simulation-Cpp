#pragma once
#include "../zwierze.h"

class Antylopa : public Zwierze {
public:
	Antylopa(Swiat& swiat, pole_t pole);
	Antylopa(Swiat& swiat, pole_t pole, int wiek, int sila);

	char gatunek() const override;
	void akcja() override;
	bool kolizja(Organizm* atakujacy) override;

private:
	Organizm* potomek(pole_t pole) const override;
	pole_t getMiejsceDwaPolaDalej(kierunek_t kierunek) const;
	bool ucieczka();
	pole_t znajdzWolnePoleDwaDalej() const;
};

