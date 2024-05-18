cmake_minimum_required(VERSION 3.27)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_2
        AVLTree.h
        BST_Tree.h
        Heap.h
        main.cpp
        Item.h
        Tree.h)
