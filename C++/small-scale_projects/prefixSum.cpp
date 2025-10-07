#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std; 
int main() {
	long long n; cin >> n; 
	vector<long long> arr(n + 1, 0); 
	for(int i = 1; i <= n; i++) {
		cin >> arr[i];  
		arr[i] += arr[i - 1]; 
	}
	//then arr becomes the prefix sum of arr
	for(int i = 1; i <= n; i++)cout << arr[i] << ' ';
	return 0; 
}






