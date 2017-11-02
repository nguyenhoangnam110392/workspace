package com.simple.one.radio;

import android.app.Activity;
import android.content.Intent;
import android.location.LocationManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Toast.makeText(this, "Start.", Toast.LENGTH_LONG).show();
    }

    @Override
    public void onStart(){
        super.onStart();
        startService(new Intent(this, MyService.class));
    }
}
