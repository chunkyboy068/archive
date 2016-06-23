package com.HamServer.Storage;
import java.util.ArrayList;

public class PlayerData {

	int fitLevel;
	int hungerLevel;
	ArrayList<String> friends;
	
	public PlayerData()
	{
		fitLevel = 0;
		hungerLevel = 0;
		friends = new ArrayList<String>();
	}
	
	public PlayerData(int fl, int hl)
	{
		fitLevel = fl;
		hungerLevel = hl;
		friends = new ArrayList<String>();
	}
	
	public ArrayList<String> getFriends()
	{
		return friends;
	}

	public void addNewFriend(String friend)
	{
		if (!friends.contains(friend))
		{
			friends.add(friend);
		}
	}
	
	public int getFitLevel() 
	{
		return fitLevel;
	}

	public void setFitLevel(int fitLevel) 
	{
		this.fitLevel = fitLevel;
	}

	public int getHungerLevel() 
	{
		return hungerLevel;
	}

	public void setHungerLevel(int hungerLevel) 
	{
		this.hungerLevel = hungerLevel;
	}
	
	
}
