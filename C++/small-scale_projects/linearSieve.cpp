#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;  
int main() {
	long long n; cin >> n;
	//lpd means least prime divisor 
	vector<long long> lpd(n + 1, 0), pnums(n, 0);
	long long k = 0; 
	for(long long i = 2; i <= n; i++) {
		//number is prime
		if(!lpd[i]) {
			lpd[i] = i; 
			pnums[k] = i; 
			k++;
		}
		for(long long j = 0; j < k; j++) {
			if(pnums[j] > lpd[i])break; 
			if(pnums[j]*i > n)break; 
			lpd[pnums[j]*i] = pnums[j]; 
		}
	}
	long long count = 0; 
	for(long long i = 2; i <= n; i++) {
		if(lpd[i] == i){
			cout << i << ' '; 
			count++; 
		}
	}
	cout << endl; 
	cout << "in total, there are " << count << 
	" prime numbers in the range from " << 2 << " to " << n << endl;  
	cout << endl; 
	cout << ". . . . . " << endl;
	for(int i = 1; i <= 100; i++)cout << lpd[i] << ' ';  
	return 0; 
}






