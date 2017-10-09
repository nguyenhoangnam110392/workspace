package com.simple.one.radio;

import android.app.Activity;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

/**
 * Created by one on 10/10/2017.
 */

public class MyService extends Service {
    private static final String TAG = "HelloService";
    private boolean isRunning  = false;

    private final IBinder binder = new LocalBinder();
    private ServiceCallbacks serviceCallbacks;

    public interface ServiceCallbacks {
        void doSomething();
    }
    public void setCallbacks(ServiceCallbacks callbacks) {
        serviceCallbacks = callbacks;
    }
    public class LocalBinder extends Binder {
        MyService getService() {
            // Return this instance of MyService so clients can call public methods
            return MyService.this;
        }
    }

    @Override
    public void onCreate() {
        Log.i(TAG, "Service onCreate");

        isRunning = true;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        Log.i(TAG, "Service onStartCommand");
        //mSetting.DataBuffer = "hihi";


        return Service.START_STICKY;
    }


    @Override
    public IBinder onBind(Intent arg0) {
        Log.i(TAG, "Service onBind");
        return null;
    }

    @Override
    public void onDestroy() {

        isRunning = false;

        Log.i(TAG, "Service onDestroy");
    }
}
