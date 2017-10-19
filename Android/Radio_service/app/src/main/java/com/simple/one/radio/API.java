package com.simple.one.radio;

import android.content.Context;
import android.location.LocationManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

/**
 * Created by Mr.HN on 10/19/2017.
 */

public class API{
    Setting setting;

    public API(Setting setting_from_main){
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

    public boolean check_internet_connection(){
        ConnectivityManager ConnectionManager=(ConnectivityManager)setting.activity.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo= ConnectionManager.getActiveNetworkInfo();
        if(networkInfo != null && networkInfo.isConnected()) {
            return true;
        }
        return false;
    }
}
