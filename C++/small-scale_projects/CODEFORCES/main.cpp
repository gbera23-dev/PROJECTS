#include <iostream> 
#include <set> 
using namespace std; 
int main() {
	multiset<int> p = {1, 1, 3, 3, 3, 4}; 
	multiset<int>:: iterator it = p.lower_bound(2); 
	cout << *it << endl; 
	p.erase(it); 
	for(const auto& i : p)cout << i << ' ';
	return 0; 
}
