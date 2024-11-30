#ifndef ExactAlg_
#define ExactAlg_ 

#include "Graph.h"
#include "objscip/objscip.h"
#include "objscip/objscipdefplugins.h"


class ExactAlg{
    public:
        C_Graph* G;
        SCIP *scip;
        vector<SCIP_VAR*> var_vertices;
        vector<SCIP_CONS*> constraints_vertices;
        
        
        void initialize(C_Graph* instance);
                void initialize(C_Graph* instance,vector<int> costs);
        void solve();
        
        void solveContinuousRelaxation();
    
    
};

#endif
