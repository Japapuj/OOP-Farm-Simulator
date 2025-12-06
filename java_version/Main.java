import javax.swing.*;
import java.awt.event.*;
import java.util.Optional;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            int width = 20, height = 20;
            Swiat swiat = new Swiat(width, height);
            Czlowiek czlowiek;

            int opcja = JOptionPane.showConfirmDialog(null, "Czy chcesz wczytać grę?", "Wczytaj", JOptionPane.YES_NO_OPTION);

            if (opcja == JOptionPane.YES_OPTION) {
                swiat.wczytajZPliku("save.txt");

                Optional<Organizm> znaleziony = swiat.getOrganizmy().stream()
                        .filter(o -> o instanceof Czlowiek)
                        .findFirst();

                czlowiek = (Czlowiek) znaleziony.orElse(null);
            } else {
                czlowiek = new Czlowiek(10, 5, swiat);
                swiat.dodajOrganizm(czlowiek);
                swiat.dodajOrganizm(new Wilk(10, 12, swiat));
                swiat.dodajOrganizm(new Wilk(10, 13, swiat));
                swiat.dodajOrganizm(new Lis(3, 15, swiat));
                swiat.dodajOrganizm(new Lis(3, 16, swiat));
                swiat.dodajOrganizm(new Trawa(0, 0, swiat));
                swiat.dodajOrganizm(new Guarana(2, 2, swiat));
                swiat.dodajOrganizm(new Zolw(5, 5, swiat));
                swiat.dodajOrganizm(new Owca(6, 6, swiat));
                swiat.dodajOrganizm(new Antylopa(8, 8, swiat));
                swiat.dodajOrganizm(new WilczeJagody(1, 1, swiat));
                swiat.dodajOrganizm(new BarszczSosnowskiego(17, 4, swiat));
                swiat.dodajOrganizm(new Mlecz(12, 6, swiat));
            }

            SwiatFrame frame = new SwiatFrame(swiat);
            frame.setVisible(true);
        });
    }
}
