#ifndef OWCA_H
#define OWCA_H

#include "Zwierze.h"

class Owca : public Zwierze {
public:
	Owca(int x, int y, Swiat& swiat);

	char rysowanie() const override;
	std::string getNazwa() const override;
	std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
	bool czyTenSamGatunek(Organizm& inny) const override;
};

#endif // OWCA_H