/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * WhatIsIn.java
 * 
 * This file contains the WhatIsIn class which executes the what_is_in command.
 */
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Vector;


public class WhatIsIn {
	
	Scanner arguments;								//command arguments
	int centerX;									//center coordinate, x
	int centerY;									//center coordinate, y
	int halfheight;									//length from the center, establishes bounds
	int halfwidth;
	
	String arg1;									//arguments in string format
	String arg2;
	String arg3;
	String arg4;
	
	/**
	 * Constructor.  Receives the arguments as a Scanner instance
	 * @param s
	 */
	public WhatIsIn(Scanner s)
	{
		arguments = s;
		halfheight = 0;
		halfwidth = 0;
	}
	
	/**
	 * Determines command modifiers and executes
	 */
	public void execute()
	{
		String s = arguments.next();
		if (s.equals("-l"))
		{
			lArgument();
		}
		else if (s.equals("-c"))
		{
			cArgument();
		}
		else
		{
			arg1 = s;
			noArgument();
		}
	}
	
	/**
	 * Executes using the -l modifier
	 */
	private void lArgument()
	{
		getRectangle(4);
		Vector<Point> results = getfromtree();
		ArrayList<Long> currentOffsets;
		Vector<Long> allOffsets = new Vector<Long>();
		
		for (int i = 0; i < results.size(); i++)
		{
			currentOffsets = results.get(i).getOffsets();
			allOffsets.addAll(currentOffsets);
		}
		
		ArrayList<GISRecord> allRecords = DataIO.getInstance().searchBuffMultiple(allOffsets);
		
		String out = allRecords.size() + " features found in " + arg1 + "+/-" + halfheight + ", ";
		out = out + arg2 + "+/-" + halfwidth + ":\n";
		
		Scanner s;
		GISRecord single;
		
		for (int j = 0; j < allRecords.size(); j ++)
		{
			single = allRecords.get(j);
			s = new Scanner(single.getFull());
			s.useDelimiter("\\|");
			out = out + getAllInfo(s) + "\n";
		}
		
		DataIO.getInstance().print(out);
	}
	
	/**
	 * Executes using the -c modifier
	 */
	private void cArgument()
	{
		int offsetCounter = 0;
		getRectangle(4);
		Vector<Point> results = getfromtree();
		
		for (int i = 0; i < results.size(); i ++)
		{
			ArrayList<Long> offsetList = results.get(i).getOffsets();
			offsetCounter = offsetCounter + offsetList.size();
		}
		
		String out = offsetCounter + " features found in " + arg1 + "+/-" + halfheight + ", " + arg2 + "+/-" + halfwidth+ "\n";
		DataIO.getInstance().print(out);
	}
	
	/**
	 * Executes command without modifiers
	 */
	private void noArgument()
	{
		getRectangle(3);
		Vector<Point> results = getfromtree();
		ArrayList<Long> currentOffsets;
		Vector<Long> allOffsets = new Vector<Long>();
		
		Point p;
		
		for (int i = 0; i < results.size(); i++)
		{
			p = results.get(i);
			currentOffsets = p.getOffsets();
			allOffsets.addAll(currentOffsets);
		}
		
		ArrayList<GISRecord> allRecords = DataIO.getInstance().searchBuffMultiple(allOffsets);
		
		String out = allRecords.size() + " features found in " + arg1 + "+/-" + halfheight + ", ";
		out = out + arg2 + "+/-" + halfwidth + ":\n";
		GISRecord single;
		
		for (int j = 0; j < allRecords.size(); j ++)
		{
			single = allRecords.get(j);
			out = out + single.getOffset() + ":\t" + single.getName() + "\t" + single.getState() + "\t";
			out = out + single.getLat() + "\t" + single.getLong() + "\n";
		}
		
		DataIO.getInstance().print(out);
	}

	/**
	 * Assigns the remaining arguments based on the command.  Input is the amount of arguments still
	 * to be assigned
	 * @param remaining
	 */
	private void getRectangle(int remaining)
	{
		if (remaining == 4)
		{
			arg1 = arguments.next();
		}
		arg2 = arguments.next();
		arg3 = arguments.next();
		arg4 = arguments.next();
		
		WorldCreator converter = new WorldCreator();
		converter.convert(arg2, arg1);
		centerX = converter.getResult();
		centerY = converter.getResult2();
		
		halfheight = Integer.parseInt(arg3);
		halfwidth = Integer.parseInt(arg4);
		
	}
	
	/**
	 * Retrieves a vector of Points that fall within the boundaries
	 * @return
	 */
	private Vector<Point> getfromtree()
	{
		int xMin = centerX - halfwidth;
		int xMax = centerX + halfwidth;
		int yMin = centerY - halfheight;
		int yMax = centerY + halfheight; 
		Vector<Point> results = DataIO.getInstance().findInTree(xMin, xMax, yMin, yMax);
		return results;
	}
	
	/**
	 * Parses out all important information from the record 
	 * @param s
	 * @return
	 */
	private String getAllInfo(Scanner s)
	{
		String result = "Feature ID:\t" + s.next() + "\nFeature Name:\t" + s.next() + "\nFeature Cat:\t";
		result = result + s.next() + "\nState:\t" + s.next() + "\nCounty:\t";
		s.next();
		result = result + s.next() + "\nLatitude:\t";
		s.next();
		result = result + s.next() + "\nLongitide:\t" + s.next() + "\n";
		
		for (int i = 0; i < 7; i++)
		{
			s.next();
		}
		
		String ele = s.next();
		if (!ele.equals(""))
		{
			result = result + "Elevation in ft:\t" + ele + "\n";
		}
		
		result = result + "USGS Quad:\t" + s.next() + "\nDate Created:\t" + s.next() + "\n";
		
		if (s.hasNext())
		{
			result = result + "Date Mod:\t" + s.next() + "\n";
		}
		
		return result;
	
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