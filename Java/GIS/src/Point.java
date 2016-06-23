/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * Point.java
 * 
 * This file contains the Point class which is used as input to the quadTree generic.  Adapted to the given
 * Point class from project 3. All coordinates have been changed to float format and addToList and getOffset
 * functions added.
 */import java.util.ArrayList;


public class Point implements Compare2D<Point> {

	private float xcoord;
	private float ycoord;
	private ArrayList<Long> offsetList;
	
	public Point() {
		xcoord = 0;
		ycoord = 0;
		offsetList = new ArrayList<Long>(0);
	}
	
	public Point(long x, long y)
	{
		xcoord = x;
		ycoord = y;
	}

	public Point(float x, float y, long offset) {
		offsetList = new ArrayList<Long>(0);
		xcoord = x;
		ycoord = y;
		offsetList.add(offset);
	}

	public float getX() {
		return xcoord;
	}

	public float getY() {
		return ycoord;
	}
	
	public Direction directionFrom(float X, float Y) 
	{
		if (ycoord >= Y && xcoord > X)
		{
			return Direction.NE;
		}
		else if (ycoord > Y && xcoord <= X)
		{
			return Direction.NW;
		}
		else if (ycoord < Y && xcoord >= X)
		{
			return Direction.SE;
		}
		else if (ycoord <= Y && xcoord < X)
		{
			return Direction.SW;
		}
		
		return Direction.NOQUADRANT;
    }
	
	public Direction inQuadrant(float xLo, float xHi, 
                               float yLo, float yHi) 
	{ 
      if ( !inBox(xLo,xHi,yLo,yHi) )
      {
    	  return Direction.NOQUADRANT;
      }
      
      float xmid = (float) (xHi + xLo) / 2;
      float ymid = (float) (yHi + yLo) / 2;
      
      Direction d = directionFrom(xmid, ymid);
      
      if (d == Direction.NOQUADRANT)
      {
    	  return Direction.NE;
      }
      
      return d;
	}

	public boolean   inBox(float xLo, float xHi, 
                          float yLo, float yHi) 
	{
		if (xcoord > xHi || xcoord < xLo || ycoord < yLo || ycoord > yHi)
	    {
			return false;
	    }
		
		return true;
	}

	public String toString() {
		return getX() + " " + getY();
	}
	
	public boolean equals(Object o) 
	{ 
		if (!o.getClass().equals(this.getClass()))
		{
			return false;
		}
		if (((Point) o).directionFrom(xcoord, ycoord) == Direction.NOQUADRANT)
		{
			return true;
		}
		return false;
	}

	/**
	 * Adds additional offsets from a collection into this offsetlist
	 */
	@Override
	public boolean addToList(Object o) 
	{
		if (!this.equals(o))
		{
			return false;
		}
		
		return offsetList.addAll(((Point) o).getOffsets());
		
	}
	/**
	 * Returns the list of offsets
	 */
	@Override
	public ArrayList<Long> getOffsets() {
		return offsetList;
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
