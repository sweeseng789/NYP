package com.sidm.android_framework;

import android.app.Activity;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;

public class MainMenu extends Activity implements View.OnClickListener {

    private Button Start_Button;
    private Button Help_Button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //Hide Title
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        //Hide top bar
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.mainmenu);

        Start_Button = (Button)findViewById(R.id.Start_Button);
        Start_Button.setOnClickListener(this);
    }

    public void onClick(View v)
    {
        Intent intent = new Intent();

        if(v == Start_Button)
        {
            //intent.setClass(this, Gamepage.class);
        }
        else if (v == Help_Button)
        {
            //intent.setClass(this, Helppage.class);
        }
        startActivity(intent);
    }

    protected void onPause()
    {
        super.onPause();
    }

    protected void onStop()
    {
        super.onStop();
    }

    protected void onDestroy()
    {
        super.onDestroy();
    }
}
