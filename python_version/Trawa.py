from Roslina import Roslina

class Trawa(Roslina):
    def __init__(self, x, y, swiat):
        super().__init__(0, x, y, swiat)

    def rysowanie(self):
        return 'T'

    def get_nazwa(self):
        return "Trawa"

    def stworz_potomka(self, x, y):
        return Trawa(x, y, self.swiat)

    def zasiej(self, x, y):
        self.swiat.dodaj_organizm(self.stworz_potomka(x, y))
