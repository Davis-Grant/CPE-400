//Grant Davis
//*Graph Implementation*

#include "graph.hpp"

//*Default Constructor*
Graph::Graph(){
    //variable initialization
    numVert = 1;
    visited = new bool[numVert];
    path = new int[numVert];
  
    for(int i=0 ; i<SIZE ; i++)
    {
        for(int j=0 ; j<SIZE ; j++)
        {
            graph[i][j] = 0;
            pathsList[i][j] = -1;
        }
    }
    for(int i=0 ; i<numVert ; i++)
        visited[i] = false;
}

//*Number of vertices constructor*
Graph::Graph(int n){
    numVert = n;
    visited = new bool[numVert];
    path = new int[numVert];
    
    for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            graph[i][j] = 0;
            pathsList[i][j] = -1;
        }
    }
    
    for(int i=0 ; i<numVert ; i++)
        visited[i] = false;
}

//*Deconstructor*
Graph::~Graph()
{
}

//*Functions*
//Adds edge between x and y nodes
void Graph::addEdge(int x, int y, int cost){
    if(x > numVert || y > numVert || x < 0 || y < 0 )
        cerr << "error: invalid edge" << "X = " << x << " Y = " << y << endl;
    else
        graph[x][y] = cost;
}

//*Prints the graph's table*
void Graph::print(){
    cout << "Graph table:" << endl;
    for(int i=0 ; i<numVert ; i++){
        for(int j=0 ; j<numVert ; j++)
            cout << graph[i][j] << " | ";
        cout << endl;
    }
}

//*Minimum path for Dijkstra algorithm* 
int Graph::minPath(int dist[], bool shortestPathTree[]){
    //variables initialize
    int min = __INT_MAX__;
    int index;
    
    for(int i=0 ; i<numVert ; i++){
        if(shortestPathTree[i] == false && dist[i]<= min){
            min = dist[i];
            index = i;
        }
    }
    return index;
}

//*Dijkstra's Shortest Path Algorithm*
void Graph::Dijkstra(int src, int dest){
    //initialize
    int dist[numVert];
    bool shortestPathTree[numVert];
    int throughVert[numVert];
    
    for(int i=0 ; i<numVert ; i++){
        dist[i] = __INT_MAX__;
        shortestPathTree[i] = false;
    }
    
    dist[src] = 0;
    //find  the index of the vertex with the desired path
    for(int i=0 ; i<numVert-1 ; i++){
        int u = minPath(dist, shortestPathTree);
        shortestPathTree[u] = true;//add vertex u to the shortestPathTree array
        for(int v=0 ; v<numVert ; v++){
            if(!shortestPathTree[v] && graph[u][v] && dist[u] != __INT_MAX__ && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                throughVert[v] = u;
            }
        }
    }            
}

//*Finds the path with the maximum bandwidth between two nodes*
void Graph::maxBandwidth(int src, int dest){ 
    //variable initialize
    int pathIndex = 0;
    int pathNum = 0;
    int routerNum = 0;
    int temp = -1;
  
    //Find All paths from source to destination and store them in 'path.txt'
    //write to file
    ofstream fout;
    fout.open("path.txt");
    //Find All paths
    findAllPaths(src, dest, pathIndex, fout);
    fout.close();
  
    //Calculate max bandwidth for each path found
    //input stream from 'path.txt'
    ifstream fin;
    fin.open("path.txt");
  
    while(!fin.eof()){
        fin >> temp;
        pathsList[pathNum][routerNum++] = temp;
        if(temp == dest){
            pathNum++;
            routerNum = 0;
        }
    }
    pathNum--;

    //All paths from router x to router y
    cout << endl <<"All paths from router " << src << " to router " << dest << ":" << endl;
    for(int i=0 ; i<pathNum ; i++){
        cout << "Path " << i << ": ";
        for(int j=0 ; j<numVert ; j++){
            if(pathsList[i][j] != -1){
                if(pathsList[i][j] == dest)
                    cout << pathsList[i][j];
                else
                    cout << pathsList[i][j] << " => ";
            }  
        }
        cout << endl;
    }
    int routersInPath = 0;
    BW bandwidths [pathNum]; 
    cout << endl;

    //Bandwidth
    for(int i=0 ; i<pathNum ; i++){
        cout << "Path " << i << " bandwidth: ";
        for(int j=0 ; j<numVert ; j++){
            if(pathsList[i][j] != -1)
                routersInPath++;
        }
        bandwidths[i].path = i;
        bandwidths[i].bandwidth = findBandwidth(pathsList[i], routersInPath);
        cout << bandwidths[i].bandwidth << " bps" << endl;
        routersInPath = 0;
    }
    
    //Take the path with the max bandwidth and print it
    BW swapTemp;
    for(int i=0 ; i<pathNum ; i++){
        for(int j=i ; j<pathNum ; j++){
            if(bandwidths[i].bandwidth <= bandwidths[j].bandwidth){
                swapTemp =  bandwidths[i];
                bandwidths[i] = bandwidths[j];
                bandwidths[j] = swapTemp;
            }
        }
    }
    cout << endl << "The path with max bandwidth: " << bandwidths[0].path << " with " << bandwidths[0].bandwidth << " bps" << endl;   
}

//Finds all paths
void Graph::findAllPaths(int source, int destination, int index, ofstream& fout){
    visited[source] = true;
    path[index] = source;
    index++;
    
    if(source == destination){
        for(int i=0; i<index ; i++){
            fout << path[i] << " ";
        }
        fout << endl;
    }
    else
    {
        for(int v=0 ; v<numVert ; v++){
            if(!visited[v] && graph[source][v] > 0){
                findAllPaths(v, destination, index, fout);
            }
        }
    }
    index--;
    visited[source] = false;
}

//Finds bandwidth
int Graph::findBandwidth(int path[], int routers)
{
    int bandwidth = __INT_MAX__;
    for(int i=0 ; i<routers-1 ; i++){
        bandwidth = min(bandwidth, graph[path[i]][path[i+1]]); 
    }
    return bandwidth;
}