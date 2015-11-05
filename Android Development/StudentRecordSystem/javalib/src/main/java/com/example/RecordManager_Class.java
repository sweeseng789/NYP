package com.example;

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
        numOfStudents_Male = 0;
        numOfStudents_Female = 0;
        currentStudent_Num = 0;
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
        for (int a = 0; a < studentList.size(); ++a)
        {
            Student_Class student = studentList.get(a);
            System.out.println("Number: " + a);
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


}
