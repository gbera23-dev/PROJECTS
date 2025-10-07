#include "UnionFind.h"
UnionFind::UnionFind(int n) {
	quantity = n;
	parent = new int[quantity];
	sizes = new int[quantity];
	for (int i = 0; i < n; i++) {
		parent[i] = i; 
		sizes[i] = 1;
	}
} 
UnionFind::~UnionFind() {
	delete[] parent;
	delete[] sizes; 
}
int UnionFind::find(int loc) {
	if (parent[loc] == loc) {
		return loc; 
	}
	parent[loc] =  find(parent[loc]); //allows the tree to be shallow and hence make it faster to reach root
	return parent[loc]; 
}
void UnionFind::merge(int loc1, int loc2) {
	int one = find(loc1); 
	int two = find(loc2); 
	if (sizes[one] > sizes[two]) {
		parent[two] = one; 
		sizes[one] += sizes[two]; 
	}
	else {
		parent[one] = two; 
		sizes[two] += sizes[one]; 
	}
}