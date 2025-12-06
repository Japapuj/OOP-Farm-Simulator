#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

#include "Swiat.h"
#include "Zwierze.h"
#include "Roslina.h"
#include "Czlowiek.h"
#include "Trawa.h"
#include "Guarana.h"
#include "Zolw.h"
#include "Lis.h"
#include "Owca.h"
#include "Antylopa.h"
#include "CyberOwca.h"
#include "BarszczSosnowskiego.h"
#include "WilczeJagody.h"
#include "Mlecz.h"
#include "Wilk.h"

int main() {
    Swiat swiat(20, 20);
    std::shared_ptr<Czlowiek> czlowiek;
    std::cout << "Czy chcesz wczytac gre? (t/n): ";
    char wybor;
    std::cin >> wybor;
    std::cin.ignore();
    if (wybor == 't')
    {
        swiat.wczytajZPliku("save.txt");

        for (auto& org : swiat.getOrganizmy()) {
            if (std::shared_ptr<Czlowiek> znaleziony = std::dynamic_pointer_cast<Czlowiek>(org)) {
                czlowiek = znaleziony;
                break;
            }
        }
    }
    else {

        czlowiek = std::make_shared<Czlowiek>(10, 5, swiat);
        swiat.dodajOrganizm(czlowiek);
        swiat.dodajOrganizm(std::make_shared<Wilk>(10, 12, swiat));
        swiat.dodajOrganizm(std::make_shared<Wilk>(10, 13, swiat));
        swiat.dodajOrganizm(std::make_shared<Lis>(3, 15, swiat));
        swiat.dodajOrganizm(std::make_shared<Lis>(3, 16, swiat));
        swiat.dodajOrganizm(std::make_shared<Trawa>(0, 0, swiat));
        swiat.dodajOrganizm(std::make_shared<Guarana>(2, 2, swiat));
        swiat.dodajOrganizm(std::make_shared<Zolw>(5, 5, swiat));
        swiat.dodajOrganizm(std::make_shared<Owca>(6, 6, swiat));
        swiat.dodajOrganizm(std::make_shared<Antylopa>(8, 8, swiat));
        swiat.dodajOrganizm(std::make_shared<CyberOwca>(15, 7, swiat));
        swiat.dodajOrganizm(std::make_shared<WilczeJagody>(1, 1, swiat));
        swiat.dodajOrganizm(std::make_shared<BarszczSosnowskiego>(17, 4, swiat));
        swiat.dodajOrganizm(std::make_shared<Mlecz>(12, 6, swiat));
    }

    std::cout << "\nWykonaj ruch strzalkami lub [U] aktywuj umiejetnosc. Jestes H\n";
    swiat.wykonajTure();
    while (true) {
        int key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
        }

        if (key == 'z')
        {
            swiat.zapiszDoPliku("save.txt");
            continue;
        }

        if (key == 'q')
            break;

        czlowiek->obsluzSterowanie(*czlowiek, key);
        system("cls");
            swiat.wykonajTure();

        if (czlowiek->czyZyje() == false) {
            std::cout << "=============\n";
            std::cout << "| GAME OVER |\n";
            std::cout << "=============\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
