public class Antylopa extends Zwierze {
    public Antylopa(int x, int y, Swiat swiat) {
        super(4, 4, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'A';
    }

    @Override
    public String getNazwa() {
        return "Antylopa";
    }

    @Override
    public Organizm stworzPotomka(int nowyX, int nowyY) {
        return new Antylopa(nowyX, nowyY, swiat);
    }

    @Override
    public void akcja() {
        int[] dx = {-2, 2, 0, 0};
        int[] dy = {0, 0, -2, 2};
        int kierunek = (int)(Math.random() * 4);

        int nowyX = x + dx[kierunek];
        int nowyY = y + dy[kierunek];

        if (swiat.czyWPlanszy(nowyX, nowyY)) {
            wykonajRuch(nowyX, nowyY);
        }
    }

    @Override
    public void kolizja(Organizm inny) {
        if (Math.random() < 0.5 && inny.getClass() == this.getClass()) {
            int[] dx = {-1, 1, 0, 0};
            int[] dy = {0, 0, -1, 1};

            for (int i = 0; i < 4; i++) {
                int nowyX = x + dx[i];
                int nowyY = y + dy[i];
                if (swiat.czyWPlanszy(nowyX, nowyY) && swiat.czyPolePuste(nowyX, nowyY)) {
                    swiat.dodajLog(getNazwa() + " uciekła na pole (" + nowyX + "," + nowyY + ")");
                    x = nowyX;
                    y = nowyY;
                    return;
                }
            }
        }

        super.kolizja(inny);
    }

    @Override
    public boolean czyTenSamGatunek(Organizm inny) {
        return inny instanceof Antylopa;
    }
}
