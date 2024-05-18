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

int main() {
    Item item("ahmed", "sss", 100);
    ifstream file("../input.txt");
    AVLTree<Item> *tree = new AVLTree<Item>(item);
    readTreeItems(file, tree);
    tree->erase(tree, item);
    tree->printInOrder(tree);
}