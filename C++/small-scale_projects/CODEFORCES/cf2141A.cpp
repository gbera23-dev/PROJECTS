#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;     
//prefix minima method
//preprocessing  - n, tracking - n --- > O(2*n) -> O(n) 
int main() {
	int t, n; cin >> t;
	while(t--) {
	cin >> n;
	vector<int> arr(n + 1, 0), pref(n + 1, 0), sol; 
	sol = {}; 
	for(int i = 1; i <= n; i++)cin >> arr[i]; 
	int minVal = 101, minInd = 0; 
	for(int i = 1; i <= n; i++) {
		if(minVal > arr[i]) {
			minVal = arr[i]; 
			minInd = i; 
		}
		pref[i] = minInd; 
	}
	int tracker = n; 
	while(tracker > 0) {
		int minInd = pref[tracker]; 
		for(int j = tracker; j > minInd; j--) {
			sol.push_back(j); 
		}
		tracker = minInd - 1; 
	}
	cout << sol.size() << endl; 
	//traverse backwards for ascending sort
	for(int i = sol.size() - 1; i >= 0; i--) {
		cout << sol[i] << ' '; 
	}
	cout << endl; 
}
	return 0; 
}






