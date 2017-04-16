/**
 * Maman 18 - AlexZ
 * 
 */
public class HashTable {
    private final int TABLESIZE=2000;
    private static final double PHI = 1.6180339887498948482/2;
    private List[] hashTable;


    public HashTable(){
        hashTable = new List[TABLESIZE];
    }


    public int hashFunction (int value){
        int result;
        double calc =(value*PHI)%1;
        result= (int)(TABLESIZE*calc);
        return result;

    }

    /*This method receives the value to be stored in the hash table and the key to be hashed
    * (Either account number or customer ID)
    */

    public void insertNewRecord(int key, Account valueAccount){
        int hashedKey = hashFunction(key);

        if (hashTable[hashedKey]==null){
            List linkedList = new List();
            hashTable[hashedKey]=linkedList;
        }
        hashTable[hashedKey].addToList(valueAccount);
    }





    public void removeRecord(int value){
        int index = hashFunction(value);

        if (hashTable[index] != null) {
            Account account = searchRecord(value);
            List values = hashTable[index];

            values.removeFromList(account);
        }

        else {
            //System.out.println("Value "+value+ "doesn't exist in the table");
        }

    }




    public Account searchRecord(int value){
        int index = hashFunction(value);
        Account result;

        if (hashTable[index]==null){
            //System.out.println("Cell "+ index + "No results found for: "+value);
            return null;
        }

        List values = hashTable[index];
        //Search by account number:

        result=values.searchForAnAccountInList(value);

        if (result==null){
            result=values.searchByCustomerId(value);
        }

        return result;
    }


    public List[] getHashTable(){
        return hashTable;
    }

}
