#include <iostream> 
#include <set> 
#include <vector>
#include <algorithm> 
#include <string> 
#include <map> 
#define ll long long
using namespace std; 
/*PROBLEM DESCRIPTION:
A : jump to next cell 

B : jump to the next white cell 


0 1 1 1 1 0 1 1 1 0 1 1 1 

A B A A B A B 


*/

int main() {
	ll t; cin >> t; 
	while(t--) {
		ll n, m; cin >> n >> m; 
		string s; cin >> s; 
		set<ll> blacks;  ll idx = 1; 
		for(int i = 0; i < m; i++) {
			ll num; cin >> num; 
			blacks.insert(num);
		}
		for(int i = 0; i < n; i++) {
			if(s[i] == 'A') {
				idx++; 
				blacks.insert(idx); 
			} else {
				idx++; 
				while(blacks.find(idx) != blacks.end()){
					idx++; 
				}
				blacks.insert(idx); 
				while(blacks.find(idx) != blacks.end())
				idx++;
			}
		}
		cout << blacks.size() << endl; 
		for(ll num : blacks)cout << num << ' '; 
		cout << endl;
	}
	return 0; 
}










