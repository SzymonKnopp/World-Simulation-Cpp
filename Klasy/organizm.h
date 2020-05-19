#pragma once
#include "swiat.h"
#include <string>

class Organizm {
public:
	Organizm(Swiat& swiat, pole_t pole);
	Organizm(Swiat& swiat, pole_t pole, int wiek, int sila);

	virtual char gatunek() const = 0;
	virtual void akcja() = 0;

	virtual bool kolizja(Organizm* atakujacy);
	virtual void zgin();
	virtual std::string eksport() const;
	void rysowanie() const;
	int getSila();
	void zwiekszSila();
	int getInicjatywa();
	bool jestZywy();

protected:
	enum kierunek_t { gora, prawo, dol, lewo };

	Swiat& _swiat;
	bool _jestZywy;
	pole_t _pozycja;
	int _wiek;
	int _sila;
	int _inicjatywa;

	pole_t getMiejsceObok(kierunek_t kierunek) const;
	bool bronSie(Organizm* atakujacy);

};