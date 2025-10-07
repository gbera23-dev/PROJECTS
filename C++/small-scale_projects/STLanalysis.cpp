#include <iostream> 
#include <set> 
#include <vector>
using namespace std;
	//consider all possible pairs and if they add up to target, return
	//it, this is brute force approach, and only way things could get
	//better is if we are able to get to amortized linear time 
	//this will be done in following way, first we will write 
	//n*logn and then n 
	//STANDARD APPROACH(O(n^2)):
    //~ vector<int> twoSum(vector<int>& nums, int target) {
		//~ int i, j; 
		//~ for(i = 0; i < nums.size(); i++) {
			//~ for(j = i + 1; j < nums.size(); j++) {
				//~ if((nums[i] + nums[j] == target)) {
				//~ return {i, j};
			//~ }
			//~ }
		//~ }
        //~ return {}; 
    //~ }
	//FASTER APPROACH(O(n*logn)) 
    //vector<int> twoSum(vector<int>& nums, int target) {
		//map<int, int> m, p;
		//for(int i = 0; i < (int)nums.size(); i++) {
			//m[i] = target - nums[i];
			//p[nums[i]] = i;  
		//}
		//for(const auto& val : m) {
			//cout << val.first << ' ' << val.second << endl;
            //map<int, int>::iterator it = p.find(val.second);
			//if(it != p.end() && (it->second != val.first)) {
				//return {it->second, val.first}; 
			//}
		//}
		//return {-1, -1}; 
       //}
      //FASTEST(O(n)) 
        //vector<int> twoSum(vector<int>& nums, int target) {
		//unordered_map<int, int> m, p;
		//for(int i = 0; i < (int)nums.size(); i++) {
			//m[i] = target - nums[i];
			//p[nums[i]] = i;  
		//}
		//for(const auto& val : m) {
            //unordered_map<int, int>::iterator it = p.find(val.second);
			//if(it != p.end() && (it->second != val.first)) {
				//return {it->second, val.first}; 
			//}
		//}
		//return {-1, -1}; 
       //}
//logn set is cool 

int main(){
	return 0; 
}
