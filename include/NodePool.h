#ifndef NODEPOOL_H
#define NODEPOOL_H

#include <iostream>
using namespace std;
/*-- NodePool.h ------------------------------------------------------------
This header file defines a NodePool class template for managing an array-based
storage pool of nodes used in linked list implementation. The type parameter T
represents the data type stored in each node.

Key Features:

Eliminates dynamic memory operations by using a fixed-size array

Maintains a free list of available nodes

Provides efficient node allocation and deallocation

Basic Operations:
newNode: Allocates a node from the free list
deleteNode: Returns a node to the free list
getPool: Provides access to the node array
getFree: Returns the head of the free list

Constants:
NULL_VALUE: Special value (-1) representing null/nonexistent nodes
NUM_NODES: Fixed size of the storage pool (2048 nodes)

Note: The pool automatically initializes all nodes in a linked free list
upon construction.
--------------------------------------------------------------------------*/
const int NULL_VALUE = -1;
const int NUM_NODES = 2048;

template<typename T>
struct NodeType {
    T data;
    int next;
};

template<typename T>
class NodePool {
public:
    NodePool();
    /*-----------------------------------------------------------------------
    Constructs a NodePool object.

    Precondition: None.
    Postcondition: The node pool is initialized with all nodes linked in
    a free list, and free points to the first node (0).
    -----------------------------------------------------------------------*/
    int newNode();
    /*-----------------------------------------------------------------------
    Allocates a node from the free list.

    Precondition: There should be available nodes in the pool.
    Postcondition: Returns index of allocated node, which is removed from
    free list. The node's next is set to NULL_VALUE.
    If no nodes available, outputs error message.
    -----------------------------------------------------------------------*/
    void deleteNode(int index);
    /*-----------------------------------------------------------------------
    Returns a node to the free list.

    Precondition: index must be valid (0 <= index < NUM_NODES).
    Postcondition: The node at index is added to beginning of free list.
    If index is invalid, outputs error message.
    -----------------------------------------------------------------------*/
    NodeType<T>* getPool() ;
    /*-----------------------------------------------------------------------
    Provides access to the node array.

    Precondition: None.
    Postcondition: Returns pointer to the node array.
    -----------------------------------------------------------------------*/
    const NodeType<T>* readPool() const;
    /*-----------------------------------------------------------------------
    Read Only for the node array.

    Precondition: None.
    Postcondition: Returns pointer to the node array.
    -----------------------------------------------------------------------*/
    int getFree() const;
    /*-----------------------------------------------------------------------
    Gets the current free list head.

    Precondition: None.
    Postcondition: Returns index of first free node (NULL_VALUE if empty).
    -----------------------------------------------------------------------*/

private:
    NodeType<T> arrNode[NUM_NODES];
    int free;
    void initializePool();
};
//implementation
template<typename T>
NodePool<T>::NodePool() {
    initializePool();
}

template<typename T>
void NodePool<T>::initializePool() {
    for(int i = 0; i < NUM_NODES - 1; i++) {
        arrNode[i].next = i + 1;
    }
    arrNode[NUM_NODES - 1].next = NULL_VALUE;
    free = 0;
}

template<typename T>
int NodePool<T>::newNode() {
    if(free == NULL_VALUE) {
        cerr << "No available space in the list";
        return NULL_VALUE;
    }
    int index = free;
    free = arrNode[free].next;
    arrNode[index].next = NULL_VALUE;
    return index;
}

template<typename T>
void NodePool<T>::deleteNode(int index) {
    if (index < 0 || index >= NUM_NODES)
        cerr << "NodePool: deleteNode index out of range";
    arrNode[index].next = free;
    free = index;
}

template<typename T>
NodeType<T>* NodePool<T>::getPool() {
    return arrNode;
}

template<typename T>
const NodeType<T>* NodePool<T>::readPool() const {
    return arrNode;
}


template<typename T>
int NodePool<T>::getFree() const {
    return free;
}

#endif