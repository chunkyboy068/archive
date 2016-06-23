package com.ece4564.group11.workout.network;

/**
 * This class sends the GPS location to the server to look for people.
 */

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;
import org.json.*;

import com.ece4564.group11.workout.sensor.LocationPackage;

import android.os.AsyncTask;
import android.widget.TextView;

public class LocationNetworkTask extends AsyncTask<String, Integer, HttpEntity> {

	LocationPackage location_;
	UUID unique_id;
	String address_;
	String name_;
	TextView status_;
	TextView friend_;
	int statuscode_;

	public LocationNetworkTask(LocationPackage l, UUID u, String addr, String n) {
		location_ = l;
		unique_id = u;
		address_ = addr;
		name_ = n;
		statuscode_ = 0;
	}

	public LocationNetworkTask(UUID u, String addr) {
		unique_id = u;
		address_ = addr;
		location_ = null;
		name_ = null;
		statuscode_ = 0;
	}

	public void setTexts(TextView stat, TextView friend) {
		status_ = stat;
		friend_ = friend;
	}

	@Override
	protected HttpEntity doInBackground(String... args) {
		HttpClient httpclient = new DefaultHttpClient();
		HttpPost httppost = new HttpPost(address_ + "/request");
		List<NameValuePair> nameValuePairs;

		if (args[0].equals("stay")) {
			nameValuePairs = new ArrayList<NameValuePair>(6);
			nameValuePairs.add(new BasicNameValuePair("lat", Double
					.toString(location_.getLat())));
			nameValuePairs.add(new BasicNameValuePair("lon", Double
					.toString(location_.getLon())));
			nameValuePairs.add(new BasicNameValuePair("top", Long
					.toString(unique_id.getMostSignificantBits())));
			nameValuePairs.add(new BasicNameValuePair("bot", Long
					.toString(unique_id.getLeastSignificantBits())));
			nameValuePairs.add(new BasicNameValuePair("name", name_));
			nameValuePairs.add(new BasicNameValuePair("state", args[0]));
		} else {
			nameValuePairs = new ArrayList<NameValuePair>(3);
			nameValuePairs.add(new BasicNameValuePair("top", Long
					.toString(unique_id.getMostSignificantBits())));
			nameValuePairs.add(new BasicNameValuePair("bot", Long
					.toString(unique_id.getLeastSignificantBits())));
			nameValuePairs.add(new BasicNameValuePair("state", args[0]));
		}

		HttpResponse response = null;
		try {
			httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
			response = httpclient.execute(httppost);
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}

		statuscode_ = response.getStatusLine().getStatusCode();
		if (response.getStatusLine().getStatusCode() == 200) {
			return response.getEntity();
		} else {
			return null;
		}
	}

	@Override
	protected void onPostExecute(HttpEntity result) {
		status_.setText("Retrieving Data...");

		if (statuscode_ == 204) {
			status_.setText("Successfully Removed from Area.");
		} else if (statuscode_ == 400) {
			status_.setText("Fatal Error");
		} else if (statuscode_ == 200) {
			JSONObject jOb;
			JSONArray names;
			try {
				jOb = new JSONObject(EntityUtils.toString(result));
				status_.setText("Results displayed!");
				if (jOb.length() == 0) {
					friend_.setText("There are no people near you.\n");

					return;
				}
				names = jOb.names();
				for (int i = 0; i < names.length(); i++) {
					friend_.setText("People Near You:\n");
					friend_.append(names.getString(i) + "\n");
				}
			} catch (Exception e) {
				status_.setText("Error in Response");
				e.printStackTrace();
			}
		} else if (statuscode_ == 0) {
			status_.setText("No Response from Server");
		}

	}

}
