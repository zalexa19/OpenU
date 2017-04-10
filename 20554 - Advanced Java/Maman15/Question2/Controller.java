/**
 * Alex Zablotsky
 * 314494964
 * Maman15, Exercise2
 */


import java.util.LinkedList;

public class Controller {
    private int arraySize;
    private int numOfThreads;
    private int activeThreads;
    private int waiting;
    private int[] origArray;
    private int origArraySize;



    LinkedList<int[]> repository;
    private boolean done = false;

    public Controller(int size, int threads){
        arraySize=size;
        numOfThreads=threads;
        activeThreads=0;
        origArray=new int[size];
        repository=new LinkedList<>();
        waiting=0;
        origArraySize=origArray.length;

        origArray=generateRandomNumbers(size);
        createRepository(origArray);

    }



    private int[] generateRandomNumbers(int size){
        int[] array = new int[size];
        for (int i=0;i<size;i++){
            array[i]=(int)(Math.random()*100);
        }
        return array;
    }


    /*This creates the initial repository - each node holds an array of 1 cell*/
    private void createRepository(int[] array){
        for (int i=0; i<arraySize;i++){
            int[] tempArray = new int[1];
            tempArray[0]=array[i];
            repository.add(tempArray);
        }

    }

    public synchronized int[] removeTwo(){
        int[] mergedResult;

        while (repository.size()<=1 && done == false){
            if (waiting==numOfThreads-1){
                done=true;
                break;
            }

            else {
                try {
                    waiting++;
                    wait();
                }catch (InterruptedException e){}
                waiting--;
            }

        }

        if (done==true){
            return null;
        }


        else {
            /*Merge to cells and send to the thread for sorting*/
            int[] array1, array2;
            array1=repository.remove(0);
            array2=repository.remove(0);
            mergedResult=mergeArrays(array1,array2);
        }

        //printArray(mergedResult);

        return mergedResult;
    }




    /*Method that merges two arrays*/
    private int[] mergeArrays(int[] array1, int[] array2){
        int size = array1.length+array2.length;
        int[] merged = new int[size];
        int array1Size=array1.length;
        int array2Size=array2.length;
        int copyFrom=0;

        for (int i=0; i<array1Size;i++){
            merged[i]=array1[i];

        }

        for (int i=array1Size;i<size;i++){
            merged[i]=array2[copyFrom];
            copyFrom++;
        }

        return merged;
    }


    public synchronized void returnToRepository(int[] array){
        repository.add(array);
        notifyAll();
    }


    /*This method checks if the sort was done correctly*/
    public void checkSort(){

        int[] sortedResult = repository.getFirst();
        printArray(sortedResult);

    }

    public synchronized void waitForThread() {
        if (activeThreads == numOfThreads) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        } else {
            activeThreads++;
        }
    }

    public synchronized void finished(){
        activeThreads--;
        //System.out.println("Finished");
        notifyAll();
    }

    public synchronized void waitForAll(){
        while (done==false){
            try{
                wait();
            }catch (InterruptedException e ){}
        }

    }


    /*Getters*/
    public LinkedList<int[]> getRepository(){
        return repository;
    }
    public int[] getOrigArray(){
        return origArray;
    }

    public int getActiveThreads() {
        return activeThreads;
    }
    public int getOrigArraySize() {
        return origArraySize;
    }




    /*Printing an array*/
    public void printArray(int[] array){
        for (int i=0;i<array.length-1;i++){
            System.out.print(array[i]+ ", ");
        }

        System.out.print(array[array.length-1]);
        System.out.println("");
    }


}
