#include <iostream> 
#include <vector>
#include <algorithm>  
using namespace std;

void update(vector<int>& tree, int idx, int val) {
	while(idx < (int)tree.size()) {
		tree[idx] += val; 	
		idx += (idx & -idx); 
	}
}

int read(vector<int>& tree, int idx) {
	int sum = 0; 
	while(idx > 0) {
		sum += tree[idx]; 
		idx -= (idx & -idx); 
	}
	return sum; 
}
int read_from(vector<int>& tree, int a, int b) {
	return (read(tree, b) - read(tree, a - 1));
}

int main() {
	int n; cin >> n; 
	vector<int> arr(n), tree(n + 1, 0); 
	for(int i = 0; i < n; i++) {
		cin >> arr[i]; 
		update(tree, i + 1, arr[i]);
	}
	int a, b; cin >> a >> b; 
	cout << read_from(tree, a, b) << endl; 
	return 0;
}







