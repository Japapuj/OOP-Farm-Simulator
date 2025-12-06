#include "WilczeJagody.h"
#include "Swiat.h"

WilczeJagody::WilczeJagody(int x, int y, Swiat& swiat)
    : Roslina(99, x, y, swiat) {
}

char WilczeJagody::rysowanie() const { return 'J'; }
std::string WilczeJagody::getNazwa() const { return "WilczeJagody"; }
std::shared_ptr<Organizm> WilczeJagody::stworzPotomka(int x, int y) {
    return std::make_shared<WilczeJagody>(x, y, swiat);
}

void WilczeJagody::kolizja(Organizm& inny) {
    inny.zabij();
    this->zabij();
    swiat.dodajLog(inny.getNazwa() + " zjad³ Wilcze Jagody i zgin¹³.");
}

void WilczeJagody::zasiej(int nowyX, int nowyY) {
    swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
}
