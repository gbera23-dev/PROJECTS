
#ifndef _instructions_
#define _instructions_
#include "Mr_Compilator.h"
/*
This module is needed for functions, which based on requirements, create elementary assembly
instructions. Memory ownership is passed to a client.
*/
//creates and returns assembly instructions for declaring a variable
char* instructions_declareVar(type_desc* td); 
//creates and returns assembly instructions for assigning a variable
char* instructions_assignVar(variable var, char* val, int already_stored, int sp_pos); 
//creates and returns assembly instructions for reading a variable 
char* instructions_readVar(variable var, char* reg, int sp_pos); 
//moves sp up by offset(if offset is negative, it moves sp down)
char* instructions_spMove(int offset); 
//special instruction that uses ecall to print out values on a console during assembly execution
char* instructions_printVar(variable var, int sp_pos); 
//creates and returns assembly instructions for operating two variables(or constants), reg for storing result
char* instructions_opVars(variable first_var, variable second_var, char* reg, char* op, int sp_pos); 
//creates and returns assembly instructions for creating a new label with given name
char* instructions_createLabel(char* label_name, int tmp_id);
//creates and returns assembly instructions for creating a new branch, when given statement is put in if
char* instructions_createBranch(char* num, int tmp_id);   
#endif
