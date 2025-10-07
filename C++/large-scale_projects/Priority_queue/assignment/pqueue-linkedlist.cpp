/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"
 
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	currentSize = 0; //initialize size to 0
	head = nullptr; //no elements, just a pointer(we have to initialize the pointer)
}
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	node* tmp; 
	while (head != nullptr) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return currentSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (currentSize == 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
	if (isEmpty()) {
		head = new node(value);
		currentSize++;
		return; 
	} 
	node* ptr = head; 
	if (value < ptr->data) {
		head = new node(value, ptr);
		currentSize++;
		return;
	}
	//we gotta find the node, whose pointer variable stores the address of such node, whose data is bigger
	//than value
	while (ptr->next != nullptr) {
		if (ptr->next->data > value) {
			ptr->next = new node(value, ptr->next);
			currentSize++;
			return;
		}
		ptr = ptr->next;
	}
	//Getting here means that our element is bigger than each element inside linked list
	//our ptr variable conveniently stores the address of the last element 
	ptr->next = new node(value);
	currentSize++;
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("Cannot peek at empty queue");
	}
	return head->data;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("Cannot dequeue an empty queue");
	}
	string min = head->data;
	node* tmp = head;
	head = head->next;
	delete tmp;
	currentSize--;
	return min;
}