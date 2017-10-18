package com.simple.one.radio;

import android.content.Context;
import android.location.Location;
import android.os.AsyncTask;
import android.util.Log;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.impl.entity.StrictContentLengthStrategy;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.HTTP;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by one on 10/9/2017.
 */

public class MyPost extends AsyncTask<Void,Void,Void> {

    private String Address = null;
    private double Longtitude = 0;
    private double Latitude = 0;


    public MyPost(String address, double longtitude, double latitude){
        this.Address = address;
        this.Longtitude = longtitude;
        this.Latitude = latitude;
    }

    @Override
    protected Void doInBackground(Void... arg0) {
        // TODO Auto-generated method stub
        // Create a new HttpClient and Post Header
        HttpClient httpclient = new DefaultHttpClient();
        HttpPost httppost = new HttpPost("http://luutruthongtinn.000webhostapp.com/test.php");

        try {
            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);
            nameValuePairs.add(new BasicNameValuePair("android_longtitude", String.valueOf(Longtitude)));
            nameValuePairs.add(new BasicNameValuePair("android_latitude", String.valueOf(Latitude)));
            nameValuePairs.add(new BasicNameValuePair("android_address", Address));
            //httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs, HTTP.UTF_8));

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