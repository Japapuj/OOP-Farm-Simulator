#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
#include <typeinfo>

Zwierze::Zwierze(int sila, int inicjatywa, int x, int y, Swiat& swiat)
    : Organizm(sila, inicjatywa, x, y, swiat) {
}

Zwierze::~Zwierze() = default;

void Zwierze::akcja() {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    int kierunek = rand() % 4;
    int nowyX = x + dx[kierunek];
    int nowyY = y + dy[kierunek];

    if (nowyX >= 0 && nowyX < swiat.getSzerokosc() &&
        nowyY >= 0 && nowyY < swiat.getWysokosc()) {
        wykonajRuch(nowyX, nowyY);
    }
}

void Zwierze::kolizja(Organizm& inny) {
    if (czyTenSamGatunek(inny)) {
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; i++) {
            int nowyX = x + dx[i];
			int nowyY = y + dy[i];
            if (nowyX >= 0 && nowyX < swiat.getSzerokosc() &&
                nowyY >= 0 && nowyY < swiat.getWysokosc() &&
                swiat.czyPolePuste(nowyX, nowyY)) {
                auto potomek = stworzPotomka(nowyX, nowyY);
                swiat.dodajOrganizm(potomek);
                swiat.dodajLog(getNazwa() + " rozmnaza sie na polu (" + std::to_string(x) + ", " + std::to_string(y) + ")");
                return;
            }
        }
    }
    else {
        if (inny.czyOdbilAtak(*this)) {
			swiat.dodajLog(getNazwa() + " na polu (" + std::to_string(x) + ", " + std::to_string(y) + ") odbil atak od " + inny.getNazwa());
			return;
        }
        else if (sila >= inny.getSila()) {
            if (inny.getNazwa() == "Guarana") {
                swiat.dodajLog(getNazwa() + " na polu (" + std::to_string(inny.getX()) + ", " + std::to_string(inny.getY()) + ") zabil " + inny.getNazwa()+" i zyskal +3 sily.");
                this->zwiekszSile(3);
            }
            else
            {
                swiat.dodajLog(getNazwa() + " na polu (" + std::to_string(inny.getX()) + ", " + std::to_string(inny.getY()) + ") zabil " + inny.getNazwa());
            }
            inny.zabij();
        }
        else {
            swiat.dodajLog(getNazwa() + " na polu (" + std::to_string(inny.getX()) + ", " + std::to_string(inny.getY()) + ") zostal zabity przez " + inny.getNazwa());
            this->zabij();
            swiat.usunMartweOrganizmy();
        }
    }
}

void Zwierze::wykonajRuch(int nowyX, int nowyY) {
    Organizm* cel = swiat.getOrganizm(nowyX, nowyY);
    if (cel == this) {
        swiat.dodajLog("Blad: proba kolizji samego ze soba!");
        return;
    }

	if (cel != nullptr && !cel->czyZyje()) {
		cel = nullptr;
	}
    if (cel == nullptr) {
        swiat.aktualizujPole(x, y, '.');
        x = nowyX;
        y = nowyY;
        swiat.aktualizujPole(x, y, rysowanie());
        swiat.dodajLog(getNazwa() + " przesunal sie na pole (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    }
    else {
        if(cel != nullptr && cel->czyZyje())
        kolizja(*cel);
        if (!this->czyZyje()) return;
        swiat.aktualizujPole(x, y, '.');
        x = nowyX;
        y = nowyY;
        swiat.aktualizujPole(x, y, rysowanie());
        swiat.dodajLog(getNazwa() + " przesunal sie na pole (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    }
}
