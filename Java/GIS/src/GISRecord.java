/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * GISRecord.java
 * 
 * This file contains the GISRecord class which houses the data retrieved from a single record
 */
import java.util.Scanner;

public class GISRecord {

	String rawRecord;
	long offsetInDB;
	String name;
	String state;
	String county;
	String longitudeDMS;
	String latitudeDMS;
	
	/**
	 * Constructor
	 * @param offset - offset of the record in the file
	 * @param record - full record in string format
	 */
	public GISRecord(long offset, String record)
	{
		offsetInDB = offset;
		rawRecord = record;
	}
	
	/**
	 * Begins parsing the records and assigns their respective fields
	 */
	public void parseRecord()
	{
		Scanner s = new Scanner(rawRecord);
		s.useDelimiter("\\|");
		s.next();
		name = s.next();
		s.next();
		state = s.next();
		s.next();
		county = s.next();
		s.next();
		latitudeDMS = s.next();
		longitudeDMS = s.next();
		s.close();
	}
	
	/**
	 * Returns the name of the feature
	 */
	public String getName()
	{
		return this.name;
	}
	
	/**
	 * Returns the state of the feature
	 */
	public String getState()
	{
		return this.state;
	}
	
	/**
	 * Returns the offset
	 */
	public long getOffset()
	{
		return this.offsetInDB;
	}
	
	/**
	 * Returns the county
	 * @return
	 */
	public String getCounty()
	{
		return county;
	}
	
	/**
	 * Returns the longitude in DDDMMSS format
	 * @return
	 */
	public String getLong()
	{
		return longitudeDMS;
	}
	
	/**
	 * Returns the latitude in DDMMSS format
	 * @return
	 */
	public String getLat()
	{
		return latitudeDMS;
	}
	
	/**
	 * Returns the raw record
	 * @return
	 */
	public String getFull()
	{
		return rawRecord;
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