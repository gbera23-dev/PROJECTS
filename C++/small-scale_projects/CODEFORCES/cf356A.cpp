#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std; 
/*
4 3
1 2 1
1 3 3
1 4 4
lets understand the implementation
we have set alive, answer vector and toErase vector, which tells 
us per query, how many knights need to be eliminated. 
The implementation is pretty close to brute force I provided above, 
but has interesting features worth knowing. 
ok we initialize set to have all knights in it, as this is set
based on binary tree, elements are naturally sorted in ascending 
order. ok so we process the querie. create the new iterator that
finds the lower bound for l in the set. Which is the first alive 
knight that participates in the fight. Then we define the vector
toErase, and traverse through the alive knights till we exceed r or 
the end. for each traversed value, if it is x, we skip it, otherwise
x defeats him, so we add the element into toErase vector and the 
defeater of the knight is determined, so answer vector is updated. 
we continue like this till the end, and then delete the defeated 
knights out of the set all at once(because deleting inplace would 
mess up the iterator possibly). alive.lower_bound(l) just tells us 
the first alive knight that participates in the fight, it is neat. 
Now, why is this algorithm faster than my BRUTE FORCE. my brute
force algorithm has complexity O(n + sum of range lengths of all queries). 
This algorithm has complexity what? lets calculate: 
so we cin numbers into vector, n operations. 
then we find the lower_bound(l), that is logn operation. 
we fill in toErase vector(some operatiosn are absolutely skipped), while
in my brute force, they were still processed. We need to count in total
how many are alive per iteration and sum it all up and multiply that 
by logn.
*/
int main() {   
	int n, m; cin >> n >> m; 
	set<int> alive; //it is of size n
	for(int i = 1; i <= n; i++)alive.insert(i);
	vector<int> ans(n + 1), toErase;  
	for(int i = 0; i < m; i++) {
		int l, r, x; cin >> l >> r >> x; 
		//find iterator to the first alive knight that fights 
		set<int>::iterator it = alive.lower_bound(l); 
		//now we track the knights fighting 
		toErase = {}; 
		while(it != alive.end()) {
			int currentKnight = *it; 
			if(currentKnight > r)break; 
			if(currentKnight != x) {
				toErase.push_back(currentKnight); 
				ans[currentKnight] = x;
			}
			it++; 
		}
		//now erase knights 
		for(int i : toErase)alive.erase(i);
	}
	for(int i = 1; i <= n; i++)cout << ans[i] << ' ';
	return 0; 
}
	
//~ //BRUTE FORCE
//~ int main() {
	//~ int n, m; cin >> n; cin >> m; 
	//~ vector<int> arr(n + 1, 0); 
	//~ for(int i = 0; i < m; i++) {
		//~ int l, r, x; cin >> l >> r >> x; 
		//~ for(int j = l; j <= r; j++) {
			//~ if(j == x || arr[j] != 0)continue; 
			//~ arr[j] = x; 
		//~ }
	//~ }
	//~ for(int i = 1; i <= n; i++)cout << arr[i] << ' ';
	//~ return 0; 
//~ }



