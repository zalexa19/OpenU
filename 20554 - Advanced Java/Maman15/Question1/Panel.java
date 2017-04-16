import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


/**
 * Created by Alex Z
 * 
 * Maman15
 * Exercise1
 */

public class Panel extends JPanel {
    private int matrixSize,numOfThreads,numOfReps,blackPixels;
    private JButton cmdGo,cmdClear,cmdPixel;
    private  JButton[][] matrix;
    private boolean active=false;

    private final Color BLACK = Color.BLACK;
    private final Color WHITE = Color.WHITE;
    JPanel controls, pixelsPane;


    public Panel() {

        String input =JOptionPane.showInputDialog("Required number of pixel: (nxn)");
        matrixSize=Integer.parseInt(input);

        matrix = new JButton[matrixSize][matrixSize];


        input=JOptionPane.showInputDialog("Enter number of threads");
        numOfThreads=Integer.parseInt(input);

        input=JOptionPane.showInputDialog("Enter number of repetitions");
        numOfReps=Integer.parseInt(input);


        //DELETE ME
       /* matrixSize = 6;
        numOfThreads=5;
        numOfReps=2;
      */


        controls = new JPanel();
        cmdGo = new JButton("Go");
        cmdClear = new JButton("Clear");


        controls.setLayout(new GridLayout(1, 2));
        controls.add(cmdGo);
        controls.add(cmdClear);

        this.setLayout(new BorderLayout());
        add(controls, BorderLayout.SOUTH);


        pixelsPane = new JPanel();
        add(pixelsPane, BorderLayout.NORTH);
        GridLayout gridLayout = new GridLayout(matrixSize, matrixSize);
        gridLayout.setHgap(0);
        gridLayout.setVgap(0);

        pixelsPane.setLayout(gridLayout);
        pixelsPane.setBackground(Color.yellow);
        BtnListner btnListner = new BtnListner();

        cmdClear.addActionListener(btnListner);
        cmdGo.addActionListener(btnListner);

        /*Creating buttons and connecting to a listner*/
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                cmdPixel = createButton();
                matrix[i][j]= cmdPixel;

                pixelsPane.add(cmdPixel);
                cmdPixel.setOpaque(true);
                cmdPixel.setBackground(WHITE);

                cmdPixel.addActionListener(btnListner);

            }
        }

    }



    /*This method creates a button with a flat background*/
    private JButton createButton() {
        JButton button = new JButton();
        Border line = new LineBorder(Color.lightGray);
        Border margin = new EmptyBorder(matrixSize, matrixSize, matrixSize, matrixSize);
        Border compound = new CompoundBorder(line, margin);
        button.setBorder(compound);
        return button;
    }


    private class BtnListner implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            if (e.getSource()==cmdClear){
                for (int i = 0; i< matrixSize; i++){
                    for (int j = 0; j< matrixSize; j++){
                        if (matrix[i][j].getBackground()==BLACK){
                            matrix[i][j].setBackground(WHITE);
                        }
                    }
                }
            }

            if (e.getSource()==cmdGo){
                if (active==true){
                    System.out.println("Button already pressed");
                }

                else {
                    active = true;

                    Controller controlBoard = new Controller(matrixSize, numOfThreads,blackPixels);
                    RepsThread reps = new RepsThread(matrixSize,numOfReps,controlBoard,matrix);
                    reps.start();

                }
                active=false;
            }


            else {
                JButton button = (JButton) e.getSource();
                if (button.getBackground() == WHITE) {
                    button.setBackground(BLACK);
                    blackPixels++;
                }

                else {
                    button.setBackground(WHITE);
                }
            }

        }

    }






}



