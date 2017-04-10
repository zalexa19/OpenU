

import javax.swing.*;
import java.awt.*;

/**
 * Created by Alex Zablotsky
 * 314494964
 * Maman15
 * Exercise1
 */




public class PrimeThread extends Thread {
    private final Color BLACK = Color.BLACK;
    private final Color WHITE = Color.white;

    private Controller controlBoard;
    private JButton[][] tMatrix;
    private int row,column;



    public PrimeThread(JButton[][] array, int i, int j,Controller c){
        tMatrix=array;
        controlBoard=c;
        row=i;
        column=j;

    }


    public void run(){

        //System.out.println("Checking cell number: " + controlBoard.getNumOfchecks());
        System.out.println("Thread#: "+ controlBoard.getActiveThreads()+" is born");

        if (!hasWhite())//if false paint black, if true remains white
        {
           // System.out.println("Setting next stage");
            controlBoard.setNextStage(row, column, 1);
        }

        else {
            if (tMatrix[row][column].getBackground()==BLACK){
                controlBoard.setNextStage(row,column,0);
                controlBoard.decreaseBlackPixels();
            }

        }

        controlBoard.setNumOfchecks();
        try{
            sleep(500);
        }catch (InterruptedException e){}

       // System.out.println("Thread finished");
        controlBoard.finished();




    }



    /*This method checks if a given cell (of the thread has a white surrounding*/
    private boolean hasWhite ( ){
       // System.out.println("Searching for white");
        JButton button = tMatrix[row][column];

        if (button.getBackground()==BLACK) {


            if ((row - 1 >= 0) && (tMatrix[row-1][column].getBackground() == WHITE)) {
               // System.out.println("Found a white left");
                return true;

            }

            if ((column + 1 < tMatrix[column].length) && (tMatrix[row][column + 1].getBackground() == WHITE)) {
                //System.out.println("Found a white bottom ");
                return true;
            }

            if ((column - 1 >= 0) && (tMatrix[row][column-1].getBackground() == WHITE)) {
                //System.out.println("Found a white top ");
                return true;
            }

            if ((row + 1 < tMatrix[row].length) && (tMatrix[row + 1][column].getBackground() == WHITE)) {
                //System.out.println("Found a white right");
                return true;
            }
        }

        if (button.getBackground()==WHITE){
            return true;
        }

        return false;
    }





}
