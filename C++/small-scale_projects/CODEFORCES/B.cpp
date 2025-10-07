#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; 
int main() { 
	long long n; cin >> n; 
	vector<long long> arr(n + 1, 0);
	for(long long i = 1; i <= n; i++){
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end()); 
	cout << arr[(n + 1) / 2]; 
	return 0; 
}
