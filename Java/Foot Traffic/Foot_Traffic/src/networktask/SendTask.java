package networktask;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import com.example.foot_traffic.Helper;

import Location_Data.LocationPackage;
import android.os.AsyncTask;

public class SendTask extends AsyncTask<String, Integer, String>{

	Helper helper_;
	String address_;
	String status_;
	
	public SendTask()
	{
		helper_ = null;
		address_ = "";
	}
	
	public SendTask(Helper h, String dest, String status)
	{
		helper_ = h;
		address_ = dest;
		status_ = status;
	}
	
	@Override
	protected String doInBackground(String... arg0) 
	{
		Calendar curTime = Calendar.getInstance();
		int curHour = curTime.get(Calendar.HOUR_OF_DAY);
		
		LocationPackage loc;
		loc = helper_.getCurLocation();
		
		HttpClient httpclient = new DefaultHttpClient();
	    HttpPost httppost = new HttpPost(address_+"/postdata");
	    
	    List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(5);
        nameValuePairs.add(new BasicNameValuePair("lat", Double.toString(loc.getLat())));
        nameValuePairs.add(new BasicNameValuePair("lon", Double.toString(loc.getLon())));
        nameValuePairs.add(new BasicNameValuePair("time", Integer.toString(curHour)));
        nameValuePairs.add(new BasicNameValuePair("light", Float.toString(helper_.getLight())));
        nameValuePairs.add(new BasicNameValuePair("temp", Float.toString(helper_.getTemp())));
        nameValuePairs.add(new BasicNameValuePair("status", status_));
        
        HttpResponse response;
        try 
        {
			httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
			response = httpclient.execute(httppost);
		} 
        catch (UnsupportedEncodingException e) 
        {
        	System.out.println("Error could not make correct POST");
		} catch (ClientProtocolException e) 
		{
			System.out.println("Error: Client protocol Exception");
		} 
        catch (IOException e) 
        {
        	System.out.println("Error: IOException");
		}
        
        return null;
	}
	

}
