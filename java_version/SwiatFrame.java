import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.List;

public class SwiatFrame extends JFrame implements KeyListener {
    private final Swiat swiat;
    private Czlowiek czlowiek;
    private final JPanel gridPanel;
    private final JTextArea logArea;
    private final JButton saveButton;
    private final JButton loadButton;
    private final int gridSize;

    public SwiatFrame(Swiat swiat) {
        this.swiat = swiat;
        this.czlowiek=swiat.getOrganizmy().stream()
                .filter(o->o instanceof Czlowiek)
                .map(o-> (Czlowiek) o)
                .findFirst()
                .orElse(null);
        this.gridSize = swiat.getSzerokosc();

        setTitle("Symulacja Świata - Gra");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Panel gry
        gridPanel = new JPanel(new GridLayout(gridSize, gridSize));
        add(gridPanel, BorderLayout.CENTER);

        // Panel kontrolny
        JPanel controlPanel = new JPanel();
        saveButton = new JButton("Zapisz");
        loadButton = new JButton("Wczytaj");

        controlPanel.add(saveButton);
        controlPanel.add(loadButton);
        add(controlPanel, BorderLayout.SOUTH);

        // Panel logów
        logArea = new JTextArea(10, 20);
        logArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(logArea);
        add(scrollPane, BorderLayout.EAST);

        // Obsługa przycisków

        saveButton.addActionListener(e -> {
            swiat.zapiszDoPliku("save.txt");
            JOptionPane.showMessageDialog(this, "Gra została zapisana.");
        });

        loadButton.addActionListener(e -> {
            swiat.wczytajZPliku("save.txt");
            updateGrid();
            updateLog();
        });

        addKeyListener(this);
        setFocusable(true);
        requestFocusInWindow();

        updateGrid();
        updateLog();
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    @Override
    public void keyPressed(KeyEvent e){
        if(czlowiek==null || !czlowiek.czyZyje()) return;

        czlowiek.obsluzSterowanie(e.getKeyCode());
        swiat.wyczyscLogi();
        swiat.wykonajTure();
        updateGrid();
        updateLog();

        if(!czlowiek.czyZyje()){
            JOptionPane.showMessageDialog(
                    this,
                    "Czlowiek zginal! Koniec gry.",
                    "GAME OVER",
                    JOptionPane.INFORMATION_MESSAGE
            );
            disableInput();
        }
    }

    private void disableInput(){
        removeKeyListener(this);
        for(Component c : gridPanel.getComponents()){
            c.setEnabled(false);
        }
        saveButton.setEnabled(false);
        loadButton.setEnabled(false);
    }

    @Override
    public void keyReleased(KeyEvent e){}

    @Override
    public void keyTyped(KeyEvent e){}

    private void updateGrid() {
        gridPanel.removeAll();

        for (int y = 0; y < swiat.getWysokosc(); y++) {
            for (int x = 0; x < swiat.getSzerokosc(); x++) {
                Organizm o = swiat.getOrganizm(x, y);
                JButton cellButton = new JButton();
                cellButton.setMargin(new Insets(0,0,0,0));
                cellButton.setFont(new Font("Monospaced", Font.PLAIN, 12));
                cellButton.setFocusPainted(false);

                if (o != null) {
                    cellButton.setText(String.valueOf(o.rysowanie()));
                    cellButton.setEnabled(false);
                }else{
                    final int finalX=x;
                    final int finalY=y;
                    cellButton.addActionListener(e-> dodajOrganizmNaPolu(finalX, finalY));
                }

                gridPanel.add(cellButton);
            }
        }

        gridPanel.revalidate();
        gridPanel.repaint();
    }

    private void dodajOrganizmNaPolu(int x, int y){
        String[] opcje={
                "Wilk", "Lis", "Trawa", "Guarana", "Zolw", "Owca",
                "Mlecz", "BarszczSosnowskiego", "WilczeJagody", "Antylopa"
        };

        String wybor = (String) JOptionPane.showInputDialog(
                this,
                "Wybierz organizm do dodania: ",
                "Dodaj organizm",
                JOptionPane.PLAIN_MESSAGE,
                null,
                opcje,
                opcje[0]
        );

        if(wybor!=null){
            Organizm nowy=OrganizmFactory.stworz(wybor, x, y, swiat);
            if(nowy!=null){
                swiat.dodajOrganizm(nowy);
                updateGrid();
            }
        }
    }

    private void updateLog() {
        List<String> logi = swiat.getLogi();
        logArea.setText("");
        for (String wpis : logi) {
            logArea.append(wpis + "\n");
        }
    }
}
