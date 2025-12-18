
#ifndef _varVector_
#define _varVector_
#include "vector.h"
#include "Data.h"
typedef struct {
    vector* vect; //uses vector directly
} varVector; 


//Initializes new variable vector
varVector* varVectorInit();

//devaroys given variable vector 
void varVectorDestroy(varVector* v);

//returns the length of variable vector
int varVectorLength(varVector *v);
	   
//returns a variable at position
variable* varVectorGet(const varVector *v, int position);
					  
//inserts new variable at position
void varVectorInsert(varVector *v, variable* var, int position);

//appends variable vector and adds an element
void varVectorAppend(varVector *v, variable* var);

//replaces a variable at given position with given variable in variable vector
void varVectorReplace(varVector *v, variable* var, int position);

//deletes a variable at position in variable vector
void varVectorDelete(varVector *v, int position);

//searches a variable vector to see if variable exists in it
int varVectorSearch(const varVector *v, variable* var);

/*Now, comes the wrapper functions needed for vector*/

//way to compare variables
int varVectorCmpWrapper(const void* elemAddr1, const void* elemAddr2); 
//way to free a given variable
void varVectorFreeWrapper(void* elemAddr); 

//Provides a way to free a variable struct
void varFree(variable* var); 
//creates a deep copy of variable(passes ownership to a client)
variable* varDeepCpy(variable* var); 
//creates a new variable with given parameters(passes ownership to a client)
variable* varCreate(char* name, char* assigned_val, int offset, type_desc* td);
//prints out all the contents of variable  
variable* varPrint(variable* var);
#endif
