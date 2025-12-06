import java.util.Random;

public abstract class Zwierze extends Organizm {
    public Zwierze(int sila, int inicjatywa, int x, int y, Swiat swiat) {
        super(sila, inicjatywa, x, y, swiat);
    }

    @Override
    public void akcja() {
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};

        int kierunek = new Random().nextInt(4);
        int nowyX = x + dx[kierunek];
        int nowyY = y + dy[kierunek];

        if (swiat.czyWPlanszy(nowyX, nowyY)) {
            wykonajRuch(nowyX, nowyY);
        }
    }

    @Override
    public void kolizja(Organizm inny) {
        if (czyTenSamGatunek(inny)) {
            int[] dx = {-1, 1, 0, 0};
            int[] dy = {0, 0, -1, 1};

            for (int i = 0; i < 4; i++) {
                int nowyX = x + dx[i];
                int nowyY = y + dy[i];
                if (swiat.czyWPlanszy(nowyX, nowyY) && swiat.czyPolePuste(nowyX, nowyY)) {
                    swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
                    swiat.dodajLog(getNazwa() + " rozmnaża się na polu (" + x + ", " + y + ")");
                    return;
                }
            }
        } else {
            if (inny.czyOdbilAtak(this)) {
                swiat.dodajLog(getNazwa() + " na (" + x + ", " + y + ") odbił atak od " + inny.getNazwa());
                return;
            } else if (sila >= inny.getSila()) {
                if (inny.getNazwa().equals("Guarana")) {
                    swiat.dodajLog(getNazwa() + " na (" + inny.getX() + ", " + inny.getY() + ") zabił " + inny.getNazwa() + " i zyskał +3 siły.");
                    zwiekszSile(3);
                } else {
                    swiat.dodajLog(getNazwa() + " na (" + inny.getX() + ", " + inny.getY() + ") zabił " + inny.getNazwa());
                }
                inny.zabij();
            } else {
                swiat.dodajLog(getNazwa() + " na (" + inny.getX() + ", " + inny.getY() + ") został zabity przez " + inny.getNazwa());
                this.zabij();
                swiat.usunMartweOrganizmy();  // Potencjalne odświeżenie GUI
            }
        }
    }

    protected void wykonajRuch(int nowyX, int nowyY) {
        Organizm cel = swiat.getOrganizm(nowyX, nowyY);
        if (cel == this) {
            swiat.dodajLog("Błąd: próba kolizji samego ze sobą!");
            return;
        }

        if (cel == null || !cel.czyZyje()) {
            swiat.aktualizujPole(x, y, '.');
            x = nowyX;
            y = nowyY;
            swiat.aktualizujPole(x, y, rysowanie());
            swiat.dodajLog(getNazwa() + " przesunął się na pole (" + x + ", " + y + ")");
        } else {
            kolizja(cel);
            if (!czyZyje()) return;

            swiat.aktualizujPole(x, y, '.');
            x = nowyX;
            y = nowyY;
            swiat.aktualizujPole(x, y, rysowanie());
            swiat.dodajLog(getNazwa() + " przesunął się na pole (" + x + ", " + y + ")");
        }
    }

    public abstract boolean czyTenSamGatunek(Organizm inny);
}
