from Organizm import Organizm
import random

class Roslina(Organizm):
    def __init__(self, sila, x, y, swiat):
        super().__init__(sila, 0, x, y, swiat)

    def akcja(self):
        if random.randint(0, 4) == 4:
            self.rozprzestrzenianie()

    def kolizja(self, inny):
        self.swiat.dodaj_log(f"{self.get_nazwa()} na ({self.x}, {self.y}) został zjedzony przez {inny.get_nazwa()}")
        self.zabij()

    def rozprzestrzenianie(self):
        for dx, dy in [(-1,0), (1,0), (0,-1), (0,1)]:
            nowy_x = self.x + dx
            nowy_y = self.y + dy
            if self.swiat.czy_pole_puste(nowy_x, nowy_y):
                self.zasiej(nowy_x, nowy_y)
                return

    def zasiej(self, nowy_x, nowy_y):
        raise NotImplementedError()
