import java.util.Iterator;

/**
 * Alex Zablotsky- 314494964 - Maman14
 *This is the tested for the class CustomerApplication
 */
public class ApplicationTester {

    public static void main (String[] args){

        CustomerApplication custApp1 = new CustomerApplication(12556,"John Doe","Wifi is down");
        CustomerApplication custApp2 = new CustomerApplication(12456,"Aaron Q. Clemens",
                "I bought your product but it doesn’t do what it’s supposed to do");
        CustomerApplication custApp3 = new CustomerApplication(12451,"Tommy Bateman",
                "I bought your product but it doesn’t do what it’s supposed to do");
        CustomerApplication custApp4 = new CustomerApplication(12451,"Tommy Bateman","Well, your competitors said they would do this…");
        CustomerApplication custApp5 = new CustomerApplication(12451,"Tommy Bateman","Termination of services");


        Queue complaints = new Queue<>(3);
        complaints.addItem(custApp1,1);
        complaints.addItem(custApp2,2);
        complaints.addItem(custApp3,2);
        complaints.addItem(custApp4,3);

        //Print the queue
        Iterator <Item<CustomerApplication>> it=complaints.getIterator();
        printComplains(complaints,it);

        System.out.println("");
        System.out.println("tests for \"containsItem\": ");
        System.out.println("Should be true:"+ complaints.containsItem(custApp3));
        System.out.println("Should be false:"+ complaints.containsItem(custApp5));

        System.out.println("");
        System.out.println("tests for \"pollHead\": ");
        System.out.println("First complaint is: "+ custApp1.get_id()+", "+ custApp1.get_userInput());
        CustomerApplication head = (CustomerApplication) complaints.pollHead();
        System.out.println("Polling: "+head.get_id()+", "+head.get_userInput());

        System.out.println("");
        System.out.println("Tests for \"RemoveItem\": ");
        System.out.println("Queue size is: "+complaints.getSize());
        System.out.println("Removing "+custApp3.get_name()+", "+custApp3.get_userInput());
        System.out.println(complaints.removeItem(custApp3));
        System.out.println("Queue size is: "+complaints.getSize());


        System.out.println("");






    }

    public static void printComplains(Queue<Item> queue, Iterator<Item<CustomerApplication>> it){
        while (it.hasNext()){
            Item<CustomerApplication> nextItem = it.next();
            System.out.println(nextItem.get_item().get_id()+", "+nextItem.get_item().get_name()+", "+nextItem.get_item().get_userInput());
        }

    }
}

/*
* */