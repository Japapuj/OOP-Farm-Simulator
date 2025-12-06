#include "Antylopa.h"
#include "Swiat.h"
#include <cstdlib>

Antylopa::Antylopa(int x, int y, Swiat& swiat)
	:Zwierze(4, 4, x, y, swiat) {}

char Antylopa::rysowanie() const {
	return 'A';
}

std::string Antylopa::getNazwa() const {
	return "Antylopa";
}

std::shared_ptr<Organizm> Antylopa::stworzPotomka(int nowyX, int nowyY) {
	return std::make_shared<Antylopa>(nowyX, nowyY, swiat);
}

void Antylopa::akcja() {
	int dx[] = { -2, 2, 0, 0 };
	int dy[] = { 0, 0, -2, 2 };

	int kierunek = rand() % 4;
	int nowyX = x + dx[kierunek];
	int nowyY = y + dy[kierunek];

	if (nowyX >= 0 && nowyX < swiat.getSzerokosc() &&
		nowyY >= 0 && nowyY < swiat.getWysokosc()) {
		wykonajRuch(nowyX, nowyY);
	}
}

void Antylopa::kolizja(Organizm& inny) {

	if ((rand() % 2==0) && typeid(*this)==typeid(inny)) {
		int dx[] = { -1,1,0,0 };
		int dy[] = { 0,0,-1,1 };
		for (int i = 0; i < 4; i++) {
			int nowyX = x + dx[i];
			int nowyY = y + dy[i];
			if (nowyX >= 0 && nowyX < swiat.getSzerokosc() && nowyY >= 0 && nowyY < swiat.getSzerokosc()
				&& swiat.czyPolePuste(nowyX, nowyY)) {
				swiat.dodajLog(getNazwa() + " uciekla na polu (" + std::to_string(nowyX) + ", " + std::to_string(nowyY) + ")");
				x = nowyX;
				y = nowyY;
				return;
			}
		}
	}

	Zwierze::kolizja(inny);
}

bool Antylopa::czyTenSamGatunek(Organizm& inny) const {
	return dynamic_cast<const Antylopa*>(&inny) != nullptr;
}