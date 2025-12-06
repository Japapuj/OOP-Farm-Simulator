#ifndef MLECZ_H
#define MLECZ_H

#include "Roslina.h"

class Mlecz : public Roslina {
public:
    Mlecz(int x, int y, Swiat& swiat);
    char rysowanie() const override;
    std::string getNazwa() const override;
    std::shared_ptr<Organizm> stworzPotomka(int, int) override;
    void akcja() override;
protected:
    void zasiej(int nowyX, int nowyY) override;
};

#endif
