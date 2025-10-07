/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = nullptr; //head at first does not point to anything
	tail = nullptr; //tail at first does not point to anything
	currentSize = 0; //initial size is 0 
}
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	node* tmp;
	while (head != nullptr) {
		tmp = head; 
		head = head->next; 
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return currentSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return currentSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	if (isEmpty()) {
		node* newNode = new node(value, nullptr, nullptr); 
		head = newNode;
		tail = newNode;
		currentSize++;
	}
	else {
		node* newNode = new node(value, nullptr, head);
		head->prev = newNode;
		head = newNode;
		currentSize++;
	}
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("Cannot peek at empty queue");
	}
		string minValue = head->data;
		for (node* traverse = head; traverse != nullptr; traverse = traverse->next) {
			if (minValue > traverse->data) {
				minValue = traverse->data;
			}
		}
		return minValue;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("Cannot dequeue an empty queue");
	}
	node* min = head; 
	for (node* tmp = head; tmp != nullptr; tmp = tmp->next) {
		if (min->data > tmp->data) {
			min = tmp;
		}
	}
	currentSize--;
	return popMin(min);
}

string DoublyLinkedListPriorityQueue::popMin(node*& min) {
	string sol = min->data;
	if (min->prev != nullptr && min->next != nullptr) {
		min->prev->next = min->next;
		min->next->prev = min->prev;
	}
	else if (min->prev == nullptr && min->next != nullptr) {
		head = head->next;
		head->prev = nullptr;
	}
	else if (min->prev != nullptr && min->next == nullptr) {
		tail = tail->prev;
		tail->next = nullptr;
	}
	else {
		head = nullptr, tail = nullptr;
	}
	delete min;
	return sol;
}
