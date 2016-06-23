package com.ece4564.group11.workout.network;

/**
 * This class is a AsyncTask inherited class that sends the workout plans stored in server and parse.
 */

import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONException;
import org.json.JSONObject;

import android.os.AsyncTask;

public class StoreDataNetworkTask extends AsyncTask<String, Integer, Boolean> {

	JSONObject jObject_;
	String jString_;
	String address_;
	String identifier_;
	String uuid_;

	public StoreDataNetworkTask() {
		jObject_ = null;
		jString_ = null;
		address_ = null;
		identifier_ = null;
		uuid_ = null;
	}

	public StoreDataNetworkTask(JSONObject jOb, String addr, String name,
			String uuid) {
		jObject_ = jOb;
		jString_ = jObject_.toString();
		address_ = addr;
		identifier_ = name;
		uuid_ = uuid;

	}

	public StoreDataNetworkTask(String jStr, String addr, String name,
			String uuid) {
		try {
			jObject_ = new JSONObject(jStr);
			jString_ = jStr;
			identifier_ = name;
			address_ = addr;
			uuid_ = uuid;
		} catch (JSONException e) {
			jObject_ = null;
			jString_ = null;
			address_ = null;
			uuid = null;
			e.printStackTrace();
		}
	}

	@Override
	protected Boolean doInBackground(String... arg0) {
		if (jString_ == null || address_ == null || identifier_ == null
				|| uuid_ == null) {
			return false;
		} else {
			HttpClient httpclient = new DefaultHttpClient();
			HttpPost httppost = new HttpPost(address_ + "store");
			List<NameValuePair> nameValuePairs;

			nameValuePairs = new ArrayList<NameValuePair>(3);
			nameValuePairs.add(new BasicNameValuePair("id", identifier_));
			nameValuePairs.add(new BasicNameValuePair("data", jString_));
			nameValuePairs.add(new BasicNameValuePair("uuid", uuid_));

			HttpResponse response = null;
			try {
				httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
				response = httpclient.execute(httppost);
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}

			if (response.getStatusLine().getStatusCode() == 204) {
				return true;
			} else {
				return false;
			}
		}
	}

	@Override
	protected void onPostExecute(Boolean result) {
		if (result) {
			System.out.println("Data Success");
		} else {
			System.out.println("Data Failure");
		}
	}

}
