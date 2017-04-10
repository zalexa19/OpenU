
/**
 * Alex Zablotsky- 314494964 - Maman14
 * This class represents each item. Includes a reference to the object, and the priority
 */

public class Item <T> {

    private int _priority;
    private T _item;

    /*Constructor*/
    public Item (int priority,T item){

        _priority=priority;
        this._item=item;

    }



    public T get_item() {
        return _item;
    }

    public int get_priority(){
        return _priority;
    }

    public void set_priority (int priority) {
        _priority=priority;
    }

    public void setItem (T newItem){
        _item=newItem;
    }
}
