#ifndef Graph_H
#define Graph_H

#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include <math.h>
#include <unistd.h>
#include <utility>
//#include "BranchingHandler.h"
using namespace std;


class C_Graph;

struct SCIP_ConsData {
  
  
	int v1; 
	int v2;
	bool same; // true for merging v1 v2 and false for adding fake edge   
	struct SCIP_ConsData* father_data; // Pointer on the data of the father node

};

/****************************  Stable Set ****************************/

class StableSet{
public :
	list<int> L_nodes;
	vector<int> nodes;
	C_Graph* G;

	
	bool contains(int n);
	bool add(int n);
	
	void initialize(int nb_nodes);

	int size();

	void print();



};


/****************************  C_edge  *******************************/
class C_link{
public:
  int num;      // Number of the edge
  int v1, v2;   // The two extremities of an edge v1v2 or of an arc (v1,v2)
  float weight;
  
  // return the extremity disctinc from v in O(1).
  int return_other_extrem(int v);
  
};


/***************************  C_node  *****************************/
class C_node{
public :
   int num;     // Number of the node
   float weight;
   
   list<C_link*> L_adjLinks;

   //Test if j is a neighbour of i in O(degre(i))
   bool test_neighbour(int j);

   //Test if j is a successor of i in O(degre(i))
   bool test_successor(int j);
   
   list<int> same;

};


/**************************  C_Graph  ******************************/
class C_Graph{
public:

  bool directed;  // True if directed / False if undirected
  int nb_nodes;   // Number of nodes
  int nb_links;   // Number of links
  vector<vector<int>> adjacency;  //
vector<vector<int>> adjacency2;
  // Encoding of the graph by adjacence list, i.e. a vector of list of edges 
  vector <C_node> V_nodes;

  // Additional encoding: a vector on the edges (on pointers over edges)
  vector <C_link*> V_links;

 int edgeNumber(int v1 , int v2);
  /*********************************************/
  /*********** ALGORITHMS **********************/
  
  C_Graph  getComplementary();
  /*********************************************/
  /*********** INPUT-OUTPUT FILES **************/
  
  // Read a DIMACS file and store the corresponding graph in C_Graph
  void read_undirected_DIMACS(istream & fic);

};
#endif
