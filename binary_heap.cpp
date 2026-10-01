#include <iostream>
#include <stdexcept>
using namespace std;

class MinHeap {
    private:
    // allocate memory for 100 integers (max size of heap for now)
    int heap[100];
    // initialize variable to track current size of heap
    int heapSize;

    public:
    MinHeap(): heapSize(0) {}

    int getSize() {
	return heapSize;
    }

    void push(int x) {
    if (heapSize >= 100) {
        throw runtime_error("Cannot push element, heap at max capacity");
    }

    // insert at the end
    int idx = heapSize;
    heap[heapSize++] = x;

    // heapify up
    if (idx == 0) return;                               // prevent root element from being heapify'd up
    int parentIdx = (idx % 2 ? idx / 2 : idx / 2 - 1); // get index of parent
    while (idx > 0 && heap[idx] < heap[parentIdx]) {
        swap(heap[idx], heap[parentIdx]);               // swap while current element is less than parent
        idx = parentIdx;                                // update current index to parent of index
        if (idx == 0) break;                            // stop heapify when the root is reached
        parentIdx = (idx % 2 ? idx / 2 : idx / 2 - 1);      // get index of parent again
    }
    }

    // todo: implement pop function
    int pop() {

    }
};

class MaxHeap {
    private:
    int* heap; // for dynamic allocation
    size_t heapMaxSize;
    size_t heapSize;
    
    public:
    // default heap max size is 2^10
    MaxHeap(size_t maxSize = (1 << 10)): heap(new int[maxSize]), heapMaxSize(maxSize), heapSize(0) {}

    size_t getMaxSize() {
	return heapMaxSize;
    }

    size_t getSize() {
	return heapSize;
    }

    void push(int x) {
	if(heapSize == heapMaxSize)
	    throw runtime_error("Cannot push element, heap at max capacity");

	// insert at the end
	size_t idx = heapSize;
	heap[heapSize++] = x;
    
	// heapify up
	size_t parentIdx = (idx % 2 ? idx/2 : idx/2 - 1);		// get index of parent
	while(parentIdx < idx && heap[idx] > heap[parentIdx]) {
	    swap(heap[idx], heap[parentIdx]);				// swap while current element is greather than parent
	    idx = parentIdx;						// update current index to parent of index
	    if(idx == 0) break;						// stop heapify process when the root is reached
	    parentIdx = (idx % 2 ? idx/2 : idx/2 - 1);			// get index of parent again
	}
    }

    int pop() {
	if(heapSize == 0)
	    throw runtime_error("Cannot pop, heap is empty");

	// store root element
	int root = heap[0];

	// heapify down
	heap[0] = heap[--heapSize];			// put last element at root
	size_t idx = 0;
	while(idx < heapSize) {
	    size_t leftIdx = 2*idx + 1;			// get index of left parent
	    size_t rightIdx = 2*idx + 2;		// get index of right parent

	    // only has left child
	    if(leftIdx < heapSize && rightIdx >= heapSize && heap[leftIdx] > heap[idx]) {
		swap(heap[leftIdx], heap[idx]);		// swap to wiich left child if it is greater
		idx = leftIdx;				// update current index to index of left child
	    }

	    // has both children
	    else if(rightIdx < heapSize) {
		// find out which child is greater
		int swapIdx = leftIdx;
		if(heap[rightIdx] > heap[swapIdx])
		    swapIdx = rightIdx;

		// swap if child is greater than current element
		if(heap[swapIdx] > heap[idx]) {
		    swap(heap[swapIdx], heap[idx]);
		    idx = swapIdx;
		}
	    }

	    // has no children
	    else break;
	}

	return root;
    }
};


int main() {
    // tests
    MinHeap minheap;
    minheap.push(1);
    minheap.push(3);
    minheap.push(8);
    minheap.push(7);
    minheap.push(0);

    cout << minheap.pop() << endl; // 0
    cout << minheap.pop() << endl; // 1
    cout << minheap.pop() << endl; // 3
    cout << minheap.pop() << endl; // 7
    cout << minheap.pop() << endl; // 8
    cout << minheap.pop() << endl; // must throw error or state that you can no longer pop since heap is empty
    
    // cout << endl;

    // MaxHeap maxheap;
    // maxheap.push(1);
    // maxheap.push(3);
    // maxheap.push(8);
    // maxheap.push(7);
    // maxheap.push(0);

    // cout << maxheap.pop() << endl; // 8
    // cout << maxheap.pop() << endl; // 7
    // cout << maxheap.pop() << endl; // 3
    // cout << maxheap.pop() << endl; // 1
    // cout << maxheap.pop() << endl; // 0
    // cout << maxheap.pop() << endl; // must throw error or state that you can no longer pop since heap is empty
    
    return 0;
}
