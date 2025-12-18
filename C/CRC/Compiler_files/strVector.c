#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strVector.h" 
#include "vector.h"
//Initializes new string vector
strVector* strVectorInit() {
    strVector* v = malloc(sizeof(strVector)); 
    v->vect = malloc(sizeof(vector)); 
    VectorNew(v->vect, sizeof(char*), strVectorFreeWrapper, 0); 
    return v; 
}

//destroys given string vector 
void strVectorDestroy(strVector* v) {
    VectorDispose(v->vect);
    free(v->vect); 
    free(v); 
}

//returns the length of string vector
int strVectorLength(strVector *v) {
    return VectorLength(v->vect); 
}
	   
//returns a duplicated string at position
char* strVectorGet(const strVector *v, int position) {
    char** elemAddress = VectorNth(v->vect, position);
    return strdup(*(elemAddress));  
}
					  
//inserts new string at position
void strVectorInsert(strVector *v, char* str, int position) {
    char* new_str = strdup(str); 
    VectorInsert(v->vect, &new_str, position); 
}

//appends string vector and adds an element
void strVectorAppend(strVector *v, char* str) {
    char* new_str = strdup(str); 
    VectorAppend(v->vect, &new_str); 
}

//replaces a string at given position with given string in string vector
void strVectorReplace(strVector *v, char* str, int position) {
    char* new_str = strdup(str); 
    VectorReplace(v->vect, &new_str, position); 
}

//deletes a string at position in string vector
void strVectorDelete(strVector *v, int position) {
    VectorDelete(v->vect, position);
}

//searches a string vector to see if string exists in it
int strVectorSearch(const strVector *v, char* str) {
    return VectorSearch(v->vect, &str, strVectorCmpWrapper, 0, 0); 
}


//way to compare strings
int strVectorCmpWrapper(const void* elemAddr1, const void* elemAddr2) {
    return strcmp(*(const char**)elemAddr1, *(const char**)elemAddr2); 
}

//way to free a given string
void strVectorFreeWrapper(void* elemAddr) {
    free((void*)*(char**)elemAddr); 
} 