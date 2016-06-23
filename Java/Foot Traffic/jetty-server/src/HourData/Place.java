package HourData;

public class Place {

	Float lat_;
	Float lon_;
	Float latMin_;
	Float latMax_;
	Float lonMin_;
	Float lonMax_;
	
	String name_;
	
	public Place(float lat, float lon, String name)
	{
		lat_ = new Float(lat);
		lon_ = new Float(lon);
		alterBounds((float).001, (float) .001);
		name_ = name;
	}
	
	public boolean isIn(float lat, float lon)
	{
		boolean inLat = false;
		boolean inLon = false;
		
		if ((lat > latMin_) && (lat < latMax_))
		{
			inLat = true;
		}
		
		if ((lon > lonMin_) && (lon < lonMax_))
		{
			inLon = true;
		}
		
		if (inLat && inLon)
		{
			return true;
		}
		
		return false;
	}
	
	public float getLat()
	{
		return lat_;
	}
	
	public float getLon()
	{
		return lon_;
	}
	
	public String getName()
	{
		return name_;
	}
	
	public void alterBounds(Float latMod, Float lonMod)
	{
		latMin_ = lat_ - latMod;
		latMax_ = lat_ + latMod;
		lonMin_ = lon_ - lonMod;
		lonMax_ = lon_ + lonMod;
	}
}
