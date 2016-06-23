/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * DatabaseManager.java
 * 
 * This file contains the DatabaseManager class which manages the database file.
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class DatabaseManager {

	File myDBFile;					//database file
	RandomAccessFile raf;			//RandomAccessfile of the databasefile
	int recordAmt;					//Amount of Records processed
	
	/**
	 * Constructor
	 * @param myDB
	 */
	public DatabaseManager(File myDB)
	{
		myDBFile = myDB;
		recordAmt = 0;
	}
	
	/**
	 * Function which sets up the RandomAccessFile
	 */
	public void setupDBFile()
	{
		try {
			raf = new RandomAccessFile(myDBFile, "rw");
		} catch (FileNotFoundException e) {
			System.out.println("Error creating dbase file writer");
		}
	}
	
	/**
	 * Closes the FileWriter and finish writing records
	 */
	public void finishedWriting()
	{
		try {
			raf.close();
		} catch (IOException e) {
			System.out.println("Error closing dbase file writer");
		}
	}
	
	/**
	 * Function which adds a record to the database file. The raw record in string format is used as input
	 * Functions Used:
	 * Construct()
	 */
	public GISRecord addToDB(String str)
	{	
		try {
			
			long offset = 0;
			GISRecord record;
			
			if (raf.getFilePointer() != 0)
			{
				offset = raf.getFilePointer();
				recordAmt ++;
			}
			raf.writeBytes(str + "\n");
			
			Scanner s = new Scanner(str);
			if (s.findInLine("FEATURE_ID") == null)
			{
				s.close();
				record = construct(offset, str);
				return record;
			}
			s.close();
			
		} catch (IOException e) {
			System.out.println("Error writing bytes to myDB");
		}
		
		return null;
	}
	
	/**
	 * Function used to construct the GISRecord
	 * Receives the offset and the whole record in String format. Returns the record in GISRecord format
	 * @param offset
	 * @param record
	 */
	public GISRecord construct(long offset, String record )
	{
		GISRecord rec = new GISRecord (offset, record);
		rec.parseRecord();
		return rec;
	}
	
	/**
	 * Function which returns the amount of records
	 */
	public int getAmount()
	{
		return recordAmt;
	}
	
	/**
	 * resets the records processed
	 */
	public void resetCount()
	{
		recordAmt = 0;
	}
	
	/**
	 * Retrieved a record from the database file give an offset.  Returns the record in GISRecord format
	 */
	public GISRecord getUsingOffset(long off)
	{
		GISRecord found = null;
		
		try {
			raf.seek(off);
			String rec = raf.readLine();
			found = new GISRecord(off, rec);
			found.parseRecord();
		} catch (IOException e) {
			System.out.println("Error finding record in db");
		}
		
		return found;
		
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
