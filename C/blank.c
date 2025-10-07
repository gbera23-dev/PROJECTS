#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h>


void rotate(void* start, void* middle, void* end) {
	int left = (char*)middle - (char*)start; 
	int right = (char*)end - (char*)middle; 
	void* tmp = malloc(right); 
	assert(tmp != NULL); 
	memcpy(tmp, (char*)start + left, right); 
	memmove((char*)start + right, start, left); 
	memcpy((char*)start, tmp, right); 
	free(tmp); 
}




int main(int argc, char** argv) { 
	return 0; 
}






