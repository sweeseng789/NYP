package com.example;

public class Student {
    private String name;
    private String RegistrationNum;
    private int Gender;
    private float GPA;

    public Student(String name, String RegistrationNum, int Gender, float GPA)
    {
        this.name = name;
        this.RegistrationNum = RegistrationNum;
        this.Gender = Gender;
        this.GPA = GPA;
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
