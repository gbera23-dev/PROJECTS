#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
//generic compare must compare byte by byte(n bytes in total)
//if one byte is different from second return uns char diff 
//programmer is responsible for at least n bytes to be allocated 
//after the byte each pointer points to(this works) 
int memcmp(const void* s1, const void* s2, size_t n) {
	size_t i; 
	for(i = 0; i < n; i++) {
		if(*((unsigned char*)s1 + i) != *((unsigned char*)s2 + i)) {
			return *((unsigned char*)s1 + i) - *((unsigned char*)s2 + i); 
		} 
	}
	return 0; 
}
//programmer is responsible for at least n bytes to be allocated 
//after the byte, whose address dest maintains and also same for the
//src, otherwise, we will get stack seg fault, as we are accessing 
//memory, which is not ours, copy byte by byte. also memories cannot
//overlap 
void* memcpy(void* dest, const void* src, size_t n) {
	size_t i; 
	for(i = 0; i < n; i++) {
		*((unsigned char*)dest + i) = *((unsigned char*)src + i); 
	}
	return dest; 
}
//concatinates dest by n bytes from src and adds null terminator at the
//end. takes one memory and after the last byte of first, copies all 
//extra bytes from src to that dest. requirement is that the size of 
//dest must be at least dest allocated memory size  + src allocated 
//memory size. we need the size of each of the memory to fully 
//concatinate. it works 
void* memcat(void* dest, const void* src, size_t dest_size, size_t src_size) {
    char* start = dest + dest_size; //this valid? 
    //b b b b b 
    //dest  points to first byte and there are 5 bytes 
    //we need to move dest after the last byte, so 
    //we need to move it exactly by its size  
    memcpy(start, src, src_size); 
    return dest;
}
//this is not possible, because there is no function that is able 
//to determine amount of memory allocated after a pointer, without 
//extra parameter passing. strings naturally have null terminator 
//at the end, so their size can be determined. for the case of 
//our analysis, this function will simply be ignored

/*
IGNORED
size_t strlen(const char* s) {
	unsigned int i = 0; 
	while(*(s + i) != 0) {
		i++; 
	}
	return i; 
}
IGNORED
*/
/*IGNORED
//POSSIBLE BUG HERE, BUG WAS THAT THE MEMORY AT DEST + LEN WAS NOT 
//OURS, SO WE NEED TO BE SURE THAT ALL THE BYTES AFTER A BYTE dest 
//points to must be accesible(necessary bytes are sum of sizes + 2 of 
//strings, so we could add safe check, but then we need extra parameter.
//but strcat of string library has only two parameters  
char* strcat(char* dest, const char* src) {
    int dest_len = strlen(dest); 
	strcpy(dest + dest_len, src);
	return dest; 
}
IGNORED
*/
/*
To make this generic, we need to pass extra argument, the amount of 
memory we need to duplicate. returns the pointer to the duplicated 
memory's first byte. this works 
*/
void* memdup(const void* s, size_t n) {
	void* buffer = malloc(n); 
	memcpy(buffer, s, n); 
	return buffer;   
}
//already generic, no need to change 
void* memset(void* s, int c, size_t n) {
	for(int i = 0; i < n; i++) {
		*(((char*)(s)) + i) = c; 	
	}
	return s; 
}
//prints n bytes in the representation of unsigned char
//will print bytes with no space inbetween them 
void* memprint(void* inp, size_t n) {
	size_t i; 
	for(i = 0; i < n; i++) {
		printf("%d", *((unsigned char*)inp + i)); 
	}
	return inp; 
}
//know comes the territory of discovery, I will come up with generic
//functions 
//first function is generic swap. generic swap will swap first n bytes
//of two places inside memory(we have address of first byte of each 
//memory). we will use already written memcpy function to do this.
//however, it uses dynamic allocation and hence is slow, there is other
//way, we can make the array of characters of size n, as each character
//maintains the memory of 1 byte. the method avoids heap allocation. 
//speeding up the swapping process. 
void memswap(void* s1, void* s2, size_t n) {
	char tmp[n]; //allocate n bytes in memory 
	memcpy((void*)tmp, s2, n); //copy first n bytes of s2 to tmp 
	memcpy(s2, s1, n); //copy first n bytes of s1 to s2 
	memcpy(s1, (void*)tmp, n); //copy first n bytes of tmp to s1  
} 
//next function will find some collection of m bytes in the memory 
//given the 
//search size is some n bytes, if it finds it, it returns its index 
//which is how many bytes after first byte is this byte. 
//otherwise returns -1 
//programmer is responsible for allocated memory being at least as large
//as n(note that n may not be divisible by m) 
//first is array, second is element, third is size of the array 
//fourth is the size of the element 
int memfind(void* arr, void* elem, size_t n, size_t elem_size) {
	size_t i = 0; 
	while(elem_size*i < n*elem_size) {
		int res = memcmp(((unsigned char*)arr + elem_size*i), 
		elem,elem_size);
		if(res == 0)return i; 
		i++; 
	}
	return -1;
}

//next function... 


//now mission is to make each function generic
int main(int argc, char** argv) { 
	return 0; 
}






