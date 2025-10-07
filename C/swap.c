#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h>

//generic swap 
void swap(void* x, void* y, int mem_size) {
	//using memcopy function 
	void* tmp = malloc(mem_size);
	memcpy(tmp, x, mem_size);
	memcpy(x, y, mem_size); 
	memcpy(y, tmp, mem_size);
	free(tmp);  
}
//generic find
int find(void* arr, void* elem, int size, int mem_size) {
	//cast array to char pointer 
	for(int i = 0; i < size; i++) {
		void* current = (char*)arr + i*mem_size; 
		if(memcmp(elem, current, mem_size) == 0)return i; 
	}
	return -1;
}
//generic cmp 
int cmp(void* one, void* two, int mem_size) {
	//in total mem_size amount need to be compared 
	while(mem_size--) {
		if(*(char*)one != *(char*)two)return 0; 
		one = (char*)one + 1; 
		two = (char*)two + 1; 
	}
	return 1; 
} 
 
 
int main(int argc, char** argv) {
	char a[6] = "sdffs"; 
	char b[6] = "sdffs"; 
	printf("%d", strcmp(a, b)); 
	return 0; 
}






