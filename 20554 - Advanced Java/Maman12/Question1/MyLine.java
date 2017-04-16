/**
 * Alex Z
 * 
 * Maman12 - Question 1, A+B
 */
import java.awt.*;
public  class MyLine extends MyShape {


    /**************/
    /*CONSTRUCTORS*/
    /**************/

    public MyLine (int x1, int y1, int x2, int y2) {
        super(x1, y1, x2, y2);
    }



    /**************/
    /*METHODS*/
    /**************/


    public void draw (Graphics g){
        g.setColor(getMyColor());
        g.drawLine(getPoint1().x,getPoint1().y,getPoint2().x,getPoint2().y);
    }


    //determine length
    public boolean equals (MyLine otherLine){

       if (calculateDistance(this.getPoint1(),this.getPoint2())==calculateDistance(otherLine.getPoint1(),otherLine.getPoint2())){
        return true;
          }
        else
          {return false;}
    }

}
