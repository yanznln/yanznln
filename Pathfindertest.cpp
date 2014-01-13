
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

//for line parsing beyond the initial line
void parse(string line, Graph<float, float>& myGraph, int counter);
//for line parsing on the firstline
int parseline(string line);
bool nonZeroEven(int num);
bool nonZeroOdd(int num);
void UI(Graph<float, float>& Graph, float initial);

int main(int argc, char* argv[]){
	int counter = 0;
	int GraphSize;
	/*instantiate Graph object*/
	Graph<float, float> *myGraph;

	fstream file(argv[1]);
	if(file.is_open()){
		string line;
		getline(file, line);
		GraphSize = parseline(line);
		counter++;
		//cout << "still running " << endl;
        //set Graph object to be a new Graph object with specific size
		myGraph = new Graph<float, float>(GraphSize);
		//need to instantiate graph here;
		while(!file.eof()){
			getline(file, line);
			//cout << "counter: " << counter << endl;
			if(counter >= 1){
				parse(line, *myGraph, counter);
			}
			counter++;
		}
	}
	file.close();

	/*******HERE WE NEED TO CHECK IF THE ADJACENCY LIST IS CORRECT BEFORE PERFORM DIKJSTRA'S********/
	myGraph->displayAdjListData();


	/******************************Hack initial vertex***************************/
    float initial = (float)atof(argv[2]);
    if(initial > GraphSize){
        cout << "Initial Vertex does not Exist!!!!" << endl;
        exit(0);
    }

	 Vertex<float, float> startingVertex(initial);

	myGraph->findPath(startingVertex.getName());
	//deallocate memory
    	myGraph->printResults();

	// Perhaps this should be placed in some sort of loop
	UI(*myGraph, initial);

	delete myGraph;

	return 0;
}

void UI(Graph<float, float>& myGraph, float initial){
    float chant (0);
    char choice;
	cout << "Place a target vertex: ";
	cin >> chant;
	myGraph.backTracking(initial, chant);

	cout << "Would you like to input more target vertex?" << endl;
	cout << "input y for yes, n for no" << endl;
	cin >> choice;
	if(choice != 'y')
        exit(0);
	while(choice == 'y'){
        UI(myGraph, initial);
    }
}

void parse(string line, Graph<float, float>& myGraph, int counter){
    //instantiate a new vertex
	Vertex<float, float> *currentVertex = new Vertex<float, float>;
	int prev = 0;
	float result;
	string word;
	int lineSize = line.length();
	pair<float, float> temporaryPair;
	int alternateCounter = 0;
	for(int i = 0; i< lineSize; i++){
        //cout << lineSize << endl;
		char tempChar = line[i];
		int tempVal = (int)tempChar;
		//on space character
		if(tempVal == 32){
			word = line.substr(prev, (i)-prev);
			prev = i;
			result = atof(word.c_str());
			//cout << "space character detected: " << result << endl;
			//insert info into vertex;
			if(alternateCounter == 0){
			    //cout << "alternateCounter zero entered" << endl;
				currentVertex->setName(result);
				//cout << "name check: " << currentVertex->getName() << endl;
			}
			if(nonZeroOdd(alternateCounter)){
                		temporaryPair.first = result;
			    }
			if(nonZeroEven(alternateCounter)){
				temporaryPair.second = result;
                currentVertex->buildAdjList(temporaryPair);
            }
			    alternateCounter++;
		}
		if(i == lineSize-1){
			word = line.substr(prev, (i-prev)+1);
			prev = 0;
			result = atof(word.c_str());
			//cout << "line ending "<< result << endl;
			//insert the vertex into the graph
			    myGraph.setVertex(counter-1 ,*currentVertex);
			    delete currentVertex;
		}
	}
}

int parseline(string line){
	int prev = 0;
	float result;
	string word;
	int lineSize = line.length();
	for(int i = 0; i < lineSize; i++){
		char tempChar = line[i];
		int tempVal = (int)tempChar;
		if(tempVal == 32){
			word = line.substr(prev, i-prev);
			prev = i;
			result = atof(word.c_str());
			break;
		}
		if(i == lineSize-1){
			word = line.substr(prev, (i-prev)+1);
			prev = 0;
			result = atof(word.c_str());
			cout << "size of graph: " << result << endl;
			break;
		}
	}
	return result;
}

bool nonZeroOdd(int num){
    if(num%2 != 0 && num > 0)
        return true;
    else
        return false;
}

bool nonZeroEven(int num){
    if(num%2 == 0 && num > 0)
        return true;
    else
        return false;
}

