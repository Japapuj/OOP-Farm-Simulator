public class OrganizmFactory {
    public static Organizm stworz(String nazwa, int x, int y, Swiat swiat) {
        switch (nazwa) {
            case "Wilk": return new Wilk(x, y, swiat);
            case "Lis": return new Lis(x, y, swiat);
            case "Trawa": return new Trawa(x, y, swiat);
            case "Guarana": return new Guarana(x, y, swiat);
            case "Zolw": return new Zolw(x, y, swiat);
            case "Owca": return new Owca(x, y, swiat);
            case "Mlecz": return new Mlecz(x, y, swiat);
            case "Czlowiek": return new Czlowiek(x, y, swiat);
            case "BarszczSosnowskiego": return new BarszczSosnowskiego(x, y, swiat);
            case "WilczeJagody": return new WilczeJagody(x, y, swiat);
            case "Antylopa": return new Antylopa(x, y, swiat);
            default: return null;
        }
    }
}
