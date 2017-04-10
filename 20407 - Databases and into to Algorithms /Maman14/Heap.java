import java.util.Arrays;

/**
 * Created by alexz on 12/23/16.
 */
public class Heap {
    int[] series;
    int[] heap;
    int dimension;
    int numOfComparisons,numOfCopies;
    int heapSize;

    /*CONSTRUCTORS*/

    public Heap (int[] newArray, int newDimension){
        if ((newDimension >5)|| (newDimension<2)){
            System.out.println("Invalid dimension. Please enter a valid one");
        }

        else {
            dimension=newDimension;
            series = Arrays.copyOf(newArray,newArray.length);
            heap = new int[series.length];
            heapSize=series.length-1;
            numOfCopies=0;
            numOfComparisons=0;
        }
    }



    /*HEAPSORT*/
    public  void heapSort(){
        //System.out.println("entered HeapSort\n");

        buildMaxHeap(series,dimension);
        for (int i=series.length-1; i>=1; i--){
            int temp=series[0];
            numOfCopies++;
            series[0]=series[i];
            numOfCopies++;
            series[i]=temp;
            numOfCopies++;

            heapSize=heapSize-1;
            maxHeapify(series,0,dimension);
        }

    }


    /*BUILD MAX HEAP*/
    public  void buildMaxHeap (int[] array, int dimention){


        for (int i=array.length/2; i>=0; i--){
            maxHeapify(array,i,dimention);
        }
    }




    /*HEAPIFY*/
    public  void maxHeapify (int[] array, int parent, int dimention) {
        //System.out.println("entered Heapify\n"+"working on index: "+parent+"["+array[parent]+"]");

        int largest = parent;
        int heapSize = array.length - 1;
        int child = 0;


        //find the largest child
        for (int i = 0; i < dimention; i++) {
            child = searchChild(parent, i, dimention);
            numOfComparisons++;

            if ((child <= heapSize) && (array[child] > array[largest])) {
                    largest = child;
            }

        }


        if ((largest != parent) && (largest!=0)){
            int temp = array[parent];
            numOfCopies++;
            array[parent] = array[largest];
            numOfCopies++;
            array[largest] = temp;
            numOfCopies++;
            maxHeapify(array, largest, dimention);


        }

    }


    //SEARCH CHILDREN
    private static int searchChild (int parent,  int child, int numOfChildren){

        if ((child > numOfChildren)|| (child<0))
        {

            System.out.println("Invalid child number. Please try again");
            return -1;
        }

     /*   if (numOfChildren==2){
            if (child%2==0){
                return 2*parent+1;
            }

            return 2*parent+2;
        }

        if (parent==0){
            return numOfChildren;
        }*/
        else {
            return (numOfChildren * parent) + (child);
        }
    }








    public int getDimension() {
        return dimension;
    }

    public int getHeapSize() {
        return heapSize;
    }

    public int getNumOfComparisons() {
        return numOfComparisons;
    }

    public int getNumOfCopies() {
        return numOfCopies;
    }

    public int[] getSeries() {
        return series;
    }
}
