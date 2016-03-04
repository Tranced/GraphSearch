
/** 
Graph.h
By Terence Yang
thyang@ucsc.edu
CMPS 101 
-A Graph module to implement Depth First Search
PA 5
**/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"

#define UNDEF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3

/*** Exported Type ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access Functions ***/
int getOrder(Graph G);
int getSize(Graph G);
// int getSource(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// int getDist(Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// void getPath(List L, Graph G, int u);

/*** Manipulation Procedures **/
//void makeNull(Graph G);
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
//void BFS(Graph G, int s);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other Operations **/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

/** 
--------helper functions--------- 
void orderedInsert(List L, int u); 
void DFS_Visit(Graph G, List S, int u);
**/

#endif
