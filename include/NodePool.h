// NodePool.h

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
    NodePool();
    int newNode();
    void deleteNode(int index);

private:
    NodeType<T> arrNode[NUM_NODES];
    int free;
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

template<typename ElementType>
void NodePool<ElementType>::deleteNode(){

}

template<typename ElementType>
void NodePool<ElementType>::deleteNode(int index) {
    if (index < 0 || index >= NUM_NODES)
        cerr << ("NodePool: deleteNode index out of range");
    pool[index].next = free;
    free = index;
}


#endif
