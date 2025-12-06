public class Zolw extends Zwierze {
    public Zolw(int x, int y, Swiat swiat) {
        super(2, 1, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'Z';
    }

    @Override
    public String getNazwa() {
        return "Zolw";
    }

    @Override
    public Organizm stworzPotomka(int nowyX, int nowyY) {
        return new Zolw(nowyX, nowyY, swiat);
    }

    @Override
    public boolean czyOdbilAtak(Organizm atakujacy) {
        return atakujacy.getSila() < 5;
    }

    @Override
    public void akcja() {
        if (Math.random() < 0.25) {
            super.akcja();
        } else {
            swiat.dodajLog("Zolw pozostaje w miejscu na polu (" + getX() + ", " + getY() + ")");
        }
    }

    @Override
    public boolean czyTenSamGatunek(Organizm inny) {
        return inny instanceof Zolw;
    }
}
