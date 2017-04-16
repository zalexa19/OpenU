import javax.swing.*;

/**
 * Alex Z
 * 
 * Maman14 Question2
 */
public class Program {
    public static void main (String [] args){


        JFrame window = new JFrame("PhoneBook");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        PhoneBookPanel panel = new PhoneBookPanel();
        //panel.setBackground(Color.pink);
        window.add(panel);
        window.setSize(500,500);
        window.setVisible(true);

    }
}
