//Grant Davis
//CPE 400 Project
//Dynamic routing mechanism design with focus on throughput

#include "graph.hpp"

#include <iostream>
#include <string>

using namespace std;

void createGraph(string, Graph*);

int main(){
    //*initialize variables*
    const int numVerts = 9;
    int src = 0;
    int dest = 0;
    int option;
  
    //*create graph*
    Graph network(numVerts);
    createGraph("data.txt", &network);

    //choose routers (source and destination)
    cout << "Source router integer: ";
          cin >> src;
          cout << "Destination router integer: ";
          cin >> dest;
    //UI
    do{
      cout << "\nCPE400 Project Menu: " << endl;
      cout << "1. Change Routers" << endl;
		  cout << "2. Maximum Bandwidth" << endl;
		  cout << "3. Print Graph Table" << endl;
		  cout << "0. Quit" << endl;;
		  cin >> option;
      switch(option){
        case 1:
          cout << "Source router integer: ";
          cin >> src;
          cout << "Destination router integer: ";
          cin >> dest;       
          break;
        case 2: 
          network.maxBandwidth(src,dest);
          break;
        case 3:
          network.print();
          break;
        default:
          break;
      }
    }while(option != 0);
    return 0;
}

//*Create graph from data.txt*
void createGraph(string filename, Graph* network){   
    //*variable initialize*
    int vert1, vert2, cost;
    string inputStream;

    //*file input stream*
    ifstream fin(filename.c_str());
    
    if(!fin.good()){
        cerr << "error '" << filename << "' not found" << endl;
        return;
    }
  
    fin >> inputStream;
    
    while(!fin.eof()){
        fin >> vert1 >> vert2 >> cost;
        network->addEdge(vert1, vert2, cost);
    }
    fin.close();   
}
