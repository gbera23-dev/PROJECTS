#include <iostream> 
#include <vector> 
using namespace std; 
/*
f(p) number of such indexes k, that xk is divisible by p 
2 <= xi <= 10^7 max prime number is 10^7  
frequency of each element, with set. 
then apply standard sieve with extra tweak. If the number 
we are analysing is inside set, increase the count of that
particular prime exactly as frequency says. do this for all
primes from 2 to 10^7.
*/
int main() {
	vector<int> freq(10000001, 0); 
	int n, x, maxElem = 2; cin >> n; 
	for(int i = 0; i < n; i++)  {
		cin >> x; 
		maxElem = max(maxElem, x);
		freq[x]++; 
	}
	//primeArray 
	vector<int> arr(maxElem + 1, 0);
	for(int i = 2; i <= maxElem; i++) {
		if(arr[i] == 0) {		
			for(int j = i; j <= maxElem; j += i) {
				arr[i] += freq[j]; 
				if(i == j)continue; 
				arr[j] = -1; 
			}
	}
	} 
	for(int i = 1; i <= maxElem; i++) {
		if(arr[i] == -1)arr[i] = 0; 
		arr[i] += arr[i - 1];
	}
	int m, a, b; cin >> m; 
	while(m--) {
		cin >> a >> b; 
		if(a > maxElem){
			cout << 0 << endl; 
			continue; 
	}
		if(b > maxElem)b = maxElem; 
		cout << arr[b] - arr[a - 1] << endl;  
	}
	return 0; 
}





