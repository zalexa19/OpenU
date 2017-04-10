import java.util.Iterator;

/**
 * Alex Zablotsky- 314494964 - Maman14
 * Created by alexz on 1/10/17.
 */
public class CustomerApplication {
    private String _name;
    private int _id;
    private String _userInput;


    public CustomerApplication (int id, String name, String input){
        _name=name;
        _id=id;
        _userInput=input;

    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof CustomerApplication ){
            CustomerApplication otherCustApp = (CustomerApplication)obj;
            if ((this.get_id()==otherCustApp.get_id())&&
                    (this.get_userInput()==otherCustApp.get_userInput())){
                return true;
            }

        }

        return false;
    }



    /*Getters*/

    public String get_name() {
        return _name;
    }

    public int get_id() {
        return _id;
    }

    public String get_userInput() {
        return _userInput;
    }




}
