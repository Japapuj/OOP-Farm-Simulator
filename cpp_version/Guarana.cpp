#include "Guarana.h"
#include "Swiat.h"
Guarana::Guarana(int x, int y, Swiat& swiat)
    : Roslina(0, x, y, swiat) {
}

char Guarana::rysowanie() const { return 'G'; }
std::string Guarana::getNazwa() const { return "Guarana"; }
std::shared_ptr<Organizm> Guarana::stworzPotomka(int x, int y) {
    return std::make_shared<Guarana>(x, y, swiat);
}

void Guarana::kolizja(Organizm& inny) {
    inny.zwiekszSile(3);
    swiat.dodajLog(inny.getNazwa() + " zjad³ Guaranê i zyska³ +3 si³y.");
    this->zabij();
}

void Guarana::zasiej(int nowyX, int nowyY) {
    swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
}
