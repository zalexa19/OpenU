import java.util.Scanner;

/**
 * Alex Zablotsky
 * 324494964
 * Maman 12 Q2
 */
public class Program {
    public static void main (String [] args) {

        Scanner input = new Scanner(System.in);
        BigInt numberA;
        BigInt numberB;

        String numberInput ="empty";
        System.out.print("Hello!");
        while (numberInput=="empty") {
            try {
                System.out.print("Please give me your first big number: ");
                numberInput = input.nextLine();
                 numberA = new BigInt(numberInput);
            } catch (IllegalArgumentException e) {
                System.out.print("You have entered an invalid number. ");
                numberInput = "empty";
            }
        }

        numberA= new BigInt(numberInput);


        numberInput="empty";
        while (numberInput=="empty") {
            try {
                System.out.print("Please give me your second big number: ");
                numberInput = input.nextLine();
                numberB = new BigInt(numberInput);
            } catch (IllegalArgumentException e) {
                System.out.print("You have entered an invalid number. ");
                numberInput = "empty";
            }
        }
        numberB= new BigInt(numberInput);

        printMath(numberA,numberB);



    }

    public static void printMath(BigInt numberA, BigInt numberB){

        System.out.println(numberA.toString()+"+"+numberB.toString()+"= "+numberA.plus(numberB).toString());
        System.out.println(numberA.toString()+"-"+numberB.toString()+"= "+numberA.minus(numberB).toString());
        System.out.println(numberA.toString()+"/"+numberB.toString()+"= "+numberA.divide(numberB).toString());
        System.out.println(numberA.toString()+"x"+numberB.toString()+"= "+numberA.multiply(numberB).toString());

    }


}
