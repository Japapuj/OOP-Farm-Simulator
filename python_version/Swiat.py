from Czlowiek import Czlowiek
from Wilk import Wilk
from Trawa import Trawa
# + inne do dodania później
import random

class Swiat:
    def __init__(self, szerokosc, wysokosc):
        self.szerokosc = szerokosc
        self.wysokosc = wysokosc
        self.plansza = [['.' for _ in range(szerokosc)] for _ in range(wysokosc)]
        self.organizmy = []
        self.logi = []
        self.wiek = {}

    def dodaj_organizm(self, organizm):
        if organizm is None: return
        self.organizmy.append(organizm)
        self.plansza[organizm.get_y()][organizm.get_x()] = organizm.rysowanie()
        self.wiek[organizm] = 0
        organizm.nowo_narodzony = True
        self.dodaj_log(f"Dodano {organizm.get_nazwa()} na ({organizm.get_x()}, {organizm.get_y()})")

    def wykonaj_ture(self):
        for org in self.organizmy:
            self.wiek[org] += 1

        self.organizmy.sort(key=lambda o: (-o.get_inicjatywa(), -self.wiek[o]))

        for org in list(self.organizmy):
            if org.czy_zyje() and not org.nowo_narodzony:
                org.akcja()

        self.usun_martwe()
        self.odswiez_plansze()
        #self.rysuj()
        #self.wyswietl_logi()
        #self.logi.clear()
        for org in self.organizmy:
            org.nowo_narodzony = False

    def odswiez_plansze(self):
        self.plansza = [['.' for _ in range(self.szerokosc)] for _ in range(self.wysokosc)]
        for org in self.organizmy:
            if org.czy_zyje():
                self.plansza[org.get_y()][org.get_x()] = org.rysowanie()

    def rysuj(self):
        print("=== PLANSZA ===")
        #for w in self.plansza:
        #    print(' '.join(w))

    def dodaj_log(self, txt):
        self.logi.append(txt)

    def wyswietl_logi(self):
        print("=== LOGI ===")
        #for log in self.logi:
        #    print(log)

    def get_szerokosc(self):
        return self.szerokosc

    def get_wysokosc(self):
        return self.wysokosc

    def aktualizuj_pole(self, x, y, symbol):
        self.plansza[y][x] = symbol

    def czy_pole_puste(self, x, y):
        if 0 <= x < self.szerokosc and 0 <= y < self.wysokosc:
            return self.plansza[y][x] == '.'
        return False

    def get_organizm(self, x, y):
        for org in self.organizmy:
            if org.get_x() == x and org.get_y() == y and org.czy_zyje():
                return org
        return None

    def get_organizmy(self):
        return self.organizmy

    def usun_martwe(self):
        przed = len(self.organizmy)
        self.organizmy = [org for org in self.organizmy if org.czy_zyje()]
        po = len(self.organizmy)
        if przed != po:
            self.dodaj_log(f"Usunięto {przed - po} martwych organizmów")

    def znajdz_najblizszy_barszcz(self, x, y):
        najblizszy = None
        min_dystans = float('inf')
        for org in self.organizmy:
            if org.czy_zyje() and org.get_nazwa() == "BarszczSosnowskiego":
                dystans = abs(x - org.get_x()) + abs(y - org.get_y())
                if dystans < min_dystans:
                    min_dystans = dystans
                    najblizszy = org
        return najblizszy

