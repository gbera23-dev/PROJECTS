#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std; 
int main() {
	//number of ( are equal to number of ) 
	//so this stack implementation might work 
	//whenever we push (, we are looking for ) after ( (no matter which)
	//to neutralize it, so if at last stack is empty, all ( are 
	//neutralized
	string s; cin >> s; 
	int cnt = 0; 
	for(char i : s) {
		if(i == '(')cnt++;
		else cnt--; 
	}
	if(cnt != 0){
		cout << "No";
		return 0; 	
	}
	stack<char> t; t.push('0'); 
	for(int i = 0; i < (int)s.size(); i++) {
		char current = s[i]; 
		if(current == ')') {
			if(t.top() == '(') {
				t.pop();
			} 
		} else {
			t.push(current);
		}
	}
	if(t.top() == '0')cout << "Yes"; 
	else cout << "No";
	return 0; 
}
