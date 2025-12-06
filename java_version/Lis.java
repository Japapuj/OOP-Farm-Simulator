public class Lis extends Zwierze {
    public Lis(int x, int y, Swiat swiat) {
        super(3, 7, x, y, swiat);
    }

    @Override
    public char rysowanie() {
        return 'L';
    }

    @Override
    public String getNazwa() {
        return "Lis";
    }

    @Override
    public Organizm stworzPotomka(int x, int y) {
        return new Lis(x, y, swiat);
    }

    @Override
    public void akcja() {
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};
        int kierunek = (int)(Math.random() * 4);

        int nowyX = x + dx[kierunek];
        int nowyY = y + dy[kierunek];
        Organizm cel = swiat.getOrganizm(nowyX, nowyY);

        if (swiat.czyWPlanszy(nowyX, nowyY)) {
            if (cel == null || cel.getSila() <= this.getSila()) {
                wykonajRuch(nowyX, nowyY);
            } else {
                swiat.dodajLog(getNazwa() + " na (" + x + "," + y + ") unika silniejszego przeciwnika.");
            }
        }
    }

    @Override
    public boolean czyTenSamGatunek(Organizm inny) {
        return inny instanceof Lis;
    }
}
