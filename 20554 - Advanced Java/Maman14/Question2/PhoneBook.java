/**
 * Alex z
 * 
 * Maman14 Question2
 */
import java.util.*;

public class PhoneBook {
    private TreeMap<String,String> dataBase;

    public PhoneBook()
    {
        dataBase =new TreeMap<String, String>();

    }


    /*Adds a new name to the database after verifying that it doesn't exist*/
    public void addRecord (String  name, String number)
            throws RecordAlreadyExists {
        if (dataBase.containsKey(name)){
            throw new RecordAlreadyExists ("Name "+name+" already exists in the DB");
        }

        dataBase.put(name,number);
    }


    public void removeRecord (String name) throws RecordDoesnotExist{
        if (dataBase.containsKey(name)){
            String tempNumber = dataBase.get(name);
            dataBase.remove(name,tempNumber);
        }

        else {
            throw new RecordDoesnotExist("Record for name: "+name+" doesn't exist");
        }

    }


    public void updateRecord (String key, String newName, String newNumber) throws RecordDoesnotExist{

        String origNumber = dataBase.get(key);
        try {
            removeRecord(key);
        }catch (RecordDoesnotExist e){
            throw new RecordDoesnotExist("Record for name: "+key+" doesn't exist");
        }

        try {
            addRecord(newName, newNumber);
        }catch (RecordAlreadyExists e){
            System.out.println("Record already exists");

            try {
                addRecord(key,origNumber);
            }catch (RecordAlreadyExists e1) {
            }

        }
    }




    public String findNumber (String name) throws RecordDoesnotExist{
        if (dataBase.containsKey(name)){
            return dataBase.get(name);
        }
        else
            throw new RecordDoesnotExist("Record doesn't exist");
    }



    public String getValue(String key){
        return dataBase.get(key);

    }

    public void printPhoneBook(){
        int size = dataBase.size();
        ArrayList<String> keys = new ArrayList<>(dataBase.keySet());
        ArrayList<String> values = new ArrayList<>(dataBase.values());

        for (int i=0;i<size;i++){
            System.out.println(keys.get(i)+", "+values.get(i));

        }

    }

    /*This method is used in the PhoneBookPanel for printing the phone book
    * It just spill the whole db into an array list and returns a new array list with a specific key and value
    * I wanted to print the phone book with my style and not key=value that treemap provides*/
    public String[] getSpesificRecord (int number){
        ArrayList<String> keys = new ArrayList<>(dataBase.keySet());
        ArrayList<String> values = new ArrayList<>(dataBase.values());
        String[] result = new String[2];

        result[0]=keys.get(number);
        result[1]=values.get(number);
        return result;

    }

    public int getSize(){
        return dataBase.size();
    }



}

