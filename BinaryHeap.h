

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "QuadraticProbing.h"
#include "dsexceptions.h"
#include <vector>

using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinaryHeap
{
  public:
    /* Constructs a heap with no input that holds 100 items. */
    /*note to cameron, the constructor here initially held 100 items,
    but since the array is a vector, it builds itself, so 100 items initially is not necessary*/
    explicit BinaryHeap( int capacity = 0 )
      : array( capacity + 1 ), currentSize( 0 )
    {}

    /* Constructs a heap using items taken from the vector
       parameter.*/
    explicit BinaryHeap( const vector<Comparable> & items )
      : array( items.size( ) + 10 ), currentSize( items.size( ) )
    {
        for( int i = 0; i < items.size( ); i++ ){
            array[ i + 1 ] = items[ i ];
            myTable.insert(array[i+1], i+1);
        }
        buildHeap( );
    }

    /* Tells if the array is empty based on the member data
       currentSize */
    bool isEmpty( ) const{
        return currentSize == 0;
    }

    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */
    const Comparable & findMin( ) const{
        if( isEmpty( ) ){
            throw UnderflowException( );
        }
        return array[ 1 ];
    }

    /**
     * Insert item x, allowing duplicates.
     */
    void insert( const Comparable & x ){
        if( currentSize == array.size( ) - 1 ){
            array.resize( array.size( ) * 2 );
        }
        //cout << "After the size stuff." << endl;
            // Percolate up
        int hole = ++currentSize;
        int poison = hole;

        for( ; hole > 1 && x.second </*=*/ array[ hole / 2 ].second; hole /= 2 ){
            array[ hole ] = array[ hole / 2 ];
            myTable.pop(array[hole], hole, hole/2);
        }
        array[ hole ] = x;
        myTable.insert(x,hole);
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( ){
        if( isEmpty( ) ){
            throw UnderflowException( );
        }

        Comparable tempKey = array[1];

        array[ 1 ] = array[ currentSize-- ];
        if(currentSize > 0){
            myTable.pop(array[currentSize + 1], 1, currentSize + 1);
        }
        array[currentSize + 1].first = 0;
	array[currentSize + 1].second = 0;
        myTable.remove(tempKey,/*myTable.roll(tempKey)Perhaps*/ 1/*(?)*/);
        percolateDown( 1 );
    }

    void removeMin( ){
        if( isEmpty( ) ){
            throw UnderflowException( );
        }

        Comparable tempKey = array[1];

        array[ 1 ] = array[ currentSize-- ];
        if(currentSize > 0){
            myTable.pop(array[currentSize + 1], 1, currentSize + 1);
        }
	/*************************************************************************/
        array[currentSize + 1].first = 0;
	array[currentSize + 1].second = 0;
        myTable.remove(tempKey,/*myTable.roll(tempKey)Perhaps*/ 1/*(?)*/);
        percolateDown( 1 );
        cout << tempKey << " ";
    }

    Comparable& operator=(Comparable& comparisonItem){
        if(this!=comparisonItem){
            this->first = comparisonItem.first;
            this->second = comparisonItem.second;
        }
        return *this;
    }

    void getResult(){
        //int initialcounter = currentSize;
        while(!isEmpty()){
            removeMin();
	}
        cout << endl;
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws Underflow if empty.
     */
    void deleteMin( Comparable & minItem ){
        if(isEmpty()){
            throw UnderflowException( );
        }

        minItem = array[ 1 ];
        array[ 1 ] = array[ currentSize-- ];
        myTable.pop(array[currentSize + 1], 1, currentSize + 1);
        array[ 1 ] = array[ currentSize + 1 ];
        myTable.remove(minItem,myTable.roll(minItem)/*Perhaps 1(?)*/);
        percolateDown( 1 );
    }

    /* This is somehow strange. It does nothing but change the
       current size to zero. Perhaps not the same as being empty.
       No more than believeing a tall person to be short just because
       someone tells you so.*/ /* this was here by default, and I do agree
	that it does not remove the items physically*/
    void makeEmpty( )
      { currentSize = 0; }

    /* A function that prints out the contents of a the heap
       and their respective positions within that heap.*/
     //yan's code-------------------
    void validate(){
        for(int i = 1; i < currentSize + 1; i++){
           cout << array[i].first << ":"<< array[i].second << ",";
        }
        cout << endl;
        /*********************************/
        //Note to cameron from Yan, we don't need to see the hashTable for assignment 5, so I commented out the line below.
        /**********************************/
	// Note from Cameron to Yan. For error checking purposes I believe it would be helpful. To that end, I include it.
        //myTable.byForce();
    }



    void decreaseKey(Comparable& key, int delta){
        //for Laziness sake will implement a search operation here
        //need to call hashtable here
        int kwap(key);
        int position = myTable.roll(key);
        //cout << "delta: " << delta << " key: " << int(key) << endl;
        key = kwap - delta;
        //cout << "newKey: " << key << endl;
        //cout << "position in array: " << position << endl;
        //cout << "before change: " << array.at(position) << endl;
        /*array.at(position) = key;*/
        array [ position ] = key;
            //cout << "after change: " << array.at(position) << endl;
        myTable.lock(kwap, key, position);

        //percolate up
        int hole = position;
        int initial = position;

        for( ; hole > 1 && key </*=*/ array[ hole / 2 ]; hole /= 2 ){
            array[ hole ] = array[ hole / 2 ];
            myTable.pop(array[hole], hole, hole/2);
        }
        array[ hole ] = key;

        if(position != hole){
            myTable.pop(array[hole],hole,position);
        }
    }

    int find(Comparable target){
        int pos;

        for(int i = 0; i < array.size(); i++){
            if(array[i] == target){
                pos = i;
                break;
            }
        }
        return pos;
    }

    void increaseKey(Comparable key, int delta){
     //delta is the number generated in getIncreaseDelta
        int position = myTable.roll(key.second);
        int meetNot(key.second);

        //key = int(key)+delta;
        key.second = meetNot + key.second;

        cout << "validation of delta: " << delta<< endl;

        cout << "validation of key: " << meetNot << endl;

        array[position] = key.second;

        cout << "change number: " << array[position] << endl;
        myTable.lock(meetNot, key, position);

        //percolate down

        //there's a bug here
        //there's no hole here
        int hole = position;

        percolateDown(position);
    }

    void remove(Comparable& key){
        if(myTable.wharf(key.second)){
            decreaseKey(key, getDecreaseDelta(key));
            //delete top
            deleteMin();
        }
        else{
            cout << key.second <<" was not found in the Heap." << endl;
            return;
        }
    }

    int getDecreaseDelta(Comparable key){

        if(array[1] != key.second)
        {
                return int((key.second-array[1])+1);
        }
        else
        {
            return array[1];
        }
    }

    int getIncreaseDelta(Comparable key){
    //cout << "currentSize: " << currentSize << " relative max: " << array.at(currentSize) << endl;
        cout << "relative max number: " << array[currentSize] <<endl;
        return int(array[currentSize]+1)-int(key);
    }

	int getSize(){
		return currentSize;
	}

	Comparable getItemAtPos(int pos){
		return array[pos];
	}

	void setAtPos(Comparable item){
		insert(item);
	}


  private:
    int currentSize;  // Number of elements in heap
    vector<Comparable> array;        // The heap array
    HashTable<Comparable> myTable;	//hashTable member
    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( ){
        for( int i = currentSize / 2; i > 0; i-- ){
		percolateDown( i );
        }
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void percolateDown( int hole )
    {
        int initialPosition = hole;
        int child(0);
        Comparable tmp = array[ hole ];

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ] < array[ child ] )
            {
			child++;
	    }

          if( array[ child ] < tmp )
	    {
                array[ hole ] = array[ child ];
                myTable.pop(array[hole], hole, child);
	    }
            else
	    {
                break;
	    }
        }
        array[ hole ] = tmp;
	if(initialPosition != hole)
        {
		myTable.pop(array[hole], hole, initialPosition);
	}
    }
};

#endif
