#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "varVector.h" 
#include "vector.h"
//Initializes new variable vector
varVector* varVectorInit() {
    varVector* v = malloc(sizeof(varVector)); 
    v->vect = malloc(sizeof(vector)); 
    VectorNew(v->vect, sizeof(char*), varVectorFreeWrapper, 0); 
    return v; 
}

//destroys given variable vector 
void varVectorDestroy(varVector* v) {
    VectorDispose(v->vect);
    free(v->vect); 
    free(v); 
}

//returns the length of variable vector
int varVectorLength(varVector *v) {
    return VectorLength(v->vect); 
}
	   
//returns a duplicated variable at position
variable* varVectorGet(const varVector *v, int position) {
    variable** elemAddress = VectorNth(v->vect, position);
    return varDeepCpy(*(elemAddress));  
}
					  
//inserts new variable at position
void varVectorInsert(varVector *v, variable* var, int position) {
    variable* new_var = varDeepCpy(var); 
    VectorInsert(v->vect, &new_var, position); 
}

//appends variable vector and adds an element
void varVectorAppend(varVector *v, variable* var) {
    variable* new_var = varDeepCpy(var); 
    VectorAppend(v->vect, &new_var); 
}

//replaces a variable at given position with given variable in string vector
void varVectorReplace(varVector *v, variable* var, int position) {
    variable* new_var = varDeepCpy(var); 
    VectorReplace(v->vect, &new_var, position); 
}

//deletes a variable at position in variable vector
void varVectorDelete(varVector *v, int position) {
    VectorDelete(v->vect, position);
}

//searches a variable vector to see if variable exists in it
int varVectorSearch(const varVector *v, variable* var) {
    return VectorSearch(v->vect, &var, varVectorCmpWrapper, 0, 0); 
}


//way to compare variables
int varVectorCmpWrapper(const void* elemAddr1, const void* elemAddr2) {
    return strcmp((*(const variable**)elemAddr1)->variable_name, (
        *(const variable**)elemAddr2)->variable_name); 
}

//function that allows vector to free a given variable
void varVectorFreeWrapper(void* elemAddr) {
    variable** var = elemAddr; 
    varFree(*var); 
} 


//fully copies the complete variable struct and 
variable* varDeepCpy(variable* var) {
    variable* new_var = malloc(sizeof(variable)); 
    new_var->assigned_val = strdup(var->assigned_val);
    new_var->offset = var->offset; 
    new_var->td = malloc(sizeof(type_desc)); 
    new_var->td->type_name = strdup(var->td->type_name); 
    new_var->td->type_size = var->td->type_size;
    new_var->variable_name = strdup(var->variable_name);
    return new_var; 
}

//way to free a given variable
void varFree(variable* var) {
    free((var)->variable_name);
    free((var)->assigned_val); 
    free((var)->td->type_name);
    free((var)->td); 
    free(var); 
}
//a way to create a new variable given the input
variable* varCreate(char* name, char* assigned_val, int offset, type_desc* td) {
    variable* var = malloc(sizeof(variable)); 
    var->variable_name = strdup(name);
    var->assigned_val = strdup(assigned_val); 
    var->offset = offset; 
    var->td = malloc(sizeof(type_desc)); 
    var->td->type_name = strdup(td->type_name); 
    var->td->type_size = td->type_size; 
    return var;  
}
//prints the contents of a variable
variable* varPrint(variable* var) {
    assert(var); 
    printf("variable name is: %s, assigned value is %s, offset in stack is: %d, ", 
    var->variable_name, var->assigned_val, var->offset); 
    printf("variable type name is: %s, variable size is: %d\n", var->td->type_name, var->td->type_size); 
}