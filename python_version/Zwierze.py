from Organizm import Organizm
import random

class Zwierze(Organizm):
    def akcja(self):
        dx = [-1, 1, 0, 0]
        dy = [0, 0, -1, 1]
        kierunek = random.randint(0, 3)

        nowy_x = self.x + dx[kierunek]
        nowy_y = self.y + dy[kierunek]

        if 0 <= nowy_x < self.swiat.get_szerokosc() and 0 <= nowy_y < self.swiat.get_wysokosc():
            self.wykonaj_ruch(nowy_x, nowy_y)

    def kolizja(self, inny):
        if self.czy_ten_sam_gatunek(inny):
            for dx, dy in [(-1,0), (1,0), (0,-1), (0,1)]:
                nowy_x = self.x + dx
                nowy_y = self.y + dy
                if self.swiat.czy_pole_puste(nowy_x, nowy_y):
                    potomek = self.stworz_potomka(nowy_x, nowy_y)
                    self.swiat.dodaj_organizm(potomek)
                    self.swiat.dodaj_log(f"{self.get_nazwa()} rozmnaża się na polu ({nowy_x}, {nowy_y})")
                    return
        else:
            if inny.czy_odbil_atak(self):
                self.swiat.dodaj_log(f"{self.get_nazwa()} odbił się od {inny.get_nazwa()}")
                return
            elif self.sila >= inny.get_sila():
                if inny.get_nazwa() == "Guarana":
                    self.zwieksz_sile(3)
                    self.swiat.dodaj_log(f"{self.get_nazwa()} zjadł Guaranę i zyskał 3 siły.")
                else:
                    self.swiat.dodaj_log(f"{self.get_nazwa()} zabił {inny.get_nazwa()}")
                inny.zabij()
            else:
                self.swiat.dodaj_log(f"{self.get_nazwa()} został zabity przez {inny.get_nazwa()}")
                self.zabij()

    def wykonaj_ruch(self, nowy_x, nowy_y):
        cel = self.swiat.get_organizm(nowy_x, nowy_y)
        if cel == self:
            self.swiat.dodaj_log("Błąd: kolizja samego ze sobą!")
            return

        if cel is None or not cel.czy_zyje():
            self.swiat.aktualizuj_pole(self.x, self.y, '.')
            self.x = nowy_x
            self.y = nowy_y
            self.swiat.aktualizuj_pole(self.x, self.y, self.rysowanie())
            self.swiat.dodaj_log(f"{self.get_nazwa()} przesunął się na ({self.x}, {self.y})")
        else:
            self.kolizja(cel)
            if self.czy_zyje():
                self.swiat.aktualizuj_pole(self.x, self.y, '.')
                self.x = nowy_x
                self.y = nowy_y
                self.swiat.aktualizuj_pole(self.x, self.y, self.rysowanie())

    def czy_odbil_atak(self, inny):
        return False

    def czy_ten_sam_gatunek(self, inny):
        raise NotImplementedError()

    def stworz_potomka(self, nowy_x, nowy_y):
        raise NotImplementedError()
