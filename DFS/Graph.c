/** 
Graph Implementation using Doubly Linked List
Graph.c
By Terence Yang
thyang@ucsc.edu
CMPS 101 
PA 5
**/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

void orderedInsert(List L, int u); 
void DFS_Visit(Graph G, List S, int u);

/*** Constructors-Destructors ***/

// Graph Object struct
typedef struct GraphObj
{
  int order, time, size;
  int *color, *disc, *fin, *parent;
  List *neighbor;
} GraphObj;

// newGraph()
// Graph constructor
// n >= 0
Graph newGraph(int n)
{
  if(n < 0)
  {
    printf("Graph Error: in constructor, n is a negative value\n");
    exit(1);
  }

  Graph G = malloc(sizeof(GraphObj)); // Graph container

  // No source/order/size
  G->order = n;
  G->size = 0;
  G->time = 0;

  // creating arrays
  G->color = calloc(n+1,sizeof(int));
  G->parent = calloc(n+1, sizeof(int));
  G->disc = calloc(n+1, sizeof(int));
  G->fin = calloc(n+1, sizeof(int));
  G->neighbor = calloc(n+1, sizeof(List));

  // creating empty graph nodes
  int i;
  for(i = 1; i <= n; i++)
  {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->disc[i] = UNDEF;
    G->fin[i] = UNDEF;
    G->neighbor[i] = newList();
  }
  return G;
}

// freeGraph() deletes graphObj
void freeGraph(Graph* pG)
{
  if(pG != NULL && *pG != NULL)
  {
    // clear int arrays
    free((*pG)->color);
    free((*pG)->disc);
    free((*pG)->fin);
    free((*pG)->parent);

    //clear array of List
    int i;
    for(i = 1; i<=(*pG)->order; i++)
    { freeList(&(*pG)->neighbor[i]); }
  }

  // free graph pointer
  free(*pG);
  *pG = NULL;
}


/*** Access Functions ***/

// getOrder()
// Pre: Graph Pointer is not null
// Post: returns an integer that is the Order of Graph 
int getOrder(Graph G)
{
  if(G == NULL)
  {
    printf("Graph Error: in getOrder(), NULL graph.\n");
    exit(1);
  }
  return(G->order);
}

// getSize()
// Pre: Graph Pointer is not null
// Post: returns an integer that is the size of Graph 
int getSize(Graph G)
{
  if(G == NULL)
  {
    printf("Graph Error: in getSize(), NULL graph.\n");
    exit(1);
  }
  return(G->size);
}

/** getSource()
 Pre: Graph Pointer is not null
 Post: returns an integer that is the source of a tree in the graph
int getSource(Graph G)
{
  if(G == NULL)
  {
    printf("Graph Error: in getSource(), NULL graph.\n");
    exit(1);
  }
  return(G->source);
}**/

// getParent()
// Pre: Graph Pointer is not null. 
// u cannot be < 1 || > order
// Post: returns integer parent of the node u in the graph
int getParent(Graph G, int u)
{
  if(G == NULL)
  {
    printf("Graph Error: in getParent(), NULL graph.\n");
    exit(1);
  }
  if(u < 1 || u > G->order)
  {
    printf("Error in getParent(): u is not within bounds\n");
    exit(1);
  }
  return G->parent[u];
}

/** getDist()
 Pre: Graph Pointer is not null.
 u cannot be < 1 || > order.
 source is not NIL
 Post: returns integer that is the distance between source and u
int getDist(Graph G, int u)
{
  if(G == NULL)
  {
    printf("Graph Error: in getDist(), NULL graph.\n");
    exit(1);
  }
  if(u < 1 || u > G->order)
  {
    printf("Error in getDist(): u is not within bounds\n");
    exit(1);
  }
  if(G->source == NIL)
  {
    printf("Error in getDist(): source is NIL\n");
    exit(1);
  }
  return G->dist[u];
}**/


/** getPath()
 Pre: Graph Pointer is not null.
 u cannot be < 1 || > order.
 source is not NIL.
 Post: returns path between u and source
void getPath(List L, Graph G, int u)
{
  if(G == NULL)
  {
    printf("Graph Error: in getPath(), NULL graph.\n");
    exit(1);
  }
  if(u < 1 || u > G->order)
  {
    printf("Error in getPath(): u is not within bounds.\n");
    exit(1);
  }
  if(G->source == NIL)
  {
    printf("Error in getPath(): source is NIL.\n");
    exit(1);
  }

  // Treat list as a Queue.
  // Case 1: u is source.
  if( u == G->source) { append(L,G->source); }
  // Case 2: parent of u is NIL.
  else if(G->parent[u] == NIL) { append(L,NIL); }
  // Case 3: path is normal.
  else
  {
    getPath(L,G,G->parent[u]); // recursively go trace back the path.
    append(L,u);
  }
} **/

// getDiscover()
// pre: G is not NULL
// u cannot be < 1 || > order.
// post: returns an integer that is the time of vertex u's discovery
int getDiscover(Graph G, int u)
{
  if(G == NULL)
  {
    printf("Graph Error: in getParent(), NULL graph.\n");
    exit(1);
  }
  if(u < 1 || u > G->order)
  {
    printf("Error in getParent(): u is not within bounds\n");
    exit(1);
  }
  return G->disc[u];
}

// getFinish()
// pre: G is not NULL
// u cannot be < 1 || > order.
// post: returns an integer that is the time of vertex u's finish
int getFinish(Graph G, int u)
{
  if(G == NULL)
  {
    printf("Graph Error: in getParent(), NULL graph.\n");
    exit(1);
  }
  if(u < 1 || u > G->order)
  {
    printf("Error in getParent(): u is not within bounds\n");
    exit(1);
  }
  return G->fin[u];
}

/*** Manipulation Procedures **/

/** makeNull()
 Pre: G is not NULL
 Post: Graph G is clear.
void makeNull(Graph G)
{
  if(G == NULL)
  {
    printf("Graph Error: in makeNull(), NULL graph.\n");
    exit(1);
  }
  int i;
  for(i = 1; i<=(G->order); i++)
  {  clear(G->neighbor[i]); }
}**/

// orderedInsert()
// Pre: none because other functions check it out
// Post: inserts new vertex into adjacency list in order
void orderedInsert(List L, int u)
{
  if(length(L) == 0)
  { 
    append(L, u); // Case 0: there are no members in L
    return;
  }

  int check;
  for(moveFront(L); index(L) >= 0; moveNext(L))
  {
    check = get(L);
    if(index(L) == 0 && u < check) // Case 1: u is less than first item in list
    {
      prepend(L, u);
      break;
    }
    if(u < check) // Case 2: Item is less than any other items
    {
      insertBefore(L, u);
      break;
    }

    if(check == back(L) && u > check) //Case 3: u is bigger than all items in list
    { 
      append(L, u);
      break;
    }
  }
}
// addEdge()
// Pre: G is not NULL
// v & u cannot be ( < 1 || > order )
// Post: adds "edge" or adjacency to List in Graph ADT
void addEdge(Graph G, int u, int v)
{
  if(G == NULL)
  {
    printf("Graph Error: in addEdge(), NULL graph.\n");
    exit(1);
  }
  if(u < 1 || u > G->order)
  {
    printf("Error in addEdge(): u is not within bounds.\n");
    exit(1);
  }
  if(v < 1 || v > G->order)
  {
    printf("Error in addEdge(): v is not within bounds.\n");
    exit(1);
  }

  // increment size
  G->size++;
  // add u and v to each others adjacency lists
  orderedInsert((G->neighbor[u]),v);
  orderedInsert((G->neighbor[v]),u);
}

// addArc()
// Pre: G is not NULL
// v & u cannot be ( < 1 || > order )
// Post: adds "Arc" or one-way adjacency to List in Graph ADT
void addArc(Graph G, int u, int v)
{
  if(G == NULL)
  {
    printf("Graph Error: in addEdge(), NULL graph.\n");
    exit(1);
  }
  if(u < 1 || u > G->order)
  {
    printf("Error in addEdge(): u is not within bounds.\n");
    exit(1);
  }
  if(v < 1 || v > G->order)
  {
    printf("Error in addEdge(): v is not within bounds.\n");
    exit(1);
  }

  // add v to u's adjacency list. u goes to v.
  orderedInsert((G->neighbor[u]),v);
}

/** BFS()
 Pre: G is not NULL
 s cannot be ( < 1 || > order )
 Post: finds distance/parent of each "edge" from s
void BFS(Graph G, int s)
{
  if(G == NULL)
  {
    printf("Graph Error: in BFS(), NULL graph.\n");
    exit(1);
  }
  if(s < 1 || s > G->order)
  {
    printf("Error in BFS(): s is not within bounds.\n");
    exit(1);
  }



  // reset int arrays that keep track of BFS
  int i;
  for(i = 1; i<=(G->order); i++)
  {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->dist[i] = INF;
  } 

  // start BFS with default values at source
  G->color[s] = GRAY;
  G->parent[s] = NIL;
  G->dist[s] = 0;
  G->source = s;

  // initializing List Q
  List Q;
  Q = newList();
  append(Q,s);

  // loop in BGS
  while(length(Q) != 0)
  { 
    i = front(Q); // treating Q as a Queue
    deleteFront(Q);

    int v = 0;
    if(length(G->neighbor[i]) != 0) // There is an adjacency matrix
    {
      moveFront(G->neighbor[i]);  // start at front of adjacency matrix
      while(index(G->neighbor[i]) != length(G->neighbor[i])-1) // Move until end of matrix.(For all nodes)
      {
        v = get(G->neighbor[i]); // go through adjacency matrix

        if(G->color[v] == WHITE) // Visited
        {
          G->color[v] = GRAY;
          G->parent[v] = i;
          G->dist[v] = G->dist[i] + 1;
          append(Q,v); // Add new neighbors to visit in Q
        }

        moveNext(G->neighbor[i]);
       }
      
       G->color[i] = BLACK; // u is visited
    }
  }

  freeList(&Q); // Q is not needed anymore
}**/

// DFS()
// Depth First Search Implementation
// Where List S is a stack containing all members of G
// pre: G != NULL and 
void DFS(Graph G, List S) 
{
  if(G == NULL)
  {
    printf("Graph Error: in getDist(), NULL graph.\n");
    exit(1);
  }

  if(length(S) != getOrder(G))
  {
    printf("in DFS(): List size != Graph Order");
  }

  int i, u, l;
  l = length(S);
  // initialize vertexes in G
  for(i = 1; i <= getOrder(G); i++)
  {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
  }

  int j = 1;
  G->time = 0;
  // Visit all nodes in G in the order specified by Stack S
  moveFront(S);
  while(index(S) != -1 && j <= getOrder(G)) 
  {
    u = get(S);
    if(G->color[u] == WHITE) // if discovered, visit.
    {
      DFS_Visit(G,S,u);
    }
    moveNext(S);
    j++;
  }
  //printf("\n");
  //printList(stderr, S);
  while(l > 0)
  {
    deleteBack(S); //"popping the stack"
    l--;
  } 
}

// DFS_VISIT()
// The Visit part of the DFS pseudocode
void DFS_Visit(Graph G, List S, int u)
{
  G->time++;
  G->disc[u] = G->time; //discovery of u is time
  G->color[u] = GRAY;
  int v;


  // for all neighbors in adjacency list.
  for(moveFront(G->neighbor[u]); index(G->neighbor[u]) >= 0 ; moveNext(G->neighbor[u]))
  {
    if(index(G->neighbor[u]) == -1) break;
    v = get(G->neighbor[u]);
    if(G->color[v] == WHITE) //if first node v in adjacency list is undiscovered
    {
      G->parent[v] = u; // the parent of v is u
      DFS_Visit(G,S,v); // Visit new node V
    }
  }

  G->color[u] = BLACK; // u is visited
  G->time++; // increment time again
  G->fin[u] = G->time; // make finishing time equal to newly incremented time
  prepend(S,u);
}



/*** Other Operations **/

// transpose()
// Uses a double for loop to transpose Adjacency List Matrix
Graph transpose(Graph G)
{
  int i, u;
  i = getOrder(G);
  Graph T = newGraph(i);

  for(i = getOrder(G); i >= 1; i--) // for the amount of vertexes in G
  {
    if(length(G->neighbor[i]) != 0)
    {
      // for the neighbors of i
      for(moveFront(G->neighbor[i]); index(G->neighbor[i]) >= 0 /**!= length(G->neightbor[i])**/; moveNext(G->neighbor[i]))
      {
        u = get(G->neighbor[i]);
        orderedInsert(T->neighbor[u], i); // put i in neighbor u's adjacency list in transpose.
      }
    }
  }

  return T;
}

// copyGraph
// copies Graph G and returns another copy C.
Graph copyGraph(Graph G)
{
  int i;
  i = getOrder(G);
  Graph C = newGraph(i);

  for(i = getOrder(G); i >= 1; i--) // for the amount of vertexes in G
  {
    if(length(G->neighbor[i]) != 0)
    {
      C->neighbor[i] = copyList(G->neighbor[i]); // copy list.
    }
  }

  return C;
}


// printGraph()
// Pre: out and Graph must not be NULL
// Post: prints Graph to out.
void printGraph(FILE* out, Graph G)
{
  if(out == NULL || G == NULL)
  {
    printf("in printGraph: Out or G are NULL\n");
    return;
  }

  int i;


  for(i = 1; i < getOrder(G)+1; i++)
  {
    fprintf(out, "%d: ", i);

    if(length(G->neighbor[i]) != 0)
    printList(out, G->neighbor[i]);

    fprintf(out, "\n");
  }
}

