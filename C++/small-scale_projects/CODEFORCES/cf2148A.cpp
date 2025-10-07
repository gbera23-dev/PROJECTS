#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; 
int main() {
	int t, x, n; cin >> t; 
	for(int i = 0; i < t; i++) {
		cin >> x >> n; 
		if((n & 1) == 1)cout << x << endl; 
		else cout << 0 << endl; 
	}
	return 0; 
}
