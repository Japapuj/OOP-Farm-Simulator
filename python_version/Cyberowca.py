from Zwierze import Zwierze

class CyberOwca(Zwierze):
    def __init__(self, x, y, swiat):
        super().__init__(10, 4, x, y, swiat)

    def rysowanie(self):
        return 'C'

    def get_nazwa(self):
        return "CyberOwca"

    def stworz_potomka(self, x, y):
        return CyberOwca(x, y, self.swiat)

    def akcja(self):
        cel = self.swiat.znajdz_najblizszy_barszcz(self.x, self.y)
        if cel:
            dx = cel.get_x() - self.x
            dy = cel.get_y() - self.y
            krok_x = int(dx / abs(dx)) if dx != 0 else 0
            krok_y = int(dy / abs(dy)) if dy != 0 else 0
            nowy_x = self.x + krok_x
            nowy_y = self.y + krok_y

            if 0 <= nowy_x < self.swiat.get_szerokosc() and 0 <= nowy_y < self.swiat.get_wysokosc():
                self.wykonaj_ruch(nowy_x, nowy_y)
        else:
            super().akcja()

    def czy_ten_sam_gatunek(self, inny):
        return isinstance(inny, CyberOwca)
