#include "Zolw.h"
#include "Swiat.h"
#include <cstdlib>

Zolw::Zolw(int x, int y, Swiat& swiat)
    : Zwierze(2, 1, x, y, swiat)
{
}

char Zolw::rysowanie() const {
    return 'Z';
}

std::string Zolw::getNazwa() const {
    return "Zolw";
}

std::shared_ptr<Organizm> Zolw::stworzPotomka(int nowyX, int nowyY) {
    return std::make_shared<Zolw>(nowyX, nowyY, swiat);
}

bool Zolw::czyOdbilAtak(Organizm& atakujacy) const {
    return atakujacy.getSila() < 5;
}

void Zolw::akcja() {
    if (rand() % 100 < 25) {
        Zwierze::akcja();
    }
    else {
        swiat.dodajLog("Zolw pozostaje w miejscu na polu (" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")");
    }
}

bool Zolw::czyTenSamGatunek(Organizm& inny) const {
    return dynamic_cast<Zolw*>(&inny) != nullptr;
}
