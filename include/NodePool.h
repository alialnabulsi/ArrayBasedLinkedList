// NodePool.h

/**
 * @file NodePool.h
 * @brief Implementation of a node pool for array-based linked list management
 *
 * This file contains the NodeType structure and NodePool class which together
 * provide a pool of nodes stored in an array. The pool manages allocation and
 * deallocation of nodes without dynamic memory operations.
 *
 * The NodePool maintains:
 * - An array of NodeType structs (storage pool)
 * - A free list to track available nodes
 * - Methods to allocate (newNode) and release (deleteNode) nodes
 */

#include <iostream>
#ifndef NODEPOOL_H
#define NODEPOOL_H

using namespace std;

const int NULL_VALUE = -1;  // Represents "no node"
const int NUM_NODES = 2048; // Size of the storage pool

template<typename T>
struct NodeType {
    T data;
    int next; // index of the next node, or NULL_VALUE
};

template<typename T>
class NodePool {
public:
    /**
     * @brief Constructs a NodePool with initialized free list
     */
    NodePool();

    /**
     * @brief Allocates a new node from the free list
     * @return Index of the allocated node
     * @pre There should be available nodes in the pool
     * @post The node is removed from free list and ready for use
     */
    int newNode();

    /**
     * @brief Returns a node to the free list
     * @param index Index of the node to deallocate
     * @pre index must be valid (0 <= index < NUM_NODES)
     * @post Node is added to the free list for reuse
     */
    void deleteNode(int index);

    /**
     * @brief Gets the node pool array
     * @return Pointer to the node array
     */
    NodeType<T>* getPool() const;

    /**
     * @brief Gets the current free list head
     * @return Index of the first free node
     */
    int getFree() const;

private:
    NodeType<T> arrNode[NUM_NODES];
    int free;

    /**
     * @brief Initializes the free list by linking all nodes
     * @post All nodes are linked in sequence, free points to first node
     */
    void initializePool();
};



template<typename ElementType>
NodePool<ElementType>::NodePool(){
    intializePool();
  }

template<typename ElementType>
void NodePool<ElementType>::intializePool(){
  for(int i = 0; i < NUM_NODES - 1; i++){
    arrNode[i].next=i+1;
    }S
  arrNode[NUM_NODES - 1] = NULL_VALUE;
  free = 0;
  }

template<typename ElementType>
int NodePool<ElementType>::newNode(){
   if(free == NULL_VALUE){
     cerr << "No availiable space in the list";
     }
   int index = free;
   free = arrNode[free].next;
   arrNode[index].next = NULL_VALUE;

    return index;
  }

/*template<typename ElementType>
void NodePool<ElementType>::deleteNode(){

}*/

template<typename ElementType>
void NodePool<ElementType>::deleteNode(int index) {
    if (index < 0 || index >= NUM_NODES)
        cerr << ("NodePool: deleteNode index out of range");
    pool[index].next = free;
    free = index;
}
template<typename ElementType>
NodeType* NodePool<ElementType>::getPool() const{
    return pool;
}

template<typename ElementType>
int NodePool<ElementType>::getFree() const{
    return free;
}


#endif
