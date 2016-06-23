/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * DataIO.java
 * 
 * This file contains the DataIO class which facilitates instantiation of all required parts and modules. Also
 * contains logic for access between these modules.
 */

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Vector;

/**
 * DataIO class.  Uses the singleton design pattern to provided access between the various modules
 *
 */
public class DataIO {

	public static DataIO instance = new DataIO();					//singleton instance
	DatabaseManager dbMgr;											//database manager - contains full entires
	HashTable<String, Long> hashTable;								//hashtable - contains Name:State and offset
	File myDatabase;												//database file
	File logFile;													//logfile
	LogPrinter logWriter;											//writes to the log
	BufferPool buf;													//buffer pool - stores recently used data
	prQuadtree<Point> quadTree;										//quadtree - stores entries by location
	
	public DataIO()
	{
		
	}
	
	/**
	 * Function used to retrieve the instance of this class
	 * @return
	 */
	public static DataIO getInstance()
	{
		return instance;				
	}
	
	/**
	 * Sets up all modules and instantiates structures
	 */
	public void setup(File dbasefile, File log)
	{
		buf = new BufferPool();
		hashTable = new HashTable<String, Long>();
		myDatabase = dbasefile;
		logFile = log;
		
		if (myDatabase.exists() || logFile.exists())
		{
			myDatabase.delete();
			logFile.delete();
		}
		
		try {
			myDatabase.createNewFile();
			logFile.createNewFile();
		} catch (IOException e) {
			System.out.println("Error creating log or database files");
		}
		
		logWriter = new LogPrinter(logFile);
		dbMgr = new DatabaseManager(myDatabase);
		dbMgr.setupDBFile();
		
	}
	
	/**
	 * Prints out comments to the log file.  Receives string as input
	 * @param comment
	 */
	public void commentDetected(String comment)
	{
		logWriter.printComment(comment);
	}
	
	/**
	 * Prints out commands to the log file.  Receives string as input
	 * @param command
	 * @param counter
	 */
	public void commandDetected(String command, int counter)
	{
		Scanner s = new Scanner(command);
		if (s.findInLine("world") == null)
		{
			logWriter.printCommand(command,counter);
		}
		else
		{
			logWriter.printCommand(command, -1);
		}
		s.close();
	}
	
	/**
	 * Sets up the world size for the quadtree. Records this in log
	 * @param west
	 * @param east
	 * @param north
	 * @param south
	 */
	public void setWorldSize(int west, int east, int north, int south)
	{
		quadTree = new prQuadtree<Point>(west, east, south, north);
		logWriter.printWorld(west, east, south, north);
	}
	
	/**
	 * Prints the header to the log file.  Receives the database file and script name as input
	 * @param db
	 * @param script
	 */
	public void printHead(String db, String script)
	{
		logWriter.printHeader(db, script);
	}
	
	/**
	 * Used to add a record to the database.  Receives the raw record in string format
	 * @param str
	 * @return
	 */
	public GISRecord printtoDB(String str)
	{
		return dbMgr.addToDB(str);
	}
	
	/**
	 * Adds a record to the hash table. Receives a record in GISRecord format
	 * @param rec
	 */
	@SuppressWarnings("unchecked")
	public void addtoHash(GISRecord rec)
	{
		String key = rec.getName() + ":" + rec.getState();
		hashTable.addEntry(key, rec.getOffset());
	}
	
	/**
	 * Prints the results of importing a file to the log
	 */
	public void printImport()
	{
		String str = dbMgr.getAmount() + " Records successfully added to " + myDatabase.getName() + "\n";
		str = str + hashTable.getSize() + " Total Entries in Hash Table\n";
		str = str + "Longest Probe Sequence: " + hashTable.getProbes() + "\n";
		dbMgr.resetCount();
		hashTable.resetProbes();
		logWriter.printMsg(str);
		
	}
	
	/**
	 * Shuts down all modules and prints a terminating message to the logfile
	 */
	public void finish()
	{
		logWriter.printMsg("Terminating Execution of Commands\nShutting down...\n");
		logWriter.ShutdownAndFinish();
		dbMgr.finishedWriting();
		System.out.println("Finished. Shutting down....");
	}
	
	/**
	 * Invokes the toString function of the hash and prints it out onto the log
	 */
	public void printHash()
	{
		logWriter.printMsg(hashTable.toString());
	}
	
	/**
	 * invokes the toString function of the bufferpool and prints it out onto the log
	 */
	public void printPool()
	{
		logWriter.printMsg(buf.toString());
	}
	
	/**
	 * Retrieves a entry from the hash table give a name and state in a concatenated string
	 * @param nameAndState
	 */
	public void findinHash(String nameAndState)
	{
		String infoFound = "";
		GISRecord result;
		
		ArrayList<Long> listofOffsets = hashTable.getOffset(nameAndState);
		if (listofOffsets == null)
		{
			infoFound = "Nothing found for " + nameAndState + "\n";
		}
		else
		{
			for (int i = 0; i < listofOffsets.size(); i++)
			{
				long curOffset = listofOffsets.get(i);
				result = buf.searchOffset(curOffset);
			
				if (result != null)
				{
					infoFound = infoFound + curOffset +": " + result.getCounty() + " ";
					infoFound = infoFound + result.getLong() + " " + result.getLat() + "\n";
				}
			}
		}
		
		logWriter.printMsg(infoFound);
		
	}
	
	/**
	 * Adds a entry into the quadTree.  Receives the record in GISRecord format.
	 * @param record
	 */
	public void addtoTree(GISRecord record)
	{
		if (record.getOffset() == 93626)
		{
			System.out.println("sadsasa");
		}
		WorldCreator converter = new WorldCreator();
		
		converter.convert(record.getLong(), record.getLat());
		int lon = converter.getResult();
		int lat = converter.getResult2();
		
		Point p = new Point(lon, lat, record.getOffset());
		quadTree.insert(p);
	}
	
	/**
	 * Finds a record in the tree given the coordinaates.  The coordinates are specified in both a long
	 * as the total number of seconds and in DDDMMSS format as strings
	 */
	public void findInTree(long x, long y, String lonS, String latS)
	{
		String out = "The following features are found at " + latS + " " + lonS + ":\n";
		Point find = new Point(x, y);
		Point p = quadTree.find(find);
		if (p == null)
		{
			out = out + "None\n";
		}
		else
		{
			GISRecord record;
			ArrayList<Long> values = p.getOffsets();
			long currentOff;
			for (int i = 0; i < values.size(); i++)
			{
				currentOff = values.get(i);
				record = buf.searchOffset(currentOff);				
				out = out + currentOff + ":\t" + record.getName() + "\t" + record.getCounty() + "\t";
				out = out + record.getState() + "\n";
			}
		}
		
		logWriter.printMsg(out);
	}
	
	/**
	 * Finds a record in the tree given a set of coordinates determine the bounds.  Returns a vector of all
	 * elements inside the coordinates
	 */
	public Vector<Point> findInTree(long xMin, long xMax, long yMin, long yMax)
	{
		Vector<Point> results = new Vector<Point>();
		results = quadTree.find(xMin, xMax, yMin, yMax);
		return results;
	}
	
	/**
	 * Retrieves an entry from the database given an offset.  Entry is returned in GISRecord form
	 * @param offset
	 * @return
	 */
	public GISRecord getFromDB(long offset)
	{
		return dbMgr.getUsingOffset(offset);
	}
	
	/**
	 * Prints the string s to the log file.
	 */
	public void print(String s)
	{
		logWriter.printMsg(s);
	}
	
	/**
	 * Search the buffer pool for a list of offsets. Each one is processed and the record is returned.
	 * Receives a vector of long as input and outputs an arraylist of GISRecords
	 */
	public ArrayList<GISRecord> searchBuffMultiple(Vector<Long> offset)
	{
		ArrayList<GISRecord> recordsList = new ArrayList<GISRecord>();
		GISRecord g;
		for (int i = 0; i < offset.size(); i++)
		{
			g = buf.searchOffset(offset.get(i));
			recordsList.add(g);
		}
		return recordsList;
		
	}
	
	/**
	 * invokes the printTree function of the quadtree and prints the returned string to the log
	 */
	public void printQuad()
	{
		String s = quadTree.printTree();
		logWriter.printMsg(s);
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