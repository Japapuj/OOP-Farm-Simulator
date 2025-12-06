from Roslina import Roslina

class WilczeJagody(Roslina):
    def __init__(self, x, y, swiat):
        super().__init__(99, x, y, swiat)

    def rysowanie(self):
        return 'J'

    def get_nazwa(self):
        return "WilczeJagody"

    def stworz_potomka(self, x, y):
        return WilczeJagody(x, y, self.swiat)

    def kolizja(self, inny):
        inny.zabij()
        self.zabij()
        self.swiat.dodaj_log(f"{inny.get_nazwa()} zjadł Wilcze Jagody i zginął.")

    def zasiej(self, x, y):
        self.swiat.dodaj_organizm(self.stworz_potomka(x, y))
