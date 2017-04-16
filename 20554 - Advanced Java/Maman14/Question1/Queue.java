import java.util.Iterator;
import java.util.LinkedList;


/**
 *Alex Z-  - Maman14
 */
public class Queue <T> {
    private final int MINIMUMPRIORITY = 1;
    private final int MAXIMUMPRIORITY = 10;
    private LinkedList<Item<T>> queue;
    private int maxPriority;


    /*A constructor that creates a new priority queue based on the given initial capacity*/
    public Queue(int priorities) {
        if ((priorities >= MINIMUMPRIORITY) && (priorities <= MAXIMUMPRIORITY)) {
            maxPriority = priorities;
            queue = new LinkedList<>();

        } else {
            throw new IllegalArgumentException("Priority can be between 1-10");
        }
    }


    /*Adding a new item to the queue*/

    public void addItem(T value, int itemPriority) {

        Item newItem = new Item(itemPriority, value);

        if ((itemPriority < MINIMUMPRIORITY) || (itemPriority > MAXIMUMPRIORITY)) {
            newItem.set_priority(maxPriority);
        }


        if (queue.size() == 0) {
            queue.addFirst(newItem);
        } else {
            int counter = 0;
            Iterator<Item<T>> iterator = getIterator();
            while( (iterator.hasNext()) && (iterator.next().get_priority()<=newItem.get_priority())){
                counter++;

            }


            queue.add(counter,newItem);

        }

    }


    /*Pulling the first item*/
    public T pollHead() {
        if (queue.isEmpty()==true){
            System.out.println("Queue is empty. Nothing to pull");
            return null;
        }

        return (T) queue.pollFirst().get_item();

    }


    public boolean  containsItem(T key) {
        int size = queue.size();
        for (int i=0; i<size; i++){
            if (queue.get(i).get_item().equals(key)){
                return true;
            }
        }
        return false;
    }





    /*Finds first occurrence of the key*/
    public int findFirstOccurence(T key) {
        int counter = 0;
        int size = queue.size();

        for (int i = 0; i < size; i++) {
            if (queue.get(i).get_item() == key) {
                return counter;
            }
            counter++;
        }

        counter=-1;
        return counter;
    }




    public boolean removeItem(T key) {
        if (this.containsItem(key)){

            int size = queue.size();

            for (int i = 0; i < size; i++) {
                if (queue.get(i).get_item().equals(key)) {
                    queue.remove(i);
                    return true;
                }
            }
        }

        return false;
    }


    public int getSize (){
        return queue.size();
    }





    public Iterator<Item<T>> getIterator(){
        Iterator<Item<T>> iterator = queue.iterator();
        return iterator;
    }


    public void printTheItems() {
        Iterator<Item<T>> it=getIterator();
        while (it.hasNext()) {
            System.out.print(it.next().get_item()+" ");
        }
        System.out.println("");
    }

    public void printPriorities(){
        Iterator<Item<T>> it=getIterator();
        while (it.hasNext()) {
            System.out.print(it.next().get_priority()+" ");
        }
        System.out.println("");
    }

    public void printWholeQueue(){
        Iterator<Item<T>> it=getIterator();
            System.out.print("Items:      ");
            printTheItems();
            System.out.print("Priorities: ");
            printPriorities();
            System.out.println("");
    }





}
