package com.simple.one.radio;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class MainActivity extends AppCompatActivity implements ServiceCallbacks{
    Geocoder geocoder = new Geocoder(this, Locale.getDefault());
    Setting mSetting = new Setting(MainActivity.this);
    ListView mainListView;
    ArrayAdapter<String> listAdapter;

    private MyService myService;
    private boolean bound = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Intent intent = new Intent(this, MyService.class);
        bindService(intent, serviceConnection, Context.BIND_AUTO_CREATE);

        /* Init array list view */
        mainListView = (ListView) findViewById(R.id.mainListView);
        mSetting.data_array = new ArrayList<String>();
        mSetting.adapter = new ArrayAdapter<String>(this,R.layout.item, mSetting.data_array);

        mSetting.locationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);

        mSetting.doJob(this, 1);

        //show_message(mSetting.DataBuffer);
    }

    private ServiceConnection serviceConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName className, IBinder service) {
            // cast the IBinder and get MyService instance
            MyService.LocalBinder binder = (MyService.LocalBinder) service;
            myService = binder.getService();
            bound = true;
            myService.setCallbacks((MyService.ServiceCallbacks) MainActivity.this); // register
        }

        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            bound = false;
        }
    };

    @Override
    public void onBackPressed() {
        moveTaskToBack(true);
    }

    public String getLocation(){
        return mSetting.Location;
    }

    public String getAddress(){
        return mSetting.Address;
    }
    //Put function wants to run period task here
    public void RunTask(){

        if(mSetting.check_internet_connection()) {
            NetworkUpdate();
            new MyPost(MainActivity.this).execute(); // Post to server
        }
        else{
            if(mSetting.checkGPS_setting()){
                GPSUpdate();
                //store in buffer
            }
        }

    }

    public void NetworkUpdate() {
        if(!mSetting.checkLocation())
            return;
        mSetting.locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER,
                60 * 1000, 10, locationListenerNetwork);
    }

    private final LocationListener locationListenerNetwork = new LocationListener() {
        public void onLocationChanged(Location location) {
            mSetting.Longtitude = location.getLongitude();
            mSetting.Latitude = location.getLatitude();

            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    //Toast.makeText(MainActivity.this, "Network Provider update", Toast.LENGTH_SHORT).show();
                    //Toast.makeText(MainActivity.this, "GPS " + mSetting.Longtitude + "," + mSetting.Latitude, Toast.LENGTH_SHORT).show();
                    mSetting.Location = build_data_struct(); // Create frame data
                    mSetting.locationManager.removeUpdates(locationListenerNetwork); //Clear location listener
                }
            });
        }

        @Override
        public void onStatusChanged(String s, int i, Bundle bundle) {}
        @Override
        public void onProviderEnabled(String s) {}
        @Override
        public void onProviderDisabled(String s) {}
    };

    public void GPSUpdate() {
        if(!mSetting.checkLocation())
            return;

        if(mSetting.button_GPS) {
            mSetting.button_GPS = false;
            mSetting.locationManager.removeUpdates(locationListenerGPS);
        }
        else {
            mSetting.button_GPS = true;
            mSetting.locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 2 * 60 * 1000, 10, locationListenerGPS);
        }
    }

    private final LocationListener locationListenerGPS = new LocationListener() {
        public void onLocationChanged(Location location) {
            mSetting.Longtitude = location.getLongitude();
            mSetting.Latitude = location.getLatitude();

            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    //Toast.makeText(MainActivity.this, "GPS Provider update", Toast.LENGTH_SHORT).show();
                    ///Toast.makeText(MainActivity.this, "GPS " + mSetting.Longtitude + "," + mSetting.Latitude,
                    //               Toast.LENGTH_SHORT).show();
                    try {
                        mSetting.addresses = geocoder.getFromLocation(mSetting.Latitude, mSetting.Longtitude, 1);
                        String tmp = String.valueOf(mSetting.Longtitude) + ",";
                        tmp += mSetting.Latitude + " : ";
                        tmp += mSetting.addresses.get(0).getAddressLine(0) + " - ";
                        tmp += mSetting.get_current_time();
                        //mSetting.add_to_list(tmp);
                        //Set variable
                        mSetting.Location = tmp;
                        mSetting.Address = mSetting.addresses.get(0).getAddressLine(0);

                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });
        }

        @Override
        public void onStatusChanged(String s, int i, Bundle bundle) {}
        @Override
        public void onProviderEnabled(String s) {}
        @Override
        public void onProviderDisabled(String s) {}
    };

    public void add_to_list(String data){
        mSetting.data_array.add(data);
        mainListView.setAdapter(mSetting.adapter);
        mSetting.adapter.notifyDataSetChanged();
    }

    public void show_message(String content){
        Toast.makeText(MainActivity.this, content, Toast.LENGTH_SHORT).show();
    }

    private String build_data_struct(){
        String tmp = null;
        try {
            mSetting.addresses = geocoder.getFromLocation(mSetting.Latitude, mSetting.Longtitude, 1);
            tmp = String.valueOf(mSetting.Longtitude) + ",";
            tmp += mSetting.Latitude + " : ";
            tmp += mSetting.addresses.get(0).getAddressLine(0) + " - ";
            tmp += mSetting.get_current_time();
            //mSetting.add_to_list(tmp);
            //Set variable
            //mSetting.Address = mSetting.addresses.get(0).getAddressLine(0);

        } catch (IOException e) {
            e.printStackTrace();
        }
        return tmp;
    }
}
