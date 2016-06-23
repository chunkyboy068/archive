/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * WorldCreator.java
 * 
 * This file contains the WorldCreator class which creates coordinates in seconds from DDDMMSS format.
 * Can also be used as a converter to convert coordinates
 */
import java.util.Scanner;


public class WorldCreator {

	String westString;								//west boundary string format DDDMMSS format
	String eastString;								//east boundary string format
	String southString;								//south boundary string format
	String northString;								//north boundary string format
	
	int westCoord;									//west boundary in seconds
	int eastCoord;									//east boundary in seconds
	int southCoord;									//south boundary in seconds
	int northCoord;									//north boundary in seconds
	
	int generic;									//data fields used only when WorldCreator is used for conversions
	int generic2;
	
	/**
	 * Default Constructor. Used for convert
	 */
	public WorldCreator()
	{		
	}
	
	/**
	 * Constructor.  Received 4 strings as input each representing the boundaries.  Assigns values 
	 * to fields.
	 */
	public WorldCreator(String west, String east, String south, String north)
	{
		westString = west;
		eastString = east;
		southString = south;
		northString = north;
		
		westCoord = 0;
		eastCoord = 0;
		southCoord = 0;
		northCoord = 0;
	}
	
	/**
	 * Conversion process for East and West coordinates
	 * @param ew
	 */
	public void convertEastWest(String ew)
	{
		Scanner tempScan;
		
		if (ew.equals("e"))
		{
			tempScan = new Scanner(eastString);
		}
		else
		{
			tempScan = new Scanner(westString);
		}
		
		String days = tempScan.findInLine("[0-9]{3}");
		String mins = tempScan.findInLine("[0-9]{2}");
		String secs = tempScan.findInLine("[0-9]{2}");
		String coord = tempScan.findInLine("[WE]");
		
		int num = (Integer.parseInt(days) * 3600) + (Integer.parseInt(mins) * 60) + (Integer.parseInt(secs));
		
		if (coord.equals("W"))
		{
			num = num * -1;
			
		}
		generic = num;
		if (ew.equals("e"))
		{
			eastCoord = num;
		}
		else
		{
			westCoord = num;
		}
		
		tempScan.close();
	}
	
	/**
	 * Conversion process for North and South coordinates
	 */
	public void convertNorthSouth(String ns)
	{

		Scanner tempScan;
		
		if (ns.equals("s"))
		{
			tempScan = new Scanner(southString);
		}
		else
		{
			tempScan = new Scanner(northString);
		}
		
		String days = tempScan.findInLine("[0-9]{2}");
		String mins = tempScan.findInLine("[0-9]{2}");
		String secs = tempScan.findInLine("[0-9]{2}");
		String coord = tempScan.findInLine("[NS]");
		
		int num = (Integer.parseInt(days) * 3600) + (Integer.parseInt(mins) * 60) + (Integer.parseInt(secs));
		
		if (coord.equals("S"))
		{
			num = num * -1;
		}
		generic2 = num;
		if (ns.equals("s"))
		{
			southCoord = num;
		}
		else
		{
			northCoord = num;
		}
		
		tempScan.close();
	}
	
	/**
	 * Sets the world size.
	 */
	public void setWorld()
	{
		DataIO.getInstance().setWorldSize(westCoord, eastCoord, northCoord, southCoord);
	}
	
	/**
	 * Returns conversion field 1
	 */
	public int getResult()
	{
		return generic;
	}
	
	/**
	 * Returns conversion field 2
	 * @return
	 */
	public int getResult2()
	{
		return generic2;
	}
	
	/**
	 *	Conversion process which converts given coordinates to seconds format as a long
	 * @param lon
	 * @param lat
	 */
	public void convert(String lon, String lat)
	{
		westString = lon;
		northString = lat;
		
		convertEastWest("w");
		convertNorthSouth("n");
	}
}

//On my honor:
//
//- I have not discussed the Java language code in my program with
//anyone other than my instructor or the teaching assistants
//assigned to this course.
//
//- I have not used Java language code obtained from another student,
//or any other unauthorized source, either modified or unmodified.
//
//- If any Java language code or documentation used in my program
//was obtained from another source, such as a text book or course
//notes, that has been clearly noted with a proper citation in
//the comments of my program.
//
//- I have not designed this program in such a way as to defeat or
//interfere with the normal operation of the Automated Grader.
//
//Pledge: On my honor, I have neither given nor received unauthorized
//aid on this assignment.
//
//Thomas Yu
