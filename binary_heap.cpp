#include <iostream>
#include <stdexcept>
using namespace std;

// base class for min and max heap with variable data type T and Compare function
// Compare = std::less<T> for MinHeap
// Compare = std::greater<T> for MaxHeap
template<typename T, typename Compare>
class BaseHeap {
    private:
    T* heap; 		// for dynamic allocation
    size_t heapMaxSize; // to track max size of heap
    size_t heapSize; 	// for tracking current size of heap

    public:
    BaseHeap(size_t maxSize): heap(new T[maxSize]), heapMaxSize(maxSize), heapSize(0) {}

    size_t getMaxSize() {
	return heapMaxSize;
    }

    size_t getSize() {
	return heapSize;
    }

    void push(T x) {
	if (heapSize >= heapMaxSize) {
	    throw runtime_error("Cannot push element, heap at max capacity");
	}

	// insert at the end
	size_t idx = heapSize;
	heap[heapSize++] = x;

	// heapify up
	if (idx == 0) return;                               	// prevent root element from being heapify'd up
	size_t parentIdx = (idx % 2 ? idx / 2 : idx / 2 - 1); 	// get index of parent
	while(idx > 0 && Compare()(heap[idx], heap[parentIdx])) {
    	    swap(heap[idx], heap[parentIdx]);               	// swap while current element is [lesser (for MinHeap) | greater (for MaxHeap)] than parent element
    	    idx = parentIdx;                                	// update current index to parent of index
    	    if (idx == 0) break;                            	// stop heapify when the root is reached
    	    parentIdx = (idx % 2 ? idx / 2 : idx / 2 - 1);      // get index of parent again
    	}
    }

    T pop() {
        if (heapSize == 0) {
            throw runtime_error("Cannot pop, heap is empty!");
        }

        // store [minimum (for MinHeap) | maximum (for MaxHeap)] value (root) to return it later
        T root = heap[0];

        // move the very last element to the root and shrink the heap size
        heap[0] = heap[--heapSize];

        // heapify down
        size_t idx = 0;
        while (idx < heapSize) {
            size_t leftIdx = 2 * idx + 1; // get index of left child
            size_t rightIdx = 2 * idx + 2; // get index of right child
            
            // case a: only has a left child
            if (leftIdx < heapSize && rightIdx >= heapSize){
		if (Compare()(heap[leftIdx], heap[idx])) {
                    swap(heap[leftIdx], heap[idx]); // swap if left child is [smaller (for MinHeap) | larger (for MaxHeap)] 
                    idx = leftIdx;
                } else {
                    break; // node is already [smaller (for MinHeap) | larger (for MaxHeap)] than child, stop sinking
                }
            } else if (rightIdx < heapSize) { // case b: has both children
                // find out which child is the absolute [smallest (for MinHeap) | greatest (for MaxHeap)]
                size_t swapIdx = leftIdx;
		if (Compare()(heap[rightIdx], heap[swapIdx])) {
                    swapIdx = rightIdx;
                }
                // swap if that [smallest (for MinHeap) | largest (for MaxHeap)] child is less than the current element
		if (Compare()(heap[swapIdx], heap[idx])) {
                    swap(heap[swapIdx], heap[idx]);
                    idx = swapIdx;
                } else {
                    break; // node is [smaller (for MinHeap) | large (for MaxHeap)] than both children, stop sinking
                }
            } else { //	case c: has no children
                break;
            }     
        }
        return root;
    }
};

template<typename T, typename Compare = less<T>>
class MinHeap : public BaseHeap<T, Compare> {
    public: 
    // set default max size to 2^10
    MinHeap(size_t maxSize = (1 << 10)): BaseHeap<T, Compare>(maxSize) {}
};

template<typename T, typename Compare = greater<T>>
class MaxHeap : public BaseHeap<T, Compare> {
    public: 
    // set default max size to 2^10
    MaxHeap(size_t maxSize = (1 << 10)): BaseHeap<T, Compare>(maxSize) {}
};

int main() {
    cout << "--- For MinHeap ---" << endl;

    cout << "Initializing MinHeap without passing max size..." << endl;
    MinHeap<int> minheap;
    cout << "Inserting 1..." << endl;
    minheap.push(1);
    cout << "Inserting 3..." << endl;
    minheap.push(3);
    cout << "Inserting 8..." << endl;
    minheap.push(8);
    cout << "Inserting 7..." << endl;
    minheap.push(7);
    cout << "Inserting 0..." << endl;
    minheap.push(0);

    cout << endl;

    cout << "Max Size: " << minheap.getMaxSize() << endl;
    cout << "Current Size: " << minheap.getSize() << endl;
    cout << "Popping elements..." << endl;
    cout << minheap.pop() << endl; // 0
    cout << minheap.pop() << endl; // 1
    cout << minheap.pop() << endl; // 3
    cout << minheap.pop() << endl; // 7
    cout << minheap.pop() << endl; // 8
    // minheap is now empty
    try {
	cout << minheap.pop() << endl;
    } catch(exception& e) {
	cerr << e.what() << endl;
    }
    
    cout << endl;

    cout << "--- For MaxHeap ---" << endl;

    cout << "Initializing MaxHeap with passed max size of 5..." << endl;
    MaxHeap<int> maxheap(5);
    cout << "Inserting 1..." << endl;
    maxheap.push(1);
    cout << "Inserting 3..." << endl;
    maxheap.push(3);
    cout << "Inserting 8..." << endl;
    maxheap.push(8);
    cout << "Inserting 7..." << endl;
    maxheap.push(7);
    cout << "Inserting 0..." << endl;
    maxheap.push(0);
    // exceeds max capacity
    try {
	cout << "Inserting 10..." << endl;
	maxheap.push(10);
    } catch(exception& e) {
	cout << e.what() << endl;
    }

    cout << endl;
    
    cout << "Max Size: " << maxheap.getMaxSize() << endl;
    cout << "Current Size: " << maxheap.getSize() << endl;
    cout << "Popping elements..." << endl;
    cout << maxheap.pop() << endl; // 8
    cout << maxheap.pop() << endl; // 7
    cout << maxheap.pop() << endl; // 3
    cout << maxheap.pop() << endl; // 1
    cout << maxheap.pop() << endl; // 0
    // maxheap is now empty
    try {
	cout << maxheap.pop() << endl;
    } catch(exception& e) {
	cerr << e.what() << endl;
    }
    
    return 0;
}
