#include <iostream> 
#include <vector>
#include <algorithm>  
#include <stack> 
#define ll unsigned long long 
using namespace std; 
/*PROBLEM ANALYSIS:

5 1 5 

monotonic stack has a property that will allow us to better understand
the problem.  
if new element is able to pop all of the elements inside monotonic 
stack, then it is smaller than all the previous elements. the reason 
is that only way first element could have ended up at the bottom of
the stack is either if it was really the first element, or it popped
all the elements bigger than it, it is impossible for element to exist
before that is smaller than the element at the bottom of the stack. 
because then our element would have popped it when we processed it. 
therefore, here if stack gets empty, whole histogram that ends at i 
is needed to be checked. also at some point, stack may look like this 
1 3 8 10 

this can happen if we have for instance
100 2 4 3 10 10 10 10 4 6 5 
this gets to 1 3 8 10 
when we start analyzing, it is better to pop out the element and 
check the difference i - top element, because all the elements between
8 and 10 for example are bigger than 10, so rectangle with height 10 
will be built and then it will be popped out, same for 8. if 8 is 
at the bottom of the stack, then it means all the elements before 8 
are bigger than 8, so it will not hurt to extend rectangle to absolute
left.  

2 3 4 5 

2 1 2 1 2 0 

 0 
h = 1 

0  

2*(3 - 1 - 1) = 2

*/

int main() { 
	ll n; cin >> n;
	ll arr[n + 1];
	for(ll i = 0; i < n; i++)cin >> arr[i]; 
	arr[n] = 0; 
	stack<ll> mono; 
	ll h = 0, max_val = 0; 
	for(ll i = 0; i <= n; i++) {
		while(!mono.empty() && arr[mono.top()] > arr[i]) {
			h = arr[mono.top()]; 
			mono.pop(); 
			if(!mono.empty())
			max_val = max(max_val, h*(i - mono.top() - 1)); 
			else max_val = max(max_val, h*i); 
		}
		mono.push(i); 
	}
	cout << max_val;
	return 0;
}









