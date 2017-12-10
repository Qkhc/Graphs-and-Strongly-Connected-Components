//----------------------------------
// Graph.h                         |
// Header file for Graph ADT       |
//                                 |
// Robert Mushkot                  |
// rmushkot                        |
// 1543374                         |
// pa5                             |
// ---------------------------------


#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"

#define UNDEF -10
#define NIL -1


// Exported Type ----------------------------------------------------------------

typedef struct GraphObj* Graph;


// Constructors - Destructors-----------------------------------------------------

// newGraph()
// returns a reference to new empty Graph object 
Graph newGraph(int n);

// freeGraph()
// frees all heap mempry associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG);


// Access funtions---------------------------------------------------------------

// getOrder()
// Returns the field value of order.
int getOrder(Graph G);


// getSize()
// Returns the field value of size.
int getSize(Graph G);


// getParent()
// Returns the parent of vertex u in the Breadth-First tree created in BFS().
// Pre: 1<= u <= getOrder(G)
int getParent(Graph G, int u);


// getDiscover()
// Returns the discover time of the given vertex.
// Pre: 1<=u<=GetOrder(G)
int getDiscover(Graph G, int u);


// getFinish()
// Returns the finish time of the given vertex.
// Pre: 1<=u<=getOrder(G)
int getFinish(Graph G, int u);


// Manipulation procedures--------------------------------------------------


// addEdge()
// inserts a new edge joining u to v: u added to adjacency List of v and v to the adjacnecy list of u.
// Pre: 1 <= u,v <= getOrder()
void addEdge(Graph G, int u, int v);


// addArc()
// inserts a new directed edge from u to v v is added to the adjacency List of u
// Pre: 1 <= u,v <= getOrder(G)
void addArc(Graph G, int u, int v);


// DFS()
// Runs the DFS algorithm on the Graph G with List S that stores the finish times in decreasing order.
// Pre: length(S) == n
void DFS(Graph G, List S);


// Other Operations----------------------------------------------------------


// transpose()
// returns a new graph that is a transpose of the given Graph.
Graph transpose(Graph G);


// copyGraph()
// returns a new graph that is a copy of the given Graph.
Graph copyGraph(Graph G);


// printGraph()
// prints the adjacency list represnetaion of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);


#endif

