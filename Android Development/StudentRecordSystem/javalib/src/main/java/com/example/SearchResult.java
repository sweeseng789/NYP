package com.example;

import java.util.Vector;

public class SearchResult {
  //  private int value;
 //   private String text;

    private Vector<Integer> value;
    private Vector<String> text;

    public SearchResult()
    {
        value = null;
        text = null;
    }

    //Setter
    public void setValue(int value) {
        //this.value = value;
        this.value.add(value);
    }

    public void setText(String text) {
        this.text.add(text);
    }

    //Getter
    public Vector getValue() {
        return value;
    }

    public Vector getText() {
        return text;
    }
}
