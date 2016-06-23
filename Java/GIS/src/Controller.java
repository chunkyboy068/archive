/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * Controller.java
 * 
 * This file contains the Controller class which interprets the command line arguments.
 */
import java.io.File;

/**
 * Controller class.
 * Variables:
 * argumentList - arguments received from the command line as an array of Strings
 * sciptFile - script file as an instance of File
 * cmdParser - used to parse commands
 *
 */
public class Controller {
	
	String[] argumentList;
	File scriptFile;
	
	CommandParser cmdParse;
	
	/**
	 * Constructor.  Receives an array of strings as arguments
	 * @param arguments
	 */
	public Controller(String[] arguments)
	{
		argumentList = arguments;
	}
	
	/**
	 * Function which begins processing the command line arguments
	 * Functions used:
	 * parseCommandLine();
	 */
	public void setUp()
	{
		parseCommandLine();
	}
	
	/**
	 * Function which parses the command arguments list and begins processing them
	 */
	private void parseCommandLine()
	{
		scriptFile = new File(argumentList[1]);
		
		if (!scriptFile.exists())
		{
			System.out.println("Error. Script file does not exist");
			System.exit(0);
		}
		
		DataIO.getInstance().setup(new File(argumentList[0]), new File(argumentList[2]));
		DataIO.getInstance().printHead(argumentList[0], argumentList[1]);
		
		cmdParse = new CommandParser(scriptFile);
		cmdParse.startParsing();
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