#include <iostream> 
#include <set>
#include <vector>
#include <map> 
#define l long long
using namespace std; 
void printout(set<l>& lones) {
	if(lones.size() == 0)cout << "Nothing" << endl; 
		else cout << *lones.rbegin() << endl; 
}
int main() {
	l n, k; cin >> n >> k; 
	map<l, l> freq; set<l> lones; l arr[n + 1]; 
	//outofbounds when i = k - 1 
	for(l i = 1; i <= n; i++) {
		cin >> arr[i]; 
		freq[arr[i]]++; 
		if(freq[arr[i]] > 1)lones.erase(arr[i]);
		else lones.insert(arr[i]); 
		if(i < k)continue; 
		freq[arr[i - k]]--; 
		if(freq[arr[i - k]] == 1)lones.insert(arr[i - k]); 
		if(freq[arr[i - k]] == 0)lones.erase(arr[i - k]); 
		printout(lones); 
	}
	return 0; 
}













