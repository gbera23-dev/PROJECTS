#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
 /*
	using only & and ~, write other operators(we are operating on type 
	int) 
	
	xor is valid only if one of a or b is valid. 
	otherwise it is not valid 
	a & b is valid only if both a and b are valid 
	~a & b is valid only if a is not valid and b is valid 
	a & ~b is valid only if a is valid and b is not valid 
	therefore we need combination of these two somehow 
	first using or operator, we determine that 
	a xor b = (~a & b) | (a & ~b), then we can transform this into 
	& operation via following rule. a | b = ~(~a & ~b)  
	then we get (~a & b) | (a & ~b) = ~(~(~a & b) & ~(a & ~b))
	do the or operation 
 */
 int xor(int a, int b) {
	 return ~(~(~a & b) & ~(a & ~b)); 
 }
 
 int or(int a, int b) {
	 return ~(~a & ~b); 
 }
 
 
int main(int argc, char** argv) {
	for(int i = 0; i <= 1; i++) {
		for(int j = 0; j <= 1; j++) {
			if(xor(i, j) == (i ^ j)) {
				printf("they match\n");
			} else {
				printf("something is wrong..."); 
			}
		}
	}
	return 0; 
}






