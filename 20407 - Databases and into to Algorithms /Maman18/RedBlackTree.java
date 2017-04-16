import java.awt.*;

/**
 ** Maman 18 - AlexZ
 * 
 */
public class RedBlackTree {
    public static final TreeNode Neil = new TreeNode();
    private TreeNode root, maxBalanceNode;

    public RedBlackTree()
    {
        root = Neil;
        Neil.setParent(Neil);
        Neil.setLeft(Neil);
        Neil.setRight(Neil);

        maxBalanceNode=Neil;
    }

    public TreeNode getRoot()
    {
        return this.root;
    }


    /**
     * This method performs a left rotation on the Red-Black tree
     * Runtime Complexity: O(1)
     * @param x The tree node to rotate around
     */
    private void leftRotate(TreeNode x)
    {
        TreeNode y = x.getRight();
        x.setRight(y.getLeft());

        if (y.getLeft() != Neil)
        {
            y.getLeft().setParent(x);
        }
        y.setParent(x.getParent());

        if (x.getParent() == Neil)
        {
            root = y;
        }
        else
        {
            if (x == x.getParent().getLeft())
            {
                x.getParent().setLeft(y);
            }
            else
            {
                x.getParent().setRight(y);
            }
        }

        y.setLeft(x);
        x.setParent(y);
    }


    /**
     * This method performs a right rotation on the Red-Black tree
     * Runtime Complexity: O(1)
     * @param x The tree node to rotate around
     */
    private void rightRotate(TreeNode x)
    {
        TreeNode y = x.getLeft();
        x.setLeft(y.getRight());

        if (y.getRight() != Neil)
        {
            y.getRight().setParent(x);
        }

        y.setParent(x.getParent());
        if (x.getParent() == Neil)
        {
            root = y;
        }
        else
        {
            if (x == x.getParent().getRight())
            {
                x.getParent().setRight(y);
            }
            else
            {
                x.getParent().setLeft(y);
            }
        }

        y.setRight(x);
        x.setParent(y);
    }

    /**
     * Insert a new node in the red black tree
     * Runtime Complexity: O(lgn)
     * @param z Tree node to insert
     */
    public void rbInsert(TreeNode z)
    {
        //Update maxBalanceNode with the highest balance
        if (maxBalanceNode==Neil) {
            maxBalanceNode = z;
        }
         if (maxBalanceNode.getAccountObj().getBalance() < z.getAccountObj().getBalance()){
            maxBalanceNode=z;
        }


        //empty tree
        if (root == Neil)
        {
            root = z;
            z.setColor(Color.BLACK);
            z.setLeft(Neil);
            z.setRight(Neil);
            z.setParent(Neil);
            return;
        }


        TreeNode y = Neil;
        TreeNode x = root;

        while (x != Neil)
        {
            y = x;
            if (z.getAccountObj().getBalance() < x.getAccountObj().getBalance())
            {
                x = x.getLeft();
            }
            else
            {
                x = x.getRight();
            }

        }

        z.setParent(y);
        if (y == Neil)
        {
            root = z;
        }
        else
        {
            if (z.getAccountObj().getBalance() < y.getAccountObj().getBalance())
            {
                y.setLeft(z);
            }
            else
            {
                y.setRight(z);
            }
        }

        z.setLeft(Neil);
        z.setRight(Neil);
        z.setColor(Color.RED);
        rbInsertFixup(z);
    }

    /**
     * Fix any red black tree violations after insert
     * Runtime Complexity: O(lgn)
     * @param z Tree node to perform the fix on
     */
    private void rbInsertFixup(TreeNode z)
    {
        while (z.getParent().getColor() == Color.RED)
        {
            if (z.getParent() == z.getParent().getParent().getLeft())
            {
                TreeNode y = z.getParent().getParent().getRight();
                if (y.getColor() == Color.RED)
                {
                    z.getParent().setColor(Color.BLACK);
                    y.setColor(Color.BLACK);
                    z.getParent().getParent().setColor(Color.RED);
                    z = z.getParent().getParent();
                }
                else
                {
                    if (z == z.getParent().getRight())
                    {
                        z = z.getParent();
                        leftRotate(z);
                    }


                    z.getParent().setColor(Color.BLACK);
                    z.getParent().getParent().setColor(Color.RED);
                    rightRotate(z.getParent().getParent());
                }

            }
            else
            {
                TreeNode y = z.getParent().getParent().getLeft();

                if (y.getColor() == Color.RED)
                {
                    z.getParent().setColor(Color.BLACK);
                    y.setColor(Color.BLACK);
                    z.getParent().getParent().setColor(Color.RED);
                    z = z.getParent().getParent();
                }
                else
                {
                    if (z == z.getParent().getLeft())
                    {
                        z = z.getParent();
                        rightRotate(z);
                    }

                    z.getParent().setColor(Color.BLACK);
                    z.getParent().getParent().setColor(Color.RED);
                    leftRotate(z.getParent().getParent());
                }
            }

        }

        root.setColor(Color.BLACK);
    }

    /**
     * Print the tree in a sorted order (run function)
     * Runtime Complexity: O(n)
     */
    public void printInOrder()
    {
        if (root == Neil)
        {
            System.out.print("- empty tree -");
        }
        else
        {
            this.printInOrder(root);
        }
    }

    /**
     * Print the tree in a sorted order (recursive method)
     * Runtime Complexity: O(n)
     */
    private void printInOrder(TreeNode node)
    {
        if (node != Neil)
        {
            printInOrder(node.getLeft());
            System.out.print(node.getAccountObj() + " ");
            printInOrder(node.getRight());
        }

    }

    /**
     * Find the lowest value of the tree
     * Runtime Complexity: O(lgn)
     * @return The node with the lowest value. (The first item in an ordered list)
     */
    public TreeNode minimum()
    {
        TreeNode index = root;
        while (index.getLeft() != Neil)
        {
            index = index.getLeft();
        }
        return index;
    }

    /**
     * Find the highest value of the tree
     * Runtime Complexity: O(lgn)
     * @return The node with the highest value. (The first item in an ordered list)
     */

    private TreeNode maximum(TreeNode x){
        TreeNode max = x;
        while (max.getRight()!=Neil){
            max=max.getRight();
        }
        return max;
    }

    /**
     * Returns the smallest node who has bigger value than the given node
     * Runtime Complexity: O(lgn)
     * @param node The node we would like to find the successor
     * @return The given node's successor
     */
    public TreeNode successor(TreeNode node)
    {
        if (node.getRight() != Neil)
        {
            //minimum in the sub tree
            TreeNode index = node.getRight();
            while (index.getLeft() != Neil)
            {
                index = index.getLeft();
            }
            return index;
        }
        TreeNode parent = node.getParent(); //Holds the parent
        while ((parent != Neil) && (parent.getRight() == node))
        {
            node = parent;
            parent = parent.getParent();
        }
        return parent; //This is the successor.

    }

    /**
     * Returns the node with the previous biggest value (balance)
     * Runtime Complexity: O(lgn)
     * @param node The node we would like to find the predecessor
     * @return The given node's predecessor
     */

    public TreeNode predeccessor(TreeNode node){

        if (node == Neil){
            return null;
        }
        if (node.getLeft() != Neil){
            return maximum(node.getLeft());
        }

        TreeNode parent = node.getParent();
        TreeNode x = node;
        TreeNode y = parent;

        while (y != Neil && x==y.getLeft()){
            x=y;
            y=y.getParent();
        }

        return y;
    }






    /**
     * Removes a node from a red black tree.
     * @param z The node to remove
     * Runtime Complexity: O(lgn)
     * @return The removed node
     *
     */
    public TreeNode rbDelete(TreeNode z)
    {
        //update maxBalanceNode
        if (maxBalanceNode==z){
            maxBalanceNode=predeccessor(z);
        }


        TreeNode y;
        TreeNode x;
        if (z.getLeft() == Neil || z.getRight() == Neil)
        {
            y = z;
        }
        else
        {
            y = successor(z);
        }
        if (y.getLeft() != Neil)
        {
            x = y.getLeft();
        }
        else
        {
            x = y.getRight();
        }
        x.setParent(y.getParent());

        if (y.getParent() == Neil)
        {
            root = x;
        }
        else
        {
            if (y == y.getParent().getLeft())
            {
                y.getParent().setLeft(x);
            }
            else
            {
                y.getParent().setRight(x);
            }

        }

        if (y != z)
        {
            z.setAccountObj(y.getAccountObj());
        }
        if (y.getColor() == Color.BLACK)
        {
            rbDeleteFixup(x);
        }
        return y;
    }

    /**
     * Fix any red black tree violations after delete
     * Runtime Complexity: O(lgn)
     * @param x Tree node to perform the fix on
     */
    private void rbDeleteFixup(TreeNode x)
    {
        TreeNode w;
        while (x != root && x.getColor() == Color.BLACK)
        {
            if (x == x.getParent().getLeft())
            {
                w = x.getParent().getRight();
                if (w.getColor() == Color.RED)
                {
                    w.setColor(Color.BLACK);
                    x.getParent().setColor(Color.RED);
                    leftRotate(x.getParent());
                    w = x.getParent().getRight();
                }
                if (w.getLeft().getColor() == Color.BLACK && w.getRight().getColor() == Color.BLACK)
                {
                    w.setColor(Color.RED);
                    x = x.getParent();
                }
                else
                {
                    if (w.getRight().getColor() == Color.BLACK)
                    {
                        w.getLeft().setColor(Color.BLACK);
                        w.setColor(Color.RED);
                        rightRotate(w);
                        w = x.getParent().getRight();
                    }
                    w.setColor(x.getParent().getColor());
                    x.getParent().setColor(Color.BLACK);
                    w.getRight().setColor(Color.BLACK);
                    leftRotate(x.getParent());
                    x = root;
                }

            }
            else
            {
                w = x.getParent().getLeft();
                if (w.getColor() == Color.RED)
                {
                    w.setColor(Color.BLACK);
                    x.getParent().setColor(Color.RED);
                    rightRotate(x.getParent());
                    w = x.getParent().getLeft();
                }
                if (w.getRight().getColor() == Color.BLACK && w.getLeft().getColor() == Color.BLACK)
                {
                    w.setColor(Color.RED);
                    x = x.getParent();
                }
                else
                {
                    if (w.getLeft().getColor() == Color.BLACK)
                    {
                        w.getRight().setColor(Color.BLACK);
                        w.setColor(Color.RED);
                        leftRotate(w);
                        w = x.getParent().getLeft();
                    }
                    w.setColor(x.getParent().getColor());
                    x.getParent().setColor(Color.BLACK);
                    w.getLeft().setColor(Color.BLACK);
                    rightRotate(x.getParent());
                    x = root;
                }
            }
        }
        x.setColor(Color.BLACK);
    }


    /**
     * Find a key in a red black tree
     * Runtime Complexity: O(lgn)
     * @param key the key value to search for
     * @return the node with the given key. If the is not in the tree it will return Tree's Nil value
     */
    public TreeNode treeSearch(int key)
    {
        TreeNode x = root;
        while (x != Neil && key != (x.getAccountObj().getBalance()))
        {
            if (key < x.getAccountObj().getBalance())
            {
                x = x.getLeft();
            }
            else
            {
                x = x.getRight();
            }
        }

        return x;
    }

    public TreeNode getMaxBalanceNode(){
        return maxBalanceNode;
    }

}
