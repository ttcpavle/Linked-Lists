# Doubly circular linked list with header

`Circular_Header_Doubly_LinkedList_.c` is a general example of doubly circular linked list with header and basic operations like adding or deleting elements, freeing list etc.
User can manipulate list elements through console interface. Header of list is different than other nodes and it can hold any additional information
about linked list, not just number of elements as shown in example. While doubly circular linked list takes up more space, it also allows us
direct access to tail of the list (through header) and traversing list in both directions. Note that in this example a pointer to list (`node* head`)
is a global variable thus it is not passed as function argument.
# Polynomial as linked list

In `Polynomials.c` , polynomials are stored in singly circular linked list with header. This representation is very practical and allows us to
efficiently do operations like polynomial addition, substraction and multiplication. Function `SortedInsert()` adds new element to polynomial
and at the same time makes sure polynomial is sorted (which is needed for other functions to work properly). 
Time complexity for adding and subtracting two polynomials, each with sizes m and n respectively, is `O(m + n)`. Time complexity for polynomial multiplication is `O(m * n)`. Header of linked list is same type of struct node and exp is set to -1 which is one way to mark end of list.
