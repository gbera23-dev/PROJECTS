#include <iostream> 
#include <set>
using namespace std; 
/*
4 3 4 
xcoord = 0, 4 
ycoord = 0, 3 
widths = 4
heigth = 3 

H 2  
xcoord = 0, 4 
ycoord = 0, 2, 3 
widths = 4 		so we get 8 
heigths = 1, 2 

V 2
xcoord = 0, 2, 4 
ycoord 0, 2, 3 
widths = 2, 2  so we get 4 
heigths = 1, 2 

V 3  
xcoord = 0, 2, 3, 4 
ycoord = 0, 2, 3 
widths = 1, 1, 2  
heights = 1, 2 
normal set cannot be used since we could have multiple widths
or heights, so we maintain counts of widths and heigths in 
hashmap or use multiset. 
vector could be used too. 
vector of size w and of size h, but that is too much memory
multiset maintians multiple elements and also orders its 
elements in increasing order, only thing left is to determine
what lower_bound returns 
each query requires total logn operations 
so time complexity is O(n*logn) 
*/
int main() {
	long long w, h, n; cin >> w >> h >> n; 
	//represent currently which lines are drawn 
	set<long long> xcoord, ycoord;
	xcoord.insert(0); ycoord.insert(0); 
	xcoord.insert(w); ycoord.insert(h);  
	//for each xcoord, maintains width of the 
	//rectangle(similar with heights) 
	multiset<long long> widths, heights; 
	//initially 
	widths.insert(w); heights.insert(h);  
	for(long long i = 0; i < n; i++) {
		char type; cin >> type;
		long long num; cin >> num; 
		if(type == 'H') {
			//find the first index smaller than 
			//num, horizontal cut modifies heights 
			//and we need to access ycoords
			set<long long>::iterator it = ycoord.lower_bound(num); 
			long long after = *it; it--; 
			long long before  = *it; 
			multiset<long long>:: iterator found = heights.find(after - before); 
			heights.erase(found); //remove only one instance of it 
			heights.insert(num - before); 
			heights.insert(after - num);
			ycoord.insert(num); 
		} else {
			set<long long>::iterator it = xcoord.lower_bound(num); 
			long long after = *it; it--; 
			long long before  = *it; 
			multiset<long long>:: iterator found = widths.find(after - before); 
			widths.erase(found); 
			widths.insert(num - before); 
			widths.insert(after - num);
			xcoord.insert(num);
		}
		cout << (long long)(*widths.rbegin())*(*heights.rbegin()) << endl;
	}
	return 0; 
}
