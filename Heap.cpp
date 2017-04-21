/* Heap.cpp
 *
 * Heap class that implements the following public functions:
 * insert, extract, out
 *
 * Author: McKay Madsen
 *
 */



#include <iostream>

using namespace std;

class Heap {

private:

	/*
	 * MyDynamicArray class
	 */
	class MyDynamicArray {
	    private:
	        int size, limit, error, *a;
	    public:
	        MyDynamicArray() {
	            a = new int[limit = 2];
	            size = error = 0;
	        }
	        MyDynamicArray(int s) {
	            a = new int[limit = size = s];
	            error = 0;
	        }
	        ~MyDynamicArray() {
	            delete a;
	        }
	        int& operator[](int i){
	            if (i>=size || i < 0) {
	            	return error;
	            }
	            return *(a+i);
	        }
	        void add(int v) {
	            if(size == limit) {
	                int *temp = new int[limit *= 2];
	                for (int i = 0; i<size; i++)  temp[i]=a[i];
	                delete a;
	                a = temp;
	            }
	            a[size++] = v;
	        }
	        void del() {
	            size--;
	            if (size <= limit/4) {
	                int *temp = new int[limit /= 2];
	                for (int i = 0; i<size; i++)  temp[i]=a[i];
	                delete a;
	                a = temp;
	            }
	        }
	        int length() { return size;}
	        void clear() {
	            delete a;
	            a = new int[limit=2];
	            size = 0;
	        }
	};




	MyDynamicArray heap;

    int parent(int index) {
        return (index - 1) / 2;
    }

    int left(int index) {
        return (2 * index + 1);
    }

    int right(int index) {
        return (2 * index + 2);
    }

    void heapify_up_min(int index) {
    	int temp = 0;
        if (index && heap[parent(index)] > heap[index]) {
        	temp = heap[index];
        	heap[index] = heap[parent(index)];
        	heap[parent(index)] = temp;

            heapify_up_min(parent(index));
        }
    }


    void heapify_down_min(int index) {
    	int temp = 0; int R = right(index); int L = left(index); int smallest = index;

        if (L < size() && heap[L] < heap[index]) {
            smallest = L;
        }
        if (R < size() && heap[R] < heap[smallest]) {
            smallest = R;
        }
        if (smallest != index) {
            temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;

            heapify_down_min(smallest);
        }
     }


    void heapify_up_max(int index) {
    	int temp = 0;
        if (index && heap[parent(index)] < heap[index]) {
            temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;

            heapify_up_max(parent(index));
        }
    }


    void heapify_down_max(int index) {
    	int temp = 0; int R = right(index); int L = left(index); int largest = index;

        if (L < size() && heap[L] > heap[index]) {
            largest = L;
        }
        if (R < size() && heap[R] > heap[largest]) {
            largest = R;
    	}
        if (largest != index) {
            temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;

            heapify_down_max(largest);
        }
    }


    void heapify() {
    	int length = size(), i;
    	if (min_max == "max") {
    	    for(i = length-1; i >= 0; --i) {
    	    	heapify_down_max(i);
    	    }
		}
    	else if (min_max == "min") {
    	    for(i = length - 1; i >= 0; --i) {
    	    	heapify_down_min(i);
    	    }
    	}
    }

public:
    /*
     * helper for min/max later in function
     */
    string min_max;

	/*
	 * default constructor: Default constructor,
	 * creates an empty min ordered heap
	 */
	Heap() {
		min_max = "min";
	}

	/*
	 *  Constructor, first parameter is an unordered array of elements
	 *  and the second parameter is the number of elements in the array.
	 *  The heap should be built in O(N) time using the bottom up heap
	 *  building algorithm. The third parameter determines whether the
	 *  heap is a min or max ordered heap, depending on whether the value
	 *  of the string is “min” or “max”. The default value should be  “min”.
	 */
	Heap(int arr[], int num, string str = "min") {
		int i=0;
		if (str == "max") {
			min_max = "max";
			for (i = 0; i < num; i++) {
				heap.add(arr[i]);
			}
			heapify();
		}

		else {
			min_max = "min";
			for (i = 0; i < num; i++) {
				heap.add(arr[i]);
			}
			heapify();
		}
	}

	/*
	 * helper - returns the length of heap
	 */
	int size() {
		return heap.length();
	}

	/*
	 * insert the integer parameter into the heap
	 */
	void insert(int element) {
		heap.add(element);
		if (min_max == "min") {
			heapify_up_min(size() - 1);
		}
		if (min_max == "max") {
			heapify_up_max(size() - 1);
		}
	}

	/*
	 * Removes the root of the heap and returns that value
	 */
	int extract() {
	    if (heap.length() == 0) { return -1;}
		int i = heap[0];
		heap[0] = heap[heap.length() - 1];
		heap.del();
		if (min_max == "min") {
			heapify_down_min(0);
		}
		else if (min_max == "max") {
			heapify_down_max(0);
		}
		return i;
	}

	/*
	 * out function: prints the values in the heap, in the
	 * order they are stored
	 */
	void out() {
		for (int i = 0; i < heap.length(); i++){
			std::cout<< heap[i] <<" ";
		}
    	std::cout << std::endl;
	}

};



