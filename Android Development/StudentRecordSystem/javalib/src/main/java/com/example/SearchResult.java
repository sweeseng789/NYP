package com.example;

import java.util.Vector;

public class SearchResult {
  //  private int value;
 //   private String text;

    private int value;
    private String text;

    public SearchResult()
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
