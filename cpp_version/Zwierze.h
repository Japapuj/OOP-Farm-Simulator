#ifndef ZWIERZE_H
#define ZWIERZE_H

#include "Organizm.h"

class Zwierze : public Organizm {
public:
    Zwierze(int sila, int inicjatywa, int x, int y, Swiat& swiat);
    virtual ~Zwierze();

    void akcja() override;
    void kolizja(Organizm& inny) override;

    virtual bool czyOdbilAtak(Organizm& inny) const override { return false; }
    virtual std::string getNazwa() const override = 0;
    virtual char rysowanie() const override = 0;
    virtual bool czyTenSamGatunek(Organizm& inny) const = 0;

protected:
    void wykonajRuch(int nowyX, int nowyY);

    virtual std::shared_ptr<Organizm> stworzPotomka(int nowyX, int nowyY) = 0;
};

#endif // ZWIERZE_H
