package com.example.cs3714yu_hwk3;

import java.net.MalformedURLException;
import java.net.URL;

import android.app.Activity;
import android.app.Fragment;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class InfoFragment extends Fragment implements SensorEventListener
{
	
	private float mAccel; // acceleration apart from gravity
    private float mAccelCurrent; // current acceleration including gravity
    private float mAccelLast; // last acceleration including gravity
    
	private float lastX = 0;
    private float lastY = 0;
    private float lastZ = 0;
	
	private MainActivity parent;
	private SensorManager sm_;
	
	private onURLParsed listener_;
	
	private EditText eText_;
	private TextView xCoords_;
	private TextView yCoords_;
	private TextView zCoords_;
	
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) 
	{
		View view = inflater.inflate(R.layout.info_frag,container, false);
		
		lastX = lastY = lastZ = 0;
		xCoords_ = (TextView) view.findViewById(R.id.xCoords);
		yCoords_ = (TextView) view.findViewById(R.id.yCoords);
		zCoords_ = (TextView) view.findViewById(R.id.zCoords);
		eText_ = (EditText) view.findViewById(R.id.editText1);
		
		parent = (MainActivity) this.getActivity();
		
		mAccel = 0.00f;
		mAccelCurrent = SensorManager.GRAVITY_EARTH;
		mAccelLast = SensorManager.GRAVITY_EARTH;
		return view;
	}
	@Override
	public void onAccuracyChanged(Sensor arg0, int arg1) 
	{
	}

	@Override
	public void onSensorChanged(SensorEvent event) 
	{
		if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
		{
			float x = event.values[0];
			float y = event.values[1];
			float z = event.values[2];
			
			if ((lastX - x) > .1)
			{
				lastX = x;
			}
			else if ((lastY - y) < .1)
			{
				lastY = y;
			}
			else if ((lastZ - z) < .1)
			{
				lastZ = z;
			}
			
			xCoords_.setText("X: " + Float.toString(lastX));
			yCoords_.setText("Y: " + Float.toString(lastY));
			zCoords_.setText("Z: " + Float.toString(lastZ));
			
		    mAccelLast = mAccelCurrent;
		    mAccelCurrent = (float) Math.sqrt((double) (x*x + y*y + z*z));
		    float delta = mAccelCurrent - mAccelLast;
		    mAccel = mAccel * 0.9f + delta; // perform low-cut filter
		    
	        if (mAccel > 6)
	        {
	        	detect();
	        }
		}
	}
	
	private void detect()
	{
		String s = eText_.getText().toString();
		listener_.show(s);
	}
	
	public void registerListener(onURLParsed oup)
	{
		listener_ = oup;
	}

}
