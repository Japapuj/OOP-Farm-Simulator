#ifndef ZOLW_H
#define ZOLW_H

#include "Zwierze.h"

class Zolw : public Zwierze {
public:
    Zolw(int x, int y, Swiat& swiat);

    char rysowanie() const override;
    std::string getNazwa() const override;
    std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
    bool czyOdbilAtak(Organizm& atakujacy) const override;
    void akcja() override;
    bool czyTenSamGatunek(Organizm& inny) const override;
};

#endif
