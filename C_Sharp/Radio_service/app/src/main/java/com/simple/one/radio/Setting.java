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
    Context mContext;
    Activity mActivity;

    public boolean button_GPS = false;
    public boolean button_Network = false;

    public double timer = 0;
    public double Latitude = 0;
    public double Longtitude = 0;

    public ArrayList<String> data_array;
    public ArrayAdapter adapter;
    public List<android.location.Address> addresses;

    public LocationManager locationManager;

    public String Location = null;
    public String Address = null;
    public String DataBuffer = null;

    public Setting(Activity activity){
        this.mActivity = activity;
    }

    private boolean isLocationEnabled() {
        return locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER) ||
                locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
    }

    public boolean checkLocation() {
        if(!isLocationEnabled())
            showAlert();
        return isLocationEnabled();
    }

    private void showAlert() {
        final AlertDialog.Builder dialog = new AlertDialog.Builder(mContext);
        dialog.setTitle("Enable Location")
                .setMessage("Your Locations Settings is set to 'Off'.\nPlease Enable Location to " +
                        "use this app")
                .setPositiveButton("Location Settings", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface paramDialogInterface, int paramInt) {
                        Intent myIntent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
                        //startActivity(myIntent);
                    }
                })
                .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface paramDialogInterface, int paramInt) {
                    }
                });
        dialog.show();
    }

    public String get_current_time(){
        Calendar cal = Calendar.getInstance(TimeZone.getTimeZone("GMT+7:00"));
        Date currentLocalTime = cal.getTime();
        DateFormat date = new SimpleDateFormat("HH:mm a");
        date.setTimeZone(TimeZone.getTimeZone("GMT+7:00"));

        String localTime = date.format(currentLocalTime);

        return localTime;
    }
    public void doJob(final MainActivity main, final long minute) {
        Timer T = new Timer();
        T.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                mActivity.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        timer++;
                        if (timer >= minute) {
                            main.RunTask();
                            timer = 0;
                        }
                    }
                });
            }
        }, 1000, 60000);  /* Delay in first run, period */
    }

    public  boolean checkGPS_setting(){
        //LocationManager manager = (LocationManager)mActivity.getSystemService(Context.LOCATION_SERVICE );
        boolean statusOfGPS = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        if(!statusOfGPS) {
            return true;
        }
        return false;
    }

    public boolean check_internet_connection(){
        ConnectivityManager ConnectionManager=(ConnectivityManager)mActivity.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo= ConnectionManager.getActiveNetworkInfo();
        if(networkInfo != null && networkInfo.isConnected()) {
            return true;
        }
        return false;
    }
}
