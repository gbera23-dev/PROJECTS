/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 */
#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an
 * binary heap.
 */
class HeapPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a binary heap. */
	HeapPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~HeapPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
	string* array;
	int currentSize; //gives us amount of elements array contains
	int maxCapacity; //gives us the maximum capacity of the array at the particular point
	int parentNode(int value); //returns the index of the parent node 
	int childNode(int value); //returns the index of the child node
	void extendArray(string*& array); //Allows us to create more storage for the elements
	void bubbleUp(string*& array); //Method corrects the heap structure after adding new element
	void bubbleDown(string*& array); //Method corrects the heap structure after popping min element
};

#endif
