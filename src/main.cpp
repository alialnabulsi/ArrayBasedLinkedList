#include <iostream>
#include <string>
#include "../include/List.h"

using namespace std;

void showMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Insert at Top\n";
    cout << "2. Insert at End\n";
    cout << "3. Insert After item\n";
    cout << "4. Delete at Top\n";
    cout << "5. Delete at End\n";
    cout << "6. Delete Item\n";
    cout << "7. Search Item\n";
    cout << "8. Display List\n";
    cout << "9. Check if Sorted\n";
    cout << "10. Sort List\n";
    cout << "11. Show Size\n";
    cout << "12. Show Free List Head\n";
    cout << "0. Exit\n";
    cout << "==========================\n";
    cout << "Choose an option: ";
}

template<typename T>
void runListMenu(List<T> &list) {
    bool running = true;

    while (running) {
        int choice;
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                T value;
                cout << "Enter value to insert at top: ";
                cin >> value;
                list.insertAtTop(value);
                break;
            }
            case 2: {
                T value;
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insertAtEnd(value);
                break;
            }
            case 3: {
                T afterValue, newValue;
                cout << "Enter existing item to insert after: ";
                cin >> afterValue;
                cout << "Enter new value to insert: ";
                cin >> newValue;
                list.insertAfterItem(afterValue, newValue);
                break;
            }
            case 4:
                list.deleteAtTop();
                break;
            case 5:
                list.deleteAtEnd();
                break;
            case 6: {
                T value;
                cout << "Enter value to delete: ";
                cin >> value;
                if (list.deleteItem(value))
                    cout << "Item deleted.\n";
                else
                    cout << "Item not found.\n";
                break;
            }
            case 7: {
                T value;
                cout << "Enter value to search: ";
                cin >> value;
                int pos = list.search(value);
                if (pos != NULL_VALUE)
                    cout << "Item found at index " << pos << ".\n";
                else
                    cout << "Item not found.\n";
                break;
            }
            case 8:
                list.display();
                break;
            case 9:
                cout << (list.isSorted() ? "List is sorted.\n" : "List is not sorted.\n");
                break;
            case 10:
                list.sortList();
                cout << "List sorted.\n";
                break;
            case 11:
                cout << "List size: " << list.size() << endl;
                break;
            case 12:
                cout << "Free list head index: " << list.getFree() << endl;
                break;
            case 0:
                running = false;
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}

int main() {
    cout << "========================================\n";
    cout << " Welcome to the Array-Based Linked List \n";
    cout << "========================================\n";
    cout << "Initializing storage pool...\n";
    cout << "ArrayList is ready to use!\n";

    cout << "\nWhich data type would you like to use?\n";
    cout << "1. int\n2. double\n3. string\nChoice: ";
    int typeChoice;
    cin >> typeChoice;

    switch (typeChoice) {
        case 1: {
            List<int> intList;
            runListMenu(intList);
            break;
        }
        case 2: {
            List<double> doubleList;
            runListMenu(doubleList);
            break;
        }
        case 3: {
            List<string> stringList;
            runListMenu(stringList);
            break;
        }
        default:
            cout << "Invalid data type choice.\n";
            break;
    }

    return 0;
}
