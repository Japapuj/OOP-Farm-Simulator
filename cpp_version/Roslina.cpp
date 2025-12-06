#include "Roslina.h"
#include "Swiat.h"
#include <cstdlib>

Roslina::Roslina(int sila, int x, int y, Swiat& swiat)
    : Organizm(sila, 0, x, y, swiat) {
}

Roslina::~Roslina() = default;

void Roslina::akcja() {
    if (rand() % 5 == 4) {
        rozprzestrzenianie();
    }
}

void Roslina::kolizja(Organizm& inny) {
    swiat.dodajLog(getNazwa() + " na polu (" + std::to_string(x) + ", " + std::to_string(y) + ") zosta³ zjedzony przez " + inny.getNazwa());
    this->zabij();
}

void Roslina::rozprzestrzenianie() {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int nowyX = x + dx[i];
        int nowyY = y + dy[i];

        if (nowyX >= 0 && nowyX < swiat.getSzerokosc() &&
            nowyY >= 0 && nowyY < swiat.getWysokosc() &&
            swiat.czyPolePuste(nowyX, nowyY)) {
            zasiej(nowyX, nowyY);
            czyRozprzesrzeniono = true;
            return;
        }
    }
}
