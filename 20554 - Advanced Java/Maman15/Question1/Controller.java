/**
 * Created by Alex Z
 * 
 * Maman15
 * Exercise1
 *
 *
 *
 *
 */



public class Controller {
    private int maxThreads,activeThreads, matrixSize, numOfchecks,blackPixels;
    private int numOfCells;
    private int[][] nextStage;



    public Controller(int n, int m,int black ){
        matrixSize=n;
        maxThreads=m;
        numOfchecks=1;
        activeThreads=0;
        blackPixels=black;
        numOfCells = matrixSize*matrixSize;
        nextStage = new int[matrixSize][matrixSize];
        clearNextStage();
    }


    public synchronized void waitForThread(){
        while (activeThreads==maxThreads){
            try{
                //System.out.println("waiting for a thread");
                wait();
            }catch (InterruptedException e){}
        }

        activeThreads++;

    }

    public synchronized void finished(){
        activeThreads--;
        notifyAll();
    }


    public synchronized void waitForAll(){
        if (numOfchecks<=numOfCells) {
            while (activeThreads > 0) {
                //System.out.println("Waiting for everyone to end: " + activeThreads + "threads");
                //System.out.println("number of checks: " + numOfchecks + " number of cells: " + numOfCells);
                try {
                    wait();
                } catch (InterruptedException e) {
                }
            }
        }
        System.out.println("All threads are done");
        numOfchecks=0;

    }

    public void clearNextStage(){

        for (int i=0;i<matrixSize;i++) {
            for (int j = 0; j < matrixSize; j++) {
                nextStage[i][j] = 0; /*Represents white*/
            }
        }
    }

    /*Setter*/
    public void setNextStage(int row, int column, int value){
        nextStage[row][column]=value;
    }

    public synchronized void  setNumOfchecks (){
        numOfchecks++;
    }

    public synchronized void decreaseBlackPixels (){
        blackPixels--;
    }



    /*Getter*/
    public int getBlackPixels(){
        return blackPixels;
    }

    public int[][] getNextStage(){
        return nextStage;
    }

    public int getNumOfchecks(){
        return numOfchecks;
    }

    public int getActiveThreads(){
        return activeThreads;
    }





    /*Temp*/
    public void printHelp(){
        for (int i=0; i<matrixSize; i++){
            for (int j=0; j<matrixSize; j++ ){
                System.out.print(nextStage[i][j]+" ");
            }
            System.out.println("");

        }
    }

}
