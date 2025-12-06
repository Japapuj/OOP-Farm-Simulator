public class Mlecz extends Roslina {
    public Mlecz(int x, int y, Swiat swiat) {
        super(0, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'M';
    }

    @Override
    public String getNazwa() {
        return "Mlecz";
    }

    @Override
    public Organizm stworzPotomka(int x, int y) {
        return new Mlecz(x, y, swiat);
    }

    @Override
    protected void zasiej(int nowyX, int nowyY) {
        swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
    }

    @Override
    public void akcja() {
        int liczbaProb = 3;
        for (int i = 0; i < liczbaProb; i++) {
            this.czyRozprzesrzeniono = false;
            super.akcja();
            if (this.czyRozprzesrzeniono) break;
        }
    }
}
