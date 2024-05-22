#include<vector>
#include<iostream>
#include<cassert>
#include "Item.h"

using namespace std;


template<class T >
class Heap {
private:
	
	Item *array { };

	int size { };
	int capacity { 1000 };
    bool (*compare)(T d1, T d2);
    static bool defaultComb(T d1, T d2) {
        return d1 < d2;
    }

	int left(int node) {
		int p = 2 * node + 1;
		if (p >= size)
			return -1;
		return p;
	}
	int right(int node) {
		int p = 2 * node + 2;
		return p >= size ? -1 : p;
	}
	int parent(int node) {
		return node == 0 ? -1 : (node - 1) / 2;
	}

	void heapify_up(int child_pos) {
		// stop when parent is smaller (or no parent)
		int par_pos = parent(child_pos);
		if (child_pos == 0 || compare(array[par_pos] , array[child_pos]))
			return;
		swap(array[child_pos], array[par_pos]);
		heapify_up(par_pos);
	}

	void heapify_down(int parent_pos) {	// O(logn)
		int child_pos = left(parent_pos);
		int right_child = right(parent_pos);

		if (child_pos == -1) // no children
			return;
		// is right smaller than left?
		if (right_child != -1 && compare(array[right_child] , array[child_pos]))
			child_pos = right_child;

		if  (compare (array[child_pos],array[parent_pos]  )) {
			swap(array[parent_pos], array[child_pos]);
			heapify_down(child_pos);
		}
	}
	void heapifyprice(int n, int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && compare(array[left] , array[smallest]))
            smallest = left;

        if (right < n && compare(array[right] , array[smallest]))
            smallest = right;

        if (smallest != i) {
            swap(array[i], array[smallest]);
            heapifyprice(n, smallest);
        }
    }
	void heapifyname(int n, int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && (array[left].get_name() < array[smallest].get_name() ))
            smallest = left;

        if (right < n && (array[right].get_name() < array[smallest].get_name() ))
            smallest = right;

        if (smallest != i) {
            swap(array[i], array[smallest]);
            heapifyname(n, smallest);
        }
    }
	

  
	void buildMinHeapprice() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapifyprice(size, i);
        }
    }
	void buildMinHeapname() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapifyname(size, i);
        }
    }
public:
	
     Heap(bool (*func)(T d1, T d2) = defaultComb){
        array = new T[capacity] { };
		size = 0;
        this->compare = func;
     }

	 void Minheapprice(){
        buildMinHeapprice();

        for (int i = size - 1; i > 0; i--) {
            swap(array[0], array[i]);
            heapifyprice(i, 0);
        }

        // To sort in ascending order using a min-heap, reverse the array
        for (int i = 0 ; i < size/2;i ++ ){
			swap(array[i], array[size-i-1]);
		}
    }

	void Minheapname() {
        buildMinHeapname();

        for (int i = size - 1; i > 0; i--) {
            swap(array[0], array[i]);
            heapifyname(i, 0);
        }

        // To sort in ascending order using a min-heap, reverse the array
        for (int i = 0 ; i < size/2;i ++ ){
			swap(array[i], array[size-i-1]);
		}
    }

	void Maxheapname() {
        buildMinHeapname();

        for (int i = size - 1; i > 0; i--) {
            swap(array[0], array[i]);
            heapifyname(i, 0);
        }

        // To sort in ascending order using a min-heap, reverse the array
       
    }

	void Maxheapprice(){
        buildMinHeapprice();

        for (int i = size - 1; i > 0; i--) {
            swap(array[0], array[i]);
            heapifyprice(i, 0);
        }

        // To sort in ascending order using a min-heap, reverse the array
        
    }
	
	
	~Heap() {
		delete[] array;
		array = nullptr;
	}
	T* get_item(){
		return array;
	}
	void push(T key) {
		assert(size + 1 <= capacity);
		array[size++] = key;
		heapify_up(size - 1);
	}

	void pop() {
		assert(!isempty());
		array[0] = array[--size];
		heapify_down(0);
	}

	T top() {
		assert(!isempty());
		return array[0];
	}

	bool isempty() {
		return size == 0;
	}
	void print (){
		for (int i = 0 ; i < size;i ++ ){
			cout << array[i] << ' ';
		}
	}
};


int main() {
	// creat_heap_n();
	Heap<Item> heap;
	Item i1("ahmed","milk",1);
	Item i2("ali","milk",4);
	Item i3("smil","milk",3);
	Item i4("d","milk",7);
	Item i5("ff","milk",5);
    heap.push(i1);
    heap.push(i2);
    heap.push(i3);
    heap.push(i4);
    heap.push(i5);
	heap.Maxheapprice();
	Item* array= heap.get_item();
	for (int i = 0 ; i < 5 ; i ++){
		cout << "Maxheap with price ";
		cout << array[i].get_price() << ' ';
	}
	


}
