package com.simple.one.radio;

import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.location.Address;
import android.location.LocationManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.provider.Settings;
import android.support.v7.app.AlertDialog;
import android.widget.ArrayAdapter;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Set;
import java.util.TimeZone;
import java.util.Timer;
import java.util.TimerTask;

import static com.simple.one.radio.R.id.mainListView;

/**
 * Created by one on 10/9/2017.
 */

public class Setting {
    public LocationManager locationManager = null;
    public Activity activity = null;

    public Setting(LocationManager location_main, Activity activity_main){
        this.locationManager = location_main;
        this.activity = activity_main;
    }
}
