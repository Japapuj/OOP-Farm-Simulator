import java.util.*;
import java.io.*;
import javax.swing.*;

public class Swiat {
    private int szerokosc;
    private int wysokosc;
    private char[][] plansza;
    private List<Organizm> organizmy = new ArrayList<>();
    private List<String> logi = new ArrayList<>();
    private Map<Organizm, Integer> wiekOrganizmow = new HashMap<>();
    private JPanel planszaPanel;

    public Swiat(int szerokosc, int wysokosc) {
        this.szerokosc = szerokosc;
        this.wysokosc = wysokosc;
        inicjalizujPlansze();
    }

    public void inicjalizujPlansze() {
        plansza = new char[wysokosc][szerokosc];
        for (int y = 0; y < wysokosc; y++) {
            for (int x = 0; x < szerokosc; x++) {
                plansza[y][x] = '.';
            }
        }
    }

    public void dodajOrganizm(Organizm organizm) {
        if (organizm == null) return;
        organizmy.add(organizm);
        plansza[organizm.getY()][organizm.getX()] = organizm.rysowanie();
        wiekOrganizmow.put(organizm, 0);
        logi.add("Dodano " + organizm.getNazwa() + " na (" + organizm.getX() + "," + organizm.getY() + ")");
        organizm.setNowoNarodzony(true);
    }

    public void wykonajTure() {
        for (Organizm org : organizmy) {
            wiekOrganizmow.put(org, wiekOrganizmow.get(org) + 1);
        }

        organizmy.sort((a, b) -> {
            if (a.getInicjatywa() != b.getInicjatywa())
                return Integer.compare(b.getInicjatywa(), a.getInicjatywa());
            return Integer.compare(wiekOrganizmow.get(b), wiekOrganizmow.get(a));
        });

        List<Organizm> kopia = new ArrayList<>(organizmy);
        for (Organizm org : kopia) {
            if (org.czyZyje() && !org.isNowoNarodzony()) {
                org.akcja();
            }
        }

        usunMartweOrganizmy();
        odswiezPlansze();
        for (Organizm org : organizmy) {
            org.setNowoNarodzony(false);
        }
    }

    public void odswiezPlansze() {
        inicjalizujPlansze();
        for (Organizm org : organizmy) {
            if (org.czyZyje())
                plansza[org.getY()][org.getX()] = org.rysowanie();
        }
    }

    public void aktualizujPole(int x, int y, char symbol){
        plansza[y][x]=symbol;
    }

    public void pokazLogi() {
        System.out.println("=== LOGI ===");
        for (String log : logi) {
            System.out.println(log);
        }
        logi.clear();
    }

    public void rysujSwiat() {
        for (int y = 0; y < wysokosc; y++) {
            for (int x = 0; x < szerokosc; x++) {
                System.out.print(plansza[y][x] + " ");
            }
            System.out.println();
        }
    }

    public Organizm getOrganizm(int x, int y) {
        for (Organizm o : organizmy) {
            if (o.getX() == x && o.getY() == y && o.czyZyje()) {
                return o;
            }
        }
        return null;
    }

    public boolean czyPolePuste(int x, int y) {
        return plansza[y][x] == '.';
    }

    public void usunMartweOrganizmy() {
        organizmy.removeIf(o -> !o.czyZyje());
    }

    public void zapiszDoPliku(String nazwa) {
        try (PrintWriter pw = new PrintWriter(new FileWriter(nazwa))) {
            pw.println(szerokosc + " " + wysokosc);
            for (Organizm o : organizmy) {
                if (!o.czyZyje()) continue;
                pw.print(o.getNazwa() + " " + o.getSila() + " " + o.getX() + " " + o.getY());
                if (o instanceof Czlowiek) {
                    Czlowiek czl = (Czlowiek) o;
                    pw.print(" cooldown:" + czl.getCooldown());
                    pw.print(" aktywna:" + czl.isAktywnaUmiejetnosc());
                    pw.print(" czasTrwania:" + czl.getCzasTrwania());
                }
                pw.println();
            }
        } catch (IOException e) {
            System.err.println("Nie mozna zapisac do pliku.");
        }
    }

    public void wczytajZPliku(String nazwa) {
        try (Scanner sc = new Scanner(new File(nazwa))) {
            szerokosc = sc.nextInt();
            wysokosc = sc.nextInt();
            sc.nextLine();

            organizmy.clear();
            inicjalizujPlansze();

            while (sc.hasNextLine()) {
                String linia = sc.nextLine();
                if (linia.trim().isEmpty()) continue;

                String[] czesci = linia.split(" ");
                String nazwaOrganizmu = czesci[0];
                int sila = Integer.parseInt(czesci[1]);
                int x = Integer.parseInt(czesci[2]);
                int y = Integer.parseInt(czesci[3]);

                Organizm org = OrganizmFactory.stworz(nazwaOrganizmu, x, y, this);

                if (org instanceof Czlowiek) {
                    Czlowiek czl = (Czlowiek) org;
                    for (String token : czesci) {
                        if (token.startsWith("cooldown:")) czl.setCooldown(Integer.parseInt(token.substring(9)));
                        else if (token.startsWith("aktywna:")) czl.setAktywnaUmiejetnosc(token.substring(8).equals("true"));
                        else if (token.startsWith("czasTrwania:")) czl.setCzasTrwania(Integer.parseInt(token.substring(12)));
                    }
                }

                if (org != null) {
                    org.zwiekszSile(sila - org.getSila());
                    dodajOrganizm(org);
                }
            }

        } catch (IOException e) {
            System.err.println("Nie udalo sie wczytac pliku.");
        }
    }

    public int getSzerokosc() { return szerokosc; }
    public int getWysokosc() { return wysokosc; }

    public List<Organizm> getOrganizmy() { return organizmy; }

    public void dodajLog(String tekst) {
        logi.add(tekst);
    }
    public boolean czyWPlanszy(int x, int y) {
        return x >= 0 && x < szerokosc && y >= 0 && y < wysokosc;
    }
    public List<String> getLogi(){
        return logi;
    }
    public void wyczyscLogi(){logi.clear();}

}
