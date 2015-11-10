package com.example;

import java.util.ArrayList;
import java.util.Vector;

public class Student_Class {
    private int studentNum;
    private String name;
    private String RegistrationNum;
    private int Gender;
    private float GPA;
    FriendList_Class friendList;

    public Student_Class(int studentNum, String name, String RegistrationNum, int Gender, float GPA)
    {
        this.studentNum = studentNum;
        this.name = name;
        this.RegistrationNum = RegistrationNum;
        this.Gender = Gender;
        this.GPA = GPA;
        friendList = new FriendList_Class();
    }

    public int getStudentNum()
    {
        return studentNum;
    }

    public String getName()
    {
        return name;
    }

    public String getRegistrationNum()
    {
        return RegistrationNum;
    }

    public int getGender()
    {
        return Gender;
    }

    public float getGPA()
    {
        return GPA;
    }

}
