/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */

 
#include "pqueue-extra.h"
#include "error.h"

ExtraPriorityQueue::ExtraPriorityQueue() {
	head = nullptr;
	currentSize = 0;
}
//recursive deletion 
ExtraPriorityQueue::~ExtraPriorityQueue() {
	dfsDelete(head);
}

int ExtraPriorityQueue::size() {
	return currentSize;
}

bool ExtraPriorityQueue::isEmpty() {
	return (currentSize == 0);
}

void ExtraPriorityQueue::enqueue(string value) {
	node* newHeap = new node(value, nullptr, nullptr);
	if (isEmpty()) {
		head = newHeap;
	}
	else {
		head = merge(head, newHeap);
	}
	currentSize++;
}

string ExtraPriorityQueue::peek() {
	if (isEmpty()) {
		error("Cannot peek at empty queue");
	}
	else {
		return head->value;
	}
}

string ExtraPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("Cannot dequeue an empty queue");
	}
	else {
		string val = head->value;	
		head = onePass(head);
		currentSize--;
		return val;
	}
}

ExtraPriorityQueue::node* ExtraPriorityQueue::merge(node* first, node* second) {
	if (first == nullptr || second == nullptr) {
		if (first != nullptr)return first;
		else if (second != nullptr)return second;
		return nullptr; 
	}
	if (first->value <= second->value) {
		//first's child must be second 
		node* tmp = first->child; 
		first->child = second; 
		second->sibling = tmp;
		return first;
	}
	else return merge(second, first);
}

void ExtraPriorityQueue::dfsDelete(node* start) {
	if (start == nullptr)return;
	dfsDelete(start->child);
	dfsDelete(start->sibling);
	delete start;
}

ExtraPriorityQueue::node* ExtraPriorityQueue::onePass(node* start) {
	node* tmp = start;
	start = start->child; //now start points to first child 
	delete tmp; 
	//now we have to traverse through the siblings and merge them all together
	if (start == nullptr)return nullptr;
	while (start->sibling != nullptr) {
		node* tmp = start->sibling->sibling;
		start = merge(start, start->sibling); 
		start->sibling = tmp;
	}
	return start;
}