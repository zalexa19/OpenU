import java.util.Arrays;
import java.util.Random;

/**
 * Created by alexz on 12/23/16.
 */
public class Program {
    public static void main (String[] args) {

        int[] numberA= randomizeNumber(50);
        int[] numberB=randomizeNumber(100);
        int[] numberC=randomizeNumber(200);

/*        int[] testNumber = new int[]{0, 2, 7, 1, 60};

        Heap newHeap = new Heap(testNumber, 2);
        newHeap.heapSort();
        System.out.println(testNumber + " New: " + newHeap.getSeries());
        System.out.println(Arrays.toString(newHeap.getSeries()));
        System.out.println("Number of Comparisons: " + newHeap.getNumOfComparisons());
        System.out.println("Number of Copies: " + newHeap.getNumOfCopies());


        */


        //NumberA

        System.out.println(Arrays.toString(numberA));


        System.out.println("NumberA:");
        System.out.println("----------------------------");
        sortAndPrint(numberA);



        //NumberB:
        System.out.println("\nNumberB:");
        System.out.println("----------------------------");
        sortAndPrint(numberB);


        //NumberC:
        System.out.println("\nNumberC:");
        System.out.println("----------------------------");
        sortAndPrint(numberC);

    }

    private static void sortAndPrint (int[] array){

        for (int i = 2; i < 6; i++) {
            Heap newHeap = new Heap(array,i);
            newHeap.heapSort();
            System.out.println("d = " + i + " Number of Comparisons: " + newHeap.getNumOfComparisons());
            System.out.println("d = " + i + " Number of Copies: " + newHeap.getNumOfCopies());

        }

    }


    private static int[] randomizeNumber (int arraySize){
        int[] array = new int[arraySize];
        int low= 0;
        int high= 1023;
        Random rand = new Random();

        for (int i = 0; i<arraySize; i++ ){
            array[i]= rand.nextInt(high-low)+low;
        }

        return array;
    }

}
