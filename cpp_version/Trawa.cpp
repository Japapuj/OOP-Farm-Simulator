#include "Trawa.h"
#include "Swiat.h"

Trawa::Trawa(int x, int y, Swiat& swiat)
    : Roslina(0, x, y, swiat) {
}

char Trawa::rysowanie() const { return 'T'; }

std::string Trawa::getNazwa() const { return "Trawa"; }

std::shared_ptr<Organizm> Trawa::stworzPotomka(int x, int y) {
    return std::make_shared<Trawa>(x, y, swiat);
}

void Trawa::zasiej(int nowyX, int nowyY) {
    swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
}
