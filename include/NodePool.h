#ifndef NODEPOOL_H
#define NODEPOOL_H

#include <iostream>
using namespace std;

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
    int newNode();
    void deleteNode(int index);
    NodeType<T>* getPool() const;
    int getFree() const;

private:
    NodeType<T> arrNode[NUM_NODES];
    int free;
    void initializePool();
};

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
NodeType<T>* NodePool<T>::getPool() const {
    return arrNode;
}

template<typename T>
int NodePool<T>::getFree() const {
    return free;
}

#endif