/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * GISParser.java
 * 
 * This file contains the GISParser class which decodes retrieves entries from the database record file.
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;

public class GISParser {

	File fromDB;										//original database file
	RandomAccessFile fromDatabase;						//original database file as a RandomAccessFile
	boolean first;										//first import
	
	/**
	 * Default constructor 
	 * @param database
	 */
	public GISParser(File database)
	{
		fromDB = database;
		first = true;
	}
	
	/**
	 * Setup function. Sets up the database file for reading 
	 */
	public void setup()
	{	
		try {
			
			if (fromDatabase != null)
			{
				fromDatabase.close();
			}
			
			fromDatabase = new RandomAccessFile(fromDB, "r");
		} catch (FileNotFoundException e) {
			System.out.println("Error Accessing database file");
		} catch (IOException e) {
			System.out.println("Error closing previous database");
		}
	}
	
	/**
	 * Sets a new database source
	 * @param newFile
	 */
	public void setNewDb(File newFile)
	{
		fromDB = newFile;
	}
	
	/**
	 * Begins importing records from the database source. Functions are also invoked to add them to
	 * the structures
	 */
	public void importFromDB()
	{
		String line = "temporary head";
		GISRecord GISRecForm = null;
		
		try {
			line = fromDatabase.readLine();
			
			if (first)
			{
				DataIO.getInstance().printtoDB(line);
				first = false;
			}
			
			long offset = fromDatabase.getFilePointer();
			
			while (offset < fromDatabase.length())
			{
				line = fromDatabase.readLine();
				offset = fromDatabase.getFilePointer();
				GISRecForm = DataIO.getInstance().printtoDB(line);
				DataIO.getInstance().addtoHash(GISRecForm);
				DataIO.getInstance().addtoTree(GISRecForm);
			}
			
		} catch (IOException e) {
			System.out.println("Error writing header/data to myDb");
		}
		
		
		
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