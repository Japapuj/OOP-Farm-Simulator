public class Wilk extends Zwierze {
    public Wilk(int x, int y, Swiat swiat) {
        super(9, 5, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'W';
    }

    @Override
    public boolean czyTenSamGatunek(Organizm inny) {
        return inny instanceof Wilk;
    }

    @Override
    public String getNazwa() {
        return "Wilk";
    }

    @Override
    public Organizm stworzPotomka(int nowyX, int nowyY) {
        return new Wilk(nowyX, nowyY, swiat);
    }
}
