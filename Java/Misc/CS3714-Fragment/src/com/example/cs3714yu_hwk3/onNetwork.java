package com.example.cs3714yu_hwk3;

import java.io.InputStream;
import java.net.URL;

import android.app.Fragment;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.util.Log;

class OnNetwork extends AsyncTask<URL, String, Bitmap> {
	
	onURLParsed activity;
	
	public OnNetwork(onURLParsed ma)
	{
		activity = ma;
	}
	
	protected void onPostExecute(Bitmap result) 
	{
		activity.showPicture(result);
	}

	@Override
	protected Bitmap doInBackground(URL... url) 
	{
		URL urldisplay = url[0];
		Bitmap image = null;
		try {
			InputStream in = urldisplay.openStream();
			image = BitmapFactory.decodeStream(in);
		} catch (Exception e) {
			Log.e("Error", e.getMessage());
			e.printStackTrace();
		}
		return image;

	}

}
