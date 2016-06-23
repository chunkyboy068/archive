/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * LogPrinter.java
 * 
 * This file contains the LogPrinter class which prints messages and data to the log file
 */
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class LogPrinter {

	File logFile;									//logFile
	FileWriter fw;									//FileWriter used to instantiate BufferedWriter
	BufferedWriter bw;								//Used to write to the logfile
	
	/**
	 * Default Constructor. Sets up log file for input
	 */
	public LogPrinter(File logfile)
	{
		this.logFile = logfile;
		try {
			fw = new FileWriter(logFile);
			bw = new BufferedWriter(fw);
			
		} catch (IOException e) {
			System.out.println("Error creating file writer or buffered writer");
		}
		
	}
	
	/**
	 * Prints a comment to the log
	 */
	public void printComment(String c)
	{
		try {
			bw.write(c);
			bw.write("\n");
		} catch (IOException e) {
			System.out.println("Error writing comment using Buffered Writer");
		}
	}
	
	/**
	 * Prints a command and its count to the log.  Receives the string and the command count
	 */
	public void printCommand(String c, int counter)
	{
		try {
			if (counter != -1)
			{
				bw.write("Command #" + counter +": ");
			}
			
			bw.write( c + "\n\n");
		} catch (IOException e) {
			System.out.println("Error writing comment using Buffered Writer");
		}
	}
	
	/**
	 * Prints the header to the logfile.  Receives the script and database source file as input strings
	 * @param GISinput
	 * @param scriptInput
	 */
	public void printHeader(String GISinput, String scriptInput)
	{
		String str = "Thomas Yu\nCS 3114 Project 4\nLOG FILE\nDatabase File to be written to: ";
		str = str + GISinput + "\nScript Input File: " + scriptInput + "\n\n";
		try {
			bw.write(str);
			printDelimiter();
		} catch (IOException e) {
			System.out.println("Error writing header to Log file");
		}
		
	}
	
	/**
	 * Prints the size of the world to the log file
	 */
	public void printWorld(int west, int east, int south, int north)
	{
		String str = "The World Size has been set to: \nNorth Latitude: ";
		str = str + north + "\nSouth Latitude: " + south + "\nWest Longitude: " + west;
		str = str + "\nEast Longitude: " + east + "\n";
		
		try {
			bw.write(str);
			printDelimiter();
		} catch (IOException e) {
			System.out.println("Error: cannot print world results");
		}
	}
	
	/**
	 * Prints delimiter used to separate each command
	 */
	public void printDelimiter()
	{
		try {
			bw.write("------------------------------------------------------------\n");
		} catch (IOException e) {
			System.out.println("Error: cannot print delimiter");
		}
	}
	
	/**
	 * Shuts down  buffered writer and finish writing to the file
	 */
	public void ShutdownAndFinish()
	{
		try {
			bw.close();
		} catch (IOException e) {
			System.out.println("Error closing buffered Writer");
		}
	}
	
	/**
	 * Prints the inputted string to the log
	 * @param str
	 */
	public void printMsg(String str)
	{
		try {
			bw.write(str);
			printDelimiter();
		} catch (IOException e) {
			System.out.println("Error writing Import results");
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