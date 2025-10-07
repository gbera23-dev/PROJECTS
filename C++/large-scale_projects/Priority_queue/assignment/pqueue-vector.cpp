/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
 
VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {
	return data.size();
}

bool VectorPriorityQueue::isEmpty() {
	return data.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	data.add(value);
}

string VectorPriorityQueue::peek() {
	if (data.isEmpty()) {
		error("Tried to peek at empty queue");
	}
	else {
		string min = data[0];
		for (int i = 1; i < data.size(); i++) {
			if (data[i] < min) {
				min = data[i];
			}
		}
		return min;
	}
}

string VectorPriorityQueue::dequeueMin() {
	if (data.isEmpty()) {
		error("Tried to dequeue an empty queue");
	}
	else {
		string min = data[0];
		int index = 0; //index of the element we are popping out
		for (int i = 1; i < data.size(); i++) {
			if (data[i] < min) {
				min = data[i];
				index = i;
			}
		}
		data.remove(index);
		return min;
	}
}

