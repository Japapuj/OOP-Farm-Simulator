#include "Mlecz.h"
#include "Swiat.h"

Mlecz::Mlecz(int x, int y, Swiat& swiat) : Roslina(0, x, y, swiat) {}

char Mlecz::rysowanie() const { return 'M'; }
std::string Mlecz::getNazwa() const { return "Mlecz"; }

std::shared_ptr<Organizm> Mlecz::stworzPotomka(int x, int y) {
    return std::make_shared<Mlecz>(x, y, swiat);
}

void Mlecz::zasiej(int nowyX, int nowyY) {
    swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
}

void Mlecz::akcja() {
    int liczbaProb = 3;
    int sukcesy = 0;
    for (int i = 0; i < liczbaProb; ++i) {
        if (sukcesy > 0) break;
        this->czyRozprzesrzeniono = false;
        Roslina::akcja();
        if (this->czyRozprzesrzeniono)
            ++sukcesy;
    }
}
