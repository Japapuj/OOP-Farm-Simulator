#include "Swiat.h"
#include "Organizm.h"
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Lis.h"
#include "Antylopa.h"
#include "BarszczSosnowskiego.h"
#include "Cyberowca.h"
#include "Czlowiek.h"
#include "Guarana.h"
#include "Mlecz.h"
#include "Owca.h"
#include "Trawa.h"
#include "WilczeJagody.h"
#include "Wilk.h"
#include "Zolw.h"

Swiat::Swiat(int szerokosc, int wysokosc) : szerokosc(szerokosc), wysokosc(wysokosc) {
    plansza.resize(wysokosc, std::vector<char>(szerokosc, '.'));
}

void Swiat::dodajOrganizm(std::shared_ptr<Organizm> organizm) {
	if (organizm == nullptr) {
		std::cerr << "Nie mozna dodac pustego organizmu!" << std::endl;
		return;
	}
    organizmy.push_back(organizm);
    plansza[organizm->getY()][organizm->getX()] = organizm->rysowanie();
    wiekOrganizmow[organizm.get()] = 0;
    dodajLog("Dodano " + organizm->getNazwa() + " na pole (" + std::to_string(organizm->getX()) + ", " + std::to_string(organizm->getY()) + ")");
    organizm->nowoNarodzony = true;
}

void Swiat::wykonajTure() {
    for (auto& org : organizmy) {
        wiekOrganizmow[org.get()]++;
    }

    std::sort(organizmy.begin(), organizmy.end(), [this](const std::shared_ptr<Organizm>& a, const std::shared_ptr<Organizm>& b) {
        if (a->getInicjatywa() != b->getInicjatywa())
            return a->getInicjatywa() > b->getInicjatywa();
        return wiekOrganizmow[a.get()] > wiekOrganizmow[b.get()];
        });

    std::vector<std::shared_ptr<Organizm>> kopiaOrganizmow = organizmy;

    for (auto& organizm : kopiaOrganizmow) {
        if (organizm->czyZyje() && !organizm->nowoNarodzony) {
            organizm->akcja();
        }
    }

    if (organizmy.size() > (getSzerokosc()*getWysokosc()*2)) {
        std::cerr << "ZA DUZO ORGANIZMOW!\n";
        exit(1);
    }

    usunMartweOrganizmy();
    odswiezPlansze();
    rysujSwiat();
    wyswietlLogi();
    logi.clear();
    for (auto& org : organizmy) {
        org->nowoNarodzony = false;
    }
    return;
}


void Swiat::rysujSwiat() {
    std::cout << "\n=== PLANSZA ===\n";
    for (const auto& wiersz : plansza) {
        for (const auto& pole : wiersz) {
            std::cout << pole << " ";
        }
        std::cout << "\n";
    }
}

void Swiat::inicjalizujPlansze() {
    plansza.clear(); // wyczysc plansze
    plansza.resize(wysokosc, std::vector<char>(szerokosc, '.'));
}


Organizm* Swiat::znajdzNajblizszyBarszcz(int x, int y) const {
    Organizm* najblizszy = nullptr;
    int minDystans = INT_MAX;
    for (const auto& org : organizmy) {
        if (org->czyZyje() && org->getNazwa() == "BarszczSosnowskiego") {
            int dx = x - org->getX();
            int dy = y - org->getY();
            int dystans = abs(dx) + abs(dy);

            if (dystans < minDystans) {
                minDystans = dystans;
                najblizszy = org.get();
            }
        }
    }
    return najblizszy;
}


void Swiat::dodajLog(const std::string& log) {
    logi.push_back(log);
}

void Swiat::wyswietlLogi() const {
    std::cout << "\n=== LOGI ===\n";
    for (const auto& log : logi) {
        std::cout << log << "\n";
    }
}

int Swiat::getSzerokosc() const {
    return szerokosc;
}

int Swiat::getWysokosc() const {
    return wysokosc;
}

void Swiat::aktualizujPole(int x, int y, char symbol) {
    plansza[y][x] = symbol;
}

bool Swiat::czyPolePuste(int x, int y) const {
    return plansza[y][x] == '.';
}

Organizm* Swiat::getOrganizm(int x, int y) const {
    for (const auto& org : organizmy) {
        if (org->getX() == x && org->getY() == y && org->czyZyje()) {
            return org.get();
        }
    }
    return nullptr;
}


void Swiat::usunMartweOrganizmy() {
    size_t przed = organizmy.size();
    organizmy.erase(
        std::remove_if(organizmy.begin(), organizmy.end(),
            [](const std::shared_ptr<Organizm>& org) {
                return !org->czyZyje();
            }),
        organizmy.end());
    size_t po = organizmy.size();
    if (przed != po) {
        dodajLog("Usunietych organizmow: " + std::to_string(przed - po));
    }
}

void Swiat::odswiezPlansze() {
    for (auto& wiersz : plansza)
        std::fill(wiersz.begin(), wiersz.end(), '.');

    for (const auto& org : organizmy) {
        plansza[org->getY()][org->getX()] = org->rysowanie();
    }
}

void Swiat::zapiszDoPliku(const std::string& nazwaPliku) {

    std::ofstream plik(nazwaPliku);

    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku do zapisu.\n";
        return;
    }

    plik << getSzerokosc() << " " << getWysokosc() << "\n";

    for (auto& organizm : organizmy) {
        if (organizm->czyZyje()) {
            plik << organizm->getNazwa() << " "
                << organizm->getSila() << " "
                << organizm->getX() << " "
                << organizm->getY();

            if (Czlowiek* czlowiek = dynamic_cast<Czlowiek*>(organizm.get())) {
                plik << " cooldown:" << czlowiek->getCooldown()
                    << " aktywna:" << czlowiek->isAktywnaUmiejetosc()
                    << " czasTrwania:" << czlowiek->getCzasTrwania();
            }

            plik << "\n";
        }
    }

    plik.close();
    std::cout << "[Swiat] Stan gry zapisany do pliku: " << nazwaPliku << "\n";
}

void Swiat::wczytajZPliku(const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);

    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku do odczytu.\n";
        return;
    }

    organizmy.clear();
    plansza.clear();

    plik >> szerokosc >> wysokosc;
    inicjalizujPlansze();

    std::string linia;
    std::getline(plik, linia);

    while (std::getline(plik, linia)) {
        if (linia.empty()) continue;

        std::istringstream iss(linia);
        std::string nazwa;
        int sila, x, y;

        if (!(iss >> nazwa >> sila >> x >> y)) {
            std::cerr << "Blad formatu pliku: " << linia << std::endl;
            continue;
        }

        std::shared_ptr<Organizm> organizm = nullptr;

        if (nazwa == "Lis") organizm = std::make_shared<Lis>(x, y, *this);
        else if (nazwa == "Owca") organizm = std::make_shared<Owca>(x, y, *this);
        else if (nazwa == "Trawa") organizm = std::make_shared<Trawa>(x, y, *this);
        else if (nazwa == "Guarana") organizm = std::make_shared<Guarana>(x, y, *this);
        else if (nazwa == "Wilk") organizm = std::make_shared<Wilk>(x, y, *this);
        else if (nazwa == "Zolw") organizm = std::make_shared<Zolw>(x, y, *this);
        else if (nazwa == "Antylopa") organizm = std::make_shared<Antylopa>(x, y, *this);
        else if (nazwa == "CyberOwca") organizm = std::make_shared<CyberOwca>(x, y, *this);
        else if (nazwa == "Mlecz") organizm = std::make_shared<Mlecz>(x, y, *this);
        else if (nazwa == "WilczeJagody") organizm = std::make_shared<WilczeJagody>(x, y, *this);
        else if (nazwa == "BarszczSosnowskiego") organizm = std::make_shared<BarszczSosnowskiego>(x, y, *this);
        else if (nazwa == "Czlowiek") {
            auto czlowiek = std::make_shared<Czlowiek>(x, y, *this);

            std::string klucz;
            while (iss >> klucz) {
                if (klucz.find("cooldown:") == 0)
                    czlowiek->setCooldown(std::stoi(klucz.substr(9)));
                else if (klucz.find("aktywna:") == 0)
                    czlowiek->setAktywnaUmiejetnosc(std::stoi(klucz.substr(8)));
                else if (klucz.find("czasTrwania:") == 0)
                    czlowiek->setCzasTrwania(std::stoi(klucz.substr(12)));
            }

            organizm = czlowiek;
        }

        if (organizm != nullptr) {
            organizm->zwiekszSile(sila - organizm->getSila());
            dodajOrganizm(organizm);
        }
    }

    plik.close();
    std::cout << "[Swiat] Stan gry wczytany z pliku: " << nazwaPliku << "\n";
}