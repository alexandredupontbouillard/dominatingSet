#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
/* scip includes */
#include "objscip/objscip.h"
#include "objscip/objscipdefplugins.h"
#include "Graph.h"
#include "ExactAlg.h"

//#include "doctest.h"
/* namespace usage */
using namespace std;
using namespace scip;

#define ADDOPT FALSE

#define NBMAXCONSITER 2000


#define SCIP_DEBUG   // Si non commente, affiche le log de SCIP






int main(int argc, char** argv)
{
	char * name,*nameext; //, *nameextsol;
	int i;

	if(argc < 2){
		cerr<<"usage: "<<argv[0]<<" <DIMACS file name> <mode>"<<endl; 
		return 1;
	}
	srand(1);
	name= new char[40];
	nameext= new char[40];
	//nameextsol= new char[40];
	//doctest::Context(argc, argv).run(); 
	name=strcat(name,argv[1]);
	nameext=strcat(nameext,argv[1]);
	ifstream fic(nameext);
	C_Graph G;
	G.read_undirected_DIMACS(fic);
	ExactAlg milp;
	milp.initialize(&G);
	milp.solveContinuousRelaxation();
	
	// Récupérer la solution



		
	return 0;
}





