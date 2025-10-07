#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std; 
/*
for simplicity, consider that all elements exhaust 
all 18 digits(meaning that all numbers are at their maximum) 
BRUTE FORCE: Consider all pairs and check if they have common digit,
if they do have common digit, increase the count.
Suppose we optimize common digit check to linear algorithm. 
Then we need n(n -1) / 2 checks and for each we need average k 
operations, so 
algorithm goes to O(10^18*n^2) complexity. 
To be precise, 10^18*n(n - 1) / 2 operations will be needed.  
EFFICIENT APPROACH: 
We need to track all elements to fill in the arr, we track each digit
of each number, so in total n*10^18, then we traverse all 1024 integers
and use O(1) formula to count in total how many same pairs we have.
So we have n*10^18 + 1024. Then we check each of the number to other
number, in total 1024*1023 / 2 = 523776 and return the count.
So in total 10^18*n + 524800. linear complexity with huge constant. 
Now let us consider the maximum n and compare both solutions' number
of operations: n = 1 000 000 = 10^6
for EFFICIENT APPROACH: we have 10^24 + 524800 = 10...524800(24 zeroes
after 1. 
for The first one: we have 10^24*(10^6 - 1) / 2 = 
(10^30 - 10^24) / 2   10^24+524800
second one is 500000 times faster than first one.  
*/
int arr[1024]; 
void scan(long long num) {
	int res = 0, bitmask = 1;
	while(num != 0) {
		int lastDigit = num % 10; 
		if((res & (bitmask << lastDigit)) == 0) {
			res += (bitmask << lastDigit); 
		}
		num /= 10; 
	}
	arr[res]++; 
}

int main() {
	long long n, num; cin >> n; 
	for(long long i = 0; i < n; i++) {
		cin >> num; 
		scan(num); 
	}
	long long totalCount = 0; 
	for(int i = 0; i <= 1023; i++) {
		totalCount += (arr[i]*(arr[i] - 1)) / 2; 
		for(int j = i + 1; j <= 1023; j++) {
			if((i & j) != 0) {
				totalCount += arr[i]*arr[j]; 
			}
		}
	}
	cout << totalCount;
	return 0; 
}
