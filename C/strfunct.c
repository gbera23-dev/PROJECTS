#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h>

int strcmp(const char *s1, const char *s2) {
	int i = 0; 
	while(*(s1 + i) != '\0' && *(s2 + i) != '\0') {
		if(*(s1 + i) != *(s2 + i)) {
			return *(s1 + i) - *(s2 + i); 
		}
		i++; 
	}
	return *(s1 + i) - *(s2 + i); 
}

char* strcpy(char* dest, const char* src) {
	int i = 0; 
	while(*(src + i) != '\0') {
		*(dest + i) = *(src + i); 
		i++; 
	}
	*(dest + i) = '\0'; 
	return dest; 
}
//concatinates dest by n bytes from src and adds null terminator at the
//end
char* strncat(char* dest, const char* src, size_t n) {
    char* start = dest + strlen(dest);
    size_t i;
    for (i = 0; i < n && *(src + i) != 0; i++) {
        *(start + i) = *(src + i);
    }
    *(start + i) = '\0';
    return dest;
}

size_t strlen(const char* s) {
	unsigned int i = 0; 
	while(*(s + i) != 0) {
		i++; 
	}
	return i; 
}

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


char* strdup(const char* s) {
	int len = strlen(s); 
	char* buffer = malloc(len + 1); 
	return strcpy(buffer, s);
}

void* memset(void* s, int c, size_t n) {
	for(int i = 0; i < n; i++) {
		*(((char*)(s)) + i) = c; 	
	}
	return s; 
}

int main(int argc, char** argv) {
	return 0; 
}






