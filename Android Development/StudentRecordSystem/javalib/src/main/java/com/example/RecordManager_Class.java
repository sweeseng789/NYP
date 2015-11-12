package com.example;

import java.io.File;
import java.util.HashMap;

/**
 * Created by sweeseng789 on 29/10/2015.
 */

public class RecordManager_Class {
    private static int numOfStudents_Male;
    private static int numOfStudents_Female;
    private static int currentStudent_Num;

    HashMap<Integer, Student_Class> studentList = new HashMap<>();

    public RecordManager_Class()
    {
        numOfStudents_Male = 2;
        numOfStudents_Female = 0;
        currentStudent_Num = 2;

        Student_Class newStudent = new Student_Class("Swee Seng", "142128G", 1, 4.0f);
        studentList.put(0, newStudent);

        newStudent = new Student_Class("Setsuna", "142852H", 1, 4.0f);
        studentList.put(1, newStudent);
    }

    public void AddStudent(String name, String RegistrationNum, int Gender, float GPA)
    {
        Student_Class newStudent = new Student_Class(name, RegistrationNum, Gender, GPA);

        //Add data to list
        studentList.put(currentStudent_Num, newStudent);

        currentStudent_Num ++;

        if(Gender == 1)
            numOfStudents_Male ++;
        else
            numOfStudents_Female ++;
    }

    public void ShowData()
    {
        String gender = "";

        for (Student_Class student : studentList.values())
        {
            System.out.println("Name: " + student.getName());
            System.out.println("RegNo: " + student.getRegistrationNum());

            if(student.getGender() == 1)
            {
                gender = "Male";
            }
            else
            {
                gender = "Female";
            }

            System.out.println("Gender: " + gender);
            System.out.println("GPA: " + student.getGPA());
            System.out.println("\n");
        }

        System.out.println("Total number of students: " + currentStudent_Num);
        System.out.println("Male: " + numOfStudents_Male + ", Female: " + numOfStudents_Female + "\n");
    }

    public SearchResult_Class GetNumOfFriends(String regNo, int degree)
    {
        SearchResult_Class result = new SearchResult_Class();

       // for(int a = 0; a < studentList.size(); ++a)
        {
        //    Student_Class student = studentList.get(a);

          //  if(student.getRegistrationNum().equals(regNo))
            {
            //    for(int b = 0; b < student.friendList.regNo.size(); ++b)
                {
              //      if(student.friendList.degreeOfFriend.get(b).equals(degree))
                    {
                //        result.setValue(student.friendList.regNo.get(b));
                  //      result.setText(student.friendList.name.get(b));
                    }
                }
            }
        }

        for (Student_Class student : studentList.values())
        {
            if(student.getRegistrationNum().equals(regNo))
            {

            }
        }


        return result;
    }

    public boolean validateStudent(String regNo)
    {
        for(Student_Class student : studentList.values())
        {
            if(student.getRegistrationNum().equals(regNo))
            {
                return true;
            }
        }
        return false;
    }

    public void addFriend(String regNo, int currentStudent_Num)
    {
        if(validateStudent(regNo))
        {
            System.out.println("Everything is awesome");
        }
    }

    public void ShowFriends(String RegNo)
    {
        for(Student_Class student : studentList.values())
        {
            if(student.getRegistrationNum().equals(RegNo))
            {
                System.out.println("Name: " + student.getName() + " RegNo: " + student.getRegistrationNum() + " Gender: " + student.getGender() + " GPA: " + student.getGPA());
            }
        }
    }

    public void ParseFile(String Filename)
    {
        File file = new File("C:\\Users\\142128G\\Desktop\\Test.txt");
        if(file.exists())
        {
            System.out.println("True");
        }
        else
        {
            System.out.println("Wrong");
        }
    }
}
