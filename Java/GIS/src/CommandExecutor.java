/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * CommandExecutor.java
 * 
 * This file contains the CommandExecutor class which facilitates processes received commands
 */

import java.io.File;
import java.util.Scanner;

/**
 * CommandExecutor class
 * Variables:
 * scannedInstruction - a script command scanned using Scanner
 * gisParse - parser module for the GIS database
 * world - WorldCreator module that creates and checks coordinates
 * WIIParser - parses the what_is_in command. Separate from the other commands due to the 
 * 				what_is_in command requiring more logic.
 *
 */
public class CommandExecutor {

	Scanner scannedInstruction;
	GISParser gisParse;
	WorldCreator world;
	WhatIsIn WIIParser;
	
	public CommandExecutor()
	{
		
	}
	
	/**
	 * processCommand function.  Determines the function to be executed and takes action accordingly
	 * 
	 * Functions used:
	 * processWorld();
	 * processImport();
	 * processDebug();
	 * processWhatIs();
	 * processWhatIsIn();
	 * processWhatIsAt();
	 */
	public void processCommand(Scanner scannedLine)
	{
		scannedInstruction = scannedLine;
		String command = scannedInstruction.next();
		
		if (command.equals("world"))
		{
			processWorld();
		}
		else if (command.equals("import")) 
		{
			processImport();
		}
		else if (command.equals("quit"))
		{
			DataIO.getInstance().finish();
		}
		else if (command.equals("debug"))
		{
			processDebug();
		}
		else if (command.equals("what_is"))
		{
			processWhatIs();
		}
		else if (command.equals("what_is_at"))
		{
			processWhatIsAt();
		}
		else if (command.equals("what_is_in"))
		{
			processWhatIsIn();
		}
	}
	
	/**
	 * Function which sets the coordinates for the world. No return value
	 */
	private void processWorld()
	{
		String w = scannedInstruction.next();
		String e = scannedInstruction.next();
		String s = scannedInstruction.next();
		String n = scannedInstruction.next();
		world = new WorldCreator(w,e,s,n);
		
		world.convertEastWest("e");
		world.convertEastWest("w");
		world.convertNorthSouth("s");
		world.convertNorthSouth("n");
		world.setWorld();

	}
	
	/**
	 * Function which processes importing. No return value.
	 */
	private void processImport()
	{
		File gisFile = new File(scannedInstruction.next());
		
		if (gisParse == null)
		{
			gisParse = new GISParser(gisFile);
		}
		else
		{
			gisParse.setNewDb(gisFile);
		}
		gisParse.setup();
		gisParse.importFromDB();
		
		DataIO.getInstance().printImport();
	}
	
	/**
	 * Function that runs the debug commands. Returns void
	 */
	private void processDebug()
	{
		String debugType = scannedInstruction.next();
		
		if (debugType.equals("hash"))
		{
			DataIO.getInstance().printHash();
		}
		else if (debugType.equals("pool"))
		{
			DataIO.getInstance().printPool();
		}
		else if (debugType.equals("quad"))
		{
			DataIO.getInstance().printQuad();
		}
	}
	
	/**
	 * Function that runs the whatis command. Returns void
	 */
	private void processWhatIs()
	{
		String nameState = scannedInstruction.next() + ":" + scannedInstruction.next();
		DataIO.getInstance().findinHash(nameState);
	}
	
	/**
	 * Function that processes the what_is_at command.  Does not return value
	 */
	private void processWhatIsAt()
	{
		String lon = scannedInstruction.next();
		String lat = scannedInstruction.next();
		
		WorldCreator converter = new WorldCreator();
		converter.convert(lat, lon);
		int lonNum = converter.getResult();
		int latNum = converter.getResult2();
		
		DataIO.getInstance().findInTree(lonNum, latNum, lon, lat);
	}
	
	/**
	 * Function that uses the WhatIsIn module to process the what_is_in command.
	 */
	private void processWhatIsIn()
	{
		WIIParser = new WhatIsIn(scannedInstruction);
		WIIParser.execute();
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