/**
 * Thomas Yu
 * CS 3114
 * Project 4 - Geographic Information System
 * Last Edited - 4/20/2013
 * 
 * HashTable.java
 * 
 * HashTable generic which hashes the key and value into a table
 */
import java.util.ArrayList;

public class HashTable<K,V> {
	
	/**
	 * An entry within the hashtable
	 * K - generic key
	 * V - generic value
	 * values - arraylist of generics
	 */
	private class HashEntry<K,V>
	{
		K key;
		ArrayList<V> values;
		
		/**
		 * Constructor. Constructs an instance of this hashtable element
		 */
		public HashEntry(K key, V value)
		{
			this.key = key;
			values = new ArrayList<V>();
			values.add(value);
		}
		
		/**
		 * Constructor.  Constructs an instance of a hashtable element used for searching by key
		 */
		public HashEntry(K key)
		{
			this.key = key;
			values = null;
		}
		
		/**
		 * Override of the hasCode function.  Uses the provided elfHash to turn this element into
		 * a hash code
		 */
		@Override
		public int hashCode()
		{
			String toHash = (String) key;
			
			long hashValue = 0;
			for (int Pos = 0; Pos < toHash.length(); Pos++) {      // use all elements

			hashValue = (hashValue << 4) + toHash.charAt(Pos);  // shift/mix
	        long hiBits = hashValue & 0xF0000000L;                // get high nybble

		    if (hiBits != 0)
		    hashValue ^= hiBits >> 24;    // xor high nybble with second nybble

		    hashValue &= ~hiBits;            // clear high nybble
			}

			return (int) hashValue;
		}
		
		/**
		 * Override of the equals function.
		 */
		public boolean equals(Object other)
		{
			if (other == null)
			{
				return false;
			}
			
			if (this.hashCode() == other.hashCode())
			{
				return true;
			}
			
			return false;
		}
		
		/**
		 * adds additional offsets to the values list
		 * @param other
		 */
		@SuppressWarnings({ "unchecked", "rawtypes" })
		public void addToEntry(HashEntry other)
		{
			values.add((V) other.getFirstValue());
		}
		
		/**
		 * returns and removes the first value in the values list
		 * @return
		 */
		public V getFirstValue()
		{
			return values.remove(0);
		}
		
		/**
		 * returns the amount of values in the valuelist
		 * @return
		 */
		public int getValuesAmount()
		{
			return values.size();
		}
		
		/**
		 * returns the key
		 * @return
		 */
		public K getKey()
		{
			return key;
		}
		
		/**
		 * returns the list of offsets as a string
		 * @return
		 */
		public String allOffsets()
		{
			return values.toString();
		}
		
		/**
		 * returns the list of offsets
		 * @return
		 */
		public ArrayList<V> getAllValues()
		{
			return values;
		}
	}
	
	int hashSize;									//size of the hash table
	int totalHashEntries;							//total number of hash entries
	int sizeLimit;									//limit of the hash before expansion -> hashSize * .7
	int[] sizePoss;									//list of integers of hash table sizes
	int sizeListCounter;							//index of current size in sizePoss
	int mostProbes;									//most probes occurred adding to the hashtable
	HashEntry<K,V>[] hashtable;						//hashtable
	
	/**
	 * Default constructor
	 */
	@SuppressWarnings("unchecked")
	public HashTable()
	{
		hashtable = new HashEntry[1019];
		hashSize = 1019;
		totalHashEntries = 0;
		sizePoss = new int[]{2027, 4079, 8123, 16267, 32503, 65011, 130027, 260111, 520279, 1040387, 2080763,
								4161539, 8323151, 16646323};
		sizeLimit = (int) (1019 * .7);
		sizeListCounter = 0;
		mostProbes = 0;
	}
	
	/**
	 * extends the size of the hash table to the next size.  Rehashes old values
	 * Functions used:
	 * addEntry()
	 */
	@SuppressWarnings("unchecked")
	private void extendSize()
	{
		int oldSize = hashSize;
		hashSize = sizePoss[sizeListCounter];
		sizeLimit = (int) (hashSize * .7);
		sizeListCounter++;
		totalHashEntries = 0;
		
		HashEntry<K,V>[] tempTable = hashtable;
		hashtable = new HashEntry[hashSize];
		
		for (int i=0; i < oldSize; i++)
		{
			if (tempTable[i] != null)
			{
				while(tempTable[i].getValuesAmount() > 0)
				{
					addEntry(tempTable[i].getKey(), tempTable[i].getFirstValue());
				}
			}
		}
		
	}
	
	/**
	 * Adds an entry to the hash table.  Also checks if the table needs to be expanded.
	 * Uses the quadratic algorithm (n^2 + n)/2
	 * 
	 */
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void addEntry(K key, V value)
	{
		HashEntry entry = new HashEntry(key, value);
		
		int index = (int) (entry.hashCode());
		index = index % hashSize;
		
		if (hashtable[index] == null)
		{
			hashtable[index] = entry;
		}
		else
		{
		
			int probes = 0;
			int offset = 1;
			while (hashtable[index] != null && !hashtable[index].equals(entry))
			{
				//quadratic func
				index = index + offset;
				offset = offset + 2;
				index = index % hashSize;
				probes ++;
				System.out.println(index);
			}
			
			if (hashtable[index] == null)
			{
				hashtable[index] = entry;
			}
			else
			{	
				hashtable[index].addToEntry(entry);
			}
		
			
			if (probes > mostProbes)
			{
				mostProbes = probes;
			}
		}
		
		totalHashEntries ++;
		if (totalHashEntries >= sizeLimit)
		{
			extendSize();
		}
	}
	
	/**
	 * Returns the amount of entries in the hash table
	 * @return
	 */
	public int getSize()
	{
		return totalHashEntries;
	}
	
	/**
	 * Returns the max amount of probes encountered
	 * @return
	 */
	public int getProbes()
	{
		return mostProbes;
	}
	
	/**
	 * resets the probe count
	 */
	public void resetProbes()
	{
		mostProbes = 0;
	}
	
	/**
	 * Override of toString function.  Iterates through the hash and returns the whole hash as a string
	 */
	public String toString()
	{
		String hashStringForm = "The current table size is: " + hashSize + "\n";
		hashStringForm = hashStringForm + "Format of output is     (Position): (Name:State) [Offset]\n\n";
		for (int i = 0 ; i <hashSize; i++)
		{
			if (hashtable[i] != null)
			{
				hashStringForm = hashStringForm + i + ": " + hashtable[i].getKey() + ", ";
				hashStringForm = hashStringForm + hashtable[i].allOffsets() + "\n";
			}
			System.out.println("Printing Hash Entry" + i);
		}
		
		return hashStringForm;
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList<V> getOffset(K stateandName)
	{
		@SuppressWarnings("rawtypes")
		HashEntry param = new HashEntry(stateandName);
		
		int index = param.hashCode() % hashSize;
		
		int offset = 1;
		while(hashtable[index] != null &&  !hashtable[index].equals(param))
		{
			index = index + offset;
			offset = offset + 2;
			index = index % hashSize;
		}
		
		if (hashtable[index] == null)
		{
			return null;
		}
		else
		{
			return hashtable[index].getAllValues();
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