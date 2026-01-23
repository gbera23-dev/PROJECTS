
#ifndef _Mr_Compilator_
#define _Mr_Compilator_
#include "varVector.h"
#include "strVector.h"
#include "Data.h" 
#include "instructions.h"
#include <assert.h> //we may need this at some point

typedef struct {
    Data* data; //gives us a way to determine if type declaration is valid or not 
    varVector* current_variables; //maintains variable structs
    strVector* generated; //maintains currently generated assembly instructions by Mr_Compilator
    strVector* open_scopes; //maintains sp positions, when the new scope was opened 
    strVector* used_labels; //maintains labels that have deliberate names(will be used for functions)
    int temp_label_index; //used to create new labels as we cannot remove older ones 
    int if_label_index; //same purpose as temp_labels 
    int loop_label_index; //same purpose as temp_labels; 
    int sp_pos; //tells us by how much we are away from initial stack pointer position
    int processed_tokens; //counts number of currently processed tokens by Mr.Assembler
} Mr_Compilator;

//creates, initializes and returns new Mr_Compilator  
Mr_Compilator* Mr_Compilator_init(); 

//Analyzes passed token and does the work based on kind of input
void Mr_Compilator_Analyze(Mr_Compilator* mra, char* token); 

//We ask Mr_Compilator kindly to analyze given input(function allows passing literal string as argument)
void Mr_Compilator_Ask(Mr_Compilator* mra, char* token);
/*
Now comes the useful functions that are part of analysis. 
They have some particular characteristic,
that is, they operate on the same memory, on instructions vector. They all insert some data into
this vector and return something
*/

//function declares a new variable(No assignment happens here) and returns copy of it
variable Mr_Compilator_declareVar(Mr_Compilator* mra, type_desc* td, char* var_name); 

//function assigns value to a particular variable and returns the value
char* Mr_Compilator_AssignVar(Mr_Compilator* mra, variable var, int already_stored, char* val); 
//functions print value of the given variable and returns the value 
char* Mr_Compilator_printVar(Mr_Compilator* mra, variable var); 
//function reads value assigned to a particular variable and returns that value
char* Mr_Compilator_readVar(Mr_Compilator* mra, char* var_name); 
//function operates on given two variables and returns the resulting value
char* Mr_Compilator_opVariables(Mr_Compilator* mra, variable first_var, variable second_var, char* op); 
//function opens new scope 
void Mr_Compilator_openScope(Mr_Compilator* mra, char* label_name, char* var_name); 
//function closes the newest scope 
void Mr_Compilator_closeScope(Mr_Compilator* mra); 
//function adds new label 
void Mr_Compilator_addLabel(Mr_Compilator* mra, char* name); 
//function adds new branch 
void Mr_Compilator_createBranch(Mr_Compilator* mra, char* label_name, int label_index, char* val, int is_variable); 
 //Sets Mr_Compilator free from unpaid labour, returns the generated assembly instructions 
strVector* Mr_Compilator_finish(Mr_Compilator* mra);

#endif
