from Zwierze import Zwierze

class Wilk(Zwierze):
    def __init__(self, x, y, swiat):
        super().__init__(9, 5, x, y, swiat)

    def rysowanie(self):
        return 'W'

    def get_nazwa(self):
        return "Wilk"

    def czy_ten_sam_gatunek(self, inny):
        return isinstance(inny, Wilk)

    def stworz_potomka(self, x, y):
        return Wilk(x, y, self.swiat)
