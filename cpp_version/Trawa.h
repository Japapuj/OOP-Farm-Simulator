#ifndef TRAWA_H
#define TRAWA_H

#include "Roslina.h"

class Trawa : public Roslina {
public:
    Trawa(int x, int y, Swiat& swiat);
    char rysowanie() const override;
    std::string getNazwa() const override;
    std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;

protected:
    void zasiej(int nowyX, int nowyY) override;
};

#endif
