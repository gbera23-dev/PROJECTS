#include <iostream> 
#include <set> 
#include <vector>
#include <algorithm>  
using namespace std; 
/*
1 2 3 2 3 4 2 3 4 
8 
subcount = 3  
subcount - 1 
n - 1 - subcount + 1 = n - subcount 
*/
int main() {
	int n; cin >> n; 
	vector<int> a(n, 0), freq(1001, 0); 
	for(int i = 0; i < n; i++) {
		cin >> a[i]; 
		freq[a[i]]++; 
	}
	int maxval = 0; 
	for(int i : freq)maxval = max(maxval, i); 
	cout << (n - maxval); 
	return 0; 
}





