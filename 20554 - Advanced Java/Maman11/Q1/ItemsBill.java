/**
 * Created by alexz on 11/3/16.
 *  * Maman11 Q1A
 * Alex Zablotsky
 * 314494964
 * This method holds the items for a client's bill
 */
public class ItemsBill
{
    private String itemName;
    private int itemAmount;
    private double itemPrice;


    public ItemsBill (String name, int amount, double price){
        itemName=name;
        itemAmount=amount;
        itemPrice=price;
    }

    public ItemsBill (ItemsBill newItem){
        ItemsBill copyItem=new ItemsBill(newItem.getItemName(),newItem.getAmount(),newItem.getPrice());



    }


    /* SETTERS and GETTERS*/
    public void setItemName (String name) {
        itemName=name;
    }

    public void setAmount (int amount){
        itemAmount=amount;
    }

    public void setPrice (int price) {
        itemPrice=price;
    }

    public String getItemName ()
    {
        return itemName;
    }

    public int getAmount()
    {
    return itemAmount;
    }

    public double getPrice ()
    {
        return itemPrice;
    }



}
