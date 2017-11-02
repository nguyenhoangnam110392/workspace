package com.simple.one.radio;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

/**
 * Created by one on 10/10/2017.
 */

public class MyService extends Service {

    private static final String TAG = "BOOMBOOMTESTGPS";
    private LocationManager mLocationManager = null;
    private Handler mHandler = new Handler();
    private Timer mTimer = null;
    Location mLastLocation;
    Geocoder geocoder = new Geocoder(MyService.this, Locale.getDefault());
    List<Address> geo;
    private boolean update_ticket = true;

    Setting setting;
    API api;

    @Override
    public void onCreate() {

        /* new */
        LocationManager locationManager = null;

        /* new class */
        setting = new Setting(locationManager);
        api = new API(setting, this);

        if(mTimer != null) {
            mTimer.cancel();
        } else {
            mTimer = new Timer();
        }
        // schedule task
        mTimer.scheduleAtFixedRate(new TimeDisplayTimerTask(), 0, setting.NOTIFY_INTERVAL);
    }

    @Override
    public void onStart(Intent intent, int startId) {
        Toast.makeText(this, "Radio Started", Toast.LENGTH_LONG).show();
    }

    @Override
    public void onDestroy() {
        //Toast.makeText(this, "MyService Stopped", Toast.LENGTH_LONG).show();
    }

    private class LocationListener implements android.location.LocationListener
    {
        public LocationListener(String provider)
        {
            mLastLocation = new Location(provider);
        }

        @Override
        public void onLocationChanged(Location location)
        {
            mLastLocation.set(location);
            setting.Longtitude = location.getLongitude();
            setting.Latitude = location.getLatitude();
        }

        @Override
        public void onProviderDisabled(String provider) {}

        @Override
        public void onProviderEnabled(String provider) {}

        @Override
        public void onStatusChanged(String provider, int status, Bundle extras) {}
    }

    LocationListener[] mLocationListeners = new LocationListener[] {
            new LocationListener(LocationManager.GPS_PROVIDER),
            new LocationListener(LocationManager.NETWORK_PROVIDER)
    };

    @Override
    public IBinder onBind(Intent arg0) {
        return null;
    }

    private void initializeLocationManager() {
        if (mLocationManager == null) {
            mLocationManager = (LocationManager) getApplicationContext().getSystemService(Context.LOCATION_SERVICE);
        }
    }
    class TimeDisplayTimerTask extends TimerTask {

        @Override
        public void run() {
            // run on another thread
            mHandler.post(new Runnable() {

                @Override
                public void run() {
                    if(update_ticket) {
                        update_ticket = false;
                        initializeLocationManager();
                        LocationUpdate();
                        //Toast.makeText(getApplicationContext(), "Location: " + setting.Longtitude + "," + setting.Latitude,
                        //        Toast.LENGTH_SHORT).show();

                        try {
                            geo = geocoder.getFromLocation(setting.Latitude, setting.Longtitude, 1);
                            setting.Address = geo.get(0).getAddressLine(0);
                            setting.DateTime = getDateTime();

                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                        //if(setting.Longtitude != 0 && setting.Latitude != 0) {
                            MyPost mypost = new MyPost(setting);
                            try {
                                mypost.execute().get(30000, TimeUnit.MILLISECONDS);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            } catch (ExecutionException e) {
                                e.printStackTrace();
                            } catch (TimeoutException e) {
                                e.printStackTrace();
                            }
                        //}
                        update_ticket = true; //need to put this variable into post method
                    }
                    final Handler handler = new Handler();
                    handler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            mLocationManager.removeUpdates(mLocationListeners[0]);
                            mLocationManager.removeUpdates(mLocationListeners[1]);
                            //api.takeSnapShots();
                            //Toast.makeText(getApplicationContext(), "Image snapshot Done",Toast.LENGTH_LONG).show();
                        }
                    }, setting.GPS_NOTIFY_OFF_INTERVAL);
                }

            });
        }

        private String getDateTime() {
            // get date time in custom format
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy/MM/dd - HH:mm:ss");
            return sdf.format(new Date());
        }

        private void LocationUpdate(){

            try {
                mLocationManager.requestLocationUpdates(
                        LocationManager.NETWORK_PROVIDER, 0, 0,
                        mLocationListeners[1]);
            } catch (java.lang.SecurityException ex) {
                Log.i(TAG, "fail to request location update, ignore", ex);
            } catch (IllegalArgumentException ex) {
                Log.d(TAG, "network provider does not exist, " + ex.getMessage());
            }
            /*
            try {
                mLocationManager.requestLocationUpdates(
                        LocationManager.GPS_PROVIDER, 0, 0,
                        mLocationListeners[0]);
            } catch (java.lang.SecurityException ex) {
                Log.i(TAG, "fail to request location update, ignore", ex);
            } catch (IllegalArgumentException ex) {
                Log.d(TAG, "gps provider does not exist " + ex.getMessage());
            }
*/
        }
    }
}
