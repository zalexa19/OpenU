import javax.swing.*;
import java.awt.*;

/**
 * Created by Alex Zablotsky
 * 314494964
 * Maman15
 * Exercise1
 */


public class RepsThread extends Thread {

    private Controller controlBoard;
    private int maxNumOfReps, numOfRepsDone, size;
    private JButton matrix[][];
    private final Color BLACK = Color.BLACK;
    private final Color WHITE = Color.white;

    public RepsThread (int n,int t, Controller c, JButton[][] buttons){
        controlBoard=c;
        maxNumOfReps=t;
        numOfRepsDone=0;
        size=n;
        matrix=buttons;
    }


    public void run(){

        while (numOfRepsDone<maxNumOfReps) {
            if (controlBoard.getBlackPixels() > 0) {
                numOfRepsDone++;
                System.out.println("Starting round #" + numOfRepsDone);

                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        PrimeThread thread = new PrimeThread(matrix, i, j, controlBoard);
                        controlBoard.waitForThread();
                        thread.start();
                    }
                }

                        /*REPAINT*/
                System.out.println("Waiting for all");
                controlBoard.waitForAll();
                repaintMatrix(matrix, controlBoard.getNextStage());
                System.out.println(" ");
                controlBoard.printHelp();
                System.out.println(" ");

                System.out.println("end of rep #" + numOfRepsDone + ". Sleeping.");

                try {
                    sleep(100);
                } catch (InterruptedException e) {
                }

            }

        }

    }


    private void repaintMatrix(JButton[][] buttonsArray, int[][] nextStageArray ){
        int length=buttonsArray.length;
        for (int i=0;i<length;i++){
            for (int j=0;j<length;j++){
                if ((nextStageArray[i][j]==0)&&(buttonsArray[i][j].getBackground()==BLACK))
                {
                    buttonsArray[i][j].setBackground(WHITE);
                }
            }
        }

    }


}
