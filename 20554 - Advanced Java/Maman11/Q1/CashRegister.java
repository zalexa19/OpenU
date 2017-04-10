import java.util.*;

/**
 * Created by alexz on 11/3/16.
 * Maman11 Q1A
 * Alex Zablotsky
 * 314494964
 * This is the cash register class.
 * This class initializes a dynamic array that expends if additional items are added to the bill.
 */
import java.util.ArrayList;

public class CashRegister {

    private double allPurchacesAmount;
    private double currentPurchaseSum;

    ArrayList<ItemsBill> billArray = new ArrayList<ItemsBill>();

    /* CONSTRUCTORS*/

    public CashRegister ()
    {
        allPurchacesAmount=0.0;
    }
    public CashRegister (double initialAmount) {
        allPurchacesAmount = initialAmount;
    }


    //Adds a new item to the bill, and also updates the current purchace calculation
    public void addItemToList (ItemsBill newItem) {
        currentPurchaseSum = currentPurchaseSum + (newItem.getAmount()*newItem.getPrice());
        billArray.add(newItem);
    }

    //returns an array with the list of items bought by the client
    public ArrayList getBillArray(){
        return billArray;
    }

    //return the current purchace sum
    public double getCurrentPurchaseSum (){

        return currentPurchaseSum;
    }

    public double calculateChange (double paid) {
        double change=0.0;
        change=paid-currentPurchaseSum;
        allPurchacesAmount=allPurchacesAmount+currentPurchaseSum;
        currentPurchaseSum=0.0;

        billArray.clear();

        return change;
    }

    public double getAllPurchacesAmount() {
        return allPurchacesAmount;
    }

}
