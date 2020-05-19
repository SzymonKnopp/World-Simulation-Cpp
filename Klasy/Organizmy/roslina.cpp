#include "roslina.h"
#include <iostream>

Roslina::Roslina(Swiat& swiat, pole_t pole) :
	Organizm(swiat, pole) {
}
Roslina::Roslina(Swiat& swiat, pole_t pole, int wiek, int sila) :
	Organizm(swiat, pole, wiek, sila) {
}

void Roslina::akcja() {
	_wiek++;
	rozprzestrzenSie();
}

void Roslina::rozprzestrzenSie() const {
	if (rand() % 20 == 0) {
		kierunek_t kierunek = static_cast<kierunek_t>(rand() % 4);
		pole_t pole = getMiejsceObok(kierunek);
		if (!_swiat.wWymiarachSwiata(pole))
			return;
		Organizm* organizm = _swiat.getOrganizmNaPolu(pole);
		if (organizm == nullptr) {
			_swiat.dodajOrganizm(potomek(pole), pole);
			std::cout << "Ro�lina na polu (" << _pozycja.x << "," << _pozycja.y << ") rozprzestrzeni�a si�." << std::endl;
		}
		else
			std::cout << "Ro�lina na polu (" << _pozycja.x << "," << _pozycja.y << ") pr�bowa�a si� rozprzestrzeni�, ale wybrane miejsce by�o zaj�te." << std::endl;
	}
}

Organizm* Roslina::potomek(pole_t pole) const throw (int) {
	throw - 1; //spr�bowano stworzy� potomka niew�a�ciwego gatunku
}
