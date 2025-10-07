#include <iostream> 
#include <vector>
#include <algorithm>  
#include <map> 
#include <numeric> 
using namespace std; 
void sieve(vector<int>& arr, vector<int>& primes) {
	for(int i = 2; i <= 1000000; i++) {
		//i is prime 
		if(arr[i] == 0) {
			arr[i] = i; 
			primes.push_back(i); 
		}
		for(int prime_num : primes) {
			if(prime_num > arr[i])break; 
			if(i*prime_num > 1000000)break; 
			arr[prime_num*i] = prime_num; 
		}
	}
}
int main() {
	vector<int> arr(1000001), primes; 
	sieve(arr, primes);
	int n; cin >> n;
	long long m; cin >> m;  
	vector<int> nums(n, 0); 
	for(int i = 0; i < n; i++)cin >> nums[i]; 
	map<int, int> lfreq, gfreq; 
	for(int i = 0; i < n; i++) {
		int num = nums[i]; 
		lfreq.clear(); 
		while(num != 1) {
			lfreq[arr[num]]++; 
			num /= arr[num];  
		}
		for(const auto& p : lfreq) {
			gfreq[p.first] = max(gfreq[p.first], p.second);
		}
	}
	long long count = 1; 
	for(const auto& p : gfreq) {
		count = (count * (p.second + 1)) % m; 
	}
	long long sol = (count - (n % m) + m) % m; 
	cout << sol;  
	return 0;
}




