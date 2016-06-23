package HourData;

import java.util.ArrayList;

public class HourData {

	Float avgLight_;
	Float avgTemp_;
	ArrayList<Float> tempList_;
	ArrayList<Float> lightList_;
	int totalUpdates_;
	int curPeople_;
	
	public HourData()
	{
		curPeople_ = 0;
		totalUpdates_ = 0;
		tempList_ = new ArrayList<Float>();
		lightList_ = new ArrayList<Float>();
		avgTemp_ = new Float(0);
		avgLight_ = new Float(0);
	}
	
	public void updateTemp(float temp)
	{
		tempList_.add(temp);
		
		float avg = 0;
		for (int i = 0; i < tempList_.size() ; i++)
		{
			avg += tempList_.get(i);
		}
		
		avgTemp_ = avg / tempList_.size();
	}
	
	public void updateLight(float light)
	{
		lightList_.add(light);
		float avg = 0;
		for (int i = 0; i < lightList_.size() ; i++)
		{
			avg += lightList_.get(i);
		}
		
		avgLight_ = avg / lightList_.size();
	}
	
	public void addPerson()
	{
		totalUpdates_ ++;
		curPeople_ ++;
	}
	
	public void removePerson()
	{
		curPeople_ --;
	}
	
	public float getLight()
	{
		return avgLight_;
	}
	
	public float getTemp()
	{
		return avgTemp_;
	}
	
	public int getCurPeople()
	{
		return curPeople_;
	}
	
	public int getTotalUps()
	{
		return totalUpdates_;
	}
}
