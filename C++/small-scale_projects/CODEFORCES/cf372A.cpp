#include <iostream> 
#include <set> 
#include <vector>
#include <algorithm>  
using namespace std; 
/*PROBLEM ANALYSIS: 
8 
2 2 4 5 6 7 8 9 
cut array into two parts 
2 2 4 5 

6 7 8 9 
now we shall prove that this algorithm yields the optimal
result. for the sake of simplicity assume that n is even. 
if n is odd, we know for sure, best we can get is still 
n / 2. 
ALGORITHM: given the array a1, a2, a3... an. 
divide it into two equal parts 
a1 a2 ... a(n/2) 

a(n/2 + 1), a(n/2 + 2)... a(n) 
for each ai from the first half, pair the first a(j) from
the second half such that a(j) >= 2*a(i).  if i and j are
paired, do not use non of them. */
int main() {
	int n, count = 0; cin >> n; 
	vector<int> arr(n, 0); 
	for(int i = 0; i < n; i++)cin >> arr[i]; 
	sort(arr.begin(), arr.end()); 
	int lptr = 0, rptr = (int)arr.size() / 2; 
	while(lptr < rptr && rptr != (int)arr.size()) {
		while(rptr != (int)arr.size() && 
		arr[rptr] < 2*arr[lptr])rptr++; 
		if(rptr == (int)arr.size())break;  
		//we have found the valid pair 
		count++; 
		rptr++; 
		lptr++; 
	}
	cout << n - count; 
	return 0; 
}





