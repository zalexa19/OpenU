/**
 *
 * Maman 18 - Alex Zablotsky
 * 314494964
 * This class is the controller of all the databases in use.
 */
public class Bank  {
    private HashTable hashTable;
    private HashTable customerIdsTable;
    private List[] hashArray;
    private List negativeBalances;
    private RedBlackTree tree;


    public Bank(){
        hashTable = new HashTable();
        negativeBalances = new List();
        tree = new RedBlackTree();
        hashArray=hashTable.getHashTable();
        customerIdsTable= new HashTable();
    }


    /*Adds a new account to all of the databases*/

    /*This method receives the user info, creates a new account and adds it the DB:
    * 1. Checks if the account already exists
    * 2. If the account is new, it is added to the hash table
    * 3. If required, the account is added to the list of negative balances
    * 4. The balance is added to the RB Tree
    */

    public void addNewAccount (String customerName, int customerId, int accountNum, int balance){

        /*Checking if the Id already exists in the DB*/
        Account acc = customerIdsTable.searchRecord(customerId);
        if (acc != null){
            System.out.println("Account for id "+ customerId+" already exists: "+acc.getAccountNumber());
            return;
        }

        /*Checking if the account number already exists in the DB*/
        acc = hashTable.searchRecord(accountNum);
        if (acc !=null){
            System.out.println("Account "+accountNum+" cannot be re-added to the hash table");
            return;
        }

        acc = new Account(accountNum,customerId,customerName,balance);

        //Adding to the negative balances list
        if (acc.isNegativeBalance()){
            ListNode newNode= negativeBalances.addToList(acc);//This method adds the account as a list node and returns the list node
            acc.setnListNode(newNode); //Setting the account to point at the relevant list node
            System.out.println("Account "+acc.getAccountNumber()+" added to the negative balances list");
        }


        /*Add account to accounts hash table*/
        hashTable.insertNewRecord(acc.getAccountNumber(),acc);
        System.out.println("\nAccount "+accountNum+" was added to hash Table (accounts)");

        /*Add account to ids hash table*/
        customerIdsTable.insertNewRecord(customerId,acc);
        System.out.println("\nCustomer id "+customerId+" was added to hash Table (Ids)");


        /*Add account to tree */
        TreeNode newTreeNode = new TreeNode(acc);
        tree.rbInsert(newTreeNode);
        acc.setTreeNode(newTreeNode);
        System.out.println("\nAccount "+acc.getAccountNumber()+" successfully added to the the balances tree\n\n");
    }


    /**
     * This method updates the balance of the account, updates the negative list, update the position in the
     * Red and Black Tree. Running time: O(lgn)
     */
    public void updateBalance (String name, int accountId, int amount){
        Account accountInfo;
        /*1. Check if account exists in our DB*/

        accountInfo = hashTable.searchRecord(accountId);
        if (accountInfo==null){
            System.out.println("Account "+accountId+" was not found in DB");
            System.out.println("Balance was not updated.");
            return;

        } else {
            if (!accountInfo.getCustomerName().equals(name)){
                System.out.println("Account name:  "+accountInfo.getCustomerName()+" does not match given name: "+name);
                System.out.println("Balance was not updated.");
                return;
            }
        }

        //Account was found and we can update it
        boolean negative = accountInfo.isNegativeBalance();
        accountInfo.updateBalance(amount);
        /*2. Check if account should be removed from the negative balances list*/

        if (negative != accountInfo.isNegativeBalance()){
            //balance became negative -> need to add to the list
            if (accountInfo.isNegativeBalance()){
                ListNode newNode=negativeBalances.addToList(accountInfo);
                accountInfo.setnListNode(newNode);
            }
            //Balance became positive
            if (!accountInfo.isNegativeBalance()){
                negativeBalances.removeFromList(accountInfo);
                accountInfo.setnListNode(null);
            }
        }

        /*3. Update the tree - remove the old record and re-insert it*/
        TreeNode treeNode = accountInfo.getTreeNode();
        tree.rbDelete(treeNode);
        TreeNode newNode = new TreeNode(accountInfo);
        accountInfo.setTreeNode(newNode);
        tree.rbInsert(newNode);

    }


    private Account convertAcountIdtoObject(int accountId){
        int index = hashTable.hashFunction(accountId);
        Account result;

        if (hashArray[index]==null){
            return null;
        }


        result = hashArray[index].searchForAnAccountInList(accountId);
        return result;
    }





    /**
     * This method receives an account number and removes it completely from the DB
     * Running time: O(lgn)
     */
    public void removeAccount(int accountID){
        Account accountInfo=hashTable.searchRecord(accountID);
        if (accountInfo == null){
            System.out.println("Account "+accountID+" was not found in DB");
            return;
        }

        //Remove from negative list
        if (accountInfo.isNegativeBalance()){
            negativeBalances.removeFromList(accountInfo);
            System.out.println("Account "+accountID+" was removed from the negative list");
        }
        accountInfo.updateBalance(0);


        //Remove from hash tables
        hashTable.removeRecord(accountID);
        System.out.println("Account "+accountID+" was removed from the hash table");

        /*Remove from ids hashTable*/
        customerIdsTable.removeRecord(accountInfo.getCustomerId());
        System.out.println("Id "+accountInfo.getCustomerId() +" was removed hash table");

        /*Remove the account from the RB Tree*/
        TreeNode treeNode = accountInfo.getTreeNode();
        tree.rbDelete(treeNode);
        System.out.println("Account was removed from the tree");

    }


    /**
     * This method prints out the balance of the received customer.
     * Running time: O(1) (Search is done in the hash table)
     *
     */
    public Account getAccountInfo(int accountId) {
        Account accountInfo = hashTable.searchRecord(accountId);
        if (accountInfo==null){
            return null;
        }
        return accountInfo;
    }

    /**
     * Returns the maximum balance
     * Run time: O(1)
     */
    public Account  getMaxBalance(){
        TreeNode result=tree.getMaxBalanceNode();
        Account acc = result.getAccountObj();

        return acc;
    }


    /*
    * This method prints all the negative balances.
    * Run time: O(n)
    */

    public void printNegativeBalances(){
        negativeBalances.printList();
    }



}

