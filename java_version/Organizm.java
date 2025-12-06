public abstract class Organizm {
    protected int sila;
    protected int inicjatywa;
    protected int x, y;
    protected Swiat swiat;
    protected boolean zyje = true;
    public boolean nowoNarodzony = false;

    public Organizm(int sila, int inicjatywa, int x, int y, Swiat swiat) {
        this.sila = sila;
        this.inicjatywa = inicjatywa;
        this.x = x;
        this.y = y;
        this.swiat = swiat;
    }

    public int getSila() { return sila; }
    public int getInicjatywa() { return inicjatywa; }
    public int getX() { return x; }
    public int getY() { return y; }
    public boolean czyZyje() { return zyje; }
    public boolean isNowoNarodzony(){
        return nowoNarodzony;
    }


    public void setNowoNarodzony(boolean nowoNarodzony){
        this.nowoNarodzony=nowoNarodzony;
    }

    public void zwiekszSile(int wartosc) { sila += wartosc; }

    public void setPozycja(int nowyX, int nowyY) {
        x = nowyX;
        y = nowyY;
    }

    public void zabij() { zyje = false; }

    public abstract void akcja();
    public abstract void kolizja(Organizm inny);
    public boolean czyOdbilAtak(Organizm inny) { return false; }

    public abstract String getNazwa();
    public abstract char rysowanie();  // Do debugowania konsolowego
    public abstract Organizm stworzPotomka(int x, int y);
}
