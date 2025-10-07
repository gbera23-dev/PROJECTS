#include<bits/stdc++.h>
using namespace std; 
int main() { 
	int t; cin >> t;
	for(int i = 0; i < t; i++) {
		int n, m; cin >> n >> m; 
		int preva = 0, prevb = 0, count = 0; 
		for(int j = 0; j < n; j++) {
			int a, b; cin >> a >> b; 
			int cnt = a - preva - 1; 
			count += cnt; 
			int dig = b; 
			if((cnt + 1) % 2 == 0) {
				if(b == 1)dig = 0;
				else dig = 1; 
			}
			if(prevb ^ dig)count++; 
			preva = a; 
			prevb = b; 
		}
		if(preva < m)count += m - preva; 
		cout << count << endl; 
	}
	return 0; 
}















