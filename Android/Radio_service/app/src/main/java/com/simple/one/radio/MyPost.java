package com.simple.one.radio;

import android.content.Context;
import android.location.Location;
import android.location.SettingInjectorService;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

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
import org.apache.http.util.EntityUtils;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by one on 10/9/2017.
 */

public class MyPost extends AsyncTask<Void,Void,Void> {
    private Setting setting;

    public MyPost(Setting arg_setting){
        this.setting = arg_setting;
    }

    @Override
    protected Void doInBackground(Void... arg0) {
        // TODO Auto-generated method stub
        // Create a new HttpClient and Post Header
        HttpClient httpclient = new DefaultHttpClient();
        HttpPost httppost = new HttpPost("https://luutruthongtinn.000webhostapp.com/Location/Location_receive.php");

        try {
            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);
            nameValuePairs.add(new BasicNameValuePair("device_username", "admin"));
            nameValuePairs.add(new BasicNameValuePair("device_password", "9999"));
            nameValuePairs.add(new BasicNameValuePair("device_longtitude", String.valueOf(setting.Longtitude)));
            nameValuePairs.add(new BasicNameValuePair("device_latitude", String.valueOf(setting.Latitude)));
            nameValuePairs.add(new BasicNameValuePair("device_address", setting.Address));
            nameValuePairs.add(new BasicNameValuePair("device_datetime", setting.DateTime));
            //httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs, HTTP.UTF_8));

            // Execute HTTP Post Request
            HttpResponse response = httpclient.execute(httppost);
            setting.response_from_web = EntityUtils.toString(response.getEntity());
        } catch (ClientProtocolException e) {
            // TODO Auto-generated catch block
        } catch (IOException e) {
            // TODO Auto-generated catch block
        }
        return null;
    }
}