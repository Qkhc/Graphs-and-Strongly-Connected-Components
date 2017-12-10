//-----------------------------------------------------------------------------
//
// GraphTest.c
//
// Robert Mushkot
// rmushkot
// 1543374 
// pa5
//  
// This is a test file used to test the functions of the Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	Graph H = newGraph(8);
	addArc(H,1,2);
	addArc(H,2,3);
	addArc(H,2,5);
	addArc(H,2,6);
	addArc(H,3,4);
	addArc(H,3,7);
	addArc(H,4,3);
	addArc(H,4,8);
	addArc(H,5,1);
	addArc(H,5,6);
	addArc(H,6,7);
	addArc(H,7,6);
	addArc(H,7,8);
	addArc(H,8,8);



	printGraph(stdout, H);
	printf("Order %i\n",getOrder(H));;
	printf("Size of H: %i\n", getSize(H));


	List S = newList();
	for(int i = 1; i<=getOrder(H); i++){
		append(S, i);
	}

	DFS(H,S);
	printf("\nD: F:\n");

	for(int i = 1; i<=getOrder(H); i++)
		printf("%d %d\n", getDiscover(H,i), getFinish(H,i)); 


	Graph G = transpose(H);

	printf("\nTranspose of H = \n");
	printGraph(stdout, G);
	printf("\nTopologcial sort: \n");
	printList(stdout, S);

	DFS(G,S);

	printf("\n");
	printList(stdout, S);

	moveFront(S); 
	for(int i=1; i<=length(S); i++){

		printf("\n%d: %d", get(S), getParent(G,get(S)));
		moveNext(S);

	}

	List L = newList();

	moveBack(S);

	while(index(S) != -1){

		while( getParent(G, get(S)) != -1){

			prepend(L, get(S));
			movePrev(S);

		}

		prepend(L, get(S));
		printf("\n");
		printList(stdout, L);
		clear(L);
		movePrev(S);
	}

	// Free objects 
	freeGraph(&G);
	freeList(&S);
	freeList(&L);
	freeGraph(&H);
	printf("\n");
	return(0);
}
