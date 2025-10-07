#include<bits/stdc++.h>
using namespace std; 
int main() {
	long long n, count = 0; cin >> n; 
	while(n != 0) {
		int current = n % 10; 
		n /= 10; 
		if(current == 4 || current == 7)count++; 
	}
	//count can be from 1 to 19, only 4 and 7 are possible
	if(count == 4 || count == 7)cout << "YES"; 
	else cout << "NO";
	return 0; 
}
