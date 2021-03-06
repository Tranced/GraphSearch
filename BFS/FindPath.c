/** 
FindPath.c
By Terence Yang
thyang@ucsc.edu
CMPS 101 
PA 4
**/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

#define MAXLEN 256

int main (int argc, char* argv[])
{
  // check command line for correct number of inputs
  if( argc != 3)
  {
    printf("Usage: %s <input file> <output file> \n", argv[0]);
    exit(1);
  }

  FILE *in, *out;
  char line[MAXLEN];

  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  if(in == NULL)
  {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if(out == NULL)
  {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  //Read First Line
  fgets(line, MAXLEN, in);
  int graphOrder, u, v, dist;
  sscanf(line, "%d", &graphOrder); // Get token graphOrder
  Graph G = newGraph(graphOrder); // Create new Graph

  // get initial graph
  while(fgets(line,MAXLEN,in) != NULL)
  {
    sscanf(line, "%d %d", &u, &v);
    if (u == 0 && v == 0) break;
    addEdge(G, u, v);
  }

  List L; 
  L = newList();
  printGraph(out, G); // print initial graph
  
  while(fgets(line,MAXLEN,in) != NULL)
  {
    sscanf(line, "%d %d", &u, &v);
    if(u == 0 && v == 0) break;
    fprintf(out, "\n");

    BFS(G, u); // BFS with first vertex found as source

    dist = getDist(G, v);

    if (dist == -1)
    { fprintf(out, "The distance from %d to %d is infinity\n ", u, v); }

    else
    { fprintf(out, "the distance from %d to %d is : %d\n", u, v, dist); }

    getPath(L, G, v); 

    if( front(L) == -2 ) // if getPath returns NIL
    { fprintf(out, "No %d-%d path exists", u, v); }
    
    else
    {
      fprintf(out, "A shortest %d-%d path is ", u, v);
      printList(out, L);
    }
    clear(L);
  }

  freeList(&L);
  freeGraph(&G);
  fclose(in);
  fclose(out);
  return(0);
}

