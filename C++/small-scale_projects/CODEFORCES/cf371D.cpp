#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std; 
/*
understand the test case 
3
0/5 0/10 0/8 

5/5 7/10 0/8 
5/5 10/10 3/8
5/5 10/10 5/8
now I understand the problem 
now we have to simulate the problem
maintain the indices inside the tree set. 
if the particular vessel becomes full, it will remain 
full over all duration of quering. so we will pop it out 
of the set. then second type operation will simply be returning
set[index] and first type operation simply will be incrementing
the index(it is guaranteed that some volume is left). if volume
does not become full, we continue, otherwise, we let it
overflow, delete that index out of the set and give the
remaining water to next vessel, if that overflows also, we do
the same thing. This will work, but we have to answer few 
questions. 
Q1: what if second type operation asks for index erased from 
set?  range
A1: we check if the index is in the set, if it is not, it means
it is filled in completely, so we return its volume, if it is 
in the set, then we can track the water of each vessel in the
separate vector, where we store the filling of not completely
filled vessels. 
Q2: what if first type operations asks for index erased from 
set? 
A2: this is where we use the set's lower_range operation, we
want to find first not fully filled vessel after that vessel. 
That is exactly what lower_bound function does.
*/
int main() {
	int n, m, typeOf, p, x, k; cin >> n;
	vector<int> vol(n + 1), track(n + 1, 0); 
	set<int> vessels; 
	//volumes are in ascending order
	//exactly as they should be 
	for(int i = 1; i <= n; i++)cin >> vol[i]; 
	for(int i = 1; i <= n; i++)vessels.insert(i);  
	//now, we start processing
	cin >> m;
	for(int i = 0; i < m; i++) {
		cin >> typeOf; 
		//here it can be combined
		if(typeOf == 1) {
			cin >> p >> x; 
			set<int>::iterator it = vessels.lower_bound(p);
			//if we reach the end, we do not do anything
			while(it != vessels.end()) {
				track[*it] += x;
				if(track[*it] < vol[*it]) {
					break; //no problem
				} 
				//overflow detected
				else {
					//x then becomes extra water
					x = track[*it] - vol[*it]; 
					it = vessels.erase(it); 
				}
			}
		} 
		else {
			cin >> k; 
			set<int>::iterator it = vessels.find(k);
			//it is not in the set, so it is filled completely
			if(it == vessels.end())cout << vol[k] << endl; 
			//in this case, it is not fully filled 
			else {
				cout << track[k] << endl; 
			}
		}
	}
	return 0; 
}






