/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	array = nullptr;
	currentSize = 0;
	maxCapacity = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] array;
}

int HeapPriorityQueue::size() {
	return currentSize;
}

bool HeapPriorityQueue::isEmpty() {
	return currentSize == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if (isEmpty()) {
		delete[] array; //we delete the object array points to and initialize new array with one string capacity
		array = new string[1];
		currentSize = 1;
		maxCapacity = 1;
		array[0] = value;
		return;
	}
	if (currentSize == maxCapacity) {
		extendArray(array);
	}
	array[currentSize] = value; 
	currentSize++;
	bubbleUp(array);
}

string HeapPriorityQueue::peek() {	
	if (isEmpty()) {
		error("Cannot peek at empty queue");
	}
	return array[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("Cannot dequeue an empty queue");
	}
	//While popping, we save the slot from which pop happened(string is still there, but we decrease currentSize)
	//This allows us to maintain capacity of the array 
	string sol = array[0];
	swap(array[0], array[currentSize - 1]);
	currentSize--; //decreases the size of the dymanic array due to popping
	bubbleDown(array); 
	return sol;
}

int HeapPriorityQueue::parentNode(int value) {
	return (value - 1) / 2;
}

int HeapPriorityQueue::childNode(int value) {
	return 2*value + 1;
}

void HeapPriorityQueue::extendArray(string*& array) {
	string* tmp = new string[2 * maxCapacity];
	for (int i = 0; i < size(); i++) {
		tmp[i] = array[i];
	}
	delete[] array;
	array = tmp;
	maxCapacity = 2 * maxCapacity;
}
void HeapPriorityQueue::bubbleUp(string*& array) {
	int copy = currentSize - 1;
	if (parentNode(copy) < 0) {
		return;
	}
	while (array[parentNode(copy)] > array[copy]) {
		swap(array[parentNode(copy)], array[copy]);
		copy = parentNode(copy);
	}
}

void HeapPriorityQueue::bubbleDown(string*& array) {
	//first case is that size of the heap becomes 0 after popping or there will be one element
	if (currentSize <= 1) {
		return; //we do not modify anything
	}
	int index = 0;
	int toSwapWith;
	int leftChild;
	int rightChild;
	while (childNode(index) < currentSize) {
		leftChild = childNode(index);
		rightChild = leftChild + 1;;
		toSwapWith = leftChild;
	    if ((rightChild < currentSize) && (array[leftChild] > array[rightChild])) {
			toSwapWith++;
		}
		if (array[index] > array[toSwapWith]) {
			swap(array[index], array[toSwapWith]);
			index = toSwapWith;
		}
	    else break; //if the parent is not bigger than the child, we just stop the loop 
	}
}