#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type -----------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to empty List object.
List newList(void);

// freeList()
// Frees all memory associated with List *pL, and sets *pL to NULL.
// Function deletes list.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the length of List L.
// Returns -1 if List is undefined.
int length(List L);

// index()
// Returns the index of cursor on List L.
// Returns -1 if Cursor is undefined.
int index(List L);

// front()
// Returns the value stored in the node at the beginning of List L.
// Pre: length() > 0
int front(List L);

// back()
// Returns the value stored in the last node of List L.
// Pre: length() > 0
int back(List L);

// get()
// Returns current value of cursor.
// Pre: length() > 0 and index() >= 0
int get(List L);

// equals()
// returns true(1) if List A is identical to List B, false(0) otherwise.
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

// clear()
// resets list back to empty state.
void clear(List L);

// moveFront()
// moves cursor to first node in the List.
// Pre: length() > 0
void moveFront(List L);

// moveBack()
// moves cursor to the last node in the List.
// Pre: length() > 0
void moveBack(List L);

// movePrev()
// moves cursor once to the left in the List.
// Pre: length() > 0 and index() >= 0 
// Will make cursor undefined if already at last node.
void movePrev(List L);

// moveNext()
// moves cursor once to the right in the List.
// Pre: length() > 0
// Will make cursor undefined if already at first node.
void moveNext(List L);

// prepend()
// attaches node before Front node.
// begins new list if L is undefined.
void prepend(List L, int data);

// append()
// attaches node after Back node.
// begins new list if L is undefined.
void append(List L, int data);

// insertBefore()
// attaches node before cursor element.
// Pre: length() > 0, index >= 0
void insertBefore(List L, int data);

// insertAfter()
// attaches node after cursor element.
// Pre: length() > 0, index >= 0
void insertAfter(List L, int data);

// deleteFront()
// deletes node at the beginning of the List.
// Pre: length() > 0
void deleteFront(List L);

// deleteBack()
// deletes the last node of the List.
// Pre: length() > 0
void deleteBack(List L);

// delete()
// deletes node cursor is pointing to.
// Pre: length() > 0, index() >= 0
void delete(List L);

// Other operations -----------------------------------------------------------

// printList()
// prints list to a file
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L);

#endif
