//----------------------------------
// FindComponents.c                |
//				   |
// Takes input file of vertices    |
// and finds strongly connected    |
// components of a graph           |
// 				   |
// Robert Mushkot                  |
// rmushkot                        |
// 1543374                         |
// pa5                             |
// ---------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main(int argc, char* argv[]){

	int n=0; 
	FILE *in, *out;
	char line[100];


	if( argc != 3){

		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);

	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if( in == NULL){

		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);

	}

	if(out == NULL){

		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);

	}

	fgets(line, sizeof(line), in);
	sscanf(line, "%d", &n);


	Graph G = newGraph(n);

	while(fgets(line,sizeof(line), in) != NULL){ // Goes thrugh file and adds edges to the graph. 

		int v1 = 0;
		int v2 = 0;

		sscanf(line, "%d %d", &v1, &v2);


		if(v1 == 0 && v2 == 0) break; // Break point for the file is "0 0" this input stops the program. 

		addArc(G,v1,v2);

	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out,G);
	fprintf(out, "\n");

	List S = newList();

	for(int i = 1; i<=n; i++){

		append(S, i);

	}

	DFS(G, S);

	Graph H = transpose(G);
	DFS(H, S);

	List L = newList();

	moveFront(S);
	int c = 0;

	while(index(S) != -1){ //gets the total number of components.

		if(getParent(H, get(S)) == -1)
			c++;

		moveNext(S);

	}

	fprintf(out, "G contains %d strongly connected components:\n", c);
	moveBack(S);

	c = 0;

	while(index(S) != -1){ // Traverse the list and finds the connected components. If the vertex has no parent prepend it to the list. 

		while(getParent(H, get(S)) != -1){

			prepend(L, get(S));
			movePrev(S);

		}

		c++;
		fprintf(out, "Component %d: ", c); 	

		prepend(L, get(S));
		printList(out, L);

		fprintf(out,"\n");
		clear(L);

		movePrev(S);

	}

	fprintf(out, "\n");

	//Free Objects
	freeList(&L);
	freeList(&S);
	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeGraph(&H);


	return 0;
}
