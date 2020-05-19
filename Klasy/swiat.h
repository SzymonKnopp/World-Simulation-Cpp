#pragma once
#include <string>
#include <vector>
class Organizm;

struct pole_t {
	int x;
	int y;
};

class Swiat {
public:
	Swiat(pole_t wymiary);
	Swiat(pole_t wymiary, int licznikTur);
	~Swiat();

	void wykonajTure();
	void rysujSwiat() const;
	bool wWymiarachSwiata(pole_t pole) const;
	Organizm* getOrganizmNaPolu(pole_t pole) const;
	void setOrganizmNaPolu(Organizm* organizm, pole_t pole);
	void wyszyscPole(pole_t pole);
	void zabijOrganizm(Organizm* organizm);
	void dodajOrganizm(Organizm* organizm, pole_t pole);
	void aktywujNoweOrganizmy();
	std::string eksport() const;

private:
	int _licznikTur;
	std::vector<Organizm*> _organizmy;
	std::vector<Organizm*> _noweOrganizmy; //organizmy stworzone w turze, nieaktywne, do nastêpnej tury
	std::vector<Organizm*> _martweOrganizmy; //organizmy do usuniêcia
	Organizm*** _pola; //dwuwymiarowa tablica wskaŸników na organizmy w konkretnym polu
	pole_t _wymiar;

	void alokujPola();
};

