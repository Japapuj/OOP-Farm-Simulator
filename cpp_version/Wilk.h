#ifndef WILK_H
#define WILK_H

#include "Zwierze.h"

class Wilk : public Zwierze {
public:
    Wilk(int x, int y, Swiat& swiat);

    char rysowanie() const override;
    bool czyTenSamGatunek(Organizm& inny) const override;
    std::string getNazwa() const override;
    std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
};

#endif // WILK_H
