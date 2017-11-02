package com.simple.one.radio;

import android.content.Context;
import android.location.LocationManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.widget.Toast;

/**
 * Created by Mr.HN on 10/19/2017.
 */

public class API {
    Setting setting;

    public API(Setting setting_from_main) {
        this.setting = setting_from_main;
    }

    public  boolean checkGPS_setting(){
        //LocationManager manager = (LocationManager)mActivity.getSystemService(Context.LOCATION_SERVICE );
        boolean statusOfGPS = setting.locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        if(!statusOfGPS) {
            return true;
        }
        return false;
    }

    public boolean isNetwork_enabled(){
        boolean tmp = setting.locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
        return tmp;
    }

    public boolean isGPS_enabled(){
        boolean tmp = setting.locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        return tmp;
    }
/*
    public boolean check_internet_connection(){
        ConnectivityManager ConnectionManager = (ConnectivityManager)setting.activity.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = ConnectionManager.getActiveNetworkInfo();
        if(networkInfo != null && networkInfo.isConnected()) {
            return true;
        }
        return false;
    }
    */
}
