
#ifndef _Mr_Assembler_
#define _Mr_Assembler_
#include "varVector.h"
#include "strVector.h"
#include "Data.h" 
#include "instructions.h"
#include <assert.h> //we may need this at some point

typedef struct {
    Data* data; //gives us a way to determine if type declaration is valid or not 
    varVector* current_variables; //maintains variable structs
    strVector* generated; //maintains currently generated assembly instructions by Mr_assembler
    int sp_pos; //tells us by how much we are away from initial stack pointer position
    int processed_tokens; //counts number of currently processed tokens by Mr.Assembler
} Mr_Assembler;

//creates, initializes and returns new Mr_Assembler  
Mr_Assembler* Mr_Assembler_init(); 

//Analyzes passed token and does the work based on kind of input
void Mr_Assembler_Analyze(Mr_Assembler* mra, char* token); 

//We ask Mr_Assembler kindly to analyze given input(function allows passing literal string as argument)
void Mr_Assembler_Ask(Mr_Assembler* mra, char* token);
/*
Now comes the useful functions that are part of analysis. 
They have some particular characteristic,
that is, they operate on the same memory, on instructions vector. They all insert some data into
this vector and return something
*/

//function declares a new variable(No assignment happens here) and returns copy of it
variable Mr_Assembler_declareVar(Mr_Assembler* mra, type_desc* td, char* var_name); 

//function assigns value to a particular variable and returns the value
char* Mr_Assembler_AssignVar(Mr_Assembler* mra, variable var, int already_stored, char* val); 
//functions print value of the given variable and returns the value 
char* Mr_Assembler_printVar(Mr_Assembler* mra, variable var); 
//function reads value assigned to a particular variable and returns that value
char* Mr_Assembler_readVar(Mr_Assembler* mra, char* var_name); 
//function operates on given two variables and returns the resulting value
char* Mr_Assembler_opVariables(Mr_Assembler* mra, variable first_var, variable second_var, char* op); 

 //Sets Mr_Assembler free from unpaid labour, returns the generated assembly instructions 
strVector* Mr_Assembler_finish(Mr_Assembler* mra);

#endif
