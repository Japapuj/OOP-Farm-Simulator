public class Trawa extends Roslina {
    public Trawa(int x, int y, Swiat swiat) {
        super(0, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'T';
    }

    @Override
    public String getNazwa() {
        return "Trawa";
    }

    @Override
    public Organizm stworzPotomka(int x, int y) {
        return new Trawa(x, y, swiat);
    }

    @Override
    protected void zasiej(int nowyX, int nowyY) {
        swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
    }
}
