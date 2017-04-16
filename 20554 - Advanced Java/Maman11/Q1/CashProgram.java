/**
 * Created by alexz
 * Maman11 Q1B
 * Alex Z
 * 
 */
import java.util.Scanner;

public class CashProgram {
    public static void main (String [] args) {
        int userChoise=0;

        Scanner userInput = new Scanner(System.in);

        System.out.println ("Welcome to the Register. Please choose how you want to start the register:");
        System.out.println ("1. Resigter is empty");
        System.out.println("2. Register already has money");

        userChoise=userInput.nextInt();
        CashRegister register;

        if (userChoise==1) {
            register = new CashRegister();
            System.out.println ("Register was initialized with as an empty register");

        }
        else {
            System.out.println ("Please enter the initial amount (double):");
            double initialAmount=userInput.nextDouble();
            register = new CashRegister(initialAmount);
            System.out.println ("Register was initialized with  "+initialAmount+" as an initial money amount\n\n");


        }


        while (userChoise != 9 ) {

            System.out.println ("\nMENU\n");
            System.out.println ("1. Add items to a bill");
            System.out.println ("2. Get current amount of money in the register");
            System.out.println ("9. Close the program  ");

            userChoise = userInput.nextInt();

            if (userChoise==1) {
                while ((userChoise !=9)&& (userChoise!=5)){
                    System.out.println ("\nMENU\n");
                    System.out.println ("1. Add a new item to the bill");
                    System.out.println ("2. View items on current bill");
                    System.out.println ("3. View sum amount of current purchase");
                    System.out.println ("4. Pay the bill");
                    System.out.println ("5. Back to the main menu");
                    System.out.println ("9. Close the program");

                    userChoise=userInput.nextInt();

                    if (userChoise==1){
                        System.out.println ("\nPlease enter the item name:");
                        String itemName = userInput.next();
                        System.out.println ("Please enter the item amount");
                        int itemAmount=userInput.nextInt();
                        System.out.println ("Please enter the item price:");
                        double itemPrice=userInput.nextDouble();

                        ItemsBill newItem = new ItemsBill(itemName,itemAmount,itemPrice);
                        register.addItemToList(newItem);
                    }

                    if (userChoise==2) {
                        System.out.println("\nCurrent Bill:");
                        System.out.println("Item Name\t ItemAmount\t Price");
                        for (int i=0;i<register.billArray.size();i++){
                            System.out.println(register.billArray.get(i).getItemName()+"\t\t\t"+
                            register.billArray.get(i).getAmount()+"\t\t\t"+
                            register.billArray.get(i).getPrice()+"\n");

                        }
                    }

                    if (userChoise==3){
                        System.out.println("\nCurrent purchace amount is: "+register.getCurrentPurchaseSum());
                    }

                    if (userChoise==4){
                        System.out.println("\nTo pay: "+register.getCurrentPurchaseSum());
                        System.out.println("Please enter the amount paid by the customer(double):");
                        double paid = userInput.nextDouble();
                        System.out.println("Paid: "+paid+"\nChange is: "+register.calculateChange(paid));
                        userChoise=5; //to go back to the previous menu
                    }
                }



            }

            if (userChoise ==2){
                System.out.println("\nCurrent amount of cash in the register: "+ register.getAllPurchacesAmount());

            }

        }

        System.out.println("END OF PROGRAM, BYE");

    }
}
