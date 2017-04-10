/**
 * Alex Zablotsky- 314494964 - Maman14
 * Tested for Integer class
 */
public class IntegerTester {

    public static void main(String[] args) {

    //Question 1B - Tests for Integer

        System.out.println("Adding");
        System.out.println("---------");
        System.out.println("Original Queue:");
        Queue<Integer> queue1 = buildIntegerQueue();
        queue1.printWholeQueue();
        System.out.println("Added number 4 with priorty 2 :");
        queue1.addItem(4,2);
        queue1.printWholeQueue();

        System.out.println("Added numbers 7,8 with priorty 3 :");
        queue1.addItem(8,3);
        queue1.addItem(7,3);
        queue1.printWholeQueue();

        System.out.println("Added numbers 9, 10 with priorty 5,1 :");

        queue1.addItem(9,5);
        queue1.addItem(10,1);
        queue1.printWholeQueue();

        System.out.println("Poll");
        System.out.println("---------");
        System.out.println("Removing the first numbers");
        for (int i=0;i<2;i++) {
            queue1.pollHead();
            queue1.printWholeQueue();
        }
        Queue queue2 = new Queue(3);
        System.out.print("Polling from an empty queue: ");
        queue2.pollHead();

        System.out.println("Contains");
        System.out.println("---------");

        System.out.println("Does the queue contain an 8 (true): "+ queue1.containsItem(8));
        System.out.println("Does the queue contain an 1 (false): "+ queue1.containsItem(1));
        System.out.println("Does the queue contain an 1 (false): "+ queue2.containsItem(1));

        System.out.println("Remove");
        System.out.println("---------");

        queue1.addItem(3,1);
        queue1.printWholeQueue();
        System.out.println("Removing 3:");
        queue1.removeItem(3);
        queue1.printWholeQueue();

        queue1.addItem(7,3);
        queue1.printWholeQueue();
        System.out.println("Removing 7:");
        queue1.removeItem(7);
        queue1.printWholeQueue();

        System.out.println("Queue size is: "+queue1.getSize());



    }


    public static Queue<Integer> buildIntegerQueue(){
        //Priority 1-5
        Queue newQueue = new Queue (5);

        for (int i=0; i<5; i++){
            newQueue.addItem(i+1,i+1);
        }
        return newQueue;
    }



}
