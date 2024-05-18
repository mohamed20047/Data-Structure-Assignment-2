//
// Created by at991 on 5/18/2024.
//
#include <iostream>
#include <fstream>
#include "BST_Tree.h"
#include "AVLTree.h"
#include "Heap.h"
#include "Item.h"

using namespace std;

template <class T>
void readHeapItems(T heap) {
    ifstream is("../input.txt");
    int n = 0;
    string tmp;
    getline(is, tmp);
    n = stoi(tmp);
    while (n--) {
        string name, category, price;
        getline(is, name);
        getline(is, category);
        getline(is, price);
        heap->insert(Item(name, category, stoi(price)));
    }
    is.close();
}

template <class T>
void readTreeItems(T &tree) {
    ifstream is("../input.txt");
    int n = 0;
    string tmp;
    getline(is, tmp);
    n = stoi(tmp);
    while (n--) {
        string name, category, price;
        getline(is, name);
        getline(is, category);
        getline(is, price);
        tree->insert(tree, Item(name, category, stoi(price)));
    }
    is.close();
}

bool compByName(Item i1, Item i2) {
    return i1.get_name() < i2.get_name();
}

bool compByPrice(Item i1, Item i2) {
    return i1.get_price() < i2.get_price();
}

void  menu (){
    cout << "=========================================================================\n";
    cout << "Enter your name please : ";
    string name;
    cin >> name ;
    cout << "=========================================================================\n\n";

    cout << "Welcom to our application " << name << endl << endl ;
    cout << "=========================================================================\n\n";

    cout << "We have three types of tree data structures\n\n=========================================================================\n";
    cout <<"(i) Binary Search Trees (BST)\n(ii) Heaps\n(iii) AVL Trees\nYou can choose any type to performe some operations\n";
    cout << "You can press ( i , ii , iii)\n";
    cout << endl;
}

void minimenu(){
    cout << "=========================================================================\n";
    cout << "This is the operations that applied the tree structures.\n";
    cout << "=========================================================================\n";
    cout << "I.Add item data.\n";
    cout << "II. Remove item data.\n";
    cout << "III. Display the item data normally.\n";
    cout << "IV. Display all the items sorted by their name ascending.\n";
    cout << "V. Display all the items sorted by their name descending.\n";
    cout << "VI. Display all the items sorted by their prices ascending.\n";
    cout << "VII. Display all the items sorted by their prices descending.\n";
    cout << "Press Q to exit from the program.\n";
    cout << "You can press ( I , II , III, IV, V, VI, VII)\n";
}

Item get_item() {
    string name, category;
    int price;
    cout << "Please enter item name: ";
    cin >> name;
    cout << endl;
    cout << "Please enter item category: ";
    cin >> category;
    cout << endl;
    cout << "Please enter item price: ";
    cin >> price;
    cout << endl;
    return Item(name, category, price);
}

void print_heap(Heap <Item> *h) {
    vector <Item> tmp;
    while(h->size()) {
        Item i;
        if (h->heapType) i = h->getMax();
        else i = h->getMin();
        cout << i << endl;
        tmp.push_back(i);
        h->remove();
    }
    for (auto i : tmp) h->insert(i);
}

int main() {
    string type = "";
    while (type != "I" && type != "II" && type != "III") {
        menu();
        cin >> type;
        transform(type.begin(), type.end(), type.begin(), ::toupper);
    }
    Item item("test1", "sss", 100);
    // BST
    if ( type == "I"){
        BST_Tree<Item> *bst_price = new BST_Tree<Item>(item);
        BST_Tree<Item> *bst_name = new BST_Tree<Item>(item, compByName);
        readTreeItems(bst_price);
        readTreeItems(bst_name);
        bst_price->erase(bst_price, item);
        bst_name->erase(bst_name, item);
        string op = "";
        while (op != "Q") {
            minimenu();
            cin >> op;
            transform(op.begin(), op.end(), op.begin(), ::toupper);
            if (op == "I") {
                Item i1 = get_item();
                bst_name->insert(bst_name, i1);
                bst_price->insert(bst_price, i1);
            }
            else if (op == "II") {
                Item i1 = get_item();
                bst_price->erase(bst_price, i1);
                bst_name->erase(bst_name, i1);
            }
            else if (op == "III") {
                bst_price->printInOrder(bst_price);
                cout << endl;
            }
            else if (op == "IV") {
                bst_name->printInOrder(bst_name);
                cout << endl;
            }
            else if (op == "V") {
                bst_name->printPostOrder(bst_name);
                cout << endl;
            }
            else if (op == "VI") {
                bst_price->printInOrder(bst_price);
                cout << endl;
            }
            else if (op == "VII") {
                bst_price->printPostOrder(bst_price);
                cout << endl;
            }
        }
    }
    // heap
    else if ( type == "II") {
        Heap<Item> *heap = new Heap<Item>(10, 1); // min heap by price
        readHeapItems(heap);
        string op = "";
        while (op != "Q") {
            minimenu();
            cin >> op;
            transform(op.begin(), op.end(), op.begin(), ::toupper);
            if (op == "I") {
                Item i1 = get_item();
                heap->insert(i1);
            }
            else if (op == "II") {
                heap->remove();
            }
            else if (op == "III") {
                heap->print_asc();
            }
            else if (op == "IV") {
                heap->set_compare(compByName);
                heap->print_asc();
            }
            else if (op == "V") {
                heap->set_compare(compByName);
                heap->print_des();
            }
            else if (op == "VI") {
                heap->set_compare(compByPrice);
                heap->print_asc();
            }
            else if (op == "VII") {
                heap->set_compare(compByPrice);
                heap->print_des();
            }
        }
    }
    // AVL
    else {
        AVLTree<Item> *avl_price = new AVLTree<Item>(item);
        AVLTree<Item> *avl_name = new AVLTree<Item>(item, compByName);
        readTreeItems(avl_price);
        readTreeItems(avl_name);
        avl_price->erase(avl_price, item);
        avl_name->erase(avl_name, item);
        string op = "";
        while (op != "Q") {
            minimenu();
            cin >> op;
            transform(op.begin(), op.end(), op.begin(), ::toupper);
            if (op == "I") {
                Item i1 = get_item();
                avl_name->insert(avl_name, i1);
                avl_price->insert(avl_price, i1);
            }
            else if (op == "II") {
                Item i1 = get_item();
                avl_price->erase(avl_price, i1);
                avl_name->erase(avl_name, i1);
            }
            else if (op == "III") {
                avl_price->printInOrder(avl_price);
                cout << endl;
            }
            else if (op == "IV") {
                avl_name->printInOrder(avl_name);
                cout << endl;
            }
            else if (op == "V") {
                avl_name->printPostOrder(avl_name);
                cout << endl;
            }
            else if (op == "VI") {
                avl_price->printInOrder(avl_price);
                cout << endl;
            }
            else if (op == "VII") {
                avl_price->printPostOrder(avl_price);
                cout << endl;
            }
        }
    }
}

