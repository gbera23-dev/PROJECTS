/**********************************************
 * File: pqueue-extra.h
 *
 * 
 */
#ifndef PQueue_Extra_Included
#define PQueue_Extra_Included

#include <string>
using namespace std;
/*
A class representing the priority queue backed by the pairing heap
*/
class ExtraPriorityQueue {
public:
	/* Constructs a new, empty priority queue. */
	ExtraPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~ExtraPriorityQueue();
	
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
	struct node {
		string value;
		node* sibling;
		node* child;
		node(string val = "", node* sib = nullptr, node* Ch = nullptr) {
			value = val;
			sibling = sib;
			child = Ch;
		}
	};
	int currentSize;
	node* head;
	node* merge(node* first, node* second); //Merges two heaps(one who has the lower value becomes second's child) 
	void dfsDelete(node* start);//Deletes the whole object using recursive dfs
	node* onePass(node* head); //Removes the parent node and merges parent's children together 
};

#endif
