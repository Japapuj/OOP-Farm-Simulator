#ifndef CYBEROWCA_H
#define CYBEROWCA_H

#include "Zwierze.h"

class CyberOwca : public Zwierze {
public:
    CyberOwca(int x, int y, Swiat& swiat);

    char rysowanie() const override;
    std::string getNazwa() const override;
    std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
    void akcja() override;
    bool czyTenSamGatunek(Organizm& inny) const override;
};

#endif
