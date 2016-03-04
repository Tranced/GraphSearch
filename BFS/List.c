/** 
Doubly Linked List Implementation in C
By Terence Yang
CMPS 101 **/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs -------------------------------------------------------------------

// Private Node Object type
typedef struct NodeObj
{
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj
{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// returns reference to new Node object. Initializes next, back, and data fields.
// Private.
Node newNode(int node_data)
{
  Node N = malloc(sizeof(NodeObj));
  N->data = node_data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}


// freeNode()
// frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
  if( pN!=NULL && *pN!=NULL)
  {
    free(*pN);
    *pN = NULL;
  }
}


// newList()
// Returns reference to empty List object.
List newList(void)
{
  List L;
  L = malloc(sizeof(ListObj));
  L->cursor = L->front = L->back = NULL;
  L->length = 0;
  L->index = -1;

  return(L);
}


// freeList()
// Frees all memory associated with List *pL, and sets *pL to NULL.
// Function deletes list.
void freeList(List* pL)
{
  clear(*pL);
  free(*pL);
  *pL = NULL;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of List L.
// Returns -1 if List is undefined.
int length(List L)
{
  if(L==NULL)
  {
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return(L->length);
}


// index()
// Returns the index of cursor on List L.
// Returns -1 if Cursor is undefined.
int index(List L)
{
  if(L->cursor==NULL)
  {
    return(-1);
  }
  else
  {
    return(L->index);
  }
}


// front()
// Returns the value stored in the node at the beginning of List L.
// Pre: length() > 0
int front(List L)
{
  if(L->length == 0)
  {
    printf("List Error: calling front on an empty List\n");
    exit(1);
  }
  return(L->front->data);
}

  
// back()
// Returns the value stored in the last node of List L.
// Pre: length() > 0
int back(List L)
{
  if(L->length == 0)
  {
    printf("List Error: calling back on an empty List\n");
    exit(1);
  }
  return(L->back->data);
}

// get()
// Returns current value of cursor.
// Pre: length() > 0 and index() >= 0
int get(List L)
{
  if(L->length > 0 && L->index > -1)
  {
    return(L->cursor->data);
  }
  else
  {
    printf("List Error: calling get() on empty list or undefined cursor");
    exit(1);
  }
  return(L->cursor->data);
}


// equals()
// returns true(1) if List A is identical to List B, false(0) otherwise.
int equals(List A, List B)
{
  if( A==NULL || B==NULL )
  {
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }

  int eq = 0;
  Node N = NULL;
  Node M = NULL;

  eq = (A->length == B->length);
  N = A->front;
  M = B->front;

  while(eq && N != NULL)
  {
    eq = ( N->data==M->data );
    N = N->next;
    M = M->next;
  }
  return eq;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// resets list back to empty state.
void clear(List L)
{
  while(L->length >= 1)
  {
    deleteFront(L);
  }
  
  L->cursor = NULL;
  L->index = -1;
}
 

// moveFront()
// moves cursor to first node in the List.
// Pre: length() > 0
void moveFront(List L)
{
  if(L->length == 0)
  { 
    printf("List Error: calling moveFront() on empty list\n");
    exit(1);
  }
  else
  {
    L->cursor = L->front;
    L->index = 0;
  }
}


// moveBack()
// moves cursor to the last node in the List.
// Pre: length() > 0
void moveBack(List L)
{
  if(L->length == 0)
  { 
    printf("List Error: calling moveBack() on empty list\n");
    exit(1);
  }
  else
  {
    L->cursor = L->back;
    L->index = L->length-1;
  }
}


// movePrev()
// moves cursor once to the left in the List.
// Pre: length() > 0 and index() >= 0 
// Will make cursor undefined if at first node.
void movePrev(List L)
{
  if(L->length == 0)
  {  
    printf("List Error: calling movePrev() on empty list\n");
    exit(1);
  }
  if(L->index == -1)
  {
    printf("List Error: calling movePrev() on undefined cursor\n");
    exit(1);
  }

  if(L->index == 0)
  {
    L->cursor = NULL;
    L->index = -1;
  }
  else
  {
    L->cursor = L->cursor->prev;
    L->index--;
  }
}  


// moveNext()
// moves cursor once to the right in the List.
// Pre: length() > 0
// Will make cursor undefined if already at last node.
void moveNext(List L)
{
  if(L->length == 0)
  { 
    printf("List Error: calling moveNext() on empty list\n");
    exit(1);
  }
  if(L->index == -1)
  {
    printf("List Error: calling moveNext() on undefined cursor\n");
    exit(1);
  }

  if(L->index == L->length)
  {
    L->cursor = NULL;
    L->index = -1;
  }
  else
  {
    L->cursor = L->cursor->next;
    L->index++;
  }
}


// prepend()
// attaches node before Front node.
// begins new list if L is undefined.
void prepend(List L, int data)
{
  if(L == NULL)
  {
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }

  Node N = newNode(data);
  if(L->length == 0) 
  { 
    L->front = L->back = N; 
    L->length++;
  }
  else
  { 
    L->front->prev = N;
    N->next = L->front; 
    L->front = N;
    L->length++;
  }
}


// append()
// attaches node after Back node.
// begins new list if L is undefined.
void append(List L, int data)
{
  if(L == NULL)
  {
    printf("List Error: calling append() on NULL List reference\n");
    exit(1);
  }

  Node N = newNode(data);

  if(L->length == 0) 
  { 
    L->front = L->back = N; 
    L->back->next = NULL;
    L->front->prev = NULL;
    L->length++;
  }
  else
  { 
    L->back->next = N;
    N->prev = L->back; 
    L->back = N;
    L->length++; 
  }

}


// insertBefore()
// attaches node before cursor element.
// Pre: length() > 0, index >= 0
void insertBefore(List L, int data)
{
  if(L == NULL)
  {
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  }

  if(L->length == 0 || L->index == -1)
  {
    printf("List Error: calling insertBefore on empty List or undefined cursor\n");
    exit(1);
  }

  Node N = newNode(data);
  Node temp;
  temp = L->cursor->prev;
  N->next = L->cursor;
  L->cursor->prev = N;
  N->prev = temp;
  temp->next = N;
  L->length++;
  L->index++;
}

    
// insertAfter()
// attaches node after cursor element.
// Pre: length() > 0, index >= 0
void insertAfter(List L, int data)
{
  Node N = newNode(data);
  Node temp;

  if(L == NULL)
  {
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  }

  if(L->length == 0 || L->index == -1)
  {
    printf("List Error: calling insertAfter on empty List or undefined cursor\n");
    exit(1);
  }
      temp = L->cursor->next;
      N->next = L->cursor->next;
      L->cursor->next = N;
      N->prev = L->cursor;
      temp->prev = N;
      L->length++;
  if(L->index-1 == L->length)
  {
    L->back = L->cursor->next;
  }
}


// deleteFront()
// deletes node at the beginning of the List.
// Pre: length() > 0
void deleteFront(List L)
{
  if(L == NULL)
  {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
  if(L->length == 0)
  {
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(1);
  }

  Node N = NULL;
  N = L->front;

  if(L->length > 1) 
  { 
    L->front = L->front->next; 
    L->front->prev = NULL;
    N->next= NULL;
  }
  else
  { 
    L->front = L->back = NULL; 
  }

  L->length--;
  freeNode(&N);
}


// deleteBack()
// deletes the last node of the List.
// Pre: length() > 0
void deleteBack(List L)
{  
  if(L == NULL)
  {
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  }
  if(L->length == 0)
  {
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(1);
  }

  Node N = NULL;
  N = L->back;

  if(L->length > 1) 
  { 
    L->back = L->back->prev; 
    L->back->next = NULL;
    N->prev= NULL;
  }
  else
  { 
    L->front = L->back = NULL; 
  }

  L->length--;
  freeNode(&N);
}

// delete()
// deletes node cursor is pointing to.
// Pre: length() > 0, index() >= 0
void delete(List L)
{
  if(L == NULL)
  {
    printf("List Error: calling delete() on NULL List reference\n");
    exit(1);
  }
  if(L->length == 0)
  {
    printf("List Error: calling delete() on an empty List\n");
    exit(1);
  }

  if(L->index == -1)
  {
    printf("List Error: calling delete() on undefined cursor\n");
    exit(1);
  }

  Node N = NULL;
  N = L->cursor;
  L->cursor->next->prev = L->cursor->prev;
  L->cursor->prev->next = L->cursor->next;
  L->cursor->next = NULL;
  L->cursor->prev = NULL;
  L->length--;
  L->index = -1;
  L->cursor = NULL;
  freeNode(&N);
}

// Other operations -----------------------------------------------------------

// printList()
// prints list to a file using cursor
void printList(FILE* out, List L)
{
  if(L == NULL)
  {
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  }
  if(out == NULL)
  {
    printf("List Error: ouput file is undefined in printList()\n");
    exit(1);
  }

  moveFront(L);
  for(moveFront(L); index(L)>=0; moveNext(L))
  {
    fprintf(out, "%d", get(L));
    fprintf(out, " ");
  }
}


// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L)
{
  List M = newList();
  Node J = NULL;

  for( J = L->front; J != NULL; J = J->next )
  {
    append(M, J->data);
  }
  return(M);
}
