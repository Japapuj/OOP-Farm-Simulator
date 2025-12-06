public abstract class Roslina extends Organizm {
    protected boolean czyRozprzesrzeniono = false;

    public Roslina(int sila, int x, int y, Swiat swiat) {
        super(sila, 0, x, y, swiat);
    }

    @Override
    public void akcja() {
        if ((int)(Math.random() * 5) == 4) {
            rozprzestrzenianie();
        }
    }

    @Override
    public void kolizja(Organizm inny) {
        swiat.dodajLog(getNazwa() + " na polu (" + x + ", " + y + ") został zjedzony przez " + inny.getNazwa());
        this.zabij();
    }

    protected void rozprzestrzenianie() {
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nowyX = x + dx[i];
            int nowyY = y + dy[i];

            if (swiat.czyWPlanszy(nowyX, nowyY) && swiat.czyPolePuste(nowyX, nowyY)) {
                zasiej(nowyX, nowyY);
                czyRozprzesrzeniono = true;
                return;
            }
        }
    }

    protected abstract void zasiej(int nowyX, int nowyY);

    public abstract String getNazwa();
    public abstract char rysowanie();
}
