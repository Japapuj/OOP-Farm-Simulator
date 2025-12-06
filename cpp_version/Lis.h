#ifndef LIS_H
#define LIS_H

#include "Zwierze.h"

class Lis : public Zwierze {
public:
	Lis(int x, int y, Swiat& swiat);
	
	void akcja() override;
	char rysowanie() const override;
	std::string getNazwa() const override;
	std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
	bool czyTenSamGatunek(Organizm& inny) const override;
};

#endif // LIS_H