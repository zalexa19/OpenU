/**
 *Alex z
 * 
 * Maman14 Question2
 */

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Paths;
import java.util.Formatter;
import java.util.Scanner;
import javax.swing.*;




public class PhoneBookPanel extends JPanel {
    private int fontX, fontY;
    PhoneBook phonebook;

    private final int MAXTEXT = 10;
    private JButton cmdAdd, cmdDelete, cmdUpdate, cmdSearch, cmdImport, cmdExport;
    private JLabel lblName, lblNumber;
    private JTextField txtName, txtNumber;
    JPanel controls,text;
    private Color myColor = new Color(219,186,247);


    public PhoneBookPanel() {
        phonebook = new PhoneBook();
        cmdAdd = new JButton("Add");
        cmdDelete = new JButton("Delete");
        cmdSearch = new JButton("Search");
        cmdUpdate = new JButton("Update");
        cmdImport = new JButton("Import Records");
        cmdExport = new JButton("Export Records");

        lblName = new JLabel("Name: ");
        lblNumber = new JLabel("Number: ");

        setBackground(myColor);

        controls = new JPanel();
        controls.setLayout(new GridLayout(2, 4, 10, 10));
        controls.add(cmdAdd);
        controls.add(cmdSearch);
        controls.add(cmdUpdate);
        controls.add(cmdDelete);
        controls.add(cmdImport);
        controls.add(cmdExport);

        this.setLayout(new BorderLayout());
        add(controls, BorderLayout.SOUTH);

        ControlListner ctrlLisner = new ControlListner();
        cmdAdd.addActionListener(ctrlLisner);
        cmdDelete.addActionListener(ctrlLisner);
        cmdSearch.addActionListener(ctrlLisner);
        cmdUpdate.addActionListener(ctrlLisner);
        cmdExport.addActionListener(ctrlLisner);
        cmdImport.addActionListener(ctrlLisner);

    }


    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.setFont(new Font("Serif",Font.BOLD,60));
        g.setColor(Color.white);
        g.drawString("Phone Book",85,50);

        //Printing the whole phone book
        int dbSize = phonebook.getSize();
        fontX = 50;
        fontY = 100;
        for (int i=0;i<dbSize;i++){
            String[] result = phonebook.getSpesificRecord(i);
            String name = result[0];
            String number = result[1];
            g.setColor(Color.BLACK);
            g.setFont(new Font("Serif",Font.BOLD,16));
            g.drawString(name+", "+number,fontX,fontY);

            fontY = fontY+25;

        }



    }


    private class ControlListner implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() == cmdAdd) {
                addButtonPressed();
            }
e
            if (e.getSource() == cmdDelete) {
                deleteButtonPressed();

            }


            if (e.getSource() == cmdUpdate) {

                updateButtonPressed();
            }


            if (e.getSource()==cmdSearch){

                searchButtonPressed();

            }
            if (e.getSource()==cmdExport) {

                exportFile();

            }
        }

        private void addButtonPressed(){
            String name = JOptionPane.showInputDialog("Enter Name:");
            String number = JOptionPane.showInputDialog("Enter phone number");

            try {
                phonebook.addRecord(name, number);
            } catch (RecordAlreadyExists e1) {
                JOptionPane.showMessageDialog(controls, "Record for name: " + name + " already exists", "Error", JOptionPane.ERROR_MESSAGE);
            }
            repaint();
        }

        private void deleteButtonPressed(){
            String name = JOptionPane.showInputDialog("Enter a name to delete:");
            try {
                phonebook.removeRecord(name);
            } catch (RecordDoesnotExist e2) {
                recordNotFound(name);
            }

            repaint();
        }

        private void updateButtonPressed(){

            String origName, newName, origNumber, newNumber;

            origName = JOptionPane.showInputDialog(controls, "Name of the record to be updated:");
            origNumber = phonebook.getValue(origName);

            Object[] options = {"Name only", "Number only", "Both"};
            int choice = JOptionPane.showOptionDialog(controls,
                    "Which field would you like to update?",
                    "Update",
                    JOptionPane.YES_NO_CANCEL_OPTION,
                    JOptionPane.QUESTION_MESSAGE,
                    null,
                    options,
                    options[2]);

            if (choice ==0) {
                //Updating the name only
                newName = JOptionPane.showInputDialog(controls, "Enter a new name");


                try {
                    phonebook.updateRecord(origName, newName, origNumber);
                } catch (RecordDoesnotExist recordDoesnotExist) {
                    recordNotFound(origName);
                }


            }

            if (choice==1){
                //number only
                newNumber = JOptionPane.showInputDialog(controls, "Enter a new number:");
                try{
                    phonebook.updateRecord(origName,origName,newNumber);
                }catch (RecordDoesnotExist e3){
                    recordNotFound(origName);

                }

            }

            else {
                newName =JOptionPane.showInputDialog(controls, "Enter new name");
                newNumber=JOptionPane.showInputDialog(controls, "Enter new number:");

                try {
                    phonebook.updateRecord(origName,newName,newNumber);
                }catch (RecordDoesnotExist e4){
                    recordNotFound(origName);
                }

            }
            repaint();
        }

        private void searchButtonPressed(){

            String name = JOptionPane.showInputDialog("Enter a name to search");

            try {
                String number=phonebook.findNumber(name);
                JOptionPane.showMessageDialog(controls,"Name: "+name+" Number: "+number);
            }catch (RecordDoesnotExist e6){
                recordNotFound(name);
            }
        }


        private void exportFile(){
            Formatter output=null;
            try{
                output=new Formatter("Contacts.txt");
            }catch (FileNotFoundException e) {
                fileNotFoundError();
            }

            int size=phonebook.getSize();
            String[] result;

            for (int i=0;i<size;i++){
                result=phonebook.getSpesificRecord(i);
                String name = result[0];
                String number = result[1];
                output.format(name+"\n"+number+"\n");
            }
            output.close();
            JOptionPane.showMessageDialog(controls, "Export Done","Success", JOptionPane.INFORMATION_MESSAGE);



        }

        /*
        Import is done using scanner. Each phonebook record should be split into two lines - first line is name,
        * second is the number, and third one is name again.
        * Scanning is done using the nextLine(). This allows us to import names with surenames
        * */
        private void importFile(){
            Scanner inputFile=null;
            int skipped = 0;
            int imported = 0;
            try {
                inputFile = new Scanner(Paths.get("ContactsInput.txt"));
            }catch (FileNotFoundException f){
                fileNotFoundError();
                System.out.println(f.getMessage());
                return;
            } catch (IOException e) {
                JOptionPane.showMessageDialog(controls, "Unexpected Error", "Error", JOptionPane.ERROR_MESSAGE);
                System.out.println(e.getMessage());
                return;
            }

            while (inputFile.hasNext()){
                String name = inputFile.nextLine();
                String number=inputFile.nextLine();
                try {
                    phonebook.addRecord(name, number);
                    imported++;
                }catch (RecordAlreadyExists e){
                    System.out.println("Record for name: "+name+"Already exists. Skipped upload");
                    skipped++;
                }
            }
            JOptionPane.showMessageDialog(controls, "Upload successfull. Imported: "+imported+", Skipped: "+skipped, "Success", JOptionPane.INFORMATION_MESSAGE);
            inputFile.close();
            repaint();
        }
    }


    private void fileNotFoundError(){
        JOptionPane.showMessageDialog(controls,"File not found","Warning", JOptionPane.ERROR_MESSAGE);

    }

    private void recordNotFound(String name){
        JOptionPane.showMessageDialog(controls, "No records were found for: " + name,"Error", JOptionPane.ERROR_MESSAGE);
    }
}


