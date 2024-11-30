#include "Graph.h"
#include<bits/stdc++.h>


#define epsilon 0.00001


/****************************  StableSet *****************************/

bool StableSet::contains(int n){

	return nodes[n]==1;

}

bool StableSet::add(int n){
	

	
	if(nodes[n] == 1 )return true;

	int neighbsize = 0;

	for(list<int>::iterator it = L_nodes.begin() ; it != L_nodes.end(); it ++ ){
		if(n == *it)
			return false;
		if(G->adjacency2[n][*it] == 1){
			for(list<int>::iterator itt = L_nodes.begin() ; itt != L_nodes.end(); itt ++ ){
				if((*itt != *it) && G->adjacency2[*it][*itt] ==1)	
					neighbsize++;
		
			}
			neighbsize++;
		}
	}
	if(neighbsize >=2)
		return false;
	

	 
	
	

		nodes[n]=1;
		L_nodes.push_back(n);

		return true;
	
	
	


}

void StableSet::print(){

	list<int>::iterator it;

	for(it = L_nodes.begin(); it != L_nodes.end(); it ++){
		//cout<<(*it)<<" ";


	}
	//cout<<endl;

}
	
void StableSet::initialize(int nb_nodes){
	L_nodes.clear();
	nodes = vector<int>(nb_nodes);
	for(int i = 0; i < nb_nodes; i++){
		nodes[i] = 0;
	
	}

}

int StableSet::size(){

	return L_nodes.size();
}


/****************************  C_link  *******************************/

int C_link::return_other_extrem(int v){
	return (v==v1?v2:v1);
}






/***************************  C_node  *****************************/

bool C_node::test_neighbour(int j){
  list<C_link*>::iterator it;
  for(it=L_adjLinks.begin() ; it !=L_adjLinks.end() ; it++){
    if((*it)->return_other_extrem(num) == j)
      return true;
  }
  return false;
}

bool C_node::test_successor(int j){
  list<C_link*>::iterator it;
  for(it=L_adjLinks.begin() ; it !=L_adjLinks.end() ; it++){
    if((*it)->return_other_extrem(num) == j)
      return true;
  }
  return false;
}

/**************************  C_Graph  ******************************/




int C_Graph::edgeNumber(int v1 , int v2){

	for(int i = 0 ; i < nb_links ; i++){
	
		if((V_links[i]->v1 == v1 && V_links[i]->v2 == v2) || (V_links[i]->v2 == v1 && V_links[i]->v1 == v2)){
			return i ;}
	
	
	}


	return -1;
}

C_Graph  C_Graph::getComplementary(){
	int i ,j , nb;
	C_Graph g;
	C_link* a;


	g.nb_nodes = nb_nodes;
	g.nb_links = nb_nodes*(nb_nodes-1) /2 - nb_links;
	g.adjacency.resize(nb_nodes);
	for( i = 0 ; i < nb_nodes; i++){

		g.adjacency[i]= vector<int>(nb_nodes,1);

    	}
	
	g.V_nodes.resize(nb_nodes);
        g.V_links.resize(g.nb_links);

        for (i=0;i<nb_nodes;i++){
        	g.V_nodes[i].num = i;
        	g.V_nodes[i].L_adjLinks.clear();
        	g.V_nodes[i].weight=0;
		g.adjacency[i][i] = 0;
        }
	

	for(i = 0 ; i < nb_links ; i++){
		g.adjacency[V_links[i]->v1][V_links[i]->v2] = 0;
		g.adjacency[V_links[i]->v2][V_links[i]->v1] = 0;

	}
	
	nb = 0;
	
	for(i = 0; i < nb_nodes ; i ++ ) {

		for(j = 0 ; j <i ; j ++){
			if(g.adjacency[i][j]==1){
				a = new C_link;
				a->v1 = min(i,j);
				a->v2 = max(i,j);
				a->weight=0;
				a->num=nb;
				g.V_links[nb] = a;
				nb++;
			}

		}

	}
	
	return g;


    
	
}





void C_Graph::read_undirected_DIMACS(istream & fic){
  if (!fic){
    //cout<<"File Error"<<endl;
  }
  else{
    int k,i,j;
    string m1,m2;
    list<C_link>::iterator it;
    C_link *a;

    fic>>m1;
    fic>>m2;
		

    while (((m1!="p")&&(m2!="edge"))||((m1!="p")&&(m2!="col"))){
      m1=m2;
      fic>>m2;
    }

    directed=false;
    
    fic>>nb_nodes;
    fic>>nb_links;
		
	this->adjacency.resize(nb_nodes);	
	this->adjacency2.resize(nb_nodes);

    
    int cb_added=0;
    for( i = 0 ; i < nb_nodes; i++){

		//adjacency[i]= vector<int>(nb_nodes);
		this->adjacency[i].resize(nb_nodes);
		this->adjacency2[i].resize(nb_nodes);
    }
    for( i = 0 ; i < nb_nodes; i++){

		for( j = 0 ; j < nb_nodes; j++){


		this->adjacency[i][j]=0;
		this->adjacency2[i][j]=0;
    }
    }
	

    V_nodes.resize(nb_nodes);
    V_links.resize(nb_links);

    for (i=0;i<nb_nodes;i++){
      V_nodes[i].num = i;
      V_nodes[i].L_adjLinks.clear();
      V_nodes[i].weight=1;
    }

    for (k=0;k<nb_links;k++){
    

	      fic>>m1;
	      fic>>i;
	      fic>>j;
     if( this->adjacency[i-1][j-1]!=1 &&   this->adjacency[j-1][i-1]!=1){
	      this->adjacency[i-1][j-1]=1;
	      this->adjacency[j-1][i-1]=1;
	      this->adjacency2[i-1][j-1]=1;
	      this->adjacency2[j-1][i-1]=1;
	      a=new C_link;
	      a->num=cb_added;
	      a->v1=min(i-1,j-1);
	      a->v2=max(i-1,j-1);
	      ////cout<<i<< " "<< j <<endl;
	      a->weight=0;
	      V_nodes[i-1].L_adjLinks.push_back(a);
	      V_nodes[j-1].L_adjLinks.push_back(a);
	      V_links[cb_added] = a;
	      cb_added++;
      }
    }
    nb_links = cb_added;
	
  }
  
}

