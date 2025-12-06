from Zwierze import Zwierze

class Czlowiek(Zwierze):
    def __init__(self, x, y, swiat):
        super().__init__(5, 4, x, y, swiat)
        self.cooldown = 0
        self.czas_trwania = 0
        self.aktywna_umiejetnosc = False
        self.sila_bazowa = self.sila
        self.dx = 0
        self.dy = 0

    def rysowanie(self):
        return 'H'

    def get_nazwa(self):
        return "Czlowiek"

    def stworz_potomka(self, x, y):
        return None  # Człowiek się nie rozmnaża

    def akcja(self):
        if self.aktywna_umiejetnosc:
            if self.czas_trwania == 5:
                self.sila = 10
                self.swiat.dodaj_log("Eliksir aktywowany! Siła Człowieka wynosi 10.")
            else:
                self.sila = self.sila_bazowa + (5 - self.czas_trwania)
            self.czas_trwania -= 1
            if self.czas_trwania == 0:
                self.aktywna_umiejetnosc = False
                self.sila = self.sila_bazowa
                self.cooldown = 5
                self.swiat.dodaj_log("Eliksir wygasł. Siła wróciła do " + str(self.sila_bazowa))
        elif self.cooldown > 0:
            self.cooldown -= 1

        if self.dx != 0 or self.dy != 0:
            nowy_x = self.x + self.dx
            nowy_y = self.y + self.dy
            if 0 <= nowy_x < self.swiat.get_szerokosc() and 0 <= nowy_y < self.swiat.get_wysokosc():
                self.wykonaj_ruch(nowy_x, nowy_y)
        self.dx = 0
        self.dy = 0

    def kolizja(self, inny):
        super().kolizja(inny)

    def aktywuj_umiejetnosc(self):
        if not self.aktywna_umiejetnosc and self.cooldown == 0:
            self.aktywna_umiejetnosc = True
            self.czas_trwania = 5
            self.swiat.dodaj_log("Człowiek wypił magiczny eliksir")
        else:
            self.swiat.dodaj_log("Eliksir niedostępny")

    def obsluz_sterowanie(self, key):
        if key == 'up':
            self.dx, self.dy = 0, -1
        elif key == 'down':
            self.dx, self.dy = 0, 1
        elif key == 'left':
            self.dx, self.dy = -1, 0
        elif key == 'right':
            self.dx, self.dy = 1, 0
        elif key == 'u':
            self.aktywuj_umiejetnosc()

    def czy_ten_sam_gatunek(self, inny):
        return False

    def get_cooldown(self):
        return self.cooldown

    def is_aktywna_umiejetnosc(self):
        return self.aktywna_umiejetnosc

    def get_czas_trwania(self):
        return self.czas_trwania

    def set_cooldown(self, c):
        self.cooldown = c

    def set_aktywna_umiejetnosc(self, a):
        self.aktywna_umiejetnosc = a

    def set_czas_trwania(self, t):
        self.czas_trwania = t
