#include "zwierze.h"
#include <iostream>

Zwierze::Zwierze(Swiat& swiat, pole_t pole) : 
	Organizm(swiat, pole) {
}
Zwierze::Zwierze(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Organizm(swiat, pole, wiek, sila) {
}

void Zwierze::akcja() {
	if (!_jestZywy)
		return;
	_wiek++;
	kierunek_t kierunekRuchu = static_cast<kierunek_t>(rand() % 4);
	pole_t nowaPozycja = getMiejsceObok(kierunekRuchu);
	testujPole(nowaPozycja);
}


void Zwierze::testujPole(pole_t pole){
	if (!_swiat.wWymiarachSwiata(pole))
		return;

	Organizm* naPolu = _swiat.getOrganizmNaPolu(pole);
	if (naPolu == nullptr) {
		przesunSie(pole);
		return;
	}
	if (naPolu->gatunek() == this->gatunek()) {
		if(_wiek >= 5)
			rozmnozSie();
	}
	else
		atakuj(pole);
}

void Zwierze::przesunSie(pole_t nowaPozycja) {
	_swiat.wyszyscPole(_pozycja);
	_pozycja = nowaPozycja;
	_swiat.setOrganizmNaPolu(this, nowaPozycja);
}


void Zwierze::atakuj(pole_t pole) {
	Organizm* przeciwnik = _swiat.getOrganizmNaPolu(pole);
	bool wygral = przeciwnik->kolizja(this);
	if (wygral) {
		przeciwnik = _swiat.getOrganizmNaPolu(pole);
		if (przeciwnik == nullptr)
			przesunSie(pole);
	}
	else {
		zgin();
	}
}

Organizm* Zwierze::potomek(pole_t pole) const {
	throw - 1; //spr�bowano stworzy� potomka niew�a�ciwego gatunku
}

void Zwierze::rozmnozSie() const{
	pole_t pozycjaDziecka;
	try {
		pozycjaDziecka = znajdzMiejsceDlaDziecka();
	}
	catch (...){
		std::cout << "Zwierz� na (" << _pozycja.x << "," << _pozycja.y << ") pr�buje si� rozmno�y�, ale brakuje miejsca na m�ode." << std::endl;
		return;
	}
	try {
		_swiat.dodajOrganizm(potomek(pozycjaDziecka), pozycjaDziecka);
	}
	catch (...) {
		std::cout << "Na polu (" << _pozycja.x << "," << _pozycja.y << ") dosz�o do pr�by rozmno�enia nieobs�ugiwanego gatunku!." << std::endl;
		return;
	}
	std::cout << "Na polu (" << _pozycja.x << "," << _pozycja.y << ") narodzi�o si� nowe zwierz�." << std::endl;
}

pole_t Zwierze::znajdzMiejsceDlaDziecka() const throw (int){
	int kierunekInt = rand() % 4;
	for (int i = 0; i < 4; i++) {
		pole_t poleDlaDziecka = getMiejsceObok(static_cast<kierunek_t>(kierunekInt + i));
		if (_swiat.wWymiarachSwiata(poleDlaDziecka) &&
			_swiat.getOrganizmNaPolu(poleDlaDziecka) == nullptr)
			return poleDlaDziecka;
	}
	throw -1; //nie znaleziono miejsca dla dziecka
}
