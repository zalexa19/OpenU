/**
 * Alex Zablotsky
 * 314494964
 * Maman12 - Question 1, A+B
 */
import javax.swing.*;

public class Tester{
    public static void main (String[] args) {



        JFrame window = new JFrame();
        MyPanel myPanel = new MyPanel();
        myPanel.setBackground(myPanel.getBg());


        window.add(myPanel);


        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setSize(400, 400);
        window.setTitle("Shapes");
        window.setVisible(true);



    }
}
