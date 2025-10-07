
#ifndef UNIONF_H
#define UNIONF_H
#include "TrailBlazerTypes.h"

class UnionFind{
public: 
	//we need to know quantity of elements initially to initialize arrays
	UnionFind(int n); 
	//destructor for arrays
	~UnionFind();
	//finds the representative of the loc
	int find(int loc);
	//does the union of the two disjoint sets
	void merge(int loc1, int loc2); 
private: 
	int quantity;
	int* parent; 
	int* sizes; 
};
#endif
