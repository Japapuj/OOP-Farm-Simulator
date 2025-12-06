from Roslina import Roslina

class Guarana(Roslina):
    def __init__(self, x, y, swiat):
        super().__init__(0, x, y, swiat)

    def rysowanie(self):
        return 'G'

    def get_nazwa(self):
        return "Guarana"

    def stworz_potomka(self, x, y):
        return Guarana(x, y, self.swiat)

    def kolizja(self, inny):
        inny.zwieksz_sile(3)
        self.swiat.dodaj_log(f"{inny.get_nazwa()} zjadł Guaranę i zyskał +3 siły.")
        self.zabij()

    def zasiej(self, x, y):
        self.swiat.dodaj_organizm(self.stworz_potomka(x, y))
