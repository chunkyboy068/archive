/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * prQuadtree.java
 * 
 * This file contains the prQuadtree class which implements a point region quadtree using generic types. 
 * The generics must implement the Compare2D interface.
 * 
 * This file is adapted from the prQuadtree generic of project 3 and incorporates the printTree and printTreeHelper
 * functions from the Lewis.java file.  Core functionality remains mostly unchanged.  The only changes
 * are to facilitate retrieval of the bucket list and multiple offsets from each point
 */

import java.util.Vector;

public class prQuadtree<T extends Compare2D<? super T>> {

	/**
	 * An abstract class.  the isLeaf function is specified
	 * as abstract and must be implemented in children
	 */
	abstract class prQuadNode 
	{
		public abstract boolean isLeaf();
	}
	
	/**
	 * Leaf class that extends prQuadNode
	 */
	class prQuadLeaf extends prQuadNode 
	{
		Vector<T> Elements;						//elements of the leaf. For this the vector size is 4

		/**
		 * Constructor
		 * @param elem - input element
		 */
		public prQuadLeaf(T elem) 				
		{
			Elements = new Vector<T>(4);
			Elements.add(elem);
		}
		
		/**
		 * Inherited isLeaf() function. Returns true since this class is a leaf
		 */
		public boolean isLeaf() 
		{
			return true;
		}	
		
		/**
		 * Checks to see if the bucket is full. Returns boolean value
		 * @return
		 */
		public boolean isFull()
		{
			if (Elements.size() == 4)
			{
				return true;
			}
			
			return false;
		}
		
		/**
		 * adds an element into a list that is not full
		 */
		public boolean addNotFull(T Elem)
		{
			Elements.add(Elem);
			return true;
		}
		
		/**
		 * Iterates through the elements and checks to see if it is already existing.  Returns 
		 * the index of the matching element
		 */
		public int checkForExisting(T Elem)
		{
			for (int i = 0; i < Elements.size(); i ++)
			{
				if (Elements.get(i).equals(Elem))
				{
					return i;
				}
			}
			
			return -1;
		}
		
		/**
		 * Adds offsets to an existing matching coordinate at the given index
		 */
		public boolean addToExisting(T Elem, int index)
		{
			Elements.get(index).addToList(Elem);
			return true;
		}
		
		/**
		 * Returns list of elements
		 */
		public Vector<T> getAllElements()
		{
			return Elements;
		}
	}
	
	/**
	 * Internal node that extends prquadNode
	 */
	class prQuadInternal extends prQuadNode {
		prQuadNode NW, NE, SE, SW;									//pointers to leaves or other internals
		float xMin, yMin, xMax, yMax;				//the bounds that this internal represents
																	//as a set of 2 points
		public prQuadInternal(float xmin, float xmax, float ymin, float ymax) 
		{
			xMin = xmin;
			yMin = ymin;
			xMax = xmax;
			yMax = ymax;
		}
		public boolean isLeaf() 
		{
			return false;
		}
		/**
		 * assigns the values (leafs/other nodes) to pointers

		 */
		public void setPointer(prQuadNode ptr, String node)
		{
			if (node.equals("NW"))
			{
				NW = ptr;
			}
			else if (node.equals("NE"))
			{
				NE = ptr;
			}
			else if (node.equals("SW"))
			{
				SW = ptr;
			}
			else if (node.equals("SE"))
			{
				SE = ptr;
			}
			
		}
		
		/**
		 * Returns the quadrant which elem belongs to
		 */
		public String getQuadrant(T elem)
		{
			float xCenter = (xMin + xMax) /2;				//finds midpoints
			float yCenter = (yMin + yMax) /2;
			
			if (elem.directionFrom(xCenter, yCenter) == Direction.NE)
			{
				return "NE";
			}
			else if (elem.directionFrom(xCenter, yCenter) == Direction.NW)
			{
				return "NW";
			}
			else if (elem.directionFrom(xCenter, yCenter) == Direction.SW)
			{
				return "SW";
			}
			else if (elem.directionFrom(xCenter, yCenter) == Direction.SE)
			{
				return "SE";
			}
			else
			{
				return "NE";
			}
			
				
		}
		
		/**
		 * Returns the pointer in the specified quadrant
		 */
		public prQuadNode getQuadPtr(String node)
		{
			if (node == "NE")
			{
				return NE;
			}
			else if (node == "NW")
			{
				return NW;
			}
			else if (node == "SW")
			{
				return SW;
			}
			else if (node == "SE")
			{
				return SE;
			}
			return null;
		}
		
		/**
		 * Create a internal pointer at the quadrant specified in input
		 */
		public prQuadInternal makeChildInternal(String quadrant)
		{
			float xCenter = (xMin + xMax) /2;				//finds the x midpoint
			float yCenter = (yMin + yMax) /2;				//finds the y midpoint
			
			if (quadrant == "NE")
			{
				prQuadInternal node = new prQuadInternal(xCenter, xMax, yCenter, yMax);
				return node;
			}
			else if (quadrant == "NW")
			{
				prQuadInternal node = new prQuadInternal(xMin, xCenter, yCenter, yMax);
				return node;
			}
			else if (quadrant == "SW")
			{
				prQuadInternal node = new prQuadInternal(xMin, xCenter, yMin, yCenter);
				return node;
			}
			else if (quadrant == "SE")
			{
				prQuadInternal node = new prQuadInternal(xCenter, xMax, yMin, yCenter);
				return node;
			}
			
			return null;
		}
		
		/**
		 * Retrieves the boundary value speicifed by the input string
		 */
		public float getBound(String s)
		{
			if (s.equals("xMin"))
			{
				return xMin;
			}
			else if (s.equals("xMax"))
			{
				return xMax;
			}
			else if (s.equals("yMin"))
			{
				return yMin;
			}
			else if (s.equals("yMax"))
			{
				return yMax;
			}
			
			return 0;
		}
	}

	prQuadNode root;								//the first node or root of the tree
	float xMin, xMax, yMin, yMax;					//boundaries
	String pad = "---";								//padding used for displaying the tree
	String outString;								//String that contains tree contents
	
	/**
	 * Constructor.  The 4 inputs are the world boundaries
	 */
	public prQuadtree(float xMin, float xMax, float yMin, float yMax) 
	{
		outString = "";
		root = null;
		this.xMin = xMin;
		this.xMax = xMax;
		this.yMin = yMin;
		this.yMax = yMax;
	}
	
	/**
	 * Inserts an element into the tree.  Returns a boolean value
	 * Functions Used:
	 * insertRecursively
	 */
	@SuppressWarnings("unchecked")
	public boolean insert(T elem) 
	{
		if (!elem.inBox(xMin, xMax, yMin, yMax)) 			//if the elem lies outside the bounds
		{
			return false;
		}

		if (root == null) 									//tree is empty
		{
			root = new prQuadLeaf(elem);					//make the root a leaf
			return true;
		}
		else if (root.isLeaf())								//creates the first internal node and adds a second item
		{
			if (!((prQuadLeaf) root).isFull())
			{
				int index = ((prQuadLeaf) root).checkForExisting(elem);
				
				if (index == -1)
				{
					((prQuadLeaf) root).addNotFull(elem);
					return true;
				}
				else
				{
					((prQuadLeaf) root).addToExisting(elem, index);
					return true;
				}
			}
			else
			{
				prQuadInternal temp = new prQuadInternal(xMin, xMax, yMin, yMax);
				
				Vector<T> ElementList = ((prQuadLeaf)root).getAllElements();
				
				T currentElem;
				while(ElementList.size() != 0)
				{
					currentElem = ElementList.remove(0);
					insertRecursively(currentElem, temp);
				}
				root = temp;
				return true;
			}
		}
		else 
		{
			return insertRecursively(elem, root);
		}
	}
	
	/**
	 * Helper function used to recursively traverse the tree and insert an element into the correct
	 * position
	 * 
	 * elem - element to be inserted
	 * node - current node
	 */
	@SuppressWarnings("unchecked")
	private boolean insertRecursively(T elem, prQuadNode node) 
	{
		if (!node.isLeaf())
		{
			String quadrant = ((prQuadInternal) node).getQuadrant(elem);
			prQuadNode toNode = ((prQuadInternal) node).getQuadPtr(quadrant);
			
			
			if (toNode == null)						//if the quadrant is null
			{
				prQuadLeaf leaf = new prQuadLeaf(elem);									//add new leaf
				((prQuadInternal) node).setPointer(leaf, quadrant);
				return true;
			}
			else if (toNode.isLeaf())					//if it is a leaf
			{
				int indexExist = ((prQuadLeaf) toNode).checkForExisting(elem);
				boolean full = ((prQuadLeaf) toNode).isFull();
				if (indexExist == -1)		//doesnt exist in vector
				{
					if (!full)
					{
						return ((prQuadLeaf) toNode).addNotFull(elem);
					}
					else
					{
						Vector<T> fullList = ((prQuadLeaf) toNode).getAllElements();
						prQuadInternal newInternal = ((prQuadInternal) node).makeChildInternal(quadrant);
						
						while (fullList.size() > 0)
						{
							insertRecursively(fullList.remove(0), newInternal);
						}
						((prQuadInternal) node).setPointer(newInternal, quadrant);
						
						return insertRecursively(elem, ((prQuadInternal) node).getQuadPtr(quadrant));
						
					}
				}
				else if (indexExist != -1)
				{
					return ((prQuadLeaf) toNode).addToExisting(elem, indexExist);
				}
				
			}
			else
			{
				return insertRecursively(elem, toNode);
			}
		}
		return false;
	}	
	
	/**
	 * Find function which returns the element matching the description if found
	 * 
	 * Functions used : findRecursively()
	 */
	public T find(T Elem) 
	{
		if (!Elem.inBox(xMin, xMax, yMin, yMax))				//if the element is within bounds
		{
			return null;
		}
		
		if (root == null)										//if the tree is empty
		{
			return null;
		}
		else
		{
			return findRecursively(root,Elem);					//recursive function call
		}
	}
	
	/**
	 * Helper function which recursively traverses the tree until the correct element is found. That element
	 * is then returned.
	 * 
	 * @param node - current node
	 * @param Elem - element to be found
	 * @return
	 */
	private T findRecursively(prQuadNode node, T Elem)
	{
		if (node == null)
		{
			return null;
		}
		if (node.isLeaf())
		{
			Vector<T> eList = ((prQuadLeaf) node).getAllElements();
			
			for (int i = 0; i < eList.size(); i++)							//compare elements
			{
				if (eList.get(i).equals(Elem))
				{
					return eList.get(i);
				}
			}
			
			return null;
		}
		else
		{
			String quadrant = ((prQuadInternal) node).getQuadrant(Elem);
			prQuadNode toCheck =  ((prQuadInternal) node).getQuadPtr(quadrant);
			return findRecursively(toCheck, Elem);
			
		}
	}

	/**
	 * find function that finds all elements that lie within a set of boundaries.  The input is 4 long
	 * numbers that serve to represent the boundaries.
	 * 
	 * A vector of all matching elements is returned.
	 * Functions used vectorfind()
	 */
	public Vector<T> find(float xLo, float xHi, float yLo, float yHi) 
	{	
		Vector<T> found = new Vector<T>();								//initalize a new vector
		
		if (root == null)												//empty tree, return empty vector
		{
			return found;
		}
		if (yLo > yMax || yHi < yMin || xHi < xMin || xLo > xMax)		//check if the search region does not collide with the tree bounds
		{
			return found;
		}
		else
		{
			return vectorFind(root, found, xLo, xHi, yLo, yHi);			//recursive function call
		}
	}
	
	/**
	 * Recursive function used to recursively traverse the tree and find all elements that are withing
	 * the specified boundaries. Returns all elements found in a vector
	 * 
	 * @param node - current node
	 * @param list - list of matching elements
	 * @param xLo - boundary
	 * @param xHi - boundary
	 * @param yLo - boundary
	 * @param yHi - boundary
	 * @return
	 */
	@SuppressWarnings("unchecked")
	private Vector<T> vectorFind(prQuadNode node, Vector<T> list, float xLo, float xHi, float yLo, float yHi)
	{
		if (node == null)
		{
			return list;
		}
		else if (node.isLeaf())
		{
			Vector<T> elements = ((prQuadLeaf) node).getAllElements();
			
			for (int i = 0; i < elements.size(); i++)
			{
				if (elements.get(i).inBox(xLo, xHi, yLo, yHi))
				{
					list.add(elements.get(i));
				}
			}
			return list;
			
		}
		else
		{
			float localxMin = ((prQuadInternal) node).getBound("xMin");										//get the bounds of current internal node
			float localxMax = ((prQuadInternal) node).getBound("xMax");	
			float localyMin = ((prQuadInternal) node).getBound("yMin");
			float localyMax = ((prQuadInternal) node).getBound("yMax");
			float xMid = (localxMin + localxMax) /2;															//find the mid points
			float yMid = (localyMin + localyMax) /2;
			
			if (!(xLo > xMid || xHi < localxMin || yLo > localyMax || yHi < yMid))							//Any of the following cases can run on any instance.  The current internal is
			{																								//split into 4 regions.  Each region is checked for no collision and reversed, 
				list = vectorFind(((prQuadInternal) node).getQuadPtr("NW"), list, xLo, xHi, yLo, yHi);		//meaning that there was collision.  If there is collision, then that particular
			}																								//pointer must be searched by using a recursive call. Since a list is returned in 
																											//recursive call, the list is assigned each time a call is made and returned at the
			if (!(xLo > localxMax || xHi < xMid || yLo > localyMax || yHi < yMid))							//very end
			{
				list = vectorFind(((prQuadInternal) node).getQuadPtr("NE"), list, xLo, xHi, yLo, yHi);
			}
			
			if (!(xLo > xMid || xHi < localxMin || yLo > yMid || yHi < localyMin))
			{
				list = vectorFind(((prQuadInternal) node).getQuadPtr("SW"), list, xLo, xHi, yLo, yHi);
			}
			
			if (!(xLo > localxMax || xHi < xMid || yLo > yMid || yHi < localyMin))
			{
				list = vectorFind(((prQuadInternal) node).getQuadPtr("SE"), list, xLo, xHi, yLo, yHi);
			}
			
			return list;
		}
	}
    
	/**
	 * function which returns a string representation of the tree contents
	 * 
	 * functions used:
	 * printTreeHelper()
	 * @return
	 */
    public String printTree() {
    	
        if (root == null )
        {
            outString = "  Empty tree.\n";
        	return outString;
        }
         else
        {
        	 printTreeHelper(root, "");
        	 return outString;
        }
      }

    /**
     * Recursive function used to traverse the tree and add its contents to outString which can be printed
     * into a file
     * 
     * @param sRoot - current node
     * @param Padding - padding used during each recursive call
     */
    public void printTreeHelper(prQuadNode sRoot, String Padding) {

        // Check for empty leaf
           if ( sRoot == null ) {
              outString = outString + " " + Padding + "*\n";
              return;
           }
           // Check for and process SW and SE subtrees
           if ( !sRoot.isLeaf() ) {
              prQuadInternal p = (prQuadInternal) sRoot;
              printTreeHelper(p.SW, Padding + pad);
              printTreeHelper(p.SE, Padding + pad);
           }
   
           // Determine if at leaf or internal and display accordingly
           if ( sRoot.isLeaf() ) {
              prQuadLeaf p = (prQuadLeaf) sRoot;
              outString = outString + Padding;
              for (int pos = 0; pos < p.Elements.size(); pos++) { 
                 outString = outString + "[" +p.Elements.get(pos) + "]" + p.Elements.get(pos).getOffsets() ;
              }
              outString = outString + "\n";
           }
           else if ( !sRoot.isLeaf())
              outString = outString + Padding + "@\n" ;
           else
              outString = outString + sRoot.getClass().getName() + "#\n";

           // Check for and process NE and NW subtrees
           if ( !sRoot.isLeaf() ) {
              prQuadInternal p = (prQuadInternal) sRoot;
              printTreeHelper( p.NE, Padding + pad);
              printTreeHelper( p.NW, Padding + pad);
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
