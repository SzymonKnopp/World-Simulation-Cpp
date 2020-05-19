#include <iostream>
#include <ctime>
#include "Klasy/kontroler.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "polish");
	srand(time(NULL));

	Kontroler kontroler;

	cout << "1. Stworzenie nowej symulacji" << endl << "2. Wczytanie symulacji z pliku" << endl;
	int opcja;
	cin >> opcja;

	if (opcja == 2)
		kontroler.wczytajSwiat();
	else
		kontroler.przygotujSwiat();
	kontroler.przeprowadzSymulacje();

	return 0;
}