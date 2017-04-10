/**
 * Alex Zablotsky, 314494964, Maman11
 */
import javax.swing.JFrame;
import javax.swing.JOptionPane;


public class ShapesProgram {
    public static void main(String[] args) {
        String input = JOptionPane.showInputDialog("How many ovals would you like?");
        int choice = Integer.parseInt(input);

        Shapes panel = new Shapes(choice);
        JFrame window = new JFrame();
        window.add(panel);

        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setSize(500, 500);
        window.setVisible(true);


        int randomizeChoice = JOptionPane.YES_OPTION;

        while (randomizeChoice==JOptionPane.YES_OPTION) {

            randomizeChoice=JOptionPane.showConfirmDialog(null, "Would you like to randomize the colors?");

            if (randomizeChoice == JOptionPane.YES_OPTION) {

                panel.generateColors();
                panel.repaint();

            }

            else {
                randomizeChoice=1;
            }
        }

        System.out.println("END");
    }
}
