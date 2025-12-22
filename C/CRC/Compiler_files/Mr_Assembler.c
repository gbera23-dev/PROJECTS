#include <stdio.h> 
#include <stdlib.h> 
#include "Mr_Assembler.h"
#include "Data.h"
/*
This is our machine, our robot, who takes in the token and throws
out RISC - V assembly instructions, which then will be written in out - file in CRC.c, from which whole 
program starts execution. The robot will not need to store any separate data. It will throw out assembly 
instructions at place. It will store vector of declared variables(which will be defined in h file). 
it will have access to available types 
*/

//creates, initializes and returns new Mr_Assembler  
Mr_Assembler* Mr_Assembler_init() {
    Mr_Assembler* fresh = malloc(sizeof(Mr_Assembler)); 
    fresh->data = Data_init(); 
    fresh->generated = strVectorInit(); 
    fresh->current_variables = varVectorInit(); 
    fresh->sp_pos = 0; 
    return fresh; 
}
//PRIVATE ACCESS: handles the case, when the variable we are working with is already defined.
void handleExistantVar(Mr_Assembler* mra, type_desc* tdp) {
     char* var_name = strdup(strtok(NULL, " "));
        assert(var_name); 
        variable dummy_var; dummy_var.variable_name = var_name; 
        if(varVectorSearch(mra->current_variables, &dummy_var) != -1) {
            printf("Redefinition of the already existing type on line %d, aborting compilation...\n",
            strVectorLength(mra->generated) + 1);
            free(var_name); 
            free(tdp); 
            abort(); 
        }
        char* equal_sign = strtok(NULL, " ");
         //skips the =(for this case, at some point, we will make all the tokens after = passed to specifier and
        //then to posfix calculator). now we are sure that value after = is some fixed 
        if(equal_sign) {
        char* var_val = strdup(strtok(NULL, " "));
        assert(var_val); 
        Mr_Assembler_AssignVar(mra, Mr_Assembler_declareVar(mra, tdp, var_name), var_val); 
        free(var_val); 
        } else {
            Mr_Assembler_declareVar(mra, tdp, var_name); 
        }
        free(var_name);
    }

//PRIVATE ACCESS: handles the case, when variable is not defined.
void handleNonExistantVar(Mr_Assembler* mra, type_desc* tdp, char* first_token) {
     char* var_name = strdup(first_token); 
        variable dummy_var; 
        dummy_var.variable_name = var_name; 
        assert(var_name); 
        int idx = varVectorSearch(mra->current_variables, &dummy_var);
        if(idx == -1) {
            printf("error on line %d, aborting Compilation...\n", strVectorLength(mra->generated) + 1);
            abort(); 
        } else {
            variable* var = varVectorGet(mra->current_variables, idx);
            strtok(NULL, " "); //jumping over = 
            char* var_val = strdup(strtok(NULL, " "));     
            Mr_Assembler_AssignVar(mra, *var, var_val); 
            varFree(var); 
            free(var_val); 
        }
        free(var_name);
} 
//asks Mr_Assembler kindly to analyze given input token
void Mr_Assembler_Ask(Mr_Assembler* new_asm, char* token) {
    char* my_tok = strdup(token); 
    Mr_Assembler_Analyze(new_asm, my_tok);
    free(my_tok);  
}

//Analyzes passed token and does the work based on kind of input
void Mr_Assembler_Analyze(Mr_Assembler* mra, char* token) {
    char* first_token = strtok(token, " "); 
    type_desc* tdp = Data_lookUp(mra->data, first_token);
    if(tdp) {
        handleExistantVar(mra, tdp); 
    } else { 
        handleNonExistantVar(mra, tdp, first_token); 
    }
    free(tdp);
}

/*
Now comes the useful functions that are part of analysis. 
They have some particular characteristic,
that is, they operate on the same memory, on instructions vector. They all insert some data into
this vector and return something
*/

//function declares a new variable(No assignment happens here) and returns copy of it
variable Mr_Assembler_declareVar(Mr_Assembler* mra, type_desc* td, char* var_name) {
    variable newVar; 
    newVar.variable_name = var_name; 
    newVar.td = td; 
    newVar.assigned_val = "0"; //C does not support this, I add this support, default value is considered and is 0(like in java)
    newVar.offset = td->type_size + mra->sp_pos; 
    mra->sp_pos += td->type_size; 
    char* intr = instructions_declareVar(td);
    strVectorAppend(mra->generated, intr); 
    free(intr); 
    varVectorAppend(mra->current_variables, &newVar); 
    return newVar; 
}

//function assigns value to a particular variable and returns the value
//function assumes that variable already exists
char* Mr_Assembler_AssignVar(Mr_Assembler* mra, variable var, char* val) {
    long long ival = atoll(val); 
    long long limit = Data_checkOverflow(mra->data, var.td->type_name);
    if(abs(ival) > limit) {
        printf("%s overflow detected on line %d, aborting compilation...\n", var.td->type_name,
        strVectorLength(mra->generated));
        abort(); 
    }
    var.assigned_val = val; 
    varVectorReplace(mra->current_variables, &var, varVectorSearch(mra->current_variables, &var)); 
    char* instr = instructions_assignVar(var, val, mra->sp_pos);
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    return val; 
}

//function reads value assigned to a particular variable and returns that value
char* Mr_Assembler_readVar(Mr_Assembler* mra, char* var_name) {
    variable dummy_var;
    dummy_var.variable_name = var_name;  
    variable* var = varVectorGet(mra->current_variables, 
        varVectorSearch(mra->current_variables, &dummy_var));
    strVectorAppend(mra->generated, instructions_readVar(*var, "t0", var->offset));
    char* val = strdup(var->assigned_val); 
    varFree(var); 
    return val; 
}

 //Sets Mr_Assembler free from unpaid labour, returns the generated assembly instructions 
strVector* Mr_Assembler_finish(Mr_Assembler* mra) { 
    Data_destroy(mra->data);
    varVectorDestroy(mra->current_variables);
    char* instr = instructions_spMove(mra->sp_pos);  
    strVectorAppend(mra->generated, instr);
    free(instr);
    strVector* generated = mra->generated; //stores the address, so freeing mra will not affect it
    free(mra); 
    return generated;  
}
