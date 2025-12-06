#include "Organizm.h"

Organizm::Organizm(int sila, int inicjatywa, int x, int y, Swiat& swiat)
    : sila(sila), inicjatywa(inicjatywa), x(x), y(y), swiat(swiat), zyje(true) {
}

Organizm::~Organizm() = default;

int Organizm::getSila() const {
    return sila;
}

int Organizm::getInicjatywa() const {
    return inicjatywa;
}

int Organizm::getX() const {
    return x;
}

int Organizm::getY() const {
    return y;
}

bool Organizm::czyZyje() const {
    return zyje;
}

void Organizm::zwiekszSile(int wartosc) {
    sila += wartosc;
}

void Organizm::setPozycja(int nowyX, int nowyY) {
    x = nowyX;
    y = nowyY;
}

void Organizm::zabij() {
    zyje = false;
}
