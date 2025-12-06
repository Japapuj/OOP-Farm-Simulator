from Zwierze import Zwierze

class Owca(Zwierze):
    def __init__(self, x, y, swiat):
        super().__init__(4, 4, x, y, swiat)

    def rysowanie(self):
        return 'O'

    def get_nazwa(self):
        return "Owca"

    def stworz_potomka(self, x, y):
        return Owca(x, y, self.swiat)

    def czy_ten_sam_gatunek(self, inny):
        return isinstance(inny, Owca)
