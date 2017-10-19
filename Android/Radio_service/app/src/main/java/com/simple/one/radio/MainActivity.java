package com.simple.one.radio;

import android.app.Activity;
import android.content.Intent;
import android.location.LocationManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /* new */
        LocationManager locationManager = null;
        Activity activity = null;

        /* new class */
        Setting setting = new Setting(locationManager, MainActivity.this);
        API api = new API(setting);
    }

    @Override
    public void onStart(){
        super.onStart();
        startService(new Intent(this, MyService.class));
    }
}
