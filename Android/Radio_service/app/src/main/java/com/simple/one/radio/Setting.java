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
    /*------------ constant -------------------*/
    public long NOTIFY_SECOND = 60;
    public long NOTIFY_MINUTE = 0;
    public long NOTIFY_INTERVAL = (NOTIFY_MINUTE * 60 + NOTIFY_SECOND) * 1000;
    public long GPS_NOTIFY_OFF_SECOND = 20;
    public long GPS_NOTIFY_OFF_INTERVAL = GPS_NOTIFY_OFF_SECOND * 1000;
    public int TAKE_PHOTO_CODE = 0;

    /*------------ variables -------------------*/
    public String Address = null;
    public double Longtitude = 0;
    public double Latitude = 0;
    public String DateTime = null;
    public String response_from_web = null;

    /*-------------- object -------------------*/
    public LocationManager locationManager = null;

    public Setting(LocationManager location_main){
        this.locationManager = location_main;
    }
}
