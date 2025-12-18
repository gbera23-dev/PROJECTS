
#ifndef _strVector_
#define _strVector_
#include "vector.h"

typedef struct {
    vector* vect; //uses vector directly
} strVector; 


//Initializes new string vector
strVector* strVectorInit();

//destroys given string vector 
void strVectorDestroy(strVector* v);

//returns the length of string vector
int strVectorLength(strVector *v);
	   
//returns a string at position
char* strVectorGet(const strVector *v, int position);
					  
//inserts new string at position
void strVectorInsert(strVector *v, char* str, int position);

//appends string vector and adds an element
void strVectorAppend(strVector *v, char* str);

//replaces a string at given position with given string in string vector
void strVectorReplace(strVector *v, char* str, int position);

//deletes a string at position in string vector
void strVectorDelete(strVector *v, int position);

//searches a string vector to see if string exists in it
int strVectorSearch(const strVector *v, char* str);

/*Now, comes the wrapper functions needed for vector*/

//way to compare strings
int strVectorCmpWrapper(const void* elemAddr1, const void* elemAddr2); 
//way to free a given string
void strVectorFreeWrapper(void* elemAddr); 

#endif
