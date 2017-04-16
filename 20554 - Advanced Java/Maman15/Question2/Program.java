/**
 * Alex Z
 * 
 * Maman15, Exercise2
 *
 * I used an ArrayList to store the int[].
 * removeTwo() removes to arrays from the LinkedList, merges them together. the merged array is picked up by the thread.
 * The thread sorts the merged array using a simple linear scan (not the best performance though) - I created a specific method for that
 * When sorting is done, the thread sends the sorted array back to the LinkedList.
 *
 *
 * Thanks
 */


import java.util.Scanner;

public class Program {
    public static void main (String [] args){
        int arraySize,numberOfThreads;

        Scanner scan=new Scanner(System.in);
        System.out.println("How many numbers do you want in the array?");
        arraySize = scan.nextInt();
        System.out.println("How many threads?");
        numberOfThreads=scan.nextInt();

        Controller controlBoard = new Controller( arraySize,numberOfThreads);

        System.out.println("Randomized Array:");

        controlBoard.printArray(controlBoard.getOrigArray());
        System.out.println("Calculating, Please wait\n");


        for (int i=0; i<numberOfThreads; i++){
            PrimeThread thread = new PrimeThread(controlBoard);
            controlBoard.waitForThread();
            thread.start();
        }



        controlBoard.waitForAll();
        System.out.println("\nThe sorted array is:");
        controlBoard.checkSort();
    }
}
