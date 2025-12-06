#include "Czlowiek.h"
#include "Swiat.h"
#include <conio.h>

Czlowiek::Czlowiek(int x, int y, Swiat& swiat)
	: Zwierze(5, 4, x, y, swiat),
	cooldown(0), czasTrwania(0), aktywnaUmiejetosc(false), silaBazowa(sila), dx(0), dy(0){}

char Czlowiek::rysowanie() const {
	return 'H';
}

std::string Czlowiek::getNazwa() const {
	return "Czlowiek";
}

std::shared_ptr<Organizm> Czlowiek::stworzPotomka(int, int) {
	return nullptr;
}

void Czlowiek::akcja() {
	if (aktywnaUmiejetosc) {
		if (czasTrwania == 5) {
			sila = 10;
			swiat.dodajLog("Eliksir aktywowany! Sila Czlowieka wynosi 10.");
		}
		else {
			sila = silaBazowa + (5 - czasTrwania);
		}
		czasTrwania--;
		if (czasTrwania == 0) {
			aktywnaUmiejetosc = false;
			sila = silaBazowa;
			cooldown = 5;
			swiat.dodajLog("Eliksir wygasl.Sila czlowieka wrocila do " + std::to_string(silaBazowa));
		}
	}
	else if (cooldown > 0) {
		cooldown--;
	}
	if (dx != 0 || dy != 0) {
		int nowyX = x + dx;
		int nowyY = y + dy;
		if (nowyX >= 0 && nowyX < swiat.getSzerokosc() && nowyY >= 0 && nowyY < swiat.getWysokosc()) {
			wykonajRuch(nowyX, nowyY);
		}
	}
	dx = 0;
	dy = 0;
}

void Czlowiek::kolizja(Organizm& inny) {
	Zwierze::kolizja(inny);
}

void Czlowiek::aktywujUmiejetnosc() {
	if (!aktywnaUmiejetosc && cooldown == 0) {
		aktywnaUmiejetosc = true;
		czasTrwania = 5;
		swiat.dodajLog("Czlowiek wypil magiczny eliksir");
	}
	else {
		swiat.dodajLog("Eliksir niedostepny (cooldown: " + std::to_string(cooldown)+ ")");
	}
}


void Czlowiek::obsluzSterowanie(Czlowiek& czlowiek, int key) {
	switch (key)
	{
	case 72: dx = 0; dy = -1; break; //w gore
	case 80: dx = 0; dy = 1; break;  //w dol
	case 75: dx = -1; dy = 0; break; //w lewo
	case 77: dx = 1; dy = 0; break;  //w prawo
	case 'u': aktywujUmiejetnosc(); break;
	default: break;
	}
}

bool Czlowiek::czyTenSamGatunek(Organizm&) const {
	return false;
}

int Czlowiek::getCooldown() const {
	return cooldown;
}

bool Czlowiek::isAktywnaUmiejetosc() const {
	return aktywnaUmiejetosc;
}

int Czlowiek::getCzasTrwania() const {
	return czasTrwania;
}

void Czlowiek::setCooldown(int c) {
	cooldown = c;
}

void Czlowiek::setAktywnaUmiejetnosc(bool a) {
	aktywnaUmiejetosc = a;
}

void Czlowiek::setCzasTrwania(int t) {
	czasTrwania = t;
}