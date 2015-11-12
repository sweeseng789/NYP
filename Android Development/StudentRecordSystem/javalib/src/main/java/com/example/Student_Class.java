package com.example;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Vector;

public class Student_Class {
    private int studentNum;
    private String name;
    private String RegistrationNum;
    private int Gender;
    private float GPA;
    private HashMap<String, SearchResult_Class> friendList;

    public Student_Class(String name, String RegistrationNum, int Gender, float GPA)
    {
        this.name = name;
        this.RegistrationNum = RegistrationNum;
        this.Gender = Gender;
        this.GPA = GPA;
        friendList = null;
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

    public HashMap<String, SearchResult_Class> getFriendList()
    {
        return friendList;
    }

}
