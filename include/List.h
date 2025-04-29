
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <functional>
#include "NodePool.h"
using namespace std;
/*-- List.h ----------------------------------------------------------------
This header file defines a List class template implementing an array-based
linked list using the NodePool for memory management. The type parameter T
represents the data type stored in the list.

Key Features:

Complete linked list implementation without dynamic memory operations

Uses NodePool for efficient node management

Supports standard list operations and traversal

Basic Operations:
Construction: Default, copy constructor, and assignment operator
Insertion: At top, at end, or after specified position
Deletion: At top, at end, or by item value
Search: Locates an item in the list
Traversal: Applies a function to each element
Sorting: In-place bubble sort implementation
Utilities: Size check, empty check, display

Advanced Operations:
isSorted: Checks if list is in ascending order
getFree: Provides access to free list head (for debugging)

Note: All operations maintain proper linkage through the NodePool and
handle edge cases (empty list, full pool, etc.) appropriately.
--------------------------------------------------------------------------*/
template<typename T>
class List {
public:
    List();
/*-----------------------------------------------------------------------
Constructs an empty List object.

Precondition: None.
Postcondition: An empty list is created with first set to NULL_VALUE.
-----------------------------------------------------------------------*/
    List(const List& other);
/*-----------------------------------------------------------------------
Copy constructor.

Precondition: None.
Postcondition: Creates a deep copy of other list with identical contents.
-----------------------------------------------------------------------*/
    List& operator=(const List& other);
/*-----------------------------------------------------------------------
Assignment operator.

Precondition: None.
Postcondition: Performs deep copy of other list. Returns reference to
this list. Handles self-assignment properly.
-----------------------------------------------------------------------*/
    ~List();
/*-----------------------------------------------------------------------
Destructor.

Precondition: None.
Postcondition: All nodes are returned to the pool.
-----------------------------------------------------------------------*/
    bool isEmpty() const;
/*-----------------------------------------------------------------------
Checks if list is empty.

Precondition: None.
Postcondition: Returns true if list is empty, false otherwise.
-----------------------------------------------------------------------*/
    int size() const;
/*-----------------------------------------------------------------------
Gets the size of the list.

Precondition: None.
Postcondition: Returns number of elements in the list.
-----------------------------------------------------------------------*/
    int search(const T& item) const;
/*-----------------------------------------------------------------------
Searches for an item in the list.

Precondition: None.
Postcondition: Returns index of item if found, NULL_VALUE otherwise.
-----------------------------------------------------------------------*/
    void insertAtEnd(const T& item);
/*-----------------------------------------------------------------------
Inserts an item at the end of the list.

Precondition: None.
Postcondition: Item is added as last element. If list was empty,
becomes first element.
-----------------------------------------------------------------------*/
    void deleteAtEnd();
/*-----------------------------------------------------------------------
Deletes the last item in the list.

Precondition: List must not be empty.
Postcondition: Last element is removed from list and returned to pool.
-----------------------------------------------------------------------*/
    void insertAtTop(const T& item);
/*-----------------------------------------------------------------------
Inserts an item at the beginning of the list.

Precondition: None.
Postcondition: Item is added as first element.
-----------------------------------------------------------------------*/
    void deleteAtTop();
/*-----------------------------------------------------------------------
Deletes the first item in the list.

Precondition: List must not be empty.
Postcondition: First element is removed from list and returned to pool.
-----------------------------------------------------------------------*/
    void insertAfterPos(int pos, const T& item);
/*-----------------------------------------------------------------------
Inserts an item after a specified position.

Precondition: pos must be a valid position in the list.
Postcondition: Item is inserted after specified position.
If position is invalid, outputs error message.
-----------------------------------------------------------------------*/
    bool deleteItem(const T& item);
/*-----------------------------------------------------------------------
Deletes the first occurrence of an item.

Precondition: None.
Postcondition: Returns true if item was found and deleted, false otherwise.
-----------------------------------------------------------------------*/
    int getFree() const;
/*-----------------------------------------------------------------------
Gets the current free list head from the pool.

Precondition: None.
Postcondition: Returns index of first free node (for debugging purposes).
-----------------------------------------------------------------------*/
    void sortList();
/*-----------------------------------------------------------------------
Sorts the list in ascending order.

Precondition: None.
Postcondition: List elements are sorted using bubble sort algorithm.
-----------------------------------------------------------------------*/
    bool isSorted() const;
/*-----------------------------------------------------------------------
Checks if the list is sorted.

Precondition: None.
Postcondition: Returns true if list is in ascending order, false otherwise.
-----------------------------------------------------------------------*/
    void display() const;
/*-----------------------------------------------------------------------
Displays the list contents.

Precondition: None.
Postcondition: List contents are output to standard output in format:
"List: [item1, item2, ...]"
-----------------------------------------------------------------------*/

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
        ptr = pool.readPool()[ptr].next;
    }
    return count;
}

template<typename T>
int List<T>::search(const T& item) const {
    int pos = NULL_VALUE, ptr = first;
    while(ptr != NULL_VALUE) {
        if (pool.readPool()[ptr].data == item) {
            pos = ptr;
        }
        ptr = pool.readPool()[ptr].next;
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
    if (isEmpty() || pool.readPool()[first].next == NULL_VALUE) {
        return true;
    }

    int curr = first;
    int next = pool.readPool()[curr].next;

    while (next != NULL_VALUE) {
        if (pool.readPool()[curr].data > pool.readPool()[next].data) {
            return false;
        }
        curr = next;
        next = pool.readPool()[next].next;
    }
    return true;
}

template<typename T>
void List<T>::display() const {
    int ptr = first;
    cout << "List: [";
    while (ptr != NULL_VALUE) {
        cout << pool.readPool()[ptr].data;
        ptr = pool.readPool()[ptr].next;
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