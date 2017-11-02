package com.simple.one.radio;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.hardware.Camera;
import android.location.LocationManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.view.SurfaceView;
import android.widget.Toast;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Created by Mr.HN on 10/19/2017.
 */

public class API {
    Setting setting;
    private Context context;
    private File photoCaptured;

    public API(Setting setting_from_main, Context context_from_main) {
        this.setting = setting_from_main;
        this.context = context_from_main;
    }

    public  boolean checkGPS_setting(){
        //LocationManager manager = (LocationManager)mActivity.getSystemService(Context.LOCATION_SERVICE );
        boolean statusOfGPS = setting.locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        if(!statusOfGPS) {
            return true;
        }
        return false;
    }

    public void takeSnapShots()
    {
        //Toast.makeText(getApplicationContext(), "Image snapshot   Started",Toast.LENGTH_SHORT).show();
        // here below "this" is activity context.
        SurfaceView surface = new SurfaceView(context);
        Camera camera = Camera.open();
        try {
            camera.setPreviewDisplay(surface.getHolder());
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        camera.startPreview();
        camera.takePicture(null,null,jpegCallback);
    }


    /** picture call back */
    Camera.PictureCallback jpegCallback = new Camera.PictureCallback() {
        public void onPictureTaken(byte[] data, Camera camera)
        {
            FileOutputStream fos = null;
            File file = new File("1.jpg");

            try {
                fos = new FileOutputStream(file, true);

                fos.write(data);
                fos.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } finally
            {
                camera.stopPreview();
                camera.release();
                camera = null;
                //Toast.makeText(getApplicationContext(), "Image snapshot Done",Toast.LENGTH_LONG).show();


            }
        }
    };
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
