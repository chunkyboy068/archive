package HourData;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;

import org.json.simple.JSONObject;

public class DataConstruct {

	HashMap<String, ArrayList<HourData>> data_;
	ArrayList<Place> places_;
	int currentHour_;
	Timer timer_;
	
	public DataConstruct()
	{
		data_ = new HashMap<String, ArrayList<HourData>>();
		places_ = new ArrayList<Place>();
		
		insertNewData((float)37.245722,(float) -80.411962, "home", (float).001, (float) .001 );
		insertNewData((float)37.227684,(float) -80.422352, "drillfield", (float).002, (float).002);
		insertNewData((float)37.231118,(float) -80.422813, "turner", (float).001, (float) .001);
	}
	
	public void addNew(String time, String lat, String lon, String light, String temp, String status)
	{
		float fLat = Float.parseFloat(lat);
		float fLon = Float.parseFloat(lon);
		float fLight = Float.parseFloat(light);
		float fTemp = Float.parseFloat(temp);
		int upHour_ = Integer.parseInt(time);
		
		ArrayList<HourData> hours;
		HourData thisHour;
		Place curPlace;
		String placeName = "";
		
		for (int i = 0; i < places_.size(); i++)
		{
			curPlace = places_.get(i);
			
			if (curPlace.isIn(fLat, fLon))
			{
				placeName = curPlace.getName();
			}
		}
		
		hours = data_.get(placeName);
		thisHour = hours.get(upHour_);
		thisHour.updateLight(fLight);
		thisHour.updateTemp(fTemp);
		
		if (status.equals("stay"))
		{
			thisHour.addPerson();
		}
		else if (status.equals("leave"))
		{
			thisHour.removePerson();
		}
		else if (status.equals("pass"))
		{
			thisHour.addPerson();
			startTimer(thisHour);
		}
		
		System.out.println("Data added in");
	}
	
	public JSONObject get(String lat, String lon, String hour)
	{
		float fLat = Float.parseFloat(lat);
		float fLon = Float.parseFloat(lon);
		
		Place curPlace;
		String placeName = "";
		
		for (int i = 0; i < places_.size(); i++)
		{
			curPlace = places_.get(i);
			
			if (curPlace.isIn(fLat, fLon))
			{
				placeName = curPlace.getName();
			}
		}
		
		return get(placeName, hour);
		
	}
	
	public JSONObject get(String descript, String hour)
	{
		ArrayList<HourData> hData = data_.get(descript.trim().toLowerCase());
		HourData thisHour = hData.get(Integer.parseInt(hour));
		
		JSONObject result = new JSONObject();
		result.put("avgtemp", thisHour.getTemp());
		result.put("avglight", thisHour.getLight());
		result.put("totalups", thisHour.getTotalUps());
		result.put("current", thisHour.getCurPeople());
		
		return result;
	}
	
	public void insertNewData(float lat, float lon, String name, float latbound, float lonbound)
	{
		Place p = new Place(lat, lon, name);
		p.alterBounds(latbound, lonbound);
		places_.add(p);
		
		ArrayList<HourData> locList = new ArrayList<HourData>();
		for (int i = 0; i < 24; i++)
		{
			HourData hour = new HourData();
			locList.add(hour);
		}
		
		data_.put(name, locList);	
	}
	
	private void startTimer(HourData hour)
	{
		removeTask rt = new removeTask(hour);
		timer_ = new Timer();
		timer_.schedule(rt, 120000);
	}
	
	class removeTask extends TimerTask{
		
		HourData hour_;
		
		public removeTask(HourData hour)
		{
			hour_ = hour;
		}
		
		@Override
		public void run() 
		{
			hour_.removePerson();
			timer_.cancel();
		}
		
	}
}
