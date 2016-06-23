package com.example.foot_traffic;

import android.graphics.Color;
import android.widget.Button;
import android.widget.ProgressBar;
import Location_Data.LocationPackage;

public class Helper {

	LocationPackage curLoc_;
	String destAddr_;
	float lightData_;
	float tempData_;
	boolean newLocData;
	boolean newLightData;
	boolean newGravData;
	ProgressBar progress_;
	Button sendButton_;
	
	public Helper()
	{
		curLoc_ = null;
		destAddr_ = "";
		newLocData = false;
		newLightData = false;
		newGravData = false;
		lightData_ = 0;
		tempData_ = 0;
		progress_ = null;
		sendButton_ = null;
	}
	
	public void setProgress(ProgressBar p)
	{
		progress_ = p;
		progress_.setProgress(0);
	}
	
	public void setLocation(LocationPackage l)
	{
		curLoc_ = l;
		
		if (!newLocData)
		{
			if (progress_.getProgress() == 25)
			{
				setProgress(75);
			}
			else if (progress_.getProgress() == 50)
			{
				setProgress(100);
			}
			else if (progress_.getProgress() == 0)
			{
				setProgress(50);
			}
		}
		
		newLocData = true;
	}
	
	public LocationPackage getCurLocation()
	{
		return curLoc_;
	}
	
	public void setDest(String dest)
	{
		destAddr_ = dest;
	}
	
	public boolean isNewLoc()
	{
		return newLocData;
	}
	
	public boolean isNewLight()
	{
		return newLightData;
	}
	
	public void setLightData(float data)
	{
		lightData_ = data;
		
		if(!newLightData)
		{
			if (progress_.getProgress() == 25)
			{
				setProgress(50);
			}
			else if (progress_.getProgress() == 50)
			{
				setProgress(75);
			}
			else if (progress_.getProgress() == 0)
			{
				setProgress(25);
			}
			else if (progress_.getProgress() == 75)
			{
				setProgress(100);
			}
		}
		
		newLightData = true;
	}
	
	public void setTempData(float data3)
	{
		tempData_ = data3;		
		
		if (!newGravData)
		{
			if (progress_.getProgress() == 25)
			{
				setProgress(50);
			}
			else if (progress_.getProgress() == 50)
			{
				setProgress(75);
			}
			else if (progress_.getProgress() == 0)
			{
				setProgress(25);
			}
			else if (progress_.getProgress() == 75)
			{
				setProgress(100);
			}
		}
		
		newGravData = true;
	}
	
	public void resetData()
	{
		newLightData = false;
		newLocData = false;
		newGravData = false;
		setProgress(0);
		sendButton_.setEnabled(false);
	}
	
	public float getLight()
	{
		return lightData_;
	}
	
	public float getTemp()
	{
		return tempData_;
	}
	
	public void setProgress(int add)
	{
		if (add == 100)
		{
			enableSend(true);
		}
		
		if (add == 0)
		{
			progress_.setProgress(0);
		}
		else
		{
			int i = progress_.getProgress();
			while(progress_.getProgress() != add)
			{
				progress_.setProgress(i++);
			}
		}
	}
	
	public void setSend(Button b)
	{
		sendButton_ = b;
	}
	
	public void enableSend(boolean b)
	{
		sendButton_.setEnabled(b);
		
		if (b)
		{
			sendButton_.setBackgroundColor(Color.parseColor("#61A5FF"));
		}
		else
		{
			sendButton_.setBackgroundColor(Color.parseColor("#8D8F94"));
		}
	}
}
