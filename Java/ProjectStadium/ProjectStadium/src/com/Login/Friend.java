package com.Login;

import java.util.ArrayList;
import java.util.List;

import twitter4j.Status;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.User;

public class Friend {
	private String name;
	private String stadium;
	private String sectionNum;
	private int area;

	public Friend(String name, String stadium, String sectionNum, int area) {
		this.name = name;
		this.stadium = stadium;
		this.sectionNum = sectionNum;
		this.area = area;
	}

	public String getName() {
		return name;
	}

	public String getSectionNum() {
		return sectionNum;
	}

	public String getStadium() {
		return stadium;
	}
	
	public int getArea(){
		return area;
	}
	public String getCheckInStatus()
	{
		return "@" + name + " is in section "+ sectionNum;
	}
}
