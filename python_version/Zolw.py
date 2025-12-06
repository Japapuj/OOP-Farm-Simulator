from Zwierze import Zwierze
import random

class Zolw(Zwierze):
    def __init__(self, x, y, swiat):
        super().__init__(2, 1, x, y, swiat)

    def rysowanie(self):
        return 'Z'

    def get_nazwa(self):
        return "Zolw"

    def stworz_potomka(self, x, y):
        return Zolw(x, y, self.swiat)

    def czy_odbil_atak(self, atakujacy):
        return atakujacy.get_sila() < 5

    def akcja(self):
        if random.randint(0, 99) < 25:
            super().akcja()
        else:
            self.swiat.dodaj_log(f"Zolw pozostaje w miejscu na polu ({self.x}, {self.y})")

    def czy_ten_sam_gatunek(self, inny):
        return isinstance(inny, Zolw)
