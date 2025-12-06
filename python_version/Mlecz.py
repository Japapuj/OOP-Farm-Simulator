from Roslina import Roslina

class Mlecz(Roslina):
    def __init__(self, x, y, swiat):
        super().__init__(0, x, y, swiat)

    def rysowanie(self):
        return 'M'

    def get_nazwa(self):
        return "Mlecz"

    def stworz_potomka(self, x, y):
        return Mlecz(x, y, self.swiat)

    def zasiej(self, x, y):
        self.swiat.dodaj_organizm(self.stworz_potomka(x, y))

    def akcja(self):
        liczba_prob = 3
        sukcesy = 0
        for _ in range(liczba_prob):
            if sukcesy > 0:
                break
            self.czyRozprzesrzeniono = False
            super().akcja()
            if self.czyRozprzesrzeniono:
                sukcesy += 1
