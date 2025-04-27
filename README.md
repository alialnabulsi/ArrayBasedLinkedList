# Array-Based Linked List (Static Node Pool)

A C++ implementation of a linked list using a pre-allocated array of nodes (static memory) instead of dynamic pointers. Part of the CSIS216 Data Structures course project.

## Key Features
- **`NodePool.h`**: Template library managing a fixed-size pool of nodes with:
    - `newNode()`: Allocates nodes from the pool.
    - `deleteNode()`: Returns nodes to the free list.
- **Templated List Class**: Supports insertion, deletion, and traversal.
- **Interactive Tester**: Demonstrates list operations (e.g., insert "Brown", "Jones", "Smith").

## Why?
- Avoids overhead of dynamic allocation/deallocation.
- Useful for memory-constrained environments (e.g., embedded systems).

## Usage
1. Include `NodePool.h` and `List.h` in your project.
2. Declare a list: `List<std::string> myList;`.
3. Test with the provided `main.cpp` or integrate into your code.

```cpp
#include "List.h"
int main() {
    List<std::string> names;
    names.insert("Brown");
    names.insert("Jones");
    names.print(); // Output: Brown -> Jones -> NULL
}