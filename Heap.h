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
    void heapifyDown(int index, int n);
    void heapifyDownMax(int index, int n);
    void heapifyDownMin(int index, int n);
    void heapifyUp(int index);
    void heapifyUpMax(int index);
    void heapifyUpMin(int index);
    void buildHeap();
    void buildHeapMin();
    void buildHeapMax();
    void resizeHeap();
    bool (*compare)(T d1, T d2);
    static bool defaultComb(T d1, T d2) {
        return d1 < d2;
    }
public:
    int heapType;
    Heap(int capacity, int type, bool (*func)(T d1, T d2) = defaultComb);
    Heap(int n, int type, T *arr, bool (*func)(T d1, T d2) = defaultComb);
    void insert(T val);
    T getMax();
    T getMin();
    void remove();
    int size();
    void set_compare(bool (*func)(T d1, T d2));
    void print_asc();
    void print_des();
};

template<class T>
void Heap<T>::set_compare(bool (*func)(T d1, T d2)) {
    this->compare = func;
}

template<class T>
void Heap<T>::print_asc() {
    // heap sort
    buildHeapMax();

    for (int i = count - 1; i > 0; i--) {
        std::swap(array[0], array[i]);

        heapifyDownMax(0, i);
    }

    for (int i = 0; i < count; i++) {
        std::cout << array[i] << std::endl;
    }

    // build heap again
    buildHeap();
}

template<class T>
void Heap<T>::print_des() {
    // heap sort
    buildHeapMin();

    for (int i = count - 1; i > 0; i--) {
        std::swap(array[0], array[i]);

        heapifyDownMin(0, i);
    }

    for (int i = 0; i < count; i++) {
        std::cout << array[i] << std::endl;
    }

    // build heap again
    buildHeap();
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
        heapifyDown(i, count);
}

template <class T>
void Heap<T>::buildHeap() {
    heapType ? buildHeapMax() : buildHeapMin();
}

template <class T>
void Heap<T>::buildHeapMin() {
    for (int i = (count - 1) / 2; i >= 0; i--)
        heapifyDownMin(i, count);
}

template <class T>
void Heap<T>::buildHeapMax() {
    for (int i = (count - 1) / 2; i >= 0; i--)
        heapifyDownMax(i, count);
}

template <class T>
void Heap<T>::heapifyDown(int index, int n) {
    heapType ? heapifyDownMax(index, count) : heapifyDownMin(index, count);
}

template <class T>
void Heap<T>::heapifyDownMax(int index, int n) {
    int child1 = 2 * index + 1;
    int child2 = 2 * index + 2;
    int max = index;
    if (child1 < n && compare(array[max], array[child1]))
        max = child1;
    if (child2 < n && compare(array[max], array[child2]))
        max = child2;
    if (compare(array[index], array[max])) {
        std::swap(array[index], array[max]);
        heapifyDownMax(max, n);
    }
}

template <class T>
void Heap<T>::heapifyDownMin(int index, int n) {
    int child1 = 2 * index + 1;
    int child2 = 2 * index + 2;
    int max = index;
    if (child1 < n && compare(array[child1], array[max]))
        max = child1;
    if (child2 < n && compare(array[child2], array[max]))
        max = child2;
    if (compare(array[max], array[index])) {
        std::swap(array[index], array[max]);
        heapifyDownMin(max, n);
    }
}

template <class T>
void Heap<T>::heapifyUp(int index) {
    heapType ? heapifyUpMax(index) : heapifyUpMin(index);
}

template <class T>
void Heap<T>::heapifyUpMax(int index) {
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
void Heap<T>::heapifyUpMin(int index) {
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
    heapifyUp(count);
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
    heapifyDown(0, count);
}


#endif //HEAP_HEAP_H
