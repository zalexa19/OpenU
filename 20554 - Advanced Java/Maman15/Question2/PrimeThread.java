
/**
 * Alex Z
 * 
 * Maman15, Exercise2
 */


public class PrimeThread extends Thread {
    private Controller controlBoard;


    public PrimeThread(Controller c){
        controlBoard=c;
    }


    public void run(){
        System.out.println("Thread is alive.");

        int[] toSort = controlBoard.removeTwo();

        while (toSort!=null) {
            sortArray(toSort);
            controlBoard.returnToRepository(toSort);

           /* System.out.println("Sorted Array:");
            controlBoard.printArray(toSort);
           */
            toSort=controlBoard.removeTwo();
        }

        //System.out.println("Finished #"+controlBoard.getActiveThreads());
        controlBoard.finished();
    }


    private void sortArray(int[] array){
        for (int i=0; i<array.length; i++){
            int min = i;
            for (int j=i;j<array.length;j++){
                if (array[j]<array[min]){
                    int temp=array[min];
                    array[min]=array[j];
                    array[j]=temp;

                }

            }
        }
    }







}
