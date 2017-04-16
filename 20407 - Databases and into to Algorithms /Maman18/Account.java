/**
 * Maman 18 - AlexZ
 * 
 */
public class Account {
    private String customerName;
    private int customerId, accountNumber;
    private int balance;
    private ListNode nListNode;
    private TreeNode treeNode;
    private boolean negativeBalance;

    public Account(int accNum, int custId, String name){
        accountNumber=accNum;
        customerName=name;
        customerId=custId;
        balance=0;
        treeNode = null;
        negativeBalance=false;
    }


    public Account(int accNum, int custId, String name, int balance){
        accountNumber=accNum;
        customerName=name;
        customerId=custId;
        this.balance=balance;
        treeNode = null;
        if (balance > 0) {
            negativeBalance = false;
        }
        else{
            negativeBalance=true;
        }
    }





    public void updateBalance(int amount){
        balance +=amount;
        if (amount<0) {

            //System.out.println("Successfully withdrew "+amount+ " account number: "+accountNumber);
        }
        else {
            //System.out.println("Successfully deposited "+amount+ " account number: "+accountNumber);
        }

        if (balance < 0){
            negativeBalance=true;
        }
        else negativeBalance=false;



    }



    public void printBalance(){
        System.out.println("Current Balance: "+balance);
    }



    /*Setters and getters*/
    public int getAccountNumber(){
        return accountNumber;
    }

    public int getCustomerId(){
        return customerId;
    }

    public String getCustomerName(){
        return customerName;
    }

    public int getBalance(){
        return balance;
    }

    public ListNode getnListNode() {
        return nListNode;
    }

    public TreeNode getTreeNode(){
        return treeNode;

    }

    public boolean isNegativeBalance() {
        return negativeBalance;
    }


    public void setTreeNode(TreeNode pointer){
        treeNode =pointer;
    }

    public void setnListNode(ListNode nListNode) {
        this.nListNode = nListNode;
    }


}
