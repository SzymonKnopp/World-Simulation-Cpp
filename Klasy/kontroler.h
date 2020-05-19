#pragma once
#include "swiat.h"
#include "Organizmy/Zwierzeta/czlowiek.h"
#include <fstream>

class Kontroler {
public:
	~Kontroler();

	void przygotujSwiat();
	void wczytajSwiat() throw (int);
	void przeprowadzSymulacje();

private:
	Swiat* _swiat;
	pole_t _wymiarySwiata;
	int _poziomZapelnieniaSwiata;;
	Czlowiek* _czlowiek;

	void zapiszSwiat() const throw (int);
	void zapelnijSwiat();
	pole_t losowaPozycjaWSwiecie();
	void zapelnijPole(pole_t pole);
	Organizm* losowyOrganizm(pole_t pole);
	void wypiszKomunikat() const;
	void przetworzInput() const;
	void wczytajOrganizmy(std::fstream& plik);
	Organizm* nowyOrganizm(char gatunek, pole_t pole) const;
	Organizm* nowyOrganizm(char gatunek, pole_t pole, int wiek, int sila) const;
};

