/**
 * Alex Zablotsky
 * 314494964
 * Maman12 - Question 1, A+B
 */


public abstract class MyBoundedShape extends MyShape {

    private boolean filledShape;


    /**************/
    /*CONSTRUCTORS*/
    /**************/


    public MyBoundedShape ( int x1, int y1, int x2, int y2, boolean filledShapeStatus) throws IllegalArgumentException{
        super(x1, y1, x2, y2);
        if ((x1 >= x2) || (y1 >= y2))
        {
            throw new IllegalArgumentException("Point1 is not at the left corner compared to Point2");
        }
        setFilledShape(filledShapeStatus);
    }



    /**************/
    /*METHODS*/
    /**************/


    //compare 2 shapes
    public boolean equals(MyBoundedShape otherShape){

        int thisHeight = Math.abs(this.getPoint1().y-this.getPoint2().y);
        int thisWidth = Math.abs(this.getPoint1().x-this.getPoint2().x);
        int otherHeight = Math.abs(otherShape.getPoint2().y-otherShape.getPoint1().y);
        int otherWidth = Math.abs(otherShape.getPoint2().x-otherShape.getPoint1().x);

        if ((thisHeight==otherHeight)&&(thisWidth==otherWidth))
        {
            return true;
        }
        else
        {return false;}
    }



    /*********************/
    /*SETTERS AND GETTERS*/
    /*********************/

    public boolean getFilledShape() {
        return filledShape;
    }

    public void setFilledShape(Boolean status){
        filledShape = status;
    }
}

