#include "ExactAlg.h"


void ExactAlg::initialize(C_Graph* inst){

    vector<int> v(inst->nb_nodes,1);
    initialize(inst,v);

}


void ExactAlg::initialize(C_Graph* inst,vector<int> costs){

    G = inst;
	//SCIP *scip=NULL;
	SCIPcreate(&scip);
	srand(1);
	SCIPprintVersion(scip, NULL);
	SCIPincludeDefaultPlugins(scip);
	SCIPsetIntParam(scip, "display/verblevel", 5);
	SCIPcreateProb(scip, "DominatingSet", 0, 0, 0, 0, 0, 0, 0);

	////////////////////////
	//////  INEQUALITIES
	////////////////////////
	// Set covering constraints
	constraints_vertices.resize(inst->nb_nodes,(SCIP_CONS*) NULL);
	var_vertices.resize(G->nb_nodes,(SCIP_VAR*) NULL);
	char con_name[255];
	for (int i = 0; i < G->nb_nodes; i++)
	{
		SCIP_CONS* con = NULL;
		(void) SCIPsnprintf(con_name, 255, "C%d", i);
		SCIPcreateConsLinear( scip, &con, con_name, 0, NULL, NULL,1.0,SCIPinfinity(scip),true,true,true,true,true,false,false,false,false,false);
		SCIPaddCons(scip, con);
		constraints_vertices[i] = con; 
	}
	
	
	/////////////////////
	// Add variables
	////////////////////
    char var_name[255];
    for(int i = 0 ; i < G->nb_nodes ; i++){
        SCIPsnprintf(var_name, 255, "V_%d",i);
		SCIPdebugMsg(scip, "new variable <%s>\n", var_name);
		SCIPcreateVar(scip,&(var_vertices[i]) , var_name,0,1,costs[i],SCIP_VARTYPE_INTEGER,true, false, NULL, NULL, NULL, NULL, NULL);
		SCIPaddVar(scip, var_vertices[i]);
        for(int j = 0 ; j < G->nb_nodes ; j++){
            if(i == j || G->adjacency[i][j])
                SCIPaddCoefLinear(scip, constraints_vertices[j], var_vertices[i], 1.0);
        }   
    }
    
    
    return;
}


void ExactAlg::solveContinuousRelaxation(){
    SCIPsetIntParam(scip,"limits/totalnodes",1);
    solve();

}

void ExactAlg::solve(){
    //SCIPsetRealParam(scip, "limits/time", 1800);
	SCIPsetObjIntegral(scip) ;
    SCIPsolve(scip);
    return;
}

