
#include<cstdlib>
#include<utility>
#include"Vertex.h"
#include"Wallop.h"

using namespace std;

template<typename comparableName, typename comparableType>
class Graph{

    public:
        Graph(int size);
        ~Graph();
        void displayAdjListData();
	//set vertex to a specific data position
        void setVertex(int position, Vertex<comparableName, comparableType> newVertex);
        //not update on dropbox
        void findPath(comparableName initialVertex);
        void printResults();
	void backTracking(comparableName verse, comparableName & vox);

    private:
        int graphSize;
        //initial vertex
        //INIT;
        Vertex<comparableName, comparableType> *datacontainer;
        //vertex stack keeps track of empty and non EMpty vertices
        Wallop<comparableName> vertexStack;


        Vertex<comparableName, comparableType>& search(comparableName targetVertex);
        void DijkstrasAlgo(Vertex<comparableName, comparableType>& INIT);
        void ReadVertex(Vertex<comparableName, comparableType>& targetVertex);
        void TraversePath(Vertex<comparableName, comparableType>& targetVertex,
                     comparableName currentVertex,comparableType weightedEdge);
        bool existOnStack(comparableName searchItem);

};

// A default constructor perhaps.
template<typename comparableName, typename comparableType>
Graph<comparableName, comparableType>::Graph(int size){
    graphSize = size;
    //need to pass array size into the class member array
    datacontainer = new Vertex<comparableName, comparableType>[size];
    //vertexStack = new Wallop<comparableName>;
    /* The above stack may need to be a stack of vertices rather
       than a stack of vertex names.*/
}

template<typename comparableName, typename comparableType>
void Graph<comparableName, comparableType>::printResults(){
    for(int i = 0; i < graphSize; i++){
        cout << "vertex: " << datacontainer[i].getName() << " Minimum distance from initial starting point: " << datacontainer[i].getMinDist() << endl;
    }
}

template<typename comparableName, typename comparableType>
void Graph<comparableName, comparableType> :: backTracking (comparableName verse, comparableName & vox)
{
	Wallop <comparableName> zen;
	Vertex <comparableName, comparableType> tch;

	comparableType result;
	try{
        tch = search(vox);
        result = tch.getMinDist();
        cout << "The path from vertex " << verse << " to vertex " << tch.getName() << " is: ";
        while(tch.getName() != verse){
            zen.putItOn(tch.getPreviousVertex());
            tch = search(tch.getPreviousVertex());
        }
        if(!zen.geh()){
            while(!zen.geh()){
                cout << zen.popItOff() << " ";
            }
        }else{
            cout << "No Path Found! ";
        }
        cout << endl;
        cout << " Total Shortest Path: " << result << endl;
	}catch(...){
        cout << "could not find target vertex!!!" << endl;
	}
}
// A destructor.
template<typename comparableName, typename comparableType>
Graph<comparableName, comparableType>::~Graph(){
    delete datacontainer;
}

// Takes a vertex and a position. Places that vertex in said position (?)
template<typename comparableName, typename comparableType>
void Graph<comparableName, comparableType>::setVertex(int position, Vertex<comparableName, comparableType> newVertex){
    datacontainer[position] = newVertex;
	//datacontainer[position].display();*/
}

//prints out the vertex data inside of the array
template<typename comparableName, typename comparableType>
void Graph<comparableName, comparableType>::displayAdjListData(){
    for(int i = 0; i < graphSize; i++){
        datacontainer[i].display();
    }
}
/******************************************************************************/
/******************************************************************************/
/************************Path finding algorithm starts here ***************************/
/******************************************************************************/
/******************************************************************************/
/* The traversal perhaps. Takes a vertex as an argument. Perhaps
   this is the starting point*/
template<typename comparableName, typename comparableType>
void Graph<comparableName, comparableType>::findPath(comparableName initialVertex){
    try{
        search(initialVertex);
	}catch(...){
		cout << "VERTEX " << initialVertex << " NOT FOUND!!! "<< endl;
	}
    DijkstrasAlgo(search(initialVertex));
}

/* Returns a vertex. From the container of vertices. */
template<typename comparableName, typename comparableType>
Vertex<comparableName, comparableType>& Graph<comparableName, comparableType>::search(comparableName targetVertex){
	/*Cannot return a reference to a local variable.*/
    //Vertex<comparableName, comparableType> ret;
    //cout << "here here" << endl;
    for(int i = 0; i<graphSize; i++){
        if(datacontainer[i].getName() == targetVertex){
            return datacontainer[i];
        }
        if(i == graphSize-1 && datacontainer[i].getName() != targetVertex){
            Vertex<comparableName, comparableType> badResult;
            throw int(0);
        }
    }
    //cout << "here here" << endl;
}

/* Takes a vertex as an argument. Sets the path length to zero.
   Continues the traversal only if edges exist in the containing ]
   binaryHeap. Returns nothing */
template<typename comparableName, typename comparableType>
void Graph<comparableName, comparableType>::DijkstrasAlgo(Vertex<comparableName, comparableType>& INIT){
    INIT.setZero();
    //cout << "init mindist: " << INIT.getMinDist() << endl;
    if(INIT.ISEMPTY())
    {
        cout << "starting vertex has no adjacent edges" << endl;
    }
    else
    {
        ReadVertex(INIT);
    }
}

/* Takes the name of a vertex as an argument. Checks if that item
   is on the stack. However, maybe this should just be taken care of
   by creating a boolean in the vertex class that tells whether an
   item is on the stack or not. */
template<typename comparableName, typename comparableType>
bool Graph<comparableName, comparableType>::existOnStack(comparableName searchItem){
    return vertexStack.existence(searchItem);
}

/* Takes a vertex as an argument. Perhaps my previous thought was
   incorrect. This may be the actual traversal.*/
template<typename comparableName, typename comparableType>
void Graph<comparableName, comparableType>::ReadVertex(Vertex<comparableName, comparableType>& targetVertex){
    //cout << "init mindist: " << INIT.getMinDist() << endl;
    /*cout << "vertex: " << targetVertex.getName() << endl;
    cout << "initial mindist: " << targetVertex.getMinDist() << endl;*/
	if(targetVertex.ISEMPTY()){
        //we need to perform a peep rather than a pop because the item on top of the stack might not be empty
		if(!vertexStack.geh()){
			comparableName topOfStack = vertexStack.peep();
			ReadVertex(search(topOfStack));
		}
		else{
			cout << "all path traversed" << endl;
		}
	}else{
        pair<comparableName, comparableType> tempPair = targetVertex.getMinPair();
        /*cout << tempPair.first << endl;
        cout << tempPair.second << endl;*/

        Vertex<comparableName, comparableType> nextVertex = search(tempPair.first);
        /*******************************CRITICAL: STACK MANAGEMENT **************************************/
        //deletemin to remove smallest heapItem
        targetVertex.delMin();
        //targetVertex.display();
        /*if the vertex's heap is empty and the top of the stack matches the name of the current vertex, pop it off*/
        if(!vertexStack.geh()){
            if(targetVertex.ISEMPTY() && vertexStack.peep()==targetVertex.getName()){
                vertexStack.popItOff();
            }
        }
        /*if target vertex's heap after deletmin() is not empty, put it on the stack. If it is not already on the stack*/
        if(!targetVertex.ISEMPTY() && !existOnStack(targetVertex.getName())){
            vertexStack.putItOn(targetVertex.getName());
        }
        /**********************************************************************************************/
        //cout << "weight to be passed in" <<tempPair.second+targetVertex.getMinDist() << endl;
        TraversePath(search(tempPair.first), targetVertex.getName(), tempPair.second+targetVertex.getMinDist());
    }
}

/* Updating stuff perhaps (?)*/
template<typename comparableName, typename comparableType>
/*Vertex<comparableName, comparableType>*/ void Graph<comparableName, comparableType>::TraversePath(Vertex<comparableName, comparableType>& targetVertex, comparableName currentVertex,comparableType weightedEdge){
    //perform tarversal operation
    //if the cumulative edge is less than the current vertex's current minimum edge
    //cout << "vertex name: " << targetVertex.getName() << " vertex mindist: " << targetVertex.getMinDist() <<endl;
    if(weightedEdge < targetVertex.getMinDist()){
        targetVertex.setNewDist(weightedEdge);
        targetVertex.setPreviousVertex(currentVertex);
        ReadVertex(targetVertex);
    }
    //if the cumulative edge is greater
    else if(weightedEdge >= targetVertex.getMinDist()){
        ReadVertex(targetVertex);
    }

}
