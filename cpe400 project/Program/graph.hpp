//Grant Davis
//Graph Declaration

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#define SIZE 50

using namespace std;

//*Bandwidth*
struct BW {
    int path;
    int bandwidth;
};
//Graph
class Graph {
    private:
        int numVert;
        int graph[SIZE][SIZE]; 
        bool* visited;
        int *path;
        int pathsList[SIZE][SIZE];

        int minPath(int[], bool[]);
        void findAllPaths(int, int, int, ofstream&);
        int findBandwidth(int[], int);
        
    public:
        Graph(); //default
        Graph(int); //constructor
        ~Graph(); //deconstructor

        void addEdge(int, int, int);
        void print();
        void maxBandwidth(int, int);
        void Dijkstra(int, int);
};
#endif //GRAPH_HPP