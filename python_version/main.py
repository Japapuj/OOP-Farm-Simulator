from Swiat import Swiat
from Wilk import Wilk
from Trawa import Trawa
from Czlowiek import Czlowiek
from Antylopa import Antylopa
from Mlecz import Mlecz
from Lis import Lis
from Guarana import Guarana
from Owca import Owca
from Barszcz_sosnowskiego import BarszczSosnowskiego
from Cyberowca import CyberOwca
from Zolw import Zolw
from Wilcze_jagody import WilczeJagody
from Gui import uruchom_gui
import tkinter as tk
from tkinter import messagebox
import os
import json
import random

def losowe_pole(swiat):
    while True:
        x=random.randint(0,swiat.get_szerokosc()-1)
        y=random.randint(0,swiat.get_wysokosc()-1)
        if swiat.czy_pole_puste(x,y):
            return (x,y)

def stworz_domyslny_swiat(szer=20, wys=20):
    swiat = Swiat(szer, wys)
    x,y=losowe_pole(swiat)
    czlowiek = Czlowiek(x, y, swiat)
    swiat.dodaj_organizm(czlowiek)

    for _ in range(3):
        x, y = losowe_pole(swiat)
        swiat.dodaj_organizm(Wilk(x,y,swiat))
    for _ in range(5):
        x, y =losowe_pole(swiat)
        swiat.dodaj_organizm(Trawa(x,y,swiat))
    for _ in range(2):
        x, y = losowe_pole(swiat)
        swiat.dodaj_organizm(CyberOwca(x,y,swiat))
        x,y = losowe_pole(swiat)
        swiat.dodaj_organizm(Antylopa(x,y,swiat))
        x, y = losowe_pole(swiat)
        swiat.dodaj_organizm(BarszczSosnowskiego(x, y, swiat))
        x, y = losowe_pole(swiat)
        swiat.dodaj_organizm(Guarana(x, y, swiat))
        x, y = losowe_pole(swiat)
        swiat.dodaj_organizm(WilczeJagody(x, y, swiat))
        x, y = losowe_pole(swiat)
        swiat.dodaj_organizm(Lis(x, y, swiat))

    return swiat

def zapisz_stan(swiat, sciezka="save.json"):
    dane = {
        "szerokosc": swiat.get_szerokosc(),
        "wysokosc": swiat.get_wysokosc(),
        "organizmy": []
    }

    for org in swiat.get_organizmy():
        entry = {
            "nazwa": org.get_nazwa(),
            "x": org.get_x(),
            "y": org.get_y(),
            "sila": org.get_sila()
        }
        if org.get_nazwa() == "Czlowiek":
            entry["cooldown"] = org.get_cooldown()
            entry["aktywny"] = org.is_aktywna_umiejetnosc()
            entry["czas_trwania"] = org.get_czas_trwania()
        dane["organizmy"].append(entry)

    with open(sciezka, "w") as f:
        json.dump(dane, f, indent=2)
    print(f"[ZAPISANO] Stan gry do pliku {sciezka}")

def wczytaj_stan(sciezka="save.json"):
    if not os.path.exists(sciezka):
        print("[INFO] Brak zapisu, tworzę nowy świat.")
        return stworz_domyslny_swiat()

    klasy = {
        "Czlowiek": Czlowiek,
        "Wilk": Wilk,
        "Trawa": Trawa,
        "Owca": Owca,
        "Lis": Lis,
        "Antylopa": Antylopa,
        "Zolw": Zolw,
        "Mlecz": Mlecz,
        "Guarana": Guarana,
        "WilczeJagody": WilczeJagody,
        "BarszczSosnowskiego": BarszczSosnowskiego,
        "CyberOwca": CyberOwca
    }

    with open(sciezka, "r") as f:
        dane = json.load(f)

    swiat = Swiat(dane["szerokosc"], dane["wysokosc"])
    for org in dane["organizmy"]:
        nazwa = org["nazwa"]
        x = org["x"]
        y = org["y"]
        sila = org["sila"]

        if nazwa in klasy:
            inst = klasy[nazwa](x, y, swiat)
            inst.zwieksz_sile(sila - inst.get_sila())
            if nazwa == "Czlowiek":
                inst.set_cooldown(org.get("cooldown", 0))
                inst.set_aktywna_umiejetnosc(org.get("aktywny", False))
                inst.set_czas_trwania(org.get("czas_trwania", 0))
            swiat.dodaj_organizm(inst)
    print(f"[WCZYTANO] Stan gry z pliku {sciezka}")
    return swiat

def main():
    wczytac=messagebox.askyesno("Wczytać grę?", "Czy chcesz wczytać zapisany stan gry?")
    if wczytac and os.path.exists("save.json"):
        swiat = wczytaj_stan("save.json")
    else:
        swiat = stworz_domyslny_swiat()

    uruchom_gui(swiat, on_zapis=zapisz_stan)


if __name__ == "__main__":
    main()

