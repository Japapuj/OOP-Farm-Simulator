#include "Owca.h"

Owca::Owca(int x, int y, Swiat& swiat)
	:Zwierze(4, 4, x, y, swiat) {}

char Owca::rysowanie() const {
	return 'O';
}

std::string Owca::getNazwa() const {
	return "Owca";	
}

std::shared_ptr<Organizm> Owca::stworzPotomka(int nowyX, int nowyY) {
	return std::make_shared<Owca>(nowyX, nowyY, swiat);
}

bool Owca::czyTenSamGatunek(Organizm& inny) const {
	return dynamic_cast<const Owca*>(&inny) != nullptr;
}