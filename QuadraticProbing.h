
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

int nextPrime( int n );
int hash( const string & key );
int hash( int key );
int hash (float key);
int hash (double key);


// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:

    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    bool contains( const HashedObj & x, const int & loc ) const
    {
        return isActive( bellowingMonkeys( x, loc ) );
    }

   bool wharf( const HashedObj & x ) const
   {
        return isActive( howlingMuskrats( x ) );
   }

    void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < array.size( ); i++ )
        {
		array[ i ].info = EMPTY;
	}
    }

    // updates the hashtable if only a position is changed.
    void pop ( const HashedObj & x, const int & loc, const int & oldLoc )
    {
	int that = bellowingMonkeys(x, oldLoc);
	//int that = howlingMuskrats(x);
	if(array[that].spot != loc && array[that].element == x)
	{
		array[that].spot = loc;
	}
	else if(array[that].spot == loc && array[that].element == x)
	{
		cout << "No need to update" << endl;
		return;
	}
	else
	{
		cout << "------------------------------" << endl;
		cout << x.first << "," << x.second << " " << loc << " " << oldLoc << endl;
		cout << "Element not in the table" << endl;
		cout << "-------------------------------" << endl;
		return;
	}
    }

    /* Updates the hashtable if a value has changed. Takes the key that was
       altered, the new key and position as input. */
    void lock ( const HashedObj & y, const HashedObj & x, const int & loc )
    {
	if(contains(y,loc))
	{
		remove(y,loc);
		insert(x,loc);
	}
    }

    /* returns position. Takes a key as an argument.*/
    int roll ( const HashedObj & y )
    {
	int that = howlingMuskrats(y);
	return array[that].spot;
    }

    bool insert( const HashedObj & x, const int & loc )
    {
            // Insert x as active
        int currentPos = findPos( x );
        /*if( isActive( currentPos ) )
            return false;*/

	//cout << "The element: " << array[ currentPos ].element << "the location: " << loc << endl;
        array[ currentPos ].element = x;
	array[ currentPos ].spot = loc;
	array[ currentPos ].info = ACTIVE;
 	//= HashEntry( x, ACTIVE, loc );

            // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
        {
		rehash( );
	}

        return true;
    }

    void byForce ()
    {
	for(int i = 0; i < array.size() ; i++)
	{
		if(array[i].info == ACTIVE)
		{
			cout << "The element in position " << i << " is: " << array[i].element.first << "," << array[i].element.second << " and has position: " << array[i].spot << endl;
		}
	}
    }

    bool remove( const HashedObj & x, const int & pie)
    {
        int currentPos = bellowingMonkeys( x, pie );
        if( !isActive( currentPos ) )
        {
		return false;
	}

	HashedObj ou;
	array[ currentPos ].element = ou;
	array[ currentPos ].spot = -1;
        array[ currentPos ].info = DELETED /*EMPTY*/;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
	/* The thing inserted into the hash table of
	   template value */
        HashedObj element;

	/* An enumerated type that perhaps gives the status
	   of an item in the table. */
        EntryType info;

	/* An interger that gives the position of the
	   key in the corresponding heap. */

	int spot;

	/* Perhaps a constructor of sorts. */
        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY, int s = -1 )
          : element( e ), info( i ), spot(s) { }
    };

    vector<HashEntry> array;
    int currentSize;

    /* Searches the hash table and returns true if the inputted
       parameter is in the table and false if not. */
    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    /* Finds an empty position. If the intial position is not empty
       it returns the position of object. If the position empty,
       then it searches for it using a quadratic probing method. */
    // used for insertion
    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

          // Assuming table is half-empty, and table length is prime,
          // this loop terminates
	  /* If we take out the second check, it allows us to
	     add doubles in the table, however, by doing that
	     we can never find the item using contains.*/
        while( array[ currentPos ].info != EMPTY /*&&
                array[ currentPos ].element != x*/)
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
            {
		currentPos = currentPos % array.size( );
	    }
        }

        return currentPos;
    }

    // used for contains
    int bellowingMonkeys( const HashedObj & x, const int & loc ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

          // Assuming table is half-empty, and table length is prime,
          // this loop terminates
	  /* If we take out the second check, it allows us to
	     add doubles in the table, however, by doing that
	     we can never find the item using contains.*/
        while( (array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x ) || (array[ currentPos ].spot != loc && array[ currentPos ].element == x) )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
            {
		currentPos = currentPos % array.size( );
	    }
        }

        return currentPos;
    }

    // used for returning position (roll)
    int howlingMuskrats( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

          // Assuming table is half-empty, and table length is prime,
          // this loop terminates
	  /* If we take out the second check, it allows us to
	     add doubles in the table, however, by doing that
	     we can never find the item using contains.*/
        while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
            {
		currentPos = currentPos % array.size( );
	    }
        }

        return currentPos;
    }

    /* Resizes the table and places the elements back in
       based on the new size. */
    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( int j = 0; j < array.size( ); j++ )
        {
		array[ j ].info = EMPTY;
	}

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldArray.size( ); i++ )
        {
		if( oldArray[ i ].info == ACTIVE )
        	{
			insert( oldArray[ i ].element, oldArray[i].spot );
		}
	}
    }

    /* Takes an object in and return the hash value of
       it.Returns the value itself if the inserted object
       happens to be an interger. If the inserted object
       happens to be a string, then the string is taken
       and a value is assigned based off the ASCII values.*/
    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash( x.second );

        hashVal %= array.size( );
        if( hashVal < 0 )
        {
	   hashVal += array.size( );
	}

        return hashVal;
    }
};

#endif
