package com.ece4564.group11.workout.network;

/**
 * This class deals with quotes.
 */

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import android.os.AsyncTask;
import android.widget.TextView;

public class QuoteNetworkTask extends AsyncTask<String, Integer, String> {

	String address_;
	TextView display_;

	public QuoteNetworkTask(String addr, TextView view) {
		address_ = addr;
		display_ = view;
	}

	@Override
	protected String doInBackground(String... arg0) {
		HttpClient httpclient = new DefaultHttpClient();
		HttpGet httpget = new HttpGet(address_ + "quote");
		try {
			HttpResponse response = httpclient.execute(httpget);
			return EntityUtils.toString(response.getEntity());
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	@Override
	protected void onPostExecute(String result) {
		if (result == null) {
			display_.setText("Try as hard in the gym as I am in contacting this server. -- Devs");
		} else {
			display_.setText(result);
		}
	}

}
