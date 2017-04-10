
import java.util.ArrayList;
import java.util.Collections;


/**
 * Alex Zablotsky
 * 324494964
 * Maman 12 Q2
 */

public class BigInt implements Comparable {
    private final int MAX=9;
    private final int DIGITSNUM=2;
    private final int CARRY=0;
    private final int RESULT=1;
    private ArrayList<Integer> bigNumberArray = new ArrayList<>();
    private boolean isNegative=false;

/*********************/
/*CONSTRUCTOR*/
/*********************/

    public BigInt (String string) {
        if (string.length()==0) {
            throw new IllegalArgumentException("No number was entered");
        }

        if ((string.length()==1) && ((string.charAt(0)=='+')||(string.charAt(0)=='-'))){
            throw new IllegalArgumentException("No number was entered");
        }


        string=string.replace(" ","");

        int start =0;
        if (string.charAt(0)=='-'){
            if (string.charAt(1)>0) {
                setNegative(true);
                start = 1;
            }
            else {
                throw new IllegalArgumentException("Number has some invalid chars");
            }

        }


        if (string.charAt(0)=='+'){
            start=1;
        }

        else {
            for (int i = start; i < string.length(); i++) {
                char character = string.charAt(i);

                if ((character < '0') || (character > '9')) {
                    throw new IllegalArgumentException("Invalid number");

                }
                else {
                    int tempChar = Character.getNumericValue(string.charAt(i));
                    bigNumberArray.add(tempChar);
                }
            }
        }
    }


    //Constructor that receives an ArrayList

    private BigInt (ArrayList<Integer> otherArray, boolean negative){
        setBigNumberArray(otherArray);
        setNegative(negative);
    }

/*********************/
/*METHODS*/
/*********************/


    public BigInt plus (BigInt otherNumber) {
        int carryover = 0;
        ArrayList<Integer> resultArray = new ArrayList();
        int[] addDigitsResult; //stores array received from a private method

        BigInt longer;
        BigInt shorter;

        /*Deciding which number is shorter*/
        if (this.getBigNumberArray().size() > otherNumber.getBigNumberArray().size()) {
            longer = this;
            shorter = otherNumber;
        }

        else if (this.getBigNumberArray().size() < otherNumber.getBigNumberArray().size()) {
            shorter = this;
            longer = otherNumber;
        }
        else {
            longer = this;
            shorter = otherNumber;
        }

        BigInt smallerCopy = shorter.clone();
        BigInt longerCopy = longer.clone();

        ArrayList<Integer> longerNum = longerCopy.getBigNumberArray();
        ArrayList<Integer> shortnerNum = smallerCopy.getBigNumberArray();

        //Actual Calculation
        if (this.isNegative != otherNumber.isNegative) { //-10 + 11   11 - 10
            if (this.isNegative==true){
                BigInt cloned = this.absolute();
                if (cloned.compareTo(otherNumber)==-1){
                    return otherNumber.minus(cloned);
                }

                return cloned.minus(otherNumber);
            }

            BigInt cloned=otherNumber.absolute();
            if (this.compareTo(cloned)==1){
                return this.minus(cloned);
            }

            return  cloned.minus(this);

        }

        Collections.reverse(longerNum);
        Collections.reverse(shortnerNum);

        /*Adding zeros for an easier loop*/
        int delta = longerNum.size() - shortnerNum.size();
        for (int i = 0; i < delta; i++) {
            shortnerNum.add(0);
        }

        for (int i = 0; i < longerNum.size(); i++) {

            addDigitsResult = addDigits(longerNum.get(i) + carryover, shortnerNum.get(i));
            resultArray.add(addDigitsResult[RESULT]);
            carryover = addDigitsResult[CARRY];
        }

        if (carryover > 0) {
            resultArray.add(carryover);
            carryover = 0;
        }

        Collections.reverse(resultArray);

        BigInt newInt = new BigInt(resultArray, this.isNegative);
        return newInt;

    }

    private BigInt absolute (){
        ArrayList<Integer> newArray = new ArrayList<>();
        newArray=(ArrayList)this.getBigNumberArray().clone();
        return new BigInt(newArray,false);

    }

    public BigInt minus (BigInt newNum){
        if (this.compareTo(newNum)==0){
            return new BigInt("0");
        }
        if ((this.isNegative==false) && (newNum.isNegative==true)) {
            BigInt cloned = newNum.clone();
            cloned.setNegative(false);
            return this.plus(cloned);

        }

        if ((this.isNegative==true) && (newNum.isNegative==false)){
            BigInt cloned = newNum.clone();
            cloned.setNegative(true);

            return this.plus(cloned);
        }


        int carryover = 0;
        int[] digitsResult;
        ArrayList<Integer> resultMinus = new ArrayList<>();

        BigInt thisNumber = this.clone();
        BigInt otherNumber = newNum.clone();

        ArrayList<Integer> thisArray=thisNumber.getBigNumberArray();
        ArrayList<Integer> otherArray=otherNumber.getBigNumberArray();

        ArrayList<Integer> shorterNum;
        ArrayList<Integer> longerNum;

        longerNum=thisArray;
        shorterNum=otherArray;


        if (thisArray.size()>otherArray.size()){
            longerNum=thisArray;
            shorterNum=otherArray;
        }


        if (thisArray.size()<otherArray.size()){
            shorterNum=thisArray;
            longerNum=otherArray;
        }

        Collections.reverse(longerNum);
        Collections.reverse(shorterNum);

        int delta = longerNum.size()-shorterNum.size();

        for (int i = 0; i < delta; i++) {
            shorterNum.add(0);
        }


        if ((thisNumber.isNegative==true)&& (otherNumber.isNegative==true)){

            BigInt temp = thisNumber;
            thisNumber=otherNumber;
            otherNumber=temp;

            thisNumber.setNegative(false);
            otherNumber.setNegative(false);

        }


        for (int i=0;i<longerNum.size(); i++) {

            longerNum.set(i, longerNum.get(i) - carryover);

            digitsResult = subtractDigits(longerNum.get(i), shorterNum.get(i));
            resultMinus.add(digitsResult[RESULT]);
            carryover = digitsResult[CARRY];
            }


        if (carryover >0) {
            resultMinus.add(carryover);
        }

        Collections.reverse(resultMinus);
        removeZeros(resultMinus);
        BigInt resultInt = new BigInt (resultMinus,false);


        if (this.compareTo(otherNumber)==-1){
            resultInt.setNegative(true);
        }
        return  resultInt;
    }



     private void removeZeros(ArrayList<Integer> array){
         if (array.size()<=1){
             return;
         }

         while ((array.get(0) == 0) && (array.size()>1)) {
             array.remove(0);

         }
     }

    public String toString(){
        String numberString = new String();

        removeZeros(this.getBigNumberArray());

        if (isNegative==true){
            numberString ="-";
        }


        for (int i=0; i<bigNumberArray.size();i++){
            int num =bigNumberArray.get(i);
            numberString=numberString+String.valueOf(num);
        }

        return numberString;

    }


    //method that adds two numbers and returns an array of 2 digits
    private int[] addDigits (int thisDigit, int otherDigit) {

        int[] resultArray = new int[DIGITSNUM];

        int res = thisDigit+otherDigit;
        if (res > MAX){
            resultArray[CARRY]=res/10;
            resultArray[RESULT]=res%10;
        }
        else {
            resultArray[CARRY]=0;
            resultArray[RESULT]=res;
        }

        return resultArray;
    }

    private int[] multiplyDigits (int thisDigit, int otherDigit,int carryover){
        int[] resultArray= new int [DIGITSNUM];

        int res = (thisDigit*otherDigit)+carryover;

        if (res > MAX){
            resultArray[CARRY]=res/10;
            resultArray[RESULT]=res%10;
        }

        else {
            resultArray[CARRY]=0;
            resultArray[RESULT]=res;
        }
        return resultArray;
    }

    /*A method that subtracts digits*/

    public int[] subtractDigits (int thisDigit, int otherDigit) {

        int[] resultArray = new int[DIGITSNUM];
        resultArray[CARRY]=0;


        if (thisDigit < otherDigit){
            resultArray[CARRY]=1;
            thisDigit = 10+thisDigit;

        }

        resultArray[RESULT]=thisDigit-otherDigit;

        return resultArray;
    }




    public boolean equals (Object otherNumber) {
        if (this.compareTo(otherNumber) == 0){
            return true;
        }
        return false;

    }


    public int compareTo(Object otherObject){
        BigInt newNumber = (BigInt)otherObject;
        final int LESS=-1;
        final int EQUAL=0;
        final int BIGGER=1;

        ArrayList<Integer> thisNumber = this.getBigNumberArray();
        ArrayList<Integer> otherNumber= newNumber.getBigNumberArray();


        if ((this.isNegative == false) && (newNumber.isNegative == true)) {
            return BIGGER;
        }
        if ((this.isNegative == true) && (newNumber.isNegative == false)) {
            return LESS;
        }

        if (thisNumber.size() != otherNumber.size()){

            if ((this.isNegative == false) && (newNumber.isNegative==false)){
                if (thisNumber.size() > otherNumber.size()){
                    return BIGGER;
                }
                return LESS;
            }

            if ((this.isNegative == true) && (newNumber.isNegative==true)){
                if (thisNumber.size() > otherNumber.size()) {
                    return LESS;
                }
                return BIGGER;
            }

        }

        for (int i=0; i<thisNumber.size();i++) {
            if (thisNumber.get(i) != otherNumber.get(i)) {

                if ((this.isNegative == false) && (newNumber.isNegative == false)) {
                    if (thisNumber.get(i) > otherNumber.get(i)) {
                        return BIGGER;
                    }
                    return LESS;
                }

                if ((this.isNegative == true) && (newNumber.isNegative == true)) {
                    if (thisNumber.get(i) > otherNumber.get(i)) {
                        return LESS;
                    }
                    return BIGGER;
                }
            }
        }

        return EQUAL;
    }


    public BigInt clone(){
        ArrayList<Integer> newArray = new ArrayList<>();
        newArray = (ArrayList)this.getBigNumberArray().clone();
        return  new BigInt(newArray,this.isNegative);

    }


    public BigInt divide (BigInt newNum) {
        BigInt thisNumber = this.absolute();
        BigInt thatNumber = newNum.absolute();
        BigInt zero = new BigInt("0");
        BigInt result= new BigInt("0");
        if (newNum.compareTo(zero)==0) {
            throw new IllegalArgumentException ("Cannot devide by '0'.");
        }

        if (this.compareTo(thatNumber)==-1){
            return zero;
        }

        int counter =0;
        while ( (thisNumber.compareTo(result) > 0) ){
            result = result.plus(thatNumber);
            counter++;

        }
        String count =  Integer.toString(counter);

        BigInt newBigInt = new BigInt(count);

        if (((this.isNegative==true) && (newNum.isNegative==false)) ||
        ((this.isNegative==false) && (newNum.isNegative==true))){

            newBigInt.setNegative(true);
        }


        return newBigInt;

    }

    public BigInt multiply (BigInt newNumber) {
        BigInt zero = new BigInt("0");
        if ((this.compareTo(zero)==0) || (newNumber.compareTo(zero)==0)) {
            return zero;
        }
        int carryover=0;
        BigInt result = new BigInt("0");
        int[] digitsResult;
        BigInt shorter;
        BigInt longer;


        if (this.getBigNumberArray().size() > newNumber.getBigNumberArray().size()){
            longer=this.clone();
            shorter=newNumber.clone();
        }

        if (this.getBigNumberArray().size() < newNumber.getBigNumberArray().size()){
            shorter=this.clone();
            longer=newNumber.clone();
        }

        else {
            longer=this.clone();
            shorter=newNumber.clone();
        }

        Collections.reverse(shorter.getBigNumberArray());
        Collections.reverse(longer.getBigNumberArray());

        BigInt ongoingSum = new BigInt("0");

        for (int s=0; s<shorter.getBigNumberArray().size(); s++){
            ArrayList<Integer> sumArray = new ArrayList<>();

            if (s>0){
                int counter=0;
                while (counter <s){
                    sumArray.add(0);
                    counter++;
                }
            }

            for (int l=0; l<longer.getBigNumberArray().size(); l++){
                digitsResult=multiplyDigits(longer.getBigNumberArray().get(l),shorter.getBigNumberArray().get(s),carryover);
                sumArray.add(digitsResult[RESULT]);
                carryover = digitsResult[CARRY];

            }

            BigInt currentSum = new BigInt(sumArray,false);
            ongoingSum = ongoingSum.plus(currentSum);


        }
        if (carryover != 0){
            ongoingSum.getBigNumberArray().add(carryover);
        }


        Collections.reverse(ongoingSum.getBigNumberArray());

        if (((this.isNegative==true) && (newNumber.isNegative==false)) ||
                ((this.isNegative==false) && (newNumber.isNegative==true))){

            ongoingSum.setNegative(true);
        }


        return ongoingSum;
    }


    /*********************/
    /*GETTERS and SETTERS*/
    /*********************/
    public void setBigNumberArray(ArrayList<Integer> bigNumberArray) {
        this.bigNumberArray = bigNumberArray;
    }

    public ArrayList<Integer> getBigNumberArray() {
        return bigNumberArray;
    }

    public boolean isNegative() {
        return isNegative;
    }


    public void setNegative(boolean negative) {
        isNegative = negative;
    }

}
