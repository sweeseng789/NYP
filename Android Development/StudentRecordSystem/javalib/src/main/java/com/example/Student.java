package com.example;

<<<<<<< HEAD:Android Development/StudentRecordSystem/javalib/src/main/java/com/example/Student.java
public class Student {
=======
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Vector;

public class Student_Class {
    private int studentNum;
>>>>>>> origin/master:Android Development/StudentRecordSystem/javalib/src/main/java/com/example/Student_Class.java
    private String name;
    private String RegistrationNum;
    private int Gender;
    private float GPA;
<<<<<<< HEAD:Android Development/StudentRecordSystem/javalib/src/main/java/com/example/Student.java

    public Student(String name, String RegistrationNum, int Gender, float GPA)
=======
    private HashMap<String, SearchResult_Class> friendList;

    public Student_Class(String name, String RegistrationNum, int Gender, float GPA)
>>>>>>> origin/master:Android Development/StudentRecordSystem/javalib/src/main/java/com/example/Student_Class.java
    {
        this.name = name;
        this.RegistrationNum = RegistrationNum;
        this.Gender = Gender;
        this.GPA = GPA;
<<<<<<< HEAD:Android Development/StudentRecordSystem/javalib/src/main/java/com/example/Student.java
=======
        friendList = null;
>>>>>>> origin/master:Android Development/StudentRecordSystem/javalib/src/main/java/com/example/Student_Class.java
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
