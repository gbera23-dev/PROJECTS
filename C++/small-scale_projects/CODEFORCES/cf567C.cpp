#include <iostream> 
#include <set>
#include <vector>
#include <map> 
#define ll long long
using namespace std; 
//given the array find all subsequences of len 3 such that it forms
//geometric progression 
//first of all, put all elements into multiset(nlogn)
//elements may repeat and k may be equal to one
//have a frequency chart for each element(n operations) 
//then put them all into the set. 
//find k*arr[i] and k*k*arr[i] inside set, if both exist
//add their freq product to the answer, it is guaranteed
//that given subsequences will be unique in relation with
//indices as we are traversing by one per iteration. 
int main() {
	ll n, k; cin >> n >> k; 
	ll count = 0; 
	vector<ll> arr(n, 0); 
    map<ll, ll> lmap, rmap, freq; 
	for(ll i = 0; i < n; i++){
		cin >> arr[i]; 
		ll a = arr[i]; 
		if(a % k == 0) {
			lmap[i] = freq[a / k]; 
		}
		freq[a]++; 
	}
	freq.clear(); 
	for(ll i = n - 1; i >= 0; i--) {
		ll a = arr[i]; 
		rmap[i] = freq[a*k]; 
		freq[a]++; 
	}
	//now that we have initialized maps 
	//we can simply traverse all values and multiply 
	//number of n / k to number of n*k 
	for(ll i = 0; i < n; i++) {
		count += lmap[i]*rmap[i]; 
	}
	cout << count; 
	return 0; 
}







