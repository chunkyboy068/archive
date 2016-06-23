/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * BufferPool.java
 * 
 * This file contains the BufferPool class which facilitates searching the database file
 * as well as provide a cache for recently used data.
 */

import java.util.ArrayList;

/**
 * Buffer Pool class Declaration
 * Variables
 * size - size of the buffer pool
 * pool - a list of recently used entries.  Oldest entries come first
 * in the list
 */
public class BufferPool {

	int size;
	ArrayList<GISRecord> pool;
	
	/**
	 * Constructor
	 * Creates new instance of the pool and sets the size to 20
	 */
	public BufferPool()
	{
		pool = new ArrayList<GISRecord>();
		size = 20;
	}
	
	/**
	 * addRecord Function
	 * Adds a new record to the buffer pool
	 * @param offset - offset in the database file
	 * @param fullRec - raw record string
	 */
	private void addRecord(long offset, String fullRec)
	{
		GISRecord record = new GISRecord(offset, fullRec);
		record.parseRecord();
		
		if (pool.size() >= 20)
		{
			pool.remove(0);
		}
		
		pool.add(record);
	}
	
	/**
	 * Searches the database for a record given an offset
	 * Returns the entry as a GISRecord type.  If the record does not exist in the pool,
	 * it is retrieved from the database file and the pool is updated.
	 * 
	 * Functions used: 
	 * searchDatabase()
	 * addRecord()
	 */
	public GISRecord searchOffset(long offset)
	{
		for (int i = 0; i < pool.size(); i++)
		{
			if (pool.get(i).getOffset() == offset)
			{
				GISRecord rec = pool.remove(i);
				pool.add(rec);
				return rec;
			}
		}
		
		GISRecord rec = searchDatabase(offset);
		
		if (rec == null)
		{
			return null;
		}
		addRecord(offset, rec.getFull());
		return rec;
	}
	
	/**
	 * Override of toString function
	 */
	public String toString()
	{
		String pString = "";
		
		for (int i = (pool.size()-1); i > -1; i--)
		{
			pString = pString + pool.get(i).getOffset() + ":\t" + pool.get(i).getFull() + "\n";
		}
		
		return pString;
	}
	
	
	private GISRecord searchDatabase(long offset)
	{
		return DataIO.getInstance().getFromDB(offset);
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