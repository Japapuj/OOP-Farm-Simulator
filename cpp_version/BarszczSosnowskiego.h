#ifndef BARSZCZSOSNOWSKIEGO_H
#define BARSZCZSOSNOWSKIEGO_H

#include "Roslina.h"

class BarszczSosnowskiego : public Roslina {
public:
    BarszczSosnowskiego(int x, int y, Swiat& swiat);
    char rysowanie() const override;
    std::string getNazwa() const override;
    std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
    void akcja() override;
    void kolizja(Organizm& inny) override;
protected:
    void zasiej(int nowyX, int nowyY) override;
};

#endif
