#ifndef CZLOWIEK_H
#define CZLOWIEK_H

#include "Zwierze.h";

class Czlowiek : public Zwierze {
private:
	int cooldown;
	int czasTrwania;
	bool aktywnaUmiejetosc;
	int silaBazowa;
	int dx;
	int dy;

public:
	Czlowiek(int x, int y, Swiat& swiat);

	char rysowanie() const override;
	std::string getNazwa() const override;
	std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
	void akcja() override;
	void kolizja(Organizm& inny) override;
	bool czyTenSamGatunek(Organizm& inny) const override;

	void aktywujUmiejetnosc();

	void obsluzSterowanie(Czlowiek& czlowiek, int key);

	int getCooldown() const;
	bool isAktywnaUmiejetosc() const;
	int getCzasTrwania() const;

	void setCooldown(int c);
	void setAktywnaUmiejetnosc(bool a);
	void setCzasTrwania(int t);
};

#endif
