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
			std::cout << "Roœlina na polu (" << _pozycja.x << "," << _pozycja.y << ") rozprzestrzeni³a siê." << std::endl;
		}
		else
			std::cout << "Roœlina na polu (" << _pozycja.x << "," << _pozycja.y << ") próbowa³a siê rozprzestrzeniæ, ale wybrane miejsce by³o zajête." << std::endl;
	}
}

Organizm* Roslina::potomek(pole_t pole) const throw (int) {
	throw - 1; //spróbowano stworzyæ potomka niew³aœciwego gatunku
}
