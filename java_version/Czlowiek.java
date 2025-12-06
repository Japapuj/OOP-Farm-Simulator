public class Czlowiek extends Zwierze {
    private int cooldown;
    private int czasTrwania;
    private boolean aktywnaUmiejetnosc;
    private int silaBazowa;
    private int dx = 0;
    private int dy = 0;

    public Czlowiek(int x, int y, Swiat swiat) {
        super(5, 4, x, y, swiat);
        this.silaBazowa = this.sila;
    }

    @Override
    public char rysowanie() {
        return 'H';
    }

    @Override
    public String getNazwa() {
        return "Czlowiek";
    }

    @Override
    public Organizm stworzPotomka(int nowyX, int nowyY) {
        return null; // Człowiek się nie rozmnaża
    }

    @Override
    public void akcja() {
        if (aktywnaUmiejetnosc) {
            if (czasTrwania == 5) {
                sila = 10;
                swiat.dodajLog("Eliksir aktywowany! Sila Czlowieka wynosi 10.");
            } else {
                sila = silaBazowa + (5 - czasTrwania);
            }

            czasTrwania--;

            if (czasTrwania == 0) {
                aktywnaUmiejetnosc = false;
                sila = silaBazowa;
                cooldown = 5;
                swiat.dodajLog("Eliksir wygasl. Sila Czlowieka wrocila do " + silaBazowa);
            }
        } else if (cooldown > 0) {
            cooldown--;
        }

        if (dx != 0 || dy != 0) {
            int nowyX = x + dx;
            int nowyY = y + dy;
            if (swiat.czyWPlanszy(nowyX, nowyY)) {
                wykonajRuch(nowyX, nowyY);
            }
        }

        dx = 0;
        dy = 0;
    }

    @Override
    public void kolizja(Organizm inny) {
        super.kolizja(inny);
    }

    @Override
    public boolean czyTenSamGatunek(Organizm inny) {
        return false;
    }

    public void aktywujUmiejetnosc() {
        if (!aktywnaUmiejetnosc && cooldown == 0) {
            aktywnaUmiejetnosc = true;
            czasTrwania = 5;
            swiat.dodajLog("Czlowiek wypil magiczny eliksir");
        } else {
            swiat.dodajLog("Eliksir niedostepny (cooldown: " + cooldown + ")");
        }
    }

    public void obsluzSterowanie(int key) {
        switch (key) {
            case 38: dx = 0; dy = -1; break; // Góra (VK_UP)
            case 40: dx = 0; dy = 1; break;  // Dół
            case 37: dx = -1; dy = 0; break; // Lewo
            case 39: dx = 1; dy = 0; break;  // Prawo
            case 'U': case 'u': aktywujUmiejetnosc(); break;
            default: break;
        }
    }

    public int getCooldown() { return cooldown; }
    public boolean isAktywnaUmiejetnosc() { return aktywnaUmiejetnosc; }
    public int getCzasTrwania() { return czasTrwania; }

    public void setCooldown(int c) { this.cooldown = c; }
    public void setAktywnaUmiejetnosc(boolean a) { this.aktywnaUmiejetnosc = a; }
    public void setCzasTrwania(int t) { this.czasTrwania = t; }
}
