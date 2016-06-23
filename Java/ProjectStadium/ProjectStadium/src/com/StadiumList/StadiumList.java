package com.StadiumList;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Helper class for providing sample content for user interfaces created by
 * Android template wizards.
 * <p>
 * TODO: Replace all uses of this class before publishing your app.
 */
public class StadiumList {

	/**
	 * An array of sample (dummy) items.
	 */
	private List<StadiumItem> items; 

	/**
	 * A map of sample (dummy) items, by ID.
	 */
	
	public static Map<String, StadiumItem> item_map;

	public StadiumList()
	{
		items = new ArrayList<StadiumItem>();
		item_map = new HashMap<String , StadiumItem>();
		init();
		
	}
	
	private void init()
	{
		addItem(new StadiumItem("1", "Lane Stadium"));
	}
	
	public void addItem(StadiumItem item) 
	{
		items.add(item);
		item_map.put(item.getID(), item);
	}
	
	public List<StadiumItem> getItems()
	{
		return items;
	}
	
	public String getID(int position)
	{
		return items.get(position).getID();
	}
}
