from abc import ABC, abstractmethod

class Organizm(ABC):
    def __init__(self, sila, inicjatywa, x, y, swiat):
        self.sila = sila
        self.inicjatywa = inicjatywa
        self.x = x
        self.y = y
        self.swiat = swiat
        self.zyje = True
        self.nowo_narodzony = False

    @abstractmethod
    def akcja(self):
        pass

    @abstractmethod
    def kolizja(self, inny):
        pass

    def czy_odbil_atak(self, inny):
        return False

    @abstractmethod
    def rysowanie(self):
        pass

    @abstractmethod
    def get_nazwa(self):
        pass

    def get_sila(self):
        return self.sila

    def get_inicjatywa(self):
        return self.inicjatywa

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def czy_zyje(self):
        return self.zyje

    def zwieksz_sile(self, wartosc):
        self.sila += wartosc

    def set_pozycja(self, nowy_x, nowy_y):
        self.x = nowy_x
        self.y = nowy_y

    def zabij(self):
        self.zyje = False
