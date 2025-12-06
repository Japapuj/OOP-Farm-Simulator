from Zwierze import Zwierze
import random

class Lis(Zwierze):
    def __init__(self, x, y, swiat):
        super().__init__(3, 7, x, y, swiat)

    def rysowanie(self):
        return 'L'

    def get_nazwa(self):
        return "Lis"

    def stworz_potomka(self, x, y):
        return Lis(x, y, self.swiat)

    def akcja(self):
        dx = [-1, 1, 0, 0]
        dy = [0, 0, -1, 1]
        kierunek = random.randint(0, 3)
        nowy_x = self.x + dx[kierunek]
        nowy_y = self.y + dy[kierunek]

        if 0 <= nowy_x < self.swiat.get_szerokosc() and 0 <= nowy_y < self.swiat.get_wysokosc():
            cel = self.swiat.get_organizm(nowy_x, nowy_y)
            if cel is None or cel.get_sila() <= self.get_sila():
                self.wykonaj_ruch(nowy_x, nowy_y)
            else:
                self.swiat.dodaj_log(f"{self.get_nazwa()} na ({self.x}, {self.y}) unika silniejszego organizmu")

    def czy_ten_sam_gatunek(self, inny):
        return isinstance(inny, Lis)
