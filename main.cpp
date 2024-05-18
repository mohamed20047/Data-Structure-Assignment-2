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
void readHeapItems(istream &is, T heap) {
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
}

template <class T>
void readTreeItems(istream &is, T &tree) {
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
}

bool compByName(Item i1, Item i2) {
    return i1.get_name() < i2.get_name();
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
    cin >> type;
    transform(type.begin(), type.end(), type.begin(),:: toupper);
    cout << "=========================================================================\n";
    cout << "=========================================================================\n";
    cout << "This is the operations that applied the tree structures.\n";
    cout << "=========================================================================\n";
    
}

void minimenu(){
    cout << "I.Add item data.\n";
    cout << "II. Remove item data.\n";
    cout << "III. Display the item data normally.\n";
    cout << "IV. Display all the items sorted by their name ascending.\n";
    cout << "V. Display all the items sorted by their name descending.\n";
    cout << "VI. Display all the items sorted by their prices ascending.\n";
    cout << "VII. Display all the items sorted by their prices descending.\n";
    cout << "Press Q to exit from the program.\n";
    cout << "You can press ( I , II , III, IV, V, VI, VII)\n";
    cin >> operation;
    transform(operation.begin(), operation.end(), operation.begin(),:: toupper);
    if ( operation == "I" && type == "i" ){
    }
}

string operation = "";
string type ;


int main() {
    Item item("test1", "sss", 100);
    ifstream file("../input.txt");
    // AVLTree<Item> *tree = new AVLTree<Item>(item);
    // tree->erase(tree, item);
    // tree->printInOrder(tree);
    menu();
    // bst
    if ( type == "I"){
        BST_Tree<Item> bst_price = new BST_Tree<Item>(item);
        BST_Tree<Item> bst_name = new BST_Tree<Item>(item);
        readTreeItems(file, bst);
        bst->erase(bst,item);
    }
    // heap
    else if ( type == "II"){

    }
    // AVL
    else {

    }


    
}

