public class Owca extends Zwierze {
    public Owca(int x, int y, Swiat swiat) {
        super(4, 4, x, y, swiat); // siła 4, inicjatywa 4
    }

    @Override
    public char rysowanie() {
        return 'O';
    }

    @Override
    public String getNazwa() {
        return "Owca";
    }

    @Override
    public Organizm stworzPotomka(int nowyX, int nowyY) {
        return new Owca(nowyX, nowyY, swiat);
    }

    @Override
    public boolean czyTenSamGatunek(Organizm inny) {
        return inny instanceof Owca;
    }
}
