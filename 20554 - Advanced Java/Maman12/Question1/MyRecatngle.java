/**
 * Alex Z
 * 
 * Maman12 - Question 1, A+B
 */
import java.awt.*;
public class MyRecatngle extends MyBoundedShape
{


    /**************/
    /*CONSTRUCTORS*/
    /**************/


    public MyRecatngle (int x1, int y1, int x2, int y2,boolean filledShapeStatus)
    {
        super(x1, y1, x2, y2,filledShapeStatus);
        Color newColor = new Color(83,70,127,185);
        setMyColor(newColor);
        setFilledShape(filledShapeStatus);
    }

    /**************/
    /*METHODS*/
    /**************/


    public void draw (Graphics g){
        g.setColor(getMyColor());
        if (getFilledShape()==true){
            g.fillRect(getPoint1().x,getPoint1().y,(getPoint2().x - getPoint1().x),(getPoint2().y - getPoint1().y));
        }
        else {
            g.drawRect(getPoint1().x, getPoint1().y, getPoint2().x, getPoint2().y);
        }

    }
}


