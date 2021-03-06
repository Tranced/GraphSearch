
/** 
Graph.h
By Terence Yang
thyang@ucsc.edu
CMPS 101 
PA 4
**/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"

/*** Exported Type ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access Functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/*** Manipulation Procedures **/
void makeNull(Graph G);
void orderedInsert(List L, int u); //helper function
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other Operations **/
void printGraph(FILE* out, Graph G);

#endif
