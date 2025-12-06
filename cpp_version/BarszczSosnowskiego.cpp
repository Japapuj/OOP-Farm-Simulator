#include "BarszczSosnowskiego.h"
#include "Zwierze.h"
#include "Swiat.h"

BarszczSosnowskiego::BarszczSosnowskiego(int x, int y, Swiat& swiat)
    : Roslina(10, x, y, swiat) {
}

char BarszczSosnowskiego::rysowanie() const { return 'B'; }
std::string BarszczSosnowskiego::getNazwa() const { return "BarszczSosnowskiego"; }
std::shared_ptr<Organizm> BarszczSosnowskiego::stworzPotomka(int x, int y) {
    return std::make_shared<BarszczSosnowskiego>(x, y, swiat);
}

void BarszczSosnowskiego::akcja() {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        Organizm* org = swiat.getOrganizm(nx, ny);
        if (org && org->czyZyje() && dynamic_cast<Zwierze*>(org) &&
            org->getNazwa() != "CyberOwca") {
            org->zabij();
            swiat.dodajLog(getNazwa() + " zabi³ " + org->getNazwa() + " w s¹siedztwie.");
        }
    }

    Roslina::akcja();
}

void BarszczSosnowskiego::kolizja(Organizm& inny) {
    if (inny.getNazwa() != "CyberOwca") {
        inny.zabij();
    }
    this->zabij();
    swiat.dodajLog(inny.getNazwa() + " zjad³ Barszcz Sosnowskiego i zgin¹³.");
}

void BarszczSosnowskiego::zasiej(int nowyX, int nowyY) {
    swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
}