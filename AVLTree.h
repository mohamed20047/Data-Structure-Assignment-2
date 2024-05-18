//
// Created by at991 on 2/11/2024.
//

#ifndef AVL_BINARY_SEARCH_TREE_AVLTREE_H
#define AVL_BINARY_SEARCH_TREE_AVLTREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include "Tree.h"

template <class T>
class AVLTree {
private:
    T data;
    AVLTree *left;
    AVLTree *right;
    int height;
    bool (*compare)(T d1, T d2);
    static bool defaultComb(T d1, T d2) {
        return d1 < d2;
    }
public:
    AVLTree(T val, bool (*func)(T d1, T d2) = defaultComb);
    void operator=(AVLTree<T> *root);
    int Height(const AVLTree *root);
    AVLTree * find(AVLTree<T> *&root, const T val);
    AVLTree * findMin(AVLTree *root);
    AVLTree * findMax(AVLTree *root);
    void leftRotate(AVLTree *&root);
    void rightRotate(AVLTree *&root);
    void balance(AVLTree<T> *&root);
    void insert(AVLTree<T> *&root, const T val);
    void erase(AVLTree<T> *&root, const T val);

    void printInOrder(AVLTree<T> *root);
    void printLevelOrder(AVLTree<T> *root);
};

template<class T>
void AVLTree<T>::printLevelOrder(AVLTree<T> *root) {
    std::queue<AVLTree<T> *> q;
    q.push(root);
    int count = 1, size = 0;
    while (!q.empty()) {
        size = q.size();
        int tmp = 1;
        std::cout << "Level " << count++ << ":" << std::endl;
        while (size--) {
            std::cout << tmp++ << std::endl;
            AVLTree<T> *temp = q.front();
            q.pop();
            std::cout << temp->data << std::endl;

            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
        std::cout << std::endl;
    }
}

template<class T>
void AVLTree<T>::printInOrder(AVLTree<T> *root) {
    if (root == nullptr)
        return;
    printInOrder(root->left);
    std::cout << root->data << std::endl;
    printInOrder(root->right);
}

template<class T>
void AVLTree<T>::operator=(AVLTree<T> *root) {
    data = root->data;
    left = root->left;
    right = root->right;
}

static const int ALLOWED_IMBALANCE = 1;

template <class T>
AVLTree<T>::AVLTree(T val, bool (*func)(T d1, T d2))
: data{val}, left{nullptr}, right{nullptr}, height{1} {
    this->compare = func;
}

template <class T>
int AVLTree<T>::Height(const AVLTree<T> *root) {
    if (root == nullptr)
        return 0;
    return root->height;
}

template <class T>
AVLTree<T> * AVLTree<T>::find(AVLTree<T> *&root, const T val) {
    if (root == nullptr)
        return nullptr;

    if (compare(val, root->data))
        return find(root->left, val);
    else if (compare(root-data, val))
        return find(root->right, val);
    else
        return root;
}

template <class T>
AVLTree<T> * AVLTree<T>::findMin(AVLTree<T> *root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

template <class T>
AVLTree<T> * AVLTree<T>::findMax(AVLTree<T> *root) {
    while (root->right != nullptr)
        root = root->right;
    return root;
}

template <class T>
void AVLTree<T>::leftRotate(AVLTree<T> *&root) {
    AVLTree<T> *x = root->right;
    root->right = x->left;
    x->left = root;

    x->height = 1 + std::max(Height(x->left), Height(x->right));
    root->height = 1 + std::max(Height(root->left), Height(root->right));

    root = x;
}

template <class T>
void AVLTree<T>::rightRotate(AVLTree<T> *&root) {
    AVLTree<T> *x = root->left;
    root->left = x->right;
    x->right = root;

    x->height = 1 + std::max(Height(x->left), Height(x->right));
    root->height = 1 + std::max(Height(root->left), Height(root->right));

    root = x;
}

template <class T>
void AVLTree<T>::balance(AVLTree<T> *&root) {
    if (root == nullptr)
        return;

    int diff = Height(root->left) - Height(root->right);

    if (ALLOWED_IMBALANCE < diff) {
        if (Height(root->left->left) >= Height(root->left->right))
            rightRotate(root);
        else {
            leftRotate(root->left);
            rightRotate(root);
        }
    }
    else if (ALLOWED_IMBALANCE < -diff) {
        if (Height(root->right->right) >= Height(root->right->left))
            leftRotate(root);
        else {
            rightRotate(root->right);
            leftRotate(root);
        }
    }

    root->height = 1 + std::max(Height(root->left), Height(root->right));
}

template <class T>
void AVLTree<T>::insert(AVLTree<T> *&root, const T val) {
    if (root == nullptr)
        root = new AVLTree<T>(val, compare);
    else if (compare(val, root->data))
        insert(root->left, val);
    else
        insert(root->right, val);

    balance(root);
}

template <class T>
void AVLTree<T>::erase(AVLTree<T> *&root, const T val) {
    if (root == nullptr)
        return;

    if (compare(val, root->data))
        erase(root->left, val);
    else if (compare(root->data, val))
        erase(root->right, val);
    else {
        // zero of one child
        if (!root->left || !root->right) {
            AVLTree<T> *node = root->left ? root->left : root->right;

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
            AVLTree<T> *node = findMax(root->left);
            root->data = node->data;
            erase(root->left, node->data);
        }

        balance(root);
    }
}


#endif //AVL_BINARY_SEARCH_TREE_AVLTREE_H
