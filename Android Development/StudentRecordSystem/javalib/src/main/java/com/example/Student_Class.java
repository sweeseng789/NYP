package com.example;

public class Student_Class {
    private String name;
    private String RegistrationNum;
    private int Gender;
    private float GPA;
    private SearchResult_Class result;

    public Student_Class(String name, String RegistrationNum, int Gender, float GPA, SearchResult_Class result)
    {
        this.name = name;
        this.RegistrationNum = RegistrationNum;
        this.Gender = Gender;
        this.GPA = GPA;
        this.result = result;
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

    public SearchResult_Class getResult()
    {
        return result;
    }
}
