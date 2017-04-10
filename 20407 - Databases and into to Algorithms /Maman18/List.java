/**
 * Maman 18 - Alex Zablotsky
 * 314494964
 */

public class List {
    private ListNode head;
    private int listLength;

    public List(){
        head = null;
        listLength=0;
    }



    public ListNode addToList(Account account){
        ListNode newNode = new ListNode(account);

        if (head == null) {
            head = newNode;
        } else {
            newNode.setNext(head);
            head.setPrevious(newNode);
            head = newNode;
        }
        listLength++;
        return newNode;
    }


    public void removeFromList(Account account){
        ListNode current = head;
        while ((current != null) && (current.getAccountObject() !=account)) {
            current=current.getNext();
        }

        if (current == null ) {
            return;
        }

        ListNode previous = current.getPrevious();
        ListNode next = current.getNext();

        if (current == head){
            if (listLength==1) {
                head = null;
            }
            else {
                head=next;
            }

        }


        if ((previous != null) && (next != null)){
            previous.setNext(next);
            next.setPrevious(previous);
        }

        //End of the list
        else if (previous != null){
            previous.setNext(null);

        }

        //Start of list
        else if (next != null){
            next.setPrevious(null);
        }

        listLength--;
        System.out.println("Account "+account.getAccountNumber()+" was removed from the  list");




    }


    public Account searchForAnAccountInList(int value){
        Account result=null;
        ListNode currentNode=head;

        if (head==null){
            System.out.println("No accounts found");
            return result;
        }

        Account acc = currentNode.getAccountObject();

        while (currentNode != null){
            if ((currentNode.getAccountObject().getAccountNumber()==value)|| (currentNode.getAccountObject().getCustomerId()==value)) {
                acc=currentNode.getAccountObject();
                return acc;
            }
            else
            {
                currentNode=currentNode.getNext();
            }

        }
        return null;
    }



    public Account searchByCustomerId (int custId){
        Account result=null;
        ListNode currentNode=head;

        while (currentNode!=null){
            if (currentNode.getAccountObject().getCustomerId()==custId){
                result=currentNode.getAccountObject();
            }
            else {
                currentNode=currentNode.getNext();
            }
        }
        return result;
    }


    public void printList(){
        if (head==null){
            System.out.println("List is empty");
        }
        else {
            System.out.println("\nList has the following: ");
            ListNode currentNode=head;
            for (int i=0;i<listLength;i++) {
                Account account = currentNode.getAccountObject();
                System.out.println("Customer name: " + account.getCustomerName() +
                        " Account number: " + account.getAccountNumber() + " Current balance: " + account.getBalance());
                if (currentNode.getNext() != null) {
                    currentNode = currentNode.getNext();
                }
            }
        }
    }



    public ListNode getHead(){
        return head;
    }
}
