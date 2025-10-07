#include <iostream> 
#include <set> 
#include <vector>
using namespace std; 
/*
It turns out the first solution I came up with was
actually the valid way to solve this shit 
*/
int main() {
	int t; cin >> t; 
	for(int i = 0; i < t; i++) {
		int n, m, count = 0; cin >> n >> m; 
		vector<vector<int>> sets(n); 
		vector<int> freq(m + 1, 0); 
		for(int j = 0; j < n; j++) {
			int l, num; cin >> l; 
			for(int z = 0; z < l; z++) {
				cin >> num; 
				freq[num]++; 
				sets[j].push_back(num);
			}
		}
		for(int i = 1; i <= m; i++) {
			if(freq[i] == 0) {
				count = -1;
				cout << "NO" << endl; 
				break; 
			}
		}
		if(count == -1)continue; 
		count++; 
		bool maintains = true; 
		for(vector<int> set : sets) {
			maintains = true; 
			for(int elem : set) {
				if(freq[elem] == 1) {
					maintains = false;
					break; 
				}
			}
			if(maintains)count++; 
		}
		if(count >= 3)cout << "YES" << endl; 
		else cout << "NO" << endl; 
	}
	return 0; 
}










