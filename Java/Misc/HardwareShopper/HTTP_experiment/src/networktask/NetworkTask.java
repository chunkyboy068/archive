package networktask;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.UnknownHostException;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;

import com.example.http_experiment.Helper;

import android.os.AsyncTask;

public class NetworkTask extends AsyncTask<String, Integer, String>{
	
	HttpClient httpclient_;
	HttpGet httpget_;
	BasicHttpParams params_;
	HttpResponse serverResponse_;
	
	String response;
	String result_;
	BufferedReader br_;
	StringBuilder builder_;
	
	String name_;
	Helper helper_;
	
	public NetworkTask(Helper h)
	{
		helper_ = h;
	}
	
	@Override
	protected String doInBackground(String... searchCrit) 
	{
		builder_ = new StringBuilder();
		String[] paramList = searchCrit[0].split(" ");
		String queryStr = new String();
		name_ = searchCrit[2];
		
		for (int i = 0; i<paramList.length; i++)
		{
			queryStr += paramList[i];
			if (i != (paramList.length-1))
			{
				queryStr+= "+";
			}
		}
		
		try 
		{
			httpclient_ = new DefaultHttpClient(); 
			params_ = new BasicHttpParams();
			
			if (name_.equals("newegg"))
			{
				params_.setParameter("Description", queryStr);
				httpget_ = new HttpGet(searchCrit[1] + "&Description=" + queryStr);
			}
			else if (name_.equals("frys"))
			{
				httpget_ = new HttpGet(searchCrit[1] + "&query_string=" + queryStr);
				params_.setParameter("query_string", queryStr);
			}
			
			httpget_.setParams(params_);
			serverResponse_ = httpclient_.execute(httpget_);
			br_ = new BufferedReader(new InputStreamReader(serverResponse_.getEntity().getContent()));
			
			while((response = br_.readLine()) != null)
			{
				builder_.append(response);
			}
			
		} 
		catch (UnknownHostException e) 
		{
			System.out.println("Error unknown host");
			e.printStackTrace();
		} 
		catch (IOException e) 
		{
			System.out.println("Error, IO exception");
			e.printStackTrace();
		}
		return builder_.toString();
	}
	
	protected void onPostExecute(String str)
	{
		helper_.giveFeedback("Done searching " + name_);
		helper_.setData(str, name_);
	}

}
