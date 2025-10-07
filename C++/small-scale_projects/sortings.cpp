#include <iostream> 
#include <vector> 
using namespace std;
int main() {
	int n, step; cin >> n; 
	vector<int> arr(n); 
	for(int i = 0; i < n; i++) {
		arr[i] = n - i; 
	}
	double factor = 1.2473309;
	step = (int)arr.size() - 1; 
	while(step >= 1) {
		for(int i = 0; i + step < (int)arr.size(); i++) {
			if(arr[i] > arr[i + step]) {
					swap(arr[i], arr[i + step]); 
			}
		}
		cout << step << endl; 
		step /= factor; 
	} 
	return 0; 
}
