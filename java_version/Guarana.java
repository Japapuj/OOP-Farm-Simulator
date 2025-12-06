public class Guarana extends Roslina {
    public Guarana(int x, int y, Swiat swiat) {
        super(0, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'G';
    }

    @Override
    public String getNazwa() {
        return "Guarana";
    }

    @Override
    public Organizm stworzPotomka(int x, int y) {
        return new Guarana(x, y, swiat);
    }

    @Override
    public void kolizja(Organizm inny) {
        inny.zwiekszSile(3);
        swiat.dodajLog(inny.getNazwa() + " zjadł Guaranę i zyskał +3 siły.");
        this.zabij();
    }

    @Override
    protected void zasiej(int nowyX, int nowyY) {
        swiat.dodajOrganizm(stworzPotomka(nowyX, nowyY));
    }
}
