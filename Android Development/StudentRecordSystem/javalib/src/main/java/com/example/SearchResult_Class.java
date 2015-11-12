package com.example;

import java.util.Vector;

/**
 * Created by 142128G on 11/5/2015.
 */
public class SearchResult_Class {
  //  private int value;
 //   private String text;

    private int value;
    private String text;

    public SearchResult_Class()
    {
        value = -1;
        text = "";
    }

    //Setter
    public void setValue(int value)
    {
        this.value = value;
    }

    public void setText(String text)
    {
        this.text = text;
    }

    //Getter
    public int getValue() {
        return value;
    }

    public String getText() {
        return text;
    }
}
