#include "CyberOwca.h"
#include "Swiat.h"

CyberOwca::CyberOwca(int x, int y, Swiat& swiat)
    : Zwierze(10, 4, x, y, swiat) {
}

char CyberOwca::rysowanie() const {
    return 'C';
}

std::string CyberOwca::getNazwa() const {
    return "CyberOwca";
}

std::shared_ptr<Organizm> CyberOwca::stworzPotomka(int nowyX, int nowyY) {
    return std::make_shared<CyberOwca>(nowyX, nowyY, swiat);
}

void CyberOwca::akcja() {
    Organizm* cel = swiat.znajdzNajblizszyBarszcz(x, y);
    if (cel != nullptr) {
        int dx = cel->getX() - x;
        int dy = cel->getY() - y;
        int krokX = (dx != 0) ? dx / abs(dx) : 0;
        int krokY = (dy != 0) ? dy / abs(dy) : 0;
        int nowyX = x + krokX;
        int nowyY = y + krokY;

        if (nowyY >= 0 && nowyX < swiat.getSzerokosc() && nowyY >= 0 && nowyY < swiat.getWysokosc()) {
            wykonajRuch(nowyX, nowyY);
        }
    }
    else {
        Zwierze::akcja();
    }
}

bool CyberOwca::czyTenSamGatunek(Organizm& inny) const {
    return dynamic_cast<const CyberOwca*>(&inny) != nullptr;
}
