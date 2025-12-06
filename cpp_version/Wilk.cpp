#include "Wilk.h"

Wilk::Wilk(int x, int y, Swiat& swiat)
    : Zwierze(9, 5, x, y, swiat) {
} 

char Wilk::rysowanie() const {
    return 'W'; 
}

bool Wilk::czyTenSamGatunek(Organizm& inny) const {
    return dynamic_cast<const Wilk*>(&inny) != nullptr;
}


std::string Wilk::getNazwa() const {
    return "Wilk";
}

std::shared_ptr<Organizm> Wilk::stworzPotomka(int nowyX, int nowyY) {
    return std::make_shared<Wilk>(nowyX, nowyY, swiat);
}
