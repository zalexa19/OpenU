/**
 * Alex Z
 * 
 * Maman12 - Question 1, A+B
 */


import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class MyPanel extends JPanel {



    private Color bg = new Color(255,140,159,70);

    ArrayList<MyShape> shapesArray= new ArrayList<>();
    ArrayList<MyShape> clonedArray= new ArrayList<>();



    /***************/
    /**CONSTRUCTOR**/
    /***************/

    public MyPanel () {
        //Generates 2 lines with random points and puts them in the array
        int n = 2; //Number of shapes to generate

        for (int i = 0; i<n; i++){
            int x1 = randomizeNumber();
            int y1 = randomizeNumber();
            int x2 = randomizeNumber();
            int y2 = randomizeNumber();

            MyShape line = new MyLine(x1,y1,x2,y2);

            shapesArray.add(line);
        }

        //Generates 2 Rectangles, and puts them in the array

        while (shapesArray.size()< n*2) {
            int x1 = randomizeNumber();
            int y1 = randomizeNumber();
            int x2 = randomizeNumber();
            int y2 = randomizeNumber();

            try {
                MyShape rectangle = new MyRecatngle(x1,y1,x2,y2,true);
                shapesArray.add(rectangle);

            } catch (IllegalArgumentException e){
                System.out.println("Invalid point1 was generated for Rectangle: ("+x1+","+y1+") "+"Point2: ("+x2+","+y2+")");
            }


        }

        //Generates 2 ovals and puts them in the array
        while (shapesArray.size()< n*3)
        {
            int x1 = randomizeNumber();
            int y1 = randomizeNumber();
            int x2 = randomizeNumber();
            int y2 = randomizeNumber();

            try {
                MyShape oval = new MyOval(x1,y1,x2,y2,true);
                shapesArray.add(oval);
            } catch (IllegalArgumentException e) {
                System.out.println("Invalid point1 was generated for Oval: (" + x1 + "," + y1 + ")" + " Point2: (" + x2 + "," + y2 + ")");
            }

        }
        try {
        clonedArray= cloneThisArray(shapesArray);}
        catch (CloneNotSupportedException e){
            System.out.println("Clone not supported error");
        }



    }



    //Cloning the listArray

    public ArrayList<MyShape> cloneThisArray(ArrayList<MyShape> original) throws CloneNotSupportedException{
        ArrayList <MyShape> clonedArray = new ArrayList<>();

        for (int i=0; i<original.size();i++){
            clonedArray.add(original.get(i).clone()); //clone the original

            int xP1=clonedArray.get(i).getPoint1().x;
            int yP1=clonedArray.get(i).getPoint1().y;
            int xP2=clonedArray.get(i).getPoint2().x;
            int yP2=clonedArray.get(i).getPoint2().y;


            clonedArray.get(i).getPoint1().move(xP1+10,yP1+10); //moves point1 to x+10, y+10
            clonedArray.get(i).getPoint2().move(xP2+10,yP2+10); //moves point 2 to x+10, y+10

            if (clonedArray.get(i) instanceof MyBoundedShape) {
                Color gray = new Color (169,169,169,100);
                clonedArray.get(i).setMyColor(gray);
            }
        }

        return clonedArray;

    }





    public void paintComponent (Graphics g) {
        super.paintComponent(g);

        for (int i =0; i <shapesArray.size(); i++){
            shapesArray.get(i).draw(g);
        }

        //drawing to clone

        for (int i =0; i <clonedArray.size(); i++){
            clonedArray.get(i).draw(g);
        }

    }




    private int randomizeNumber()

    {
        Random rand = new Random();

        int low = 0;
        int high = 200;

        int result = rand.nextInt(high - low) + low;
        return result;
    }

    /**********************/
    /**SETTERS AND GETTERS*/
    /**********************/

    public Color getBg() {
        return bg;
    }
}

