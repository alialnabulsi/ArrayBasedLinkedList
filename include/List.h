#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <functional>
#include "NodePool.h"
using namespace std;

template<typename T>
class List {
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
    bool deleteItem(const T& item);
    int getFree() const;
    void sortList();
    bool isSorted() const;
    void display() const;

private:
    NodePool<T> pool;
    int first;
};

template<typename T>
List<T>::List() : pool(), first(NULL_VALUE) {}

template<typename T>
List<T>::List(const List& other) : pool(), first(NULL_VALUE) {
    int otherPtr = other.first;
    int lastNewNode = NULL_VALUE;

    while (otherPtr != NULL_VALUE) {
        int newNodeIndex = pool.newNode();
        pool.getPool()[newNodeIndex].data = other.pool.getPool()[otherPtr].data;

        if (lastNewNode == NULL_VALUE) {
            first = newNodeIndex;
        } else {
            pool.getPool()[lastNewNode].next = newNodeIndex;
        }

        lastNewNode = newNodeIndex;
        otherPtr = other.pool.getPool()[otherPtr].next;
    }
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        while (!isEmpty()) {
            deleteAtTop();
        }

        int otherPtr = other.first;
        int lastNewNode = NULL_VALUE;

        while (otherPtr != NULL_VALUE) {
            int newNodeIndex = pool.newNode();
            pool.getPool()[newNodeIndex].data = other.pool.getPool()[otherPtr].data;

            if (lastNewNode == NULL_VALUE) {
                first = newNodeIndex;
            } else {
                pool.getPool()[lastNewNode].next = newNodeIndex;
            }

            lastNewNode = newNodeIndex;
            otherPtr = other.pool.getPool()[otherPtr].next;
        }
    }
    return *this;
}

template<typename T>
List<T>::~List() {
    while (!isEmpty()) {
        deleteAtTop();
    }
}

template<typename T>
bool List<T>::isEmpty() const {
    return first == NULL_VALUE;
}

template<typename T>
int List<T>::size() const {
    int count = 0, ptr = first;
    while(ptr != NULL_VALUE) {
        count++;
        ptr = pool.getPool()[ptr].next;
    }
    return count;
}

template<typename T>
int List<T>::search(const T& item) const {
    int pos = NULL_VALUE, ptr = first;
    while(ptr != NULL_VALUE) {
        if (pool.getPool()[ptr].data == item) {
            pos = ptr;
        }
        ptr = pool.getPool()[ptr].next;
    }
    return pos;
}

template<typename T>
void List<T>::insertAtEnd(const T& item) {
    int ptr = first;
    int newNodeIndex;
    while(ptr != NULL_VALUE) {
        if(pool.getPool()[ptr].next == NULL_VALUE) {
            newNodeIndex = pool.newNode();
            pool.getPool()[newNodeIndex].data = item;
        }
        ptr = pool.getPool()[ptr].next;
    }
}

template<typename T>
void List<T>::deleteAtEnd() {
    int ptr = first;
    while(ptr != NULL_VALUE) {
        if(pool.getPool()[ptr].next == NULL_VALUE) {
            pool.deleteNode(ptr);
        }
        ptr = pool.getPool()[ptr].next;
    }
}

template<typename T>
void List<T>::insertAtTop(const T& item) {
    int index = pool.newNode();
    pool.getPool()[index].data = item;
    pool.getPool()[index].next = first;
    first = index;
}

template<typename T>
void List<T>::deleteAtTop() {
    if (isEmpty())
        cerr << "List::deleteFront() on empty list";
    int index = first;
    first = pool.getPool()[index].next;
    pool.deleteNode(index);
}

template<typename T>
void List<T>::insertAfterPos(int pos, const T& item) {
    if (isEmpty()) {
        cerr << "List::insertAfter() on empty list";
    }
    if (pos == NULL_VALUE || pos < 0 || pos >= NUM_NODES)
        cerr << "List::insertAfter invalid position";
    int index = pool.newNode();
    pool.getPool()[index].data = item;
    int nextIndex = pool.getPool()[pos].next;
    pool.getPool()[pos].next = index;
    pool.getPool()[index].next = nextIndex;
}

template<typename T>
bool List<T>::deleteItem(const T& item) {
    int prev = NULL_VALUE;
    int curr = first;

    while (curr != NULL_VALUE) {
        if (pool.getPool()[curr].data == item) {
            if (prev == NULL_VALUE) {
                first = pool.getPool()[curr].next;
            } else {
                pool.getPool()[prev].next = pool.getPool()[curr].next;
            }
            pool.deleteNode(curr);
            return true;
        }
        prev = curr;
        curr = pool.getPool()[curr].next;
    }
    return false;
}

template<typename T>
void List<T>::traverse(const function<void(const T&)>& visit) const {
    int ptr = first;
    while (ptr != NULL_VALUE) {
        visit(pool.getPool()[ptr].data);
        ptr = pool.getPool()[ptr].next;
    }
}

template<typename T>
void List<T>::sortList() {
    bool swapped;
    do {
        swapped = false;
        int prev = NULL_VALUE;
        int curr = first;
        int next = (curr != NULL_VALUE) ? pool.getPool()[curr].next : NULL_VALUE;

        while (next != NULL_VALUE) {
            if (pool.getPool()[curr].data > pool.getPool()[next].data) {
                T temp = pool.getPool()[curr].data;
                pool.getPool()[curr].data = pool.getPool()[next].data;
                pool.getPool()[next].data = temp;
                swapped = true;
            }
            prev = curr;
            curr = next;
            next = pool.getPool()[next].next;
        }
    } while (swapped);
}

template<typename T>
bool List<T>::isSorted() const {
    if (isEmpty() || pool.getPool()[first].next == NULL_VALUE) {
        return true;
    }

    int curr = first;
    int next = pool.getPool()[curr].next;

    while (next != NULL_VALUE) {
        if (pool.getPool()[curr].data > pool.getPool()[next].data) {
            return false;
        }
        curr = next;
        next = pool.getPool()[next].next;
    }
    return true;
}

template<typename T>
void List<T>::display() const {
    int ptr = first;
    cout << "List: [";
    while (ptr != NULL_VALUE) {
        cout << pool.getPool()[ptr].data;
        ptr = pool.getPool()[ptr].next;
        if (ptr != NULL_VALUE) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

template<typename T>
int List<T>::getFree() const {
    return pool.getFree();
}

#endif