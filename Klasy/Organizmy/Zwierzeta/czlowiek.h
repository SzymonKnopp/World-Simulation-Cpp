#pragma once
#include <string>
#include "../zwierze.h"

class Czlowiek : public Zwierze {
public:
	Czlowiek(Swiat& swiat, pole_t pole);
	Czlowiek(Swiat& swiat, pole_t pole, int wiek, int sila, bool specjalnaZdolnosc, int timerZdolnosci);

	char gatunek() const override;
	void akcja() override;
	void zgin() override;
	int getIleTurZdolnosci();
	void setInput(int input);
	bool czyZdolnoscAktywowana();
	std::string eksport() const override;

private:
	bool _specjalnaZdolnosc;
	int _timerZdolnosci;
	int _input;

	void ustawSpecjalnaZdolnosc();
	void atakuj(pole_t pole) override;
};

