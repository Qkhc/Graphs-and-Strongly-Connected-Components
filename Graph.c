//----------------------------------
// Graph.c			   |
// Implementation for Graph ADT    |
// 				   |
// Robert Mushkot		   |
// rmushkot			   |
// 1543374			   |
// pa5				   |
// ---------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"


// Structs ------------------------------------------


// private GraphObj type
typedef struct GraphObj{
	int order;  // Number of vertices
	int size;  // Number of edges

	List* vertices;
	char* color;

	int* parent;

	int* disc;
	int* fin;

} GraphObj;





// Constructors - Destructors-----------------------------------------------------

// newGraph()
// returns a reference to new empty Graph object 
Graph newGraph(int n){
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;

	G->vertices = calloc(n+1,sizeof(List*));
	G->color = calloc(n+1,sizeof(char*));

	G->parent = calloc(n+1,sizeof(int*));

	G->disc = calloc(n+1, sizeof(int*));
	G->fin = calloc(n+1, sizeof(int*));

	for(int i = 1; i<=n; i++){

		G->vertices[i] = newList();
		G->color[i] = 'w';

		G->parent[i] = NIL;

		G->disc[i] = UNDEF;
		G->fin[i] = UNDEF;
	}

	return G;
}


// freeGraph()
// frees all heap mempry associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG){
	if(pG != NULL && *pG != NULL){

		for(int i = 1; i <= getOrder(*pG); i++){

			freeList(&(*pG)->vertices[i]);
		}
		free((*pG)->vertices);
		free((*pG)->color);

		free((*pG)->parent);

		free((*pG)->disc);
		free((*pG)->fin);


		free(*pG);
		*pG = NULL;
	}
}



// Access funtions---------------------------------------------------------------

// getOrder()
// Returns the field value of order.
int getOrder(Graph G){

	return G->order;

}


// getSize()
// Returns the field value of size.
int getSize(Graph G){

	return G->size;

}


// getParent()
// Returns the parent of vertex u in the Breadth-First tree created in BFS().
// Pre: 1<= u <= getOrder(G)
int getParent(Graph G, int u){

	if(G == NULL){

		printf("Graph Error: calling getParent on NULL Graph reference");
		exit(1);

	}

	if( u >= 1 && u <= getOrder(G)){

		return G->parent[u];

	}

	else{

		printf("Graph Error: getParent Prerequisites are not fulfilled.");
		exit(1);
	}

}


// getDiscover
// gets the Discover time of the given vertex after running DFS
// Pre: 1<=u<= getOrder(G)
int getDiscover(Graph G,int u){

	if(G == NULL){

		printf("Graph Error: Calling getDiscover() on NULL graph reference");
		exit(1);

	}

	if( u <= getOrder(G) &&  u >= 1 ){

		return G->disc[u];

	}

	else{

		printf("Graph Error: getDiscover() prerequisites not met.");
		exit(1);

	}

	return UNDEF;
}

// getFinish()
// returns the finish time of the given vertex after running DFS
int getFinish(Graph G, int u){
	if(G == NULL){

		printf("Graph Error: Calling getDiscover() on NULL graph reference");
		exit(1);

	}

	if( u <= getOrder(G) &&  u >= 1 ){

		return G->fin[u];

	}

	else{

		printf("Graph Error: getFinish() prerequisites not met.");
		exit(1);

	}

	return UNDEF;
}	


// Manipulation procedures--------------------------------------------------


// addEdge()
// inserts a new edge joining u to v: u added to adjacency List of v and v to the adjacnecy list of u.
// Pre: 1 <= u,v <= getOrder()
void addEdge(Graph G, int u, int v){

	if(G == NULL){

		printf("Graph Error: calling addEdge on NULL Graph reference.");
		exit(1);

	}

	if( u >= 1 && v >=1 && u <= getOrder(G) && v <= getOrder(G)){

		addArc(G,u,v);
		addArc(G,v,u);
		G->size--;

	}else{

		printf("Graph error: addEdge u or v out of range 1<=u,v<=getOrder()");
		exit(1);

	}
}



// addArc()
// inserts a new directed edge from u to v v is added to the adjacency List of u
// Pre: 1 <= u,v <= getOrder(G)
void addArc(Graph G, int u, int v){

	if( G == NULL){

		printf("Graph error: addArc() calling on NULL graph reference");
		exit(1);

	}

	if(u >= 1 && v >=1 && u <= getOrder(G) && v <= getOrder(G)){

		if(length(G->vertices[u]) == 0){

			append(G->vertices[u], v);
		}

		moveFront(G->vertices[u]);

		while(v > get(G->vertices[u])){ // Puts the value v into the sorted order of u's adjacency list.

			if(length(G->vertices[u]) == index(G->vertices[u]) + 1){ // If v belongs at the back.

				append(G->vertices[u],v);
			}

			moveNext(G->vertices[u]);
		}

		if( v < get(G->vertices[u])){ // v is in the right spot and inserts before.

			insertBefore(G->vertices[u], v);

		}
		G->size++;

	}

	else{
		printf("Graph Error: addArc u or v out of range 1<=u,v<=getOrder()");
		exit(1);
	}
}

// Private visit()
// Private function used in the DFS() algorithm. Recursively calls itself inorder to find and discover the next nodes.
void visit(Graph G, int x, int* time, List S){

	G->color[x] = 'g';
	G->disc[x] = ++(*time);

	if(length(G->vertices[x]) >0){

		moveFront(G->vertices[x]);
		while(index(G->vertices[x]) != -1){

			int y = get(G->vertices[x]);

			if(G->color[y] == 'w'){

				G->parent[y] = x;
				visit(G, y, time, S);

			}

			moveNext(G->vertices[x]);
		}
	}
	G->color[x] ='b';

	G->fin[x] = ++(*time);
	prepend(S, x);

}


// DFS()
// Runs the DFS algorithm on the Graph G and list S which contains a topological sort.
// Pre: length(S) == getOrder(G);
void DFS(Graph G, List S){

	if( G == NULL ){

		printf("Graph Error: Calling DFS on NULL Graph reference.");
		exit(1);

	}

	if( length(S) == getOrder(G) ){

		for(int i = 1; i<=getOrder(G);i++){

			G->color[i] = 'w';
			G->parent[i] = NIL;
			G->disc[i] = UNDEF;
			G->fin[i] = UNDEF;

		}

		int time = 0;
		moveFront(S);
		for(int i = 1; i<= getOrder(G); i++){
			int x = get(S);

			moveNext(S);

			if(G->color[x] == 'w'){

				visit(G, x, &time, S);

			}
		}

		for(int i = 1; i<=getOrder(G); i++)
			deleteBack(S);
	}

	else{

		printf("Graph Error: DFS() prerequisites not met.");
		exit(1);

	}

}


// Other Operations----------------------------------------------------------


// transpose()
// Returns a new graph reference that is the transpose of Graph G.
Graph transpose(Graph G){

	if( G == NULL){

		printf("Graph Error: Calling transpose() on NULL graph reference");
		exit(1);

	}


	Graph H = newGraph(getOrder(G));

	for(int i = 1; i<= getOrder(G); i++){

		if(length(G->vertices[i]) > 0){

			moveFront(G->vertices[i]);

			while( index(G->vertices[i]) != -1 ){

				addArc(H, get(G->vertices[i]), i);
				moveNext(G->vertices[i]);

			}
		}

	}

	return H;
}

Graph copyGraph(Graph G){

	if (G == NULL){

		printf("Graph Error: Calling copyGraph on NULL graph reference.");
		exit(1);

	}

	Graph H = newGraph(getOrder(G));

	for(int i = 1; i <= getOrder(G); i++){

		if(length(G->vertices[i]) > 0){

			H->vertices[i] = copyList(G->vertices[i]);

		}

	}

	return H;
}




// printGraph()
// prints the adjacency list represnetaion of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){

	for(int i=  1; i<=getOrder(G); i++){

		fprintf(out,"%i: ", i);
		printList(out, G->vertices[i]);

		fprintf(out,"\n");
	}
} 



