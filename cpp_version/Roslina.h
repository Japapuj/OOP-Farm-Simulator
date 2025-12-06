#ifndef ROSLINA_H
#define ROSLINA_H

#include "Organizm.h"

class Roslina : public Organizm {
public:
    Roslina(int sila, int x, int y, Swiat& swiat);
    virtual ~Roslina();

    void akcja() override;
    void kolizja(Organizm& inny) override;

    virtual char rysowanie() const override = 0;
    virtual std::string getNazwa() const override = 0;
    virtual std::shared_ptr<Organizm> stworzPotomka(int x, int y) = 0;

protected:
    void rozprzestrzenianie();
    bool czyRozprzesrzeniono = false;
    virtual void zasiej(int nowyX, int nowyY) = 0;
};

#endif
