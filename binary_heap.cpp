#include <iostream>
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

    // todo: implement push function
    void push(int x) {

    }

    // todo: implement pop function
    int pop() {

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
    
    return 0;
}
