//
// Created by at991 on 2/13/2024.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H


#include <algorithm>
#include "Tree.h"

template <class T>
class Heap {
private:
    T *array;
    int capacity;
    int count;
    int heapType;
    void percolateDown(int index);
    void percolateDownMax(int index);
    void percolateDownMin(int index);
    void percolateUp(int index);
    void percolateUpMax(int index);
    void percolateUpMin(int index);
    void resizeHeap();
    bool (*compare)(T d1, T d2);
    static bool defaultComb(T d1, T d2) {
        return d1 < d2;
    }
public:
    Heap(int capacity, int type, bool (*func)(T d1, T d2) = defaultComb);
    Heap(int n, int type, T *arr, bool (*func)(T d1, T d2) = defaultComb);
    void insert(T val);
    T getMax();
    T getMin();
    void remove();
    int size();
    void print();
};

template<class T>
void Heap<T>::print() {
    for (int i = 0; i < count; i++)
        std::cout << array[i] << std::endl;
}

template<class T>
int Heap<T>::size() {
    return count;
}

template<class T>
void Heap<T>::resizeHeap() {
    T *oldArr = array;
    array = new T[2 * capacity];
    for (int i = 0; i < count; i++)
        array[i] = oldArr[i];
    capacity *= 2;
}

template <class T>
Heap<T>::Heap(int capacity, int type, bool (*func)(T d1, T d2))
: capacity{capacity}, heapType{type}, count{0} {
    array = new T[capacity];
    this->compare = func;
}

template <class T>
Heap<T>::Heap(int n, int type, T *arr, bool (*func)(T d1, T d2))
: Heap(1, type) {
    count = n;
    this->compare = func;
    while (n > capacity)
        resizeHeap();
    for (int i = 0; i < count; i++)
        array[i] = arr[i];
    for (int i = (count - 1) / 2; i >= 0; i--)
        percolateDown(i);
}

template <class T>
void Heap<T>::percolateDown(int index) {
    heapType ? percolateDownMax(index) : percolateDownMin(index);
}

template <class T>
void Heap<T>::percolateDownMax(int index) {
    int child1 = 2 * index + 1;
    int child2 = 2 * index + 2;
    int max;
    if (child1 > count && child2 > count)
        return;
    if (child1 > count)
        max = child2;
    else if (child2 > count)
        max = child1;
    else
        max = (compare(array[child2], array[child1])) ? child1 : child2;
    if (compare(array[index], array[max])) {
        std::swap(array[index], array[max]);
        percolateDownMax(max);
    }
}

template <class T>
void Heap<T>::percolateDownMin(int index) {
    int child1 = 2 * index + 1;
    int child2 = 2 * index + 2;
    int max;
    if (child1 > count && child2 > count)
        return;
    else if (child1 > count)
        max = child2;
    else if (child2 > count)
        max = child1;
    else
        max = (compare(array[child1], array[child2])) ? child1 : child2;
    if (compare(array[max], array[index])) {
        std::swap(array[index], array[max]);
        percolateDownMin(max);
    }
}

template <class T>
void Heap<T>::percolateUp(int index) {
    heapType ? percolateUpMax(index) : percolateUpMin(index);
}

template <class T>
void Heap<T>::percolateUpMax(int index) {
    int parent = (index - 1) / 2;
    while (parent >= 0) {
        if (compare(array[parent], array[index])) {
            std::swap(array[index], array[parent]);
            index = parent;
            parent = (index-1) / 2;
        }
        else
            break;
    }
}

template <class T>
void Heap<T>::percolateUpMin(int index) {
    int parent = (index - 1) / 2;
    while (parent >= 0) {
        if (compare(array[index], array[parent])) {
            std::swap(array[index], array[parent]);
            index = parent;
            parent = (index-1) / 2;
        }
        else
            break;
    }
}

template <class T>
void Heap<T>::insert(T val) {
    if (count >= capacity)
        resizeHeap();

    array[count] = val;
    percolateUp(count);
    count++;
}

template <class T>
T Heap<T>::getMax() {
    if (heapType)
        return array[0];

    T max = array[count-1];
    for (int i = (count-1)/2 + 1; i < count; i++)
        if (compare(max, array[i])) max = array[i];

    return max;

}

template <class T>
T Heap<T>::getMin() {
    if (!heapType)
        return array[0];

    T min = array[count-1];
    for (int i = (count-1)/2 + 1; i < count; i++)
        if (compare(array[i], min)) min = array[i];

    return min;
}

template <class T>
void Heap<T>::remove() {
    array[0] = array[count-1];
    count--;
    percolateDown(0);
}


#endif //HEAP_HEAP_H
