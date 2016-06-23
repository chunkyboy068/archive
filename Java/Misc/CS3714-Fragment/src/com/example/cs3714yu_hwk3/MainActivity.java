package com.example.cs3714yu_hwk3;

import java.net.MalformedURLException;
import java.net.URL;

import android.graphics.Bitmap;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.Toast;

public class MainActivity extends Activity implements onURLParsed{

	//default pic frag
	public final static String FRAG1_TAG = "FRAG1";
	//pic frag
	public final static String FRAG2_TAG = "FRAG2";
	//info frag
	public final static String FRAG3_TAG = "FRAG3";
	
	private SensorManager sm_;
    
    OnCommunicateSwapFragment defaultPic_;
    OnCommunicateSwapFragment swapPic_;
    InfoFragment info_;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		sm_ = (SensorManager)this.getSystemService(SENSOR_SERVICE);
		
		defaultPic_ = new OnCommunicateSwapFragment();
		swapPic_ = new OnCommunicateSwapFragment();
		info_ = new InfoFragment();
		info_.registerListener(this);
		
		if (this.getFragmentManager().findFragmentByTag(FRAG1_TAG) == null)
		{
			this.getFragmentManager().beginTransaction().add(R.id.frame1, defaultPic_, FRAG1_TAG).commit();
		}
		
		if (this.getFragmentManager().findFragmentByTag(FRAG3_TAG) == null)
		{
			this.getFragmentManager().beginTransaction().add(R.id.frame2, info_ , FRAG3_TAG).commit();
		}
		
	}

	@Override
	protected void onResume() 
	{
		super.onResume();
		Sensor accel = sm_.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		sm_.registerListener(info_, accel, SensorManager.SENSOR_DELAY_NORMAL);
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		sm_.unregisterListener(info_);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void show(String url)
	{
		try 
		{
			OnNetwork netTask = new OnNetwork(this);
			URL internet = new URL(url);
			netTask.execute(internet);
		} 
		catch (MalformedURLException e) 
		{
			Toast.makeText(this, "Enter a valid URL", Toast.LENGTH_SHORT).show();
		}
	}
	
	public void showPicture(Bitmap Result)
	{
		if (this.getFragmentManager().findFragmentByTag(FRAG1_TAG) != null)
		{
			if (Result == null)
			{
				Toast.makeText(this, "Couldn't Retrieve Image", Toast.LENGTH_SHORT).show();
			}
			else
			{
				swapPic_.show(Result);
				this.getFragmentManager().beginTransaction().replace(R.id.frame1, swapPic_, FRAG2_TAG).commit();
			}
		}
		else if (this.getFragmentManager().findFragmentByTag(FRAG2_TAG) != null)
		{
			this.getFragmentManager().beginTransaction().replace(R.id.frame1, defaultPic_, FRAG1_TAG).commit();
		}
	}

}
