//
// Created by at991 on 5/18/2024.
//

#ifndef ASSIGNMENT_2_BST_TREE_H
#define ASSIGNMENT_2_BST_TREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include "Tree.h"

template <class T>
class BST_Tree {
private:
    T data;
    BST_Tree *left;
    BST_Tree *right;
    bool (*compare)(T d1, T d2);
    static bool defaultComb(T d1, T d2) {
        return d1 < d2;
    }
public:
    BST_Tree(bool (*func)(T d1, T d2) = defaultComb);
    BST_Tree(T val, bool (*func)(T d1, T d2) = defaultComb);
    void operator=(BST_Tree<T> *root);
    BST_Tree * find(BST_Tree<T> *&root, const T val);
    BST_Tree * findMin(BST_Tree *root);
    BST_Tree * findMax(BST_Tree *root);
    void insert(BST_Tree<T> *&root, const T val);
    void erase(BST_Tree<T> *&root, const T val);

    void printInOrder(BST_Tree<T> *root);
    void printLevelOrder(BST_Tree<T> *root);
};

template<class T>
void BST_Tree<T>::printLevelOrder(BST_Tree<T> *root) {
    std::queue<BST_Tree<T> *> q;
    q.push(root);
    int count = 1, size = 0;
    while (!q.empty()) {
        size = q.size();
        std::cout << "Level " << count++ << ": ";
        while (size--) {
            BST_Tree<T> *temp = q.front();
            q.pop();
            std::cout << temp->data << ' ';

            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
        std::cout << std::endl;
    }
}

template<class T>
void BST_Tree<T>::printInOrder(BST_Tree<T> *root) {
    if (root == nullptr)
        return;
    printInOrder(root->left);
    std::cout << root->data << std::endl;
    printInOrder(root->right);
}

template<class T>
void BST_Tree<T>::operator=(BST_Tree<T> *root) {
    data = root->data;
    left = root->left;
    right = root->right;
}

template <class T>
BST_Tree<T>::BST_Tree(bool (*func)(T d1, T d2))
    : data{}, left{nullptr}, right{nullptr} {
    this->compare = func;
}

template <class T>
BST_Tree<T>::BST_Tree(T val, bool (*func)(T d1, T d2))
        : data{val}, left{nullptr}, right{nullptr} {
    this->compare = func;
}

template <class T>
BST_Tree<T> * BST_Tree<T>::find(BST_Tree<T> *&root, const T val) {
    if (root == nullptr)
        return nullptr;

    if (compare(val, root->data))
        return find(root->left, val);
    else if (compare(root->data, val))
        return find(root->right, val);
    else
        return root;
}

template <class T>
BST_Tree<T> * BST_Tree<T>::findMin(BST_Tree<T> *root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

template <class T>
BST_Tree<T> * BST_Tree<T>::findMax(BST_Tree<T> *root) {
    while (root->right != nullptr)
        root = root->right;
    return root;
}

template <class T>
void BST_Tree<T>::insert(BST_Tree<T> *&root, const T val) {
    if (root == nullptr) {
        root = new BST_Tree<T>(val, compare);
    }
    else if (compare(val, root->data))
        insert(root->left, val);
    else
        insert(root->right, val);
}

template <class T>
void BST_Tree<T>::erase(BST_Tree<T> *&root, const T val) {
    if (root == nullptr)
        return;

    if (compare(val, root->data))
        erase(root->left, val);
    else if (compare(root->data, val))
        erase(root->right, val);
    else {
        // zero of one child
        if (!root->left || !root->right) {
            BST_Tree<T> *node = root->left ? root->left : root->right;

            if (node)
                *root = *node;
            else {
                node = root;
                root = nullptr;
            }
            delete node;
        }
            // two children
        else {
            BST_Tree<T> *node = findMax(root->left);
            root->data = node->data;
            erase(root->left, node->data);
        }
    }
}

#endif //ASSIGNMENT_2_BST_TREE_H
