/**
 * Created by alexz on 3/6/17.
 */
public class ListNode {
    private Account accountNumber;
    private ListNode previous;
    private ListNode next;



    public ListNode(Account a){
        accountNumber=a;
        previous=null;
        next=null;
    }



    public void setListNodePointers (ListNode p, ListNode n){
        previous=p;
        next=n;
    }

    public ListNode getPrevious(){
        return previous;
    }

    public ListNode getNext(){
        return next;
    }

    public void setPrevious(ListNode l){
        previous=l;
    }
    public void setNext(ListNode newNext){
        next=newNext;
    }

    public Account getAccountObject(){
        return accountNumber;
    }

}
