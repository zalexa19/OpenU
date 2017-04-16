import java.awt.*;
import javax.swing.JPanel;
import java.util.Random;

/**
 * 
 * Alex Z, Maman11
 */
public class Shapes extends JPanel {
    private int choice;
    private Color[][] colorTable;

    public Shapes(int userChoice) {
        choice = userChoice;
        colorTable = new Color[choice][choice];

        generateColors(); //Generates an array of random colors

    }


    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        int ovalWidth = getWidth() / choice;
        int ovalHeight = getHeight() / choice;

        for (int y = 0; y < choice; y++) {
            for (int x = 0; x < choice; x++) {
                g.setColor(colorTable[y][x]);
                g.fillOval(x * ovalWidth, y * ovalHeight, ovalWidth, ovalHeight);
            }
        }

    }


    public void generateColors(){
        for (int row=0;row<choice;row++) {
            for (int column =0; column < choice;column++){
                colorTable[row][column]=getRandomColor();
            }
        }
    }


    private Color getRandomColor()

    {
        Random rand = new Random();

        int low = 0;
        int high = 3;

        int result = rand.nextInt(high - low) + low;

        if (result == 0) {
            return Color.BLACK;
        }

        if (result == 1) {
            return Color.WHITE;

        }

        else
        {
            return Color.GRAY;
        }
    }
}








