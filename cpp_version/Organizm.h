#ifndef ORGANIZM_H
#define ORGANIZM_H

#include <iostream>
#include <string>

class Swiat;

class Organizm {
protected:
    int sila;
    int inicjatywa;
    int x, y;
    Swiat& swiat;
    bool zyje;
public:
    Organizm(int sila, int inicjatywa, int x, int y, Swiat& swiat);
    virtual ~Organizm();

    virtual void akcja() = 0;
    virtual void kolizja(Organizm& inny) = 0;
	virtual bool czyOdbilAtak(Organizm& inny) const { return false; }
    virtual char rysowanie() const = 0;
    virtual std::string getNazwa() const = 0;

    bool nowoNarodzony=false;
    int getSila() const;
    int getInicjatywa() const;
    int getX() const;
    int getY() const;
    bool czyZyje() const;
    void zwiekszSile(int wartosc);

    void setPozycja(int nowyX, int nowyY);
    void zabij();
};

#endif
