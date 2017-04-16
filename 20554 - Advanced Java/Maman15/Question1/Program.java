import javax.swing.*;

/**
 * Created by Alex Z
 * 
 * Maman15
 * Exercise1
 *
 * Pixels pane is represented by JButtons. Each click on a "pixel" changes the background to black/white.
 * I have created another array of type int[][] to represent the next picture.
 * When creating the threads, each thread receives 1 pixel and checks it's neightbours. If that pixel is black in a white surroundingg,
 * the Thread marks the representing cell of the next stage array as white.
 * When all threads are done running, I fix the Jbuttons to match the 'next stage array' - meaning updating the background.
 * I have created a thread that creates the 'worker' threads so I can easily count the number of 't's.
 *
 *
 */


public class Program {

    public static void main (String[] args){
        int n = 15;
        int screenSize=n*35;

        JFrame window = new JFrame("Shrink");

        Panel myPanel = new Panel();
        window.add(myPanel);
        window.setSize(screenSize,screenSize);
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    }
}
