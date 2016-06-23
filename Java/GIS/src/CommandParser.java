/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * CommandParser.java
 * 
 * This file contains the CommandParser class which facilitates retrieval of commands from the script
 * file
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

/**
 * CommandParser class
 * Variables:
 * script - the script file to be read as a RandomAccessFile instance
 * cmdExecute - module used for command execution
 * s - Scanner used to scan each line
 */
public class CommandParser {
	
	RandomAccessFile script = null;
	CommandExecutor cmdExecute;
	Scanner s;
	
	/**
	 * Constructor. Receives a File instance as input
	 */
	public CommandParser(File commandFile)
	{
		try {
			script = new RandomAccessFile(commandFile, "r");
		} catch (FileNotFoundException e) {
			System.out.println("Error. File not Found");
		}
		cmdExecute = new CommandExecutor();
		
	}

	/**
	 * Function used to start parsing the script file.
	 */
	public void startParsing()
	{
		String singleLine = null;							//each individual line of the script
		int cmdCounter = -1;								//count each command. World does not count
		String first;										//used to store each element in the read line
		
		try {
			
			singleLine = script.readLine();
			while (singleLine != null)
			{
				s = new Scanner(singleLine);
				first = s.findInLine(";.*");
			
				if (s.hasNext())
				{
					s.useDelimiter("\t");
					cmdCounter++;
					DataIO.getInstance().commandDetected(singleLine, cmdCounter);
					cmdExecute.processCommand(s);
				}
				else
				{
					DataIO.getInstance().commentDetected(first);
				}
				
				singleLine = script.readLine();
				s.close();
			}
		} catch (IOException e) {
			System.out.println("Error reading line");
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