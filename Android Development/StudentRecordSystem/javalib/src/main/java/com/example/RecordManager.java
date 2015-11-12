package com.example;

import org.omg.CORBA.Environment;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Array;
import java.nio.file.FileSystem;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

import javax.naming.Context;

public class RecordManager
{
    private static int numOfStudents_Male;
    private static int numOfStudents_Female;
    private static int currentStudent_Num;

    HashMap<Integer, Student> studentList = new HashMap<>();

    public RecordManager()
    {
        numOfStudents_Male = 0;
        numOfStudents_Female = 0;
        currentStudent_Num = 0;
    }

    public void AddStudent(String name, String RegistrationNum, int Gender, float GPA)
    {
        Student newStudent = new Student(name, RegistrationNum, Gender, GPA);

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
            Student student = studentList.get(a);
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

    public void readText()
    {
        File file = new File("C:\\Users\\Ong\\Desktop\\NYP\\Android Development\\StudentRecordSystem\\javalib\\src\\main\\java\\com\\example\\studentlist.txt");
        Scanner sc = null;
        if(file.exists())
        {
            System.out.println("True");

            try
            {
                sc = new Scanner(file);
            }
            catch (IOException a)
            {
                System.out.println("Error");
            }

            String regNo = null, name = null, gender = null, gpa = null;
            String num1 = null, num2 = null, num3 = null, num4 = null;
            while (sc.hasNext())
            {
                System.out.println(regNo = sc.next());
                System.out.println(name = sc.next());
                System.out.println(gender = sc.next());
                System.out.println(gpa = sc.next());
               // System.out.println(num1 = sc.next());
               // System.out.println(num2 = sc.next());
               // System.out.println(num3 = sc.next());
               // System.out.println(num4 = sc.next());



                System.out.println("\n");
            }
        }
        else
        {
            System.out.println("False");
        }
    }

}
