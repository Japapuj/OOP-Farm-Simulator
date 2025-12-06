public class WilczeJagody extends Roslina {
    public WilczeJagody(int x, int y, Swiat swiat) {
        super(99, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'J';
    }

    @Override
    public String getNazwa() {
        return "WilczeJagody";
    }

    @Override
    public Organizm stworzPotomka(int x, int y) {
        return new WilczeJagody(x, y, swiat);
    }

    @Override
    public void kolizja(Organizm inny) {
        inny.zabij();
        this.zabij();
        swiat.dodajLog(inny.getNazwa() + " zjadł Wilcze Jagody i zginął.");
    }

    @Override
    protected void zasiej(int nowyX, int nowyY) {
        swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
    }
}
