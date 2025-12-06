import tkinter as tk
from tkinter import messagebox, simpledialog
from Swiat import Swiat
from Czlowiek import Czlowiek
from Wilk import Wilk
from Trawa import Trawa
from Owca import Owca
from Lis import Lis
from Antylopa import Antylopa
from Zolw import Zolw
from Mlecz import Mlecz
from Guarana import Guarana
from Wilcze_jagody import WilczeJagody
from Barszcz_sosnowskiego import BarszczSosnowskiego
from Cyberowca import CyberOwca

ORGANIZMY = {
    "Wilk": Wilk,
    "Owca": Owca,
    "Lis": Lis,
    "Antylopa": Antylopa,
    "Zolw": Zolw,
    "Czlowiek": Czlowiek,
    "Trawa": Trawa,
    "Mlecz": Mlecz,
    "Guarana": Guarana,
    "WilczeJagody": WilczeJagody,
    "BarszczSosnowskiego": BarszczSosnowskiego,
    "CyberOwca": CyberOwca
}

class WorldGUI:
    def __init__(self, root, swiat, on_zapis=None):
        self.root = root
        self.swiat = swiat
        self.on_zapis = on_zapis
        self.czlowiek = next((o for o in swiat.get_organizmy() if o.get_nazwa() == "Czlowiek"), None)
        self.szer = swiat.get_szerokosc()
        self.wys = swiat.get_wysokosc()
        self.buttons = [[None for _ in range(self.szer)] for _ in range(self.wys)]

        self.frame = tk.Frame(root)
        self.frame.pack(side=tk.LEFT)

        self.canvas = tk.Frame(self.frame)
        self.canvas.pack()

        for y in range(self.wys):
            for x in range(self.szer):
                btn = tk.Button(self.canvas, width=2, height=1, command=lambda x=x, y=y: self.dodaj_organizm_na(x, y))
                btn.grid(row=y, column=x)
                self.buttons[y][x] = btn

        self.przyciski = tk.Frame(root)
        self.przyciski.pack(side=tk.RIGHT)

        self.btn_zapisz = tk.Button(self.przyciski, text="Zapisz grę", command=self.zapisz_gre)
        self.btn_zapisz.pack(pady=10)
        self.btn_koniec = tk.Button(self.przyciski, text="Koniec gry", command=self.koniec_gry)
        self.btn_koniec.pack(pady=10)

        self.log = tk.Text(self.przyciski, width=40)
        self.log.pack(fill=tk.BOTH)

        self.root.bind("<KeyPress>", self.key_pressed)
        self.root.bind("<Return>", lambda e: self.nowa_tura())

        self.aktualizuj_gui()

    def aktualizuj_gui(self):
        for y in range(self.wys):
            for x in range(self.szer):
                symbol = self.swiat.plansza[y][x]
                self.buttons[y][x].config(text=symbol if symbol != '.' else '')
        self.log.delete("1.0", tk.END)
        for linia in self.swiat.logi:
            self.log.insert(tk.END, linia + "\n")
        self.swiat.logi.clear()

    def dodaj_organizm_na(self, x, y):
        if not self.swiat.czy_pole_puste(x, y):
            return

        wybor = simpledialog.askstring("Organizm", f"Wybierz organizm:\n{', '.join(ORGANIZMY.keys())}")
        if wybor in ORGANIZMY:
            if wybor == "Czlowiek" and self.czlowiek is not None:
                messagebox.showinfo("Blad", "Czlowiek juz istnieje")
                return
            nowy = ORGANIZMY[wybor](x, y, self.swiat)
            self.swiat.dodaj_organizm(nowy)
            if wybor == "Czlowiek":
                self.czlowiek = nowy
            self.aktualizuj_gui()

    def key_pressed(self, event):
        if not self.czlowiek:
            return
        key = event.keysym.lower()
        kierunek = {
            "up": "up",
            "down": "down",
            "left": "left",
            "right": "right",
            "u": "u"
        }
        if key in kierunek:
            self.czlowiek.obsluz_sterowanie(kierunek[key])
            self.nowa_tura()

    def nowa_tura(self):
        self.swiat.wykonaj_ture()
        self.aktualizuj_gui()
        if self.czlowiek and not self.czlowiek.czy_zyje():
            messagebox.showinfo("Koniec gry", "Człowiek zginął! Gra zakończona")
            self.czlowiek = None
            self.koniec_gry()

    def zapisz_gre(self):
        if self.on_zapis:
            self.on_zapis(self.swiat)
            messagebox.showinfo("Zapis", "Gra została zapisana.")

    def koniec_gry(self):
        self.root.destroy()

def uruchom_gui(swiat=None, on_zapis=None):
    root = tk.Tk()
    root.title("Wirtualny Świat")
    if swiat is None:
        swiat = Swiat(20, 20)
    app = WorldGUI(root, swiat, on_zapis)
    root.protocol("WM_DELETE_WINDOW", app.koniec_gry)
    root.mainloop()
