import java.awt.*;

/**
 * Created by alexz on 3/15/17.
 */
public class TreeNode {
    private Account accountObj;
    private TreeNode parent,leftChild,rightChild;
    private Color color;

    public TreeNode (Account a){
        accountObj=a;

    }

    public TreeNode (Account account, TreeNode left, TreeNode right, TreeNode parent){
        accountObj=account;
        this.parent=parent;
        leftChild=left;
        rightChild=right;
        color= Color.BLACK;
    }


    public TreeNode(){
        this(null,null,null,null);
        this.color=Color.BLACK;
    }



    /*Setters and getters*/
    public void setAccount (TreeNode node){
        accountObj = node.getAccountObj();
        accountObj.setTreeNode(node);

    }


    public Account getAccountObj() {
        return accountObj;
    }

    public TreeNode getParent() {
        return parent;
    }

    public TreeNode getLeft() {
        return leftChild;
    }

    public TreeNode getRight() {
        return rightChild;
    }

    public Color getColor() {
        return color;
    }

    public void setParent(TreeNode parent) {
        this.parent = parent;
    }

    public void setLeft(TreeNode leftChild) {
        this.leftChild = leftChild;
    }

    public void setRight(TreeNode rightChild) {
        this.rightChild = rightChild;
    }

    public void setColor(Color c) {
        color=c;
    }
    public void setAccountObj (Account a){
        accountObj=a;
    }


}
