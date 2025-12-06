from Roslina import Roslina
from Zwierze import Zwierze

class BarszczSosnowskiego(Roslina):
    def __init__(self, x, y, swiat):
        super().__init__(10, x, y, swiat)

    def rysowanie(self):
        return 'B'

    def get_nazwa(self):
        return "BarszczSosnowskiego"

    def stworz_potomka(self, x, y):
        return BarszczSosnowskiego(x, y, self.swiat)

    def akcja(self):
        for dx, dy in [(-1,0), (1,0), (0,-1), (0,1)]:
            nx = self.x + dx
            ny = self.y + dy
            org = self.swiat.get_organizm(nx, ny)
            if org and org.czy_zyje() and isinstance(org, Zwierze) and org.get_nazwa() != "CyberOwca":
                org.zabij()
                self.swiat.dodaj_log(f"{self.get_nazwa()} zabił {org.get_nazwa()} w sąsiedztwie.")
        super().akcja()

    def kolizja(self, inny):
        if inny.get_nazwa() != "CyberOwca":
            inny.zabij()
        self.zabij()
        self.swiat.dodaj_log(f"{inny.get_nazwa()} zjadł Barszcz Sosnowskiego i zginął.")

    def zasiej(self, x, y):
        self.swiat.dodaj_organizm(self.stworz_potomka(x, y))
