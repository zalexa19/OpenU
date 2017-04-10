/**
 * Alex Zablotsky
 * 314494964
 * Maman12 - Question 1, A+B
 */
import javax.swing.*;
import java.awt.*;
import java.awt.geom.Point2D;
import java.util.Objects;

public abstract class MyShape extends JPanel implements Cloneable {


    private Point point1;
    private Point point2;
    private Color myColor = Color.black;


    /**************/
    /*CONSTRUCTORS*/
    /**************/

    public MyShape (int xP1, int yP1, int xP2, int yP2){
        point1=new Point (xP1,yP1);
        point2=new Point(xP2,yP2);
    }


    /**************/
    /*METHODS*/
    /**************/
    public abstract void draw(Graphics g);

//This method calculates a distance between 2 points using a formula
    public double calculateDistance (Point point1, Point point2) {
        int x1 = point1.x;
        int x2 = point2.x;
        int y1 = point1.y;
        int y2 = point2.y;

        double length = Math.sqrt((x1 - x2)*(x1 - x2) + ((y1 - y2)*(y1 - y2)));
        return length;

    }
    //This method clones an object
    public MyShape clone() throws CloneNotSupportedException {
        MyShape cloned = (MyShape) super.clone();
        cloned.setPoint1((Point) this.getPoint1().clone());
        cloned.setPoint2((Point)this.getPoint2().clone());

        return cloned;
    }


    /*********************/
    /*SETTERS AND GETTERS*/
    /*********************/

    public Point getPoint1 (){
        return point1;

    }

    public Point getPoint2(){
        return point2;
    }

    public void setPoint1(Point point) {

        this.point1 = point;
    }

    public void setPoint2(Point point) {
        this.point2 = point;
    }

    public Color getMyColor (){
        return myColor;
    }

    public void setMyColor (Color newColor){
       myColor = newColor;

    }

}
