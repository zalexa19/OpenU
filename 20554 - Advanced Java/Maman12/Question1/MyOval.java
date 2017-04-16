/**
 * Alex Z
 * 
 * Maman12 - Question 1, A+B
 */
import java.awt.*;

public class MyOval extends MyBoundedShape {

    /**************/
    /*CONSTRUCTORS*/
    /**************/



    public MyOval (int x1, int y1, int x2, int y2,boolean filledShapeStatus)
    {
        super(x1, y1, x2, y2,filledShapeStatus);
        Color newColor = new Color(38,85,160,185);
        setMyColor(newColor);
        setFilledShape(filledShapeStatus);
    }

    /**************/
    /*METHODS*/
    /**************/

    public void draw(Graphics g) {
        g.setColor(getMyColor());
        if (getFilledShape() == true) {
            g.fillOval(getPoint1().x, getPoint1().y, (getPoint2().x - getPoint1().x), (getPoint2().y - getPoint1().y));
        }
        else {
            g.drawOval(getPoint1().x, getPoint1().y, (getPoint2().x - getPoint1().x), (getPoint2().y - getPoint1().y));
        }



    }
}

