#ifndef ANTYLOPA_H
#define ANTYLOPA_H

#include "Zwierze.h"

class Antylopa : public Zwierze {
public:
	Antylopa(int x, int y, Swiat& swiat);
	
	char rysowanie() const override;
	std::string getNazwa() const override;
	std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
	bool czyTenSamGatunek(Organizm& inny) const override;

	void akcja() override;
	void kolizja(Organizm& inny) override;
};

#endif // ANTYLOPA_H