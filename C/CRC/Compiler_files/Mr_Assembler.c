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
    fresh->processed_tokens = 1; 
    return fresh; 
}
//PRIVATE ACCESS: determines if str is a string representation of a number
int isNumber(const char* str) {
    const char* trav = str; 
    if(trav[0] == '-')trav++; 
    while(*trav != '\0') {
        char curr = *trav; 
        if(curr < '0' || curr > '9')return 0; 
        trav++; 
    }
    return 1; 
}
//PRIVATE ACCESS: takes care of finding out whether token is the valid variable name or just a constant
variable* isVarOrConstant(Mr_Assembler* mra, char* name) {
    variable* dummy_var = malloc(sizeof(variable)); dummy_var->variable_name = strdup(name); 
    dummy_var->assigned_val = NULL; dummy_var->td = NULL;
    int idx = varVectorSearch(mra->current_variables, dummy_var); 
        if(idx == -1) {
            if(isNumber(name)) {
                free(dummy_var->variable_name); 
                dummy_var->variable_name = strdup("const"); 
                dummy_var->assigned_val = strdup(name); 
                return dummy_var; 
            }
            varFree(dummy_var); 
            printf("error on line %d, aborting Compilation...\n", mra->processed_tokens);
            abort(); 
        }
    varFree(dummy_var); 
    return varVectorGet(mra->current_variables, idx); 
}


//PRIVATE ACCESS: handles expressions of type x or 3 or 3 + 5 or x + y, number of elements must be at most 2 and operation must be only one
char* analyzeExpression(Mr_Assembler* mra, int* already_stored) {
    char* first = strtok(NULL, " "); 
    char* op = strtok(NULL, " "); 
    char* second = op ? strtok(NULL, " ") : "0";
    variable* first_var; variable* second_var; 
    first_var = isVarOrConstant(mra, first); 
    if(op == NULL) {
        char* val = strdup(first_var->assigned_val); 
        varFree(first_var); 
        *already_stored = 0;
        return val; 
    }
    second_var = isVarOrConstant(mra, second); 
    char* val = Mr_Assembler_opVariables(mra, *first_var, *second_var, op);
    varFree(first_var); varFree(second_var); 
    *already_stored = 1; 
    return val;  
}

//PRIVATE ACCESS: handles the case, when variable is not defined.
void handleNonExistantVar(Mr_Assembler* mra, type_desc* tdp) {
     char* var_name = strdup(strtok(NULL, " "));
        assert(var_name); 
        variable dummy_var; dummy_var.variable_name = var_name; 
        if(varVectorSearch(mra->current_variables, &dummy_var) != -1) {
            printf("Redefinition of the variable on line %d, aborting compilation...\n",
            mra->processed_tokens);
            free(var_name); 
            free(tdp); 
            abort(); 
        }
        char* equal_sign = strtok(NULL, " ");
        if(equal_sign) {
          int already_stored = 0; 
          char* val = analyzeExpression(mra, &already_stored); 
          Mr_Assembler_AssignVar(mra, Mr_Assembler_declareVar(mra, tdp, var_name),already_stored, val); 
          free(val); 
        } else {
            Mr_Assembler_declareVar(mra, tdp, var_name); 
        }
        free(var_name);
    }

//PRIVATE ACCESS: handles the case, when the variable we are working with is already defined.
void handleExistantVar(Mr_Assembler* mra, char* first_token) {
     char* var_name = strdup(first_token); 
        variable dummy_var; 
        dummy_var.variable_name = var_name; 
        assert(var_name); 
        int idx = varVectorSearch(mra->current_variables, &dummy_var);
        if(idx == -1) {
            printf("error on line %d, aborting Compilation...\n", mra->processed_tokens);
            abort(); 
        } else {
            variable* var = varVectorGet(mra->current_variables, idx);
            strtok(NULL, " "); 
            int already_stored = 0; 
            char* val = analyzeExpression(mra, &already_stored);     
            Mr_Assembler_AssignVar(mra, *var,already_stored, val); 
            varFree(var); 
            free(val); 
        }
        free(var_name);
} 
//PRIVATE ACCESS: handles the case, when the custom print function of our compiler is inputted by the user
void handleCustomPrinting(Mr_Assembler* mra) {
    char* var_name = strtok(NULL, " "); assert(var_name); 
    variable* var = isVarOrConstant(mra, var_name); 
    Mr_Assembler_printVar(mra, *var); 
    varFree(var); 
}

//asks Mr_Assembler kindly to analyze given input token
void Mr_Assembler_Ask(Mr_Assembler* new_asm, char* token) {
    char* my_tok = strdup(token); 
    Mr_Assembler_Analyze(new_asm, my_tok);
    free(my_tok);  
    new_asm->processed_tokens++; 
}
//functions print value of the given variable and returns the value 
char* Mr_Assembler_printVar(Mr_Assembler* mra, variable var) {
    char* instr = instructions_printVar(var, mra->sp_pos);
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    return var.variable_name; 
}

//Analyzes passed token and does the work based on kind of input
void Mr_Assembler_Analyze(Mr_Assembler* mra, char* token) {
    char* first_token = strtok(token, " "); 
    if(strcmp(first_token, "CRC_OUT") == 0) {
        handleCustomPrinting(mra); 
        return; 
    }
    type_desc* tdp = Data_lookUp(mra->data, first_token);
    if(tdp) {
        handleNonExistantVar(mra, tdp); 
    } else { 
        handleExistantVar(mra, first_token); 
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
    char* instr = instructions_declareVar(td);
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    varVectorAppend(mra->current_variables, &newVar); 
    return newVar; 
}

//function assigns value to a particular variable and returns the value
//function assumes that variable already exists
char* Mr_Assembler_AssignVar(Mr_Assembler* mra, variable var, int already_stored, char* val) {
    long long ival = atoll(val); 
    long long limit = Data_checkOverflow(mra->data, var.td->type_name);
    if(abs(ival) > limit) {
        printf("%s overflow detected on line %d, aborting compilation...\n", var.td->type_name,
        mra->processed_tokens);
        abort(); 
    }
    var.assigned_val = val; 
    varVectorReplace(mra->current_variables, &var, varVectorSearch(mra->current_variables, &var)); 
    char* instr = instructions_assignVar(var, val, already_stored, mra->sp_pos);
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
    char* instr = instructions_readVar(*var, "t0", var->offset);
    strVectorAppend(mra->generated, instr);
    free(instr); 
    char* val = strdup(var->assigned_val); 
    varFree(var); 
    return val; 
}

//PRIVATE ACCESS: returns first_var op second_var
char* opValues(variable first_var, variable second_var, char* op) {
    int first_val = atoi(first_var.assigned_val); 
    int second_val = atoi(second_var.assigned_val); 
    char* result = malloc(100); //number of digits cannot be more than 100 or even 100
    if(*op == '+') {
        snprintf(result, 100, "%d", first_val + second_val); 
    } 
    else if(*op == '-') {
        snprintf(result, 100, "%d", first_val - second_val); 
    }
    else if(*op == '*') {
        snprintf(result, 100, "%d", first_val * second_val); 
    }
    else {
        snprintf(result, 100, "%d", first_val / second_val); 
    }
    return result; 
}

//function does operation op on given two variables and returns the resulting value
char* Mr_Assembler_opVariables(Mr_Assembler* mra, variable first_var, variable second_var, char* op) {
    char* res = opValues(first_var, second_var, op); 
    char* instr = instructions_opVars(first_var, second_var, "t0", op, mra->sp_pos); 
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    return res; 
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
