import java.util.Scanner;

/**
 * Maman 18 - Alex Zablotsky
 * 314494964
 */


public class Program {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input, name;
        int custId, accNo, bal;
        String[] words;
        Bank bank = new Bank();

        System.out.println("Welcome to the bank!");
        for (int i=0;i<1000; i++){
            bank.addNewAccount("AA AAA"+i,1000000+i,1000+i,(int)(Math.random()*5000));
        }


        input="start";
        while (!input.equals("end")) {
            System.out.println("\nPlease enter your query. Type \"end\" to quit the program");
            words=null;

            input = scanner.nextLine();
            words = input.split(" ");
            String s = words[0];

            if ((s.equals("+"))||(s.equals("-"))||(s.equals("?"))){
                int length = words.length;
                //A new customer is added (+ Name1 Name2 Id Account Amount
                if (length == 6) {
                    name = words[1] + " " + words[2];
                    custId = Integer.parseInt(words[3]);
                    accNo = Integer.parseInt(words[4]);
                    bal = Integer.parseInt(words[5]);
                    bank.addNewAccount(name, custId, accNo, bal);
                }

                //Queries
                if (length == 2) {
                    // Customer is leaving
                    if (words[0].equals("-")) {
                        accNo = Integer.parseInt(words[1]);
                        bank.removeAccount(accNo);

                    }
                    if (words[0].equals("?")){
                        //Getting maximum balance
                        if (words[1].equals("MAX") ) {
                            Account accountInfo=bank.getMaxBalance();
                            if (accountInfo==null){
                                System.out.println("There are no accounts in the system");
                            }
                            else {
                                System.out.println("Customer with the highest balance is:");
                                System.out.println(accountInfo.getCustomerName());
                                System.out.println("Id: "+accountInfo.getCustomerId());
                                System.out.println("Account number:: "+accountInfo.getAccountNumber());
                                System.out.println("Balance: " + accountInfo.getBalance());

                            }

                        } else if (words[1].equals("MINUS")) {
                            bank.printNegativeBalances();

                        } else {
                            accNo = Integer.parseInt(words[1]);
                            Account accountInfo = bank.getAccountInfo(accNo);

                            if (accountInfo==null){
                                System.out.println("Account "+accNo +" doesn't exit");
                            } else {
                                System.out.println("Balance for account number "+accNo+": "+accountInfo.getBalance());

                            }
                        }
                    }
                }
            }

            else {

                //Balance is updated: Name1 Name2 Account Amount
                if (words.length == 4) {
                    name = words[0]+" "+words[1];
                    accNo = Integer.parseInt(words[2]);
                    bal = Integer.parseInt(words[3]);
                    bank.updateBalance(name,accNo, bal);
                }

            }

        }

        System.out.println("Program ended");

    }

}