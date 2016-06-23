/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * Compare2D.java
 * 
 * This file was adapted from the given file from project 3.  2 addition functions were added:
 * addToList() and getOffsets()
 */
import java.util.ArrayList;

// The interface Compare2D is intended to supply facilities that are useful in
// supporting the the use of a generic spatial structure with a user-defined
// data type.
//
public interface Compare2D<T> {
	
   // Returns the x-coordinate field of the user data object.
   public float getX();
   
   // Returns the y-coordinate field of the user data object.
   public float getY();
   
   // Returns indicator of the direction to the user data object from the 
   // location (X, Y) specified by the parameters.
   // The indicators are defined in the enumeration Direction, and are used
   // as follows:
   //
   //    NE:  vector from (X, Y) to user data object has a direction in the 
   //         range [0, 90) degrees (relative to the positive horizontal axis
   //    NW:  same as above, but direction is in the range [90, 180) 
   //    SW:  same as above, but direction is in the range [180, 270)
   //    SE:  same as above, but direction is in the range [270, 360)  
   //    NOQUADRANT:  location of user object is equal to (X, Y)
   //
   public Direction directionFrom(float X, float Y);
    
   // Returns indicator of which quadrant of the rectangle specified by the
   // parameters that user data object lies in.
   // The indicators are defined in the enumeration Direction, and are used
   // as follows, relative to the center of the rectangle:
   //
   //    NE:  user data object lies in NE quadrant, including non-negative
   //         x-axis, but not the positive y-axis      
   //    NW:  user data object lies in the NW quadrant, including the positive
   //         y-axis, but not the negative x-axis
   //    SW:  user data object lies in the SW quadrant, including the negative
   //         x-axis, but not the negative y-axis
   //    SE:  user data object lies in the SE quadrant, including the negative
   //         y-axis, but not the positive x-axis
   //    NOQUADRANT:  user data object lies outside the specified rectangle
   //
   public Direction inQuadrant(float xLo, float xHi, float yLo, 
                               float yHi);
   
   // Returns true iff the user data object lies within or on the boundaries
   // of the rectangle specified by the parameters.
   public boolean   inBox(float xLo, float xHi, float yLo, float yHi);
   
   // Overrides the user data object's inherited equals() method with an
   // appropriate definition; it is necessary to place this in the interface
   // that is used as a bound on the type parameter for the generic spatial
   // structure, otherwise the compiler will bind to Object.equals(), which
   // will almost certainly be inappropriate.
   public boolean equals(Object o);
   
   public boolean addToList(Object o);
   
   public ArrayList<Long> getOffsets();
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