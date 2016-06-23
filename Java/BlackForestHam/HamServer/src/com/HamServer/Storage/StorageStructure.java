package com.HamServer.Storage;
import java.util.HashMap;

public class StorageStructure 
{
	private static StorageStructure ss = new StorageStructure(); 
	private HashMap<String, PlayerData> users;
	
	private StorageStructure()
	{
		users = new HashMap<String, PlayerData>();
	}
	
	public static StorageStructure getInstance()
	{
		return ss;
	}
	
	public PlayerData getUser(String friendID)
	{
		return users.get(friendID);
	}
	
	public boolean addUser(String id, int fl, int hl)
	{
		if (users.containsKey(id))
		{
			return false;
		}
		else
		{
			users.put(id, new PlayerData(fl, hl));
			return true;
		}
	}
	
	public boolean updateUser(String id, int fl, int hl)
	{
		if (!users.containsKey(id))
		{
			return false;
		}
		else
		{
			PlayerData pd = users.get(id);
			pd.setFitLevel(fl);
			pd.setHungerLevel(hl);
			users.put(id, pd);
			return true;
		}
	}
	
	public boolean addNewFriend(String req, String friend)
	{
		if (!users.containsKey(req))
		{
			return false;
		}
		else
		{
			users.get(req).addNewFriend(friend);
			return true;
		}
	}
}
