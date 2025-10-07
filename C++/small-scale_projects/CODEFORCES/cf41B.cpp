#include <iostream> 
#include <vector>
#include <algorithm>  
#include <map> 
#include <numeric> 
using namespace std; 
/*PROBLEM ANALYSIS: 
*/
int main() {
	int n, b; cin >> n >> b; 
	int arr[n]; 
	for(int i = 0; i < n; i++)cin >> arr[i]; 
	int curr_possible = 0, max_possible = 0; 
	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			curr_possible = (b % arr[i]) + ((b / arr[i])*arr[j]);
			max_possible = max(max_possible, curr_possible); 
		}
	}
	cout << max_possible; 
	return 0;
}





