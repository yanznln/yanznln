/*
Group members, Yan Zhen Lin, Cameron Rivera, Gabriella Voll, Sidney Thelusma, Vladislav Mayzlin
Assignment 5
File: Vertex.h
*/

#ifndef VERTEX_H
#define VERTEX_H
#include<cstdlib>
#include"BinaryHeap.h"
#include<utility>
#include<limits>
#include<iostream>

using namespace std;

/* This class needs an equal operator overload. This is because of this line in Graph.h
   INIT = search(initialVertex); */

template<typename comparableName, typename comparableType>
class Vertex{

   public:
        Vertex(): name(comparableName()), hasBeenTraversed(false), minDistFromINIT(numeric_limits<float>::infinity()), previousVertex(comparableName()), adjacentVertices(new BinaryHeap< pair<comparableName, comparableType> >)
	{}
	Vertex(comparableName passIn);
	//~Vertex();
	void setName(comparableName newName);
	void buildAdjList(pair<comparableName, comparableType> insertionPair);
	void display();

	bool ISEMPTY(){
        	return adjacentVertices->isEmpty();
	}

	comparableName getName(){
        return name;
	}

	void setZero(){
        minDistFromINIT = 0;
	}

	pair<comparableName, comparableType> getMinPair(){
        	return adjacentVertices->findMin();
	}

	void delMin(){
        	adjacentVertices->deleteMin();
	}

	float getMinDist(){
        	return minDistFromINIT;
	}

	void setNewDist(comparableType newDist){
        	minDistFromINIT = newDist;
	}

	const float & getMinDistFromINIT()
	{
		return minDistFromINIT;
	}

	const bool & getHasBeenTraversed()
	{
		return hasBeenTraversed;
	}

        void setPreviousVertex(comparableName newPrev){
        	previousVertex = newPrev;
        }

	const comparableName & getPreviousVertex()
	{
		return previousVertex;
	}

	Vertex<comparableName, comparableType> & operator= (Vertex<comparableName, comparableType> & hyuk);

   private:

	comparableName name;
	/* The Pair for the binaryHeap may have to be explicitly
           defined. Allowing it to be comparableName and
           comparableType respectively sets the pair in the binary
           heap to pair<float,float>. What I imagine we want is
	   pair<Vertex,float>.*/
	BinaryHeap< pair<comparableName, comparableType> > *adjacentVertices;
	bool hasBeenTraversed;
	comparableType minDistFromINIT;
	comparableName previousVertex;

};

template<typename comparableName, typename comparableType>
Vertex<comparableName, comparableType>::Vertex(comparableName passIn){
	name = passIn;
	hasBeenTraversed = false;
	minDistFromINIT = numeric_limits<float>::infinity();
	previousVertex = comparableName();
	adjacentVertices = new BinaryHeap< pair<comparableName, comparableType> >;
}
/*
template<typename comparableName, typename comparableType>
Vertex<comparableName, comparableType>::~Vertex(){
	//delete adjacentVertices;
}*/

template<typename comparableName, typename comparableType>
void Vertex<comparableName, comparableType>::buildAdjList(pair<comparableName, comparableType> Data){
    //cout << Data.first << " : " << Data.second << endl;
    /**************************************************************/
    /* cameron, make the necessary adjustments to the BinaryHeap.h class to accept and correctly work with pair template*/
    /* This works. However, the hashtable assumes that the second element in the pair is an interger,
    float, double, or string. It has to be one of these four things otherwise there is no way to hash the element to a position in the hashtable. */
    adjacentVertices->insert(Data);
}

template<typename comparableName, typename comparableType>
void Vertex<comparableName, comparableType>::setName(comparableName newName){
    name = newName;
}

template<typename comparableName, typename comparableType>
void Vertex<comparableName, comparableType>::display(){
    cout << "VERTEX: " << name << " : ";
    /*****************************************************************/
    //will need a validate that works for pairs. Cameron, we need the display to work with pairs!!!
    /* Yokay. So I managed to get the display to work for pairs. It assumes that everything has its own "cout" operator. To that end, I tried to implement an operator<< overload for this class. It proved to be more difficult than I had imagined; especially since my knowledge of the operator<< is less than sufficient. Perhaps we can work on this another time. */
    adjacentVertices->validate();
}

template<typename comparableName, typename comparableType>
Vertex <comparableName, comparableType> & Vertex<comparableName, comparableType> :: operator= (Vertex<comparableName, comparableType> & hyuk){
	//cout << "inside of vertex operator overload "<< endl;

	this->name = hyuk.getName();
	this->hasBeenTraversed = hyuk.getHasBeenTraversed();
	this->minDistFromINIT = hyuk.getMinDistFromINIT();
	this->previousVertex = hyuk.getPreviousVertex();
	pair<comparableName, comparableType> temp;

	//cout << "hyuk list size: " << hyuk.adjacentVertices->getSize() << endl;

	for(int i = 1; i <= hyuk.adjacentVertices->getSize(); i++){
		temp = hyuk.adjacentVertices->getItemAtPos(i);
		this->adjacentVertices->setAtPos(temp);
	}

	return *this;
}

#endif
