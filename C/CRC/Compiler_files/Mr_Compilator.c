#include <stdio.h> 
#include <stdlib.h> 
#include "Mr_Compilator.h"
#include "Data.h"
/*
This is our machine, our robot, who takes in the token and throws
out RISC - V assembly instructions, which then will be written in out - file in CRC.c, from which whole 
program starts execution. The robot will not need to store any separate data. It will throw out assembly 
instructions at place. It will store vector of declared variables(which will be defined in h file). 
it will have access to available types 
*/

//creates, initializes and returns new Mr_Compilator  
Mr_Compilator* Mr_Compilator_init() {
    Mr_Compilator* fresh = malloc(sizeof(Mr_Compilator)); 
    fresh->data = Data_init(); 
    fresh->generated = strVectorInit(); 
    fresh->open_scopes = strVectorInit(); 
    fresh->current_variables = varVectorInit(); 
    fresh->used_labels = strVectorInit(); 
    fresh->if_label_index = 0; 
    fresh->temp_label_index = 0; 
    fresh->sp_pos = 0; 
    fresh->processed_tokens = 1; 
    return fresh; 
}
//PRIVATE ACCESS: determines if str is a string representation of a number
int isNum(const char* str) {
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
variable* isVarOrConstant(Mr_Compilator* mra, char* name) {
    variable* dummy_var = malloc(sizeof(variable)); dummy_var->variable_name = strdup(name); 
    dummy_var->assigned_val = NULL; dummy_var->td = NULL;
    int idx = varVectorSearch(mra->current_variables, dummy_var); 
        if(idx == -1) {
            if(isNum(name)) {
                free(dummy_var->variable_name); 
                dummy_var->variable_name = strdup("const"); 
                dummy_var->assigned_val = strdup(name); 
                return dummy_var; 
            }
            varFree(dummy_var); 
            printf("variable not found error on line %d, aborting Compilation...\n", mra->processed_tokens);
            abort(); 
        }
    varFree(dummy_var); 
    return varVectorGet(mra->current_variables, idx); 
}


//PRIVATE ACCESS: handles expressions of type x or 3 or 3 + 5 or x + y, number of elements must be at most 2 and operation must be only one
char* analyzeExpression(Mr_Compilator* mra, int* already_stored) {
    char* first = strtok(NULL, " "); 
    char* op = strtok(NULL, " "); 
    char* second = op ? strtok(NULL, " ") : "0";
    variable* first_var; variable* second_var; 
    first_var = isVarOrConstant(mra, first); 
    if(op == NULL) {
        char* val = strdup(first_var->assigned_val); 
        if(strcmp(first_var->variable_name, "const") != 0) {
            char* val = Mr_Compilator_readVar(mra, first_var->variable_name); 
            free(val); 
            *already_stored = 1; 
        }
        varFree(first_var); 
        return val; 
    }
    second_var = isVarOrConstant(mra, second); 
    char* val = Mr_Compilator_opVariables(mra, *first_var, *second_var, op);
    varFree(first_var); varFree(second_var); 
    *already_stored = 1; 
    return val;  
}

//PRIVATE ACCESS: handles the case, when variable is not defined.
void handleNonExistantVar(Mr_Compilator* mra, type_desc* tdp) {
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
          Mr_Compilator_AssignVar(mra, Mr_Compilator_declareVar(mra, tdp, var_name),already_stored, val); 
          free(val); 
        } else {
            Mr_Compilator_declareVar(mra, tdp, var_name); 
        }
        free(var_name);
    }

//PRIVATE ACCESS: handles the case, when the variable we are working with is already defined.
void handleExistantVar(Mr_Compilator* mra, char* first_token) {
     char* var_name = strdup(first_token); 
        variable dummy_var; 
        dummy_var.variable_name = var_name; 
        assert(var_name); 
        int idx = varVectorSearch(mra->current_variables, &dummy_var);
        if(idx == -1) {
            printf("variable not found error on line %d, aborting Compilation...\n", mra->processed_tokens);
            abort(); 
        } else {
            variable* var = varVectorGet(mra->current_variables, idx);
            strtok(NULL, " "); 
            int already_stored = 0; 
            char* val = analyzeExpression(mra, &already_stored);     
            Mr_Compilator_AssignVar(mra, *var,already_stored, val); 
            varFree(var); 
            free(val); 
        }
        free(var_name);
} 
//PRIVATE ACCESS: handles the case, when the custom print function of our compiler is inputted by the user
void handleCustomPrinting(Mr_Compilator* mra) {
    char* var_name = strtok(NULL, " "); assert(var_name); 
    variable* var = isVarOrConstant(mra, var_name); 
    Mr_Compilator_printVar(mra, *var); 
    varFree(var); 
}
void handleSimpleIfStatement(Mr_Compilator* mra) {
    strtok(NULL, " "); //jumping over ( 
    char* var = strtok(NULL, " ");
    char* var_val = NULL; 
    int is_variable = !isNum(var);  
    if(is_variable){
        var_val = Mr_Compilator_readVar(mra, var); 
    }
    if(var_val)var = var_val; 
    char buffer[100]; 
    snprintf(buffer, 100, "G%d", mra->if_label_index); 
    Mr_Compilator_openScope(mra, buffer); 
    Mr_Compilator_createBranch(mra, var, is_variable);
    if(var_val)free(var); 
    mra->if_label_index++; 
}

//asks Mr_Compilator kindly to analyze given input token
void Mr_Compilator_Ask(Mr_Compilator* new_asm, char* token) {
    char* my_tok = strdup(token); 
    Mr_Compilator_Analyze(new_asm, my_tok);
    free(my_tok);  
    new_asm->processed_tokens++; 
}
//functions print value of the given variable and returns the value 
char* Mr_Compilator_printVar(Mr_Compilator* mra, variable var) {
    char* instr = instructions_printVar(var, mra->sp_pos);
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    return var.variable_name; 
}
//PRIVATE ACCESS: clears out all the variables that were created in stack after sp_position
void clearOutVariables(Mr_Compilator* mra, char* sp_position) {
    int varVect_len = varVectorLength(mra->current_variables); 
    int criminal_count = 0; 
    for(int i = 0; i < varVect_len; i++) {
        variable* curr_var = varVectorGet(mra->current_variables, i);
        if((curr_var->offset - curr_var->td->type_size) >= atoi(sp_position)) { 
        varVectorDelete(mra->current_variables, i); 
        varVectorAppend(mra->current_variables, curr_var); 
        criminal_count++; 
        }
        varFree(curr_var);  
    }
    for(int i = 0; i < criminal_count; i++) {
        varVectorDelete(mra->current_variables, varVectorLength(mra->current_variables) - 1); 
    }
}

//opens a new scope(called when { comes)
void Mr_Compilator_openScope(Mr_Compilator* mra, char* name) {
    // Mr_Compilator_addLabel(mra, name); 
    char buffer[100]; 
    snprintf(buffer, 100, "%d %s", mra->sp_pos, name); 
    strVectorAppend(mra->open_scopes, buffer); 
}
//closes a newly opened scope
void Mr_Compilator_closeScope(Mr_Compilator* mra) {
    int vect_size = strVectorLength(mra->open_scopes); 
    if(vect_size == 0) {
        printf("closing unopened bracket error on line %d, aborting Compilation...\n", mra->processed_tokens); 
        abort(); 
    }
    char* bracket_info = strVectorGet(mra->open_scopes, vect_size - 1); 
    strVectorDelete(mra->open_scopes, vect_size - 1); 
    char* instr = instructions_spMove(mra->sp_pos - atoi(bracket_info));  
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    clearOutVariables(mra, bracket_info); 
    mra->sp_pos = atoi(bracket_info); 
    char* label_name = strtok(bracket_info, " "); 
    label_name = strtok(NULL, " ");
    if(label_name[0] == 'G') {
        Mr_Compilator_addLabel(mra, label_name); 
    }
    free(bracket_info); 
}

//Analyzes passed token and does the work based on kind of input
void Mr_Compilator_Analyze(Mr_Compilator* mra, char* token) {
    char* first_token = strtok(token, " "); 
    if(strcmp(first_token, "{") == 0) {
        Mr_Compilator_openScope(mra, NULL); 
        return; 
    }
    if(strcmp(first_token, "}") == 0) {
        Mr_Compilator_closeScope(mra); 
        return;
    }
    if(strcmp(first_token, "CRC_OUT") == 0) {
        handleCustomPrinting(mra); 
        return; 
    }
    if((strcmp(first_token, "if") == 0)) {
        handleSimpleIfStatement(mra); 
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
variable Mr_Compilator_declareVar(Mr_Compilator* mra, type_desc* td, char* var_name) {
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
char* Mr_Compilator_AssignVar(Mr_Compilator* mra, variable var, int already_stored, char* val) {
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
char* Mr_Compilator_readVar(Mr_Compilator* mra, char* var_name) {
    variable dummy_var;
    dummy_var.variable_name = var_name;  
    int idx = varVectorSearch(mra->current_variables, &dummy_var); 
    if(idx == -1) {
        printf("variable not found error on line %d, aborting Compilation...\n", mra->processed_tokens);
            abort(); 
    }
    variable* var = varVectorGet(mra->current_variables, 
    idx);
    char* instr = instructions_readVar(*var, "t0", mra->sp_pos);
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
    if(strcmp(op, "+") == 0) {
        snprintf(result, 100, "%d", first_val + second_val); 
    } 
    else if(strcmp(op, "-") == 0) {
        snprintf(result, 100, "%d", first_val - second_val); 
    }
    else if(strcmp(op, "*") == 0) {
        snprintf(result, 100, "%d", first_val * second_val); 
    }
    else if(strcmp(op, "/") == 0) {
        snprintf(result, 100, "%d", first_val / second_val); 
    }
    else if(strcmp(op, ">") == 0) {
        snprintf(result, 100, "%d", first_val > second_val); 
    }
    else if(strcmp(op, "<") == 0) {
        snprintf(result, 100, "%d", first_val < second_val); 
    } else {
        snprintf(result, 100, "%d", first_val == second_val); 
    }
    return result; 
}

//function does operation op on given two variables and returns the resulting value
char* Mr_Compilator_opVariables(Mr_Compilator* mra, variable first_var, variable second_var, char* op) {
    char* res = opValues(first_var, second_var, op); 
    char* instr = instructions_opVars(first_var, second_var, "t0", op, mra->sp_pos); 
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    return res; 
} 
//function adds new label 
void Mr_Compilator_addLabel(Mr_Compilator* mra, char* name) {
    char* instr; 
    if(name) {
        instr = instructions_createLabel(name, -1); 
        strVectorAppend(mra->used_labels, name); 
    } else {
        instr = instructions_createLabel(NULL, mra->temp_label_index); 
        mra->temp_label_index++;  
    }
    strVectorAppend(mra->generated, instr); 
    free(instr); 
} 

void Mr_Compilator_createBranch(Mr_Compilator* mra, char* val, int is_variable) {
        char instr[100]; instr[0] = '\0'; 
    if(!is_variable) {
        snprintf(instr, 100, "li t0, %s\n", val);  
    }
     char* branch_instr = instructions_createBranch(mra->if_label_index);
     strcat(instr, branch_instr);  
     strVectorAppend(mra->generated, instr); 
    free(branch_instr); 
}

 //Sets Mr_Compilator free from unpaid labour, returns the generated assembly instructions 
strVector* Mr_Compilator_finish(Mr_Compilator* mra) { 
    Data_destroy(mra->data);
    strVectorDestroy(mra->used_labels); 
    varVectorDestroy(mra->current_variables);
    int numBrackets = strVectorLength(mra->open_scopes);    
    strVectorDestroy(mra->open_scopes); 
    char* instr = instructions_spMove(mra->sp_pos);  
    strVectorAppend(mra->generated, instr);
    free(instr);
    strVector* generated = mra->generated; //stores the address, so freeing mra will not affect it
    if(numBrackets) { 
       printf("Not all brackets were closed error, aborting compilation...\n"); 
       abort(); 
    }
    free(mra);
    return generated;  
}
