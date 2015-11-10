package com.example;

import java.util.Scanner;

public class SRS_Class {
    public static void main(String[] args)
    {
        RecordManager_Class record = new RecordManager_Class();
        Scanner input = new Scanner(System.in);
        boolean usingProgramme = true;

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
                    System.out.println("Please enter the number of the student");
                    int studentRegNo = Integer.parseInt(input.next());

                    if(record.validateStudent(studentRegNo))
                    {
                        boolean addingFriend = true;
                        while(addingFriend)
                        {
                            System.out.println("Please enter the number of the student to be friend with");
                            System.out.println("Enter -1 to stop");
                            int friendToBe = Integer.parseInt(input.next());

                            if(friendToBe != -1)
                                record.addFriend(friendToBe, studentRegNo);
                            else
                                addingFriend = false;
                        }
                    }

                }
                break;

                case(4):
                {
                    System.out.println("Please enter the number of the student");
                    int studentRegNo = Integer.parseInt(input.next());

                    record.ShowFriends(studentRegNo);
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