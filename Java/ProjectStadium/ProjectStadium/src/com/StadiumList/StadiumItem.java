package com.StadiumList;

public class StadiumItem
{
	private String id;
	private String content;

	public StadiumItem(String id, String content) {
		this.id = id;
		this.content = content;
	}
	
	public String getID()
	{
		return id;
	}
	
	public String getContent()
	{
		return content;
	}

	@Override
	public String toString() {
		return content;
	}
}