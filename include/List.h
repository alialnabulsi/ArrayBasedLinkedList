// List.h

#include <iostream>
#ifndef LIST_H
#define LIST_H
#include "NodePool.h"

using namespace std;

class List{
    public:
        List();
        List(const List& other);
        List& operator=(const List& other);
        ~List();
        bool isEmpty() const;
        void traverse(const function<void(const T&)>& visit) const;
        int size() const;
        int search(const T& item) const;
        void insertAtEnd(const T& item);
        void deleteAtEnd();
        void insertAtTop(const T& item);
        void deleteAtTop();
        void insertAfterPos(int pos, const T& item);
        bool delete(const T& item);
        int getFree() const;
        void sortList();
        void isSorted();
        void display() const;
    private:
        NodePool<T> pool;  // Node pool for memory management
        int first;  // First element in the list
};

template<typename ElementType>
List<ElementType>::List(): pool(), first(NULL_VALUE){

}
template<typename ElementType>
List<ElementType>::List(const List& other){

}

template<typename ElementType>
List& List<ElementType> operator=(const List& other){

}

template<typename ElementType>
List<ElementType>::~List(){

}

template<typename ElementType>
void List<ElementType>::traverse(const function<void(const T&)>& visit) const;

template<typename ElementType>
int List<ElementType>::size() const{
    int count = 0 , ptr = first;
    while(size != NULL_VALUE){
        count++;
        ptr = pool.getPool()[ptr].next;

    }
    return count;
}
template<typename ElementType>
int List<ElementType>::search(const T& item) const{
    int pos = NULL_VALUE , ptr = first;
    while(ptr != NULL_VALUE){
        if (pool.getPool()[ptr].data == item){
            pos = ptr;
        }

        ptr = pool.getPool()[ptr].next;
    }
    return pos;
}
template<typename ElementType>
void List<ElementType>::insertAtEnd(const T& item){
    int ptr = first;
    int newNodeIndex;
    while(ptr != NULL_VALUE){
        if(pool.getPool()[ptr].next == NULL_VALUE){
            newNodeIndex = pool.newNode();
            pool.getPool()[newNodeIndex].data = item;
        }
        ptr = pool.getPool()[ptr].next;
    }
}

template<typename ElementType>
void List<ElementType>::deleteAtEnd(){
    int ptr = first;
    while(ptr != NULL_VALUE){
        if(pool.getPool()[ptr].next == NULL_VALUE){
            pool.deleteNode(ptr);
        }
        ptr = pool.getPool()[ptr].next;
    }
}

template<typename ElementType>
void List<ElementType>::insertAtTop(const T& item){
    int index = pool.newNode();
    pool.getPool()[index].data = item;
    pool.getPool()[index].next = first;
    first = index;
}

template<typename ElementType>
void List<ElementType>::deleteAtTop(){
    if (isEmpty())
        cerr << ("List::deleteFront() on empty list");
    int index = first;
    first = pool.getPool()[index].next;
    pool.deleteNode(index);
}

template<typename ElementType>
void List<ElementType>::insertAfterPos(int pos, const T& item){
    if (isEmpty()) {
        cerr << ("List::insertAfter() on empty list ");
    }
    if (pos == NULL_VALUE || pos < 0 || pos >= NUM_NODES)
        cerr << ("List::insertAfter invalid position");
    int index = pool.newNode();
    pool.getPool()[index].data = item;
    int nextIndex = pool.getPool()[pos].next;
    pool.getPool()[pos].next = index;
    pool.getPool()[index].next = nextIndex;
}

template<typename ElementType>
bool List<ElementType>::delete(const T& item){
    int pos, ptr = first;
    while(ptr != NULL_VALUE){
        if(pool.getPool()[ptr].data == item){

        }
        ptr = pool.getPool()[ptr].next;
    }
    return false;
}

template<typename ElementType>
int List<ElementType>::getFree() const{
    return pool.getFree();
}

