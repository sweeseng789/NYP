package com.example;

import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        RecordManager record = new RecordManager();
        Scanner input = new Scanner(System.in);
        boolean usingProgramme = true;

        record.readText();
        while(usingProgramme)
        {
            System.out.println("Welcome to the Student Record Management");
            System.out.println("Enter 1 to add new student data");
            System.out.println("Enter 2 to show all data");
            System.out.println("Enter 3 to add friend");
            System.out.println("Enter 4 to show friends of a student");
            System.out.println("Enter 5 to terminate programme");
            System.out.println("Please enter your choice");
            int choice = input.nextInt();


            switch(choice)
            {
                case(1):
                {
                    System.out.println("Please enter your name: ");
                    input.nextLine();
                    String name = input.nextLine();

                    System.out.println("Please enter your Registration Number: ");
                    String RegistrationNum = input.next();

                    System.out.println("Please enter your Gender: ");
                    int Gender = Integer.parseInt(input.next());

                    System.out.println("Please enter your GPA: ");
                    float GPA = Float.parseFloat(input.next());

                    record.AddStudent(name, RegistrationNum, Gender, GPA);
                    System.out.println("Data added");
                }
                break;

                case(2):
                {
                    record.ShowData();
                }
                break;

                case(3):
                {

                }
                break;

                case(4):
                {

                }
                break;

                case(5):
                {
                    System.out.println("You have exited the programme");
                    usingProgramme = false;
                }
                break;

                default:
                    break;
            }
        }
    }
}