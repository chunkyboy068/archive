package networktask;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;
import org.json.JSONException;
import org.json.JSONObject;

import android.os.AsyncTask;
import android.widget.TextView;

public class GetTask extends AsyncTask<String, Integer, JSONObject>{

	String address_;
	int hour_;
	TextView view_;
	
	public GetTask()
	{
		address_ = "";
	}
	
	public GetTask(String dest, int h, TextView view)
	{
		address_ = dest;
		hour_ = h;
		view_ = view;
	}

	@Override
	protected JSONObject doInBackground(String... strings) 
	{
		HttpResponse response = null;
		
		if (strings.length == 1)
		{
			response = sendDescription(strings[0]);
		}
		else if (strings.length == 2)
		{
			response = sendGPSLoc(strings[0], strings[1]);
		}
		
		if (response == null)
		{
			return null;
		}
		
		JSONObject jObject = null;
		try 
		{
			jObject = new JSONObject(EntityUtils.toString(response.getEntity()));
		} 
		catch (Exception e)
		{
			return null;
		}
		return jObject;
	}
	
	private HttpResponse sendDescription(String descrip)
	{
		HttpClient httpclient = new DefaultHttpClient();
	    HttpPost httppost = new HttpPost(address_+"/getdata");
	    
	    List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(5);
	    nameValuePairs.add(new BasicNameValuePair("description", descrip));
	    nameValuePairs.add(new BasicNameValuePair("hour", String.valueOf(hour_)));
	    
	    HttpResponse response = null;
        try 
        {
			httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
			response = httpclient.execute(httppost);
		} 
        catch (Exception e) 
        {
        	System.out.println("HTTP RESPONSE ERROR");
		}
        
        return response;
	}
	
	private HttpResponse sendGPSLoc(String lat, String lon)
	{
		HttpClient httpclient = new DefaultHttpClient();
	    HttpPost httppost = new HttpPost(address_+"/getdata");
	    
	    List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(5);
	    nameValuePairs.add(new BasicNameValuePair("lat", lat));
	    nameValuePairs.add(new BasicNameValuePair("lon", lon));
	    nameValuePairs.add(new BasicNameValuePair("hour", String.valueOf(hour_)));
	    
	    HttpResponse response = null;
        try 
        {
			httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
			response = httpclient.execute(httppost);
		} 
        catch (Exception e) 
        {
        	System.out.println("HTTP RESPONSE ERROR");
		} 
        
        return response;
	}

	@Override
	protected void onPostExecute(JSONObject result)
	{
		if (result == null)
		{
			view_.setText("No data could be retrieved");
			return;
		}
		
		String str = "";
		
		try 
		{
			str += "Total People at this Location: \n" + result.get("current") + "\n\n";
			str += "Average Temperature Since " + hour_ + ":00\n" + result.get("avgtemp") + " degrees C ";
			str += checkTemp(result.getString("avgtemp"));
			str += "Average Amount of Light Since " + hour_ + ":00\n" + result.get("avglight") + " Lumens ";
			str += checkLight(result.getString("avglight"));			
			str += "Total Traffic since " + hour_ + ":00\n" + result.get("totalups") + " people\n\n";
		} 
		catch (JSONException e) 
		{
			System.out.println("JSON ERROR");
		}
		
		view_.setText(str);
		
	}
	
	private String checkLight(String light)
	{
		Float fLight = Float.parseFloat(light);
		if (fLight.compareTo((float) 10) == -1)
		{
			return "(Very Dark)\n\n";
		}
		else if (fLight.compareTo((float) 30) == -1)
		{
			return "(Dark) \n\n";
		}
		else if (fLight.compareTo((float) 50) == -1)
		{
			return "(Light) \n\n";
		}
		else if (fLight.compareTo((float) 70) == -1)
		{
			return "(Bright) \n\n";
		}
		else if (fLight.compareTo((float) 100) == -1)
		{
			return "(Very Bright) \n\n";
		}
		
		return "\n\n";
	}
	
	private String checkTemp(String temp)
	{
		Float fTemp = Float.parseFloat(temp);
		
		if (fTemp.compareTo((float) 1) == -1)
		{
			return "(Freezing)\n\n";
		}
		else if (fTemp.compareTo((float) 4) == -1)
		{
			return "(Very Cold) \n\n";
		}
		else if (fTemp.compareTo((float) 10) == -1)
		{
			return "(Cold) \n\n";
		}
		else if (fTemp.compareTo((float) 16) == -1)
		{
			return "(Cool) \n\n";
		}
		else if (fTemp.compareTo((float) 22) == -1)
		{
			return "(Warm) \n\n";
		}
		else if (fTemp.compareTo((float) 26) == -1)
		{
			return "(Very Warm) \n\n";
		}
		else if (fTemp.compareTo((float) 100) == -1)
		{
			return "(Hot) \n\n";
		}
		
		return "\n\n";
	}
	
}
