#ifndef SWIAT_H
#define SWIAT_H

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include "Czlowiek.h"

class Organizm;

class Swiat {
private:
    int szerokosc;
    int wysokosc;
    std::vector<std::vector<char>> plansza;
    std::vector<std::shared_ptr<Organizm>> organizmy;
    std::vector<std::string> logi;
    std::map<Organizm*, int> wiekOrganizmow;

    void odswiezPlansze();
    void inicjalizujPlansze();

public:
    Swiat(int szerokosc, int wysokosc);

    void dodajOrganizm(std::shared_ptr<Organizm> organizm);
    void wykonajTure();
    void rysujSwiat();

    Organizm* znajdzNajblizszyBarszcz(int x, int y) const;

    void dodajLog(const std::string& log);
    void wyswietlLogi() const;
    void usunMartweOrganizmy();

    int getSzerokosc() const;
    int getWysokosc() const;
    void aktualizujPole(int x, int y, char symbol);
    bool czyPolePuste(int x, int y) const;

    Organizm* getOrganizm(int x, int y) const;

    const std::vector<std::shared_ptr<Organizm>>& getOrganizmy() const { return organizmy; };

    void zapiszDoPliku(const std::string& nazwaPliku);
    void wczytajZPliku(const std::string& nazwaPliku);

};

#endif
