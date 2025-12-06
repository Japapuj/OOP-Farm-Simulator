public class BarszczSosnowskiego extends Roslina {
    public BarszczSosnowskiego(int x, int y, Swiat swiat) {
        super(10, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'B';
    }

    @Override
    public String getNazwa() {
        return "BarszczSosnowskiego";
    }

    @Override
    public Organizm stworzPotomka(int x, int y) {
        return new BarszczSosnowskiego(x, y, swiat);
    }

    @Override
    public void akcja() {
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            Organizm org = swiat.getOrganizm(nx, ny);
            if (org instanceof Zwierze && !org.getNazwa().equals("CyberOwca")) {
                org.zabij();
                swiat.dodajLog(getNazwa() + " zabił " + org.getNazwa() + " w sąsiedztwie.");
            }
        }

        super.akcja();
    }

    @Override
    public void kolizja(Organizm inny) {
        if (!inny.getNazwa().equals("CyberOwca")) {
            inny.zabij();
        }
        this.zabij();
        swiat.dodajLog(inny.getNazwa() + " zjadł Barszcz Sosnowskiego i zginął.");
    }

    @Override
    protected void zasiej(int nowyX, int nowyY) {
        swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
    }
}
