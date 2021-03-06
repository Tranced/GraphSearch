
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

#define INF -1
#define NIL -2

int main(int argc, char* argv[])
{
  int n = 21;
  Graph G;
  G = newGraph(n);
  int i;

  for(i = 1; i < 10; i++)
  {
    addEdge(G, i, i+2);
    addEdge(G, i, i+10);
  }

  printGraph(stdout, G);

  for(i = 1; i < 20; i++)
  {
    addEdge(G, 20, i);
  }

  BFS(G, 1);
  List L;
  L = newList();
  i = getDist(G, 11);
  printf("\n Distance from 11 to 1 is : %d\n", i);
  getPath(L, G, 11);
  printList(stdout, L);
  clear(L);

  i = getDist(G, 19);
  printf("\n Distance from 19 to 1 is : %d\n", i);
  getPath(L, G, 19);
  printList(stdout, L);
 
  for(i = 1; i < 21; i++)
  {
  printf(" The parent of %d is : ", i);
  printf("%d\n", getParent(G,i));
  }

  BFS(G, 2);
  printf("\n Source is two\n");
  for(i = 1; i < 21; i++)
  {
  printf(" The parent of %d is : ", i);
  printf("%d\n", getParent(G,i));
  }
  
  makeNull(G);

  for(i = 1; i < 10; i++)
  {
    addArc(G, i, i+2);
    addArc(G, i, i+10);
  }

  printf("\n");
  printGraph(stdout, G);

  return(0);
}

