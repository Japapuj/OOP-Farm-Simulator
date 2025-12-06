#ifndef WILCZEJAGODY_H
#define WILCZEJAGODY_H

#include "Roslina.h"

class WilczeJagody : public Roslina {
public:
    WilczeJagody(int x, int y, Swiat& swiat);
    char rysowanie() const override;
    std::string getNazwa() const override;
    std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) override;
    void kolizja(Organizm& inny) override;
protected:
    void zasiej(int nowyX, int nowyY) override;
};

#endif
