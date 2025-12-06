#include "Lis.h"
#include "Swiat.h"

Lis::Lis(int x, int y, Swiat& swiat)
	:Zwierze(3, 7, x, y, swiat) {}

char Lis::rysowanie() const {
	return 'L';
}

std::string Lis::getNazwa() const {
	return "Lis";	
}

std::shared_ptr<Organizm> Lis::stworzPotomka(int nowyX, int nowyY) {
	return std::make_shared<Lis>(nowyX, nowyY, swiat);
}

void Lis::akcja() {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	int kierunek = rand() % 4;
	int nowyX = x + dx[kierunek];
	int nowyY = y + dy[kierunek];
	Organizm* cel = swiat.getOrganizm(nowyX, nowyY);
	if (nowyX >= 0 && nowyX < swiat.getSzerokosc() && nowyY >= 0 && nowyY < swiat.getWysokosc()) {
		if (cel == nullptr || cel->getSila() <= this->getSila()) {
			Zwierze::wykonajRuch(nowyX, nowyY);
		}
		else {
			swiat.dodajLog(getNazwa() + " na polu (" + std::to_string(x) + ", " + std::to_string(y) + ") uniknal silniejszego organizmu");
		}
		return;
	}
}

bool Lis::czyTenSamGatunek(Organizm& inny) const {
	return dynamic_cast<const Lis*>(&inny) != nullptr;
}