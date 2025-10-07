#include <iostream> 
#include <set> 
#include <vector>
#include <algorithm>  
using namespace std; 
/*PROBLEM ANALYSIS: 
3 3 4 5 7 8 
max difference is 8 / 3. So either maximum or minimum 
needs to be moved, there are three cases, and that would
be pretty pretty large search. In the final array, some 
elements will participate. the first element can be
one of any, then that subarray has the property that its 
last element is actually the largest the element can get
such that largest over first is not more than 2, this is
the case, because otherwise, we would be able to extend
the array and hence solution would not be maximal as we 
have found the larger solution. So all we have to do is for
each element is to find the largest element such that 
largest over the element is not more than 2, and find
the size of it. This can be done in linear time via 
backwards traversal(kind of dynamic programming). for last
index, its size is 1, then we move the left pointer, if 
arr[rptr] / arr[lptr] is less or equal to 2, then for lptr,
the size will be rptr - lptr + 1, if not, then moving lptr
to the left will only make the division larger, so we have
to move rptr and check again, then if lptr meets rptr, it
is guaranteed that no other subarrays can guarantee what
we want. sorting of course is crucial for this to work.
 */
int main() {
	//freopen("input.txt", "r", stdin); 
	//freopen("output.txt", "w", stdout); 
	int n; cin >> n; 
	vector<int> arr(n, 0); 
	int maxlen = 1; 
	for(int i = 0; i < n; i++)cin >> arr[i]; 
	sort(arr.begin(), arr.end()); 
	int lptr = n - 2, rptr = n - 1;
	while(lptr >= 0 && lptr != rptr) {
		//means it is valid 
		if(arr[rptr] <= 2*arr[lptr]) {
			maxlen = max(maxlen, rptr - lptr + 1); 
			lptr--; 
		} 
		//the case if division is not satisfied
		else {
			rptr--; 
		}
	} 
	cout << (n - maxlen); 
	return 0;
}





