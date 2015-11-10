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
        currentStudent_Num = 2;

        Student_Class newStudent = new Student_Class(0, "Swee Seng", "142128G", 1, 4.0f);
        studentList.put(0, newStudent);

        newStudent = new Student_Class(1, "Setsuna", "142852H", 1, 4.0f);
        studentList.put(1, newStudent);
    }

    public void AddStudent(String name, String RegistrationNum, int Gender, float GPA)
    {
        Student_Class newStudent = new Student_Class(currentStudent_Num, name, RegistrationNum, Gender, GPA);

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


        return result;
    }

    public boolean validateStudent(int regNo)
    {
        for(int a = 0; a < studentList.size(); ++a)
        {
            Student_Class student = studentList.get(a);

            if(student.getStudentNum() == regNo)
            {
                return true;
            }
        }

        return false;
    }

    public void addFriend(int regNo, int currentStudent_Num)
    {
        Student_Class studentToAdd = null;
        for (int a = 0; a < studentList.size(); ++a)
        {
            if(studentList.get(a).getStudentNum() == currentStudent_Num)
            {
                studentToAdd = studentList.get(a);
                break;
            }
        }

        if(studentToAdd != null)
        {
            for(int a = 0; a < studentList.size(); ++a)
            {
                if(studentList.get(a).getStudentNum() == regNo && studentList.get(a) != studentToAdd)
                {
                    studentToAdd.friendList.name.add(studentList.get(a).getName());
                    studentToAdd.friendList.regNo.add(studentList.get(a).getStudentNum());
                    studentToAdd.friendList.degreeOfFriend.add(1);
                }
            }
        }
    }

    public void ShowFriends(int RegNo)
    {
        Student_Class studentToAdd = null;
        for (int a = 0; a < studentList.size(); ++a)
        {
            if(studentList.get(a).getStudentNum() == RegNo)
            {
                studentToAdd = studentList.get(a);
                break;
            }
        }

        if(studentToAdd != null)
        {
            for(int a = 0; a < studentToAdd.friendList.name.size(); ++a)
            {
                System.out.println("Friend: " + a);
                System.out.println("Name: " + studentToAdd.friendList.name.get(a));
                System.out.println("Number: " + studentToAdd.friendList.regNo.get(a));
            }
        }

    }
}
