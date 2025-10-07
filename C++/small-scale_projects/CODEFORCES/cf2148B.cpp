#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; 
/*
Greedy approach: horizontally cross all the vertical lines
necessary, then vertically cross all the horizontal lines
necessary. Solution is amount of lines from 0 to x plus
amount of lines from 0 to y 
*/
int main() {
	int t, n, m, x, y, count, num; cin >> t;
	for(int i = 0; i < t; i++) {
		count = 0;
		cin >> n >> m >> x >> y; 
		//horizontal lines
		for(int i = 0; i < n; i++) {
			cin >> num; 
			if(num < y)count++;
		}
		//vertical lines
		for(int i = 0; i < m; i++) {
			cin >> num;
			if(num < x)count++; 
		}
		cout << count << endl; 
	}
	return 0; 
}
