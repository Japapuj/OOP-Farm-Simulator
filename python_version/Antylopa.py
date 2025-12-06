from Zwierze import Zwierze
import random

class Antylopa(Zwierze):
    def __init__(self, x, y, swiat):
        super().__init__(4, 4, x, y, swiat)

    def rysowanie(self):
        return 'A'

    def get_nazwa(self):
        return "Antylopa"

    def stworz_potomka(self, x, y):
        return Antylopa(x, y, self.swiat)

    def akcja(self):
        dx = [-2, 2, 0, 0]
        dy = [0, 0, -2, 2]
        kierunek = random.randint(0, 3)
        nowy_x = self.x + dx[kierunek]
        nowy_y = self.y + dy[kierunek]

        if 0 <= nowy_x < self.swiat.get_szerokosc() and 0 <= nowy_y < self.swiat.get_wysokosc():
            self.wykonaj_ruch(nowy_x, nowy_y)

    def kolizja(self, inny):
        if random.randint(0, 1) == 0 and isinstance(inny, Antylopa):
            for dx, dy in [(-1,0), (1,0), (0,-1), (0,1)]:
                nowy_x = self.x + dx
                nowy_y = self.y + dy
                if 0 <= nowy_x < self.swiat.get_szerokosc() and 0 <= nowy_y < self.swiat.get_wysokosc():
                    if self.swiat.czy_pole_puste(nowy_x, nowy_y):
                        self.swiat.dodaj_log(f"{self.get_nazwa()} uciekła na pole ({nowy_x}, {nowy_y})")
                        self.set_pozycja(nowy_x, nowy_y)
                        return
        super().kolizja(inny)

    def czy_ten_sam_gatunek(self, inny):
        return isinstance(inny, Antylopa)
