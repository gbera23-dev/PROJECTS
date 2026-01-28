#include <stdio.h> 
#include <stdlib.h> 
#include "Mr_Compilator.h"
#include "Data.h"
/*
This is our machine, our robot, who takes in the token and throws
out RISC - V assembly instructions, which then will be written in out - file in CRC.c, from which whole 
program starts execution. It will throw out assembly 
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
    fresh->defined_functions = strVectorInit(); 
    fresh->defined_function_descriptions = strVectorInit();
    fresh->if_label_index = 0; 
    fresh->temp_label_index = 0; 
    fresh->loop_label_index = 0; 
    fresh->sp_pos = 0; 
    fresh->processed_tokens = 1; 
    return fresh; 
}

//PRIVATE ACCESS: for convenience, I will transform token's whitespaced information into strVector 
strVector* to_vect(char* token, char* terminator) {
    char* tkn = strdup(token); //tokenizer violates string
    strVector* new_vect = strVectorInit(); 
    char* first_token = strtok(tkn, terminator); 
    strVectorAppend(new_vect, first_token);
    while(1) {
        first_token = strtok(NULL, terminator); 
        if(first_token == NULL)break; 
        strVectorAppend(new_vect, first_token); 
    }
    free(tkn);
    return new_vect;  
}

//PRIVATE ACCESS: determines if str is a string representation of a number
int isNum(const char* str) {
    const char* trav = str; 
    while(*trav != '\0') {
        char curr = *trav; 
        if(curr < '0' || curr > '9'){
            return 0;
        } 
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
//PRIVATE ACCESS: handles the case when operator present is binary or if we have just an assignment
char* analyzeBinaryExpression(Mr_Compilator* mra, int* already_stored, char* first, char* op, char* second) {
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

char* analyzeUnaryExpression(Mr_Compilator* mra, char* operator, int* already_stored) {
    char* var_name = strtok(NULL, " "); 
    variable* var = isVarOrConstant(mra, var_name); 
    if(strcmp(operator, "U&") == 0 && strcmp(var->variable_name, "const") == 0) {
        printf("cannot obtain address of value not stored on stack error on line %d. aborting compilation...\n", mra->processed_tokens);  
        abort(); 
    }
    char* val = Mr_Compilator_opVariable(mra, *var, operator);
    if(strcmp(var->variable_name, "const") != 0) {
        *already_stored = 1; 
    } 
    varFree(var);
    return val; 
}

//PRIVATE ACCESS: handles expressions of type x or 3 or 3 + 5 or x + y, number of elements must be at most 2 and operation must be only one
char* analyzeExpression(Mr_Compilator* mra, int* already_stored) {
    char* first = strtok(NULL, " "); 
    if(strcmp(first, "U*") == 0 || strcmp(first, "U&") == 0) {
        return analyzeUnaryExpression(mra, first, already_stored); 
    }
    char* op = strtok(NULL, " "); 
    char* second = op ? strtok(NULL, " ") : "0";
    return analyzeBinaryExpression(mra, already_stored, first, op, second); 
}

//PRIVATE ACCESS: handles the case, when variable is not defined.
void handleNonExistantVar(Mr_Compilator* mra, type_desc* tdp) {
    char* var_name = strtok(NULL, " ");
    while(strcmp(var_name, "*")==0)var_name = strtok(NULL, " "); 
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
          Mr_Compilator_AssignVar(mra, Mr_Compilator_declareVar(mra, tdp, var_name),already_stored, val, "sp"); 
          free(val); 
        } else {
            Mr_Compilator_declareVar(mra, tdp, var_name); 
        }
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
            Mr_Compilator_AssignVar(mra, *var,already_stored, val, "sp"); 
            varFree(var); 
            free(val); 
        }
        free(var_name);
} 
//PRIVATE ACCESS: handles the case, when the custom print function of our compiler is inputted by the user
void handleCustomPrinting(Mr_Compilator* mra) {
    strtok(NULL, " "); //jumping over ( 
    char* var_name = strtok(NULL, " "); assert(var_name); 
    variable* var = isVarOrConstant(mra, var_name); 
    Mr_Compilator_printVar(mra, *var); 
    varFree(var); 
}
//PRIVATE ACCESS: reads the statement inside if and while 
char* readStatement(Mr_Compilator* mra, char* var, int* is_variable, char** var_name) {
    strtok(NULL, " "); //jumping over ( 
    var = strtok(NULL, " ");
    if(var_name) {
        *var_name = var; 
    }
    char* var_val = NULL; 
    (*is_variable) = !isNum(var);  
    if((*is_variable)){
        var_val = Mr_Compilator_readVar(mra, var); 
    }
    if(var_val){
        var = strdup(var_val);
        free(var_val); 
    } 
    return var; 
}


//PRIVATE ACCESS: 
void handleSimpleIfStatement(Mr_Compilator* mra) {
    int is_variable; 
    char* var = readStatement(mra, var, &is_variable, NULL); 
    char buffer[100]; 
    snprintf(buffer, 100, "G%d", mra->if_label_index); 
    Mr_Compilator_openScope(mra, buffer, NULL); 
    Mr_Compilator_createBranch(mra, "G", mra->if_label_index, var, is_variable);
    mra->if_label_index++; 
    if(is_variable)free(var); 
}

//PRIVATE ACCESS: 
void handleSimpleWhileStatement(Mr_Compilator* mra) {
    int is_variable; 
    char* var_name; 
    char* var = readStatement(mra, var, &is_variable, &var_name); 
    char buffer[100]; 
    Mr_Compilator_createBranch(mra, "L", mra->loop_label_index + 1, var, is_variable); 
    snprintf(buffer, 100, "L%d", mra->loop_label_index);
    Mr_Compilator_openScope(mra, buffer, var_name); 
    Mr_Compilator_addLabel(mra, buffer); 
    mra->loop_label_index += 2; 
    if(is_variable)free(var); 
}


//PRIVATE ACCESS: 
char* fill_in_funct_description(Mr_Compilator* mra, int is_call) {
    strtok(NULL, " "); //jumping over (
    char* type = strtok(NULL, " "); 
    char buffer[1000]; buffer[0] = '\0';

    while(strcmp(type, ")") != 0) {
        type_desc* td = Data_lookUp(mra->data, type, 0);
         if(td || (strcmp(type, ",") != 0)) {
            strcat(buffer, type);
            strcat(buffer, " ");  
         }
         if(td)free(td);  
         type = strtok(NULL, " "); 
    }
    strcat(buffer, "void");
    if(!is_call) {
    strVectorAppend(mra->defined_function_descriptions, buffer);  
    }
    return strdup(buffer); 
}


strVector* transform_asterisks(Data* data, char* variables) {
    strVector* tokenized = to_vect(variables, " ");
    strVector* res = strVectorInit(); 
    int aster_count = 0; 
    for(int i = 0; i < strVectorLength(tokenized); i++) {
        char* curr = strVectorGet(tokenized, i); 
        if(strcmp(curr, "void") == 0){
            strVectorAppend(res, curr); 
            free(curr); 
            break;
        } 
        if(strcmp(curr, "*") == 0){
            aster_count++; 
        }
        else {
            type_desc* td = Data_lookUp(data, curr, 0);
            if(!td) {
                char tmp[100]; snprintf(tmp, 100, "%d", aster_count); 
                aster_count = 0; 
                strVectorAppend(res, tmp); 
            } 
            strVectorAppend(res, curr); 
            if(td)free(td); 
        }
        free(curr); 
    } 
    strVectorDestroy(tokenized); 
    return res; 
}

//PRIVATE ACCESS: 
void validateFunctionCall(Mr_Compilator* mra, char* buff, char* function_name) {
    int idx = strVectorSearch(mra->defined_functions, function_name);
    if(idx == -1) {
        printf("no function named \"%s\" is defined error on line %d. aborting compilation...\n", function_name,
        mra->processed_tokens);
        abort(); 
    }
    char* definition_args = strVectorGet(mra->defined_function_descriptions, idx); 
    strVector* definition_args_vct = transform_asterisks(mra->data, definition_args); 
    strVector* called_args_vct = to_vect(buff, " "); 
    int definition_len = strVectorLength(definition_args_vct), called_len = strVectorLength(called_args_vct);
    if((definition_len / 3) != (called_len - 1)) {
        printf("specified function needs %d arguments, %d arguments are provided. aborting compilation...\n", 
        (definition_len / 3), called_len - 1);
        abort();
    } 
    strVectorDestroy(definition_args_vct); 
    strVectorDestroy(called_args_vct); 
    free(definition_args); 
}
//PRIVATE ACCESS: 
void storeVariablesInStack(Mr_Compilator* mra, char* buff) {
    strVector* buff_vct = to_vect(buff, " "); 
    int size = strVectorLength(buff_vct) - 1;
    int tmp_idx = 1; 
    char buffer[100]; 
    for(int i = size - 1; i >= 0; i--) {
        char* curr = strVectorGet(buff_vct, i); 
        snprintf(buffer, 100, "int __ARG%d = %s", tmp_idx, curr); 
        strtok(buffer, " ");  
        type_desc* td = Data_lookUp(mra->data, "int", 0); 
        handleNonExistantVar(mra, td);
        free(curr); 
        free(td); 
        tmp_idx++; 
    }
    strVectorDestroy(buff_vct); 
} 


//PRIVATE ACCESS: 
void handleFunctionDefinition(Mr_Compilator* mra) {
    char* function_name = strtok(NULL, " "); 
    if(strVectorSearch(mra->defined_functions, function_name) != -1) {
        printf("Function redefinition error at line %d, aborting compilation...\n", mra->processed_tokens); 
        abort(); 
    }
    strVectorAppend(mra->defined_functions, function_name); 
    char* buff =  fill_in_funct_description(mra, 0); free(buff);  
    Mr_Compilator_addComment(mra, "FUNCTION");
    Mr_Compilator_openScope(mra, NULL, NULL); 
    char* variables = strVectorGet(mra->defined_function_descriptions, 
        strVectorLength(mra->defined_function_descriptions) - 1); 

    strVector* tokenized = transform_asterisks(mra->data, variables);   
    free(variables); 
    int i = strVectorLength(tokenized) - 2;
    for(; i > 0; i-=3) {
        char* arg_type = strVectorGet(tokenized, i - 2); 
        char* asterisk_count = strVectorGet(tokenized, i - 1);
        char* arg_name = strVectorGet(tokenized, i);
        type_desc* td = Data_lookUp(mra->data, arg_type, atoi(asterisk_count));  
        Mr_Compilator_declareVar(mra, td, arg_name);
        if(td) { 
        free(td);
        }
        free(arg_type); free(arg_name); free(asterisk_count);
    }
    Mr_Compilator_addComment(mra, "F_START"); 
    Mr_Compilator_addLabel(mra, function_name); 
    Mr_Compilator_openScope(mra, function_name, NULL);
    strVectorDestroy(tokenized); 
}
    /*funct(x, y);*/ 
//     {;
//         /*addi sp, sp -4*/ 
//         /*sw ra, 0(sp)*/
//         int phantom_ra; 
//     {;
//         // int __ARG1 = x; 
//         // int __ARG2 = y; 
//         /*call funct*/ 
//     };
//         /*lw ra 0(sp)*/
//    }; 
void handleFunctionCall(Mr_Compilator* mra, char* token) {
    char* function_name = token; 
    char* buff = fill_in_funct_description(mra, 1); 
    validateFunctionCall(mra, buff, token); 
    Mr_Compilator_openScope(mra, NULL, NULL);
    type_desc* td = Data_lookUp(mra->data, "int", 0);  
    Mr_Compilator_declareVar(mra, td, "___RA");
    if(td)free(td); 
    strVectorAppend(mra->generated, "sw ra, 0(sp)\n"); 
    Mr_Compilator_openScope(mra, NULL, NULL);
    storeVariablesInStack(mra, buff); 
    free(buff); 
    char call_buffer[100]; 
    snprintf(call_buffer, 100, "call %s\n", function_name); 
    strVectorAppend(mra->generated, call_buffer);
    Mr_Compilator_closeScope(mra); 
    strVectorAppend(mra->generated, "lw ra, 0(sp)\n"); 
    Mr_Compilator_closeScope(mra); 
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
void Mr_Compilator_openScope(Mr_Compilator* mra, char* label_name, char* var_name) {
    // Mr_Compilator_addLabel(mra, name); 
    char buffer[100]; 
    if(var_name) {
        snprintf(buffer, 100, "%d %s %s", mra->sp_pos, label_name, var_name);  
    } else {
        snprintf(buffer, 100, "%d %s", mra->sp_pos, label_name); 
    }
    strVectorAppend(mra->open_scopes, buffer); 
}


void closeScopeInteractions(Mr_Compilator* mra, char* label_name, char* variable) {
 if(label_name[0] == 'G') {
        Mr_Compilator_addLabel(mra, label_name); 
    } 
    else if(label_name[0] == 'L') {
        char* var = Mr_Compilator_readVar(mra, variable); 
        free(var); 
        char buffer[100];
        snprintf(buffer, 100, "bne t0, zero %s\n", label_name); 
        strVectorAppend(mra->generated, buffer); 
    }
    else if(label_name[0] != '('){
        strVectorAppend(mra->generated, "ret\n"); 
        Mr_Compilator_closeScope(mra);
        Mr_Compilator_addComment(mra, "FUNCTION");
    }
}


//closes the last open scope 
void Mr_Compilator_closeScope(Mr_Compilator* mra) {
    int vect_size = strVectorLength(mra->open_scopes); 
    if(vect_size == 0) {
        printf("closing unopened bracket error on line %d, aborting Compilation...\n", mra->processed_tokens); 
        abort(); 
    }
    char* bracket_info = strVectorGet(mra->open_scopes, vect_size - 1);
    strVectorDelete(mra->open_scopes, vect_size - 1); 
    int sp_pos = atoi(bracket_info); 
    char* bracket_info_cpy = strdup(bracket_info); 
    char* label_name = strtok(bracket_info_cpy, " "); 
    label_name = strtok(NULL, " ");
    char* variable = strtok(NULL, " "); 
    char* instr = instructions_spMove(mra->sp_pos - sp_pos);  
    strVectorAppend(mra->generated, instr); 
    free(instr); 
        if(variable) {
        int label_num = atoi(label_name + 1); 
        label_num++; 
        char buffer[1000]; sprintf(buffer, "L%d", label_num); 
        Mr_Compilator_addLabel(mra, buffer);
        }
    clearOutVariables(mra, bracket_info); 
    mra->sp_pos = sp_pos; 
    closeScopeInteractions(mra, label_name, variable); 
    free(bracket_info); 
    free(bracket_info_cpy); 
}
//PRIVATE ACCESS: 
int count_asterisks(strVector* v) {
    char* asterisk = "*";
    int asterisk_count = 0;  
    int size = strVectorLength(v); 
    for(int i = 0; i < size; i++) {
        char* curr = strVectorGet(v, i); 
        if(strcmp(curr, "=") == 0) {
            free(curr); 
            break; 
        }
        if(strcmp(curr, asterisk) == 0) {
            asterisk_count++; 
        }
        free(curr); 
    }
    return asterisk_count; 
}

//Analyzes passed token and does the work based on kind of input
void Mr_Compilator_Analyze(Mr_Compilator* mra, char* token) {
    strVector* vct = to_vect(token, " ");
    char* first_token = strtok(token, " "); 
    if(strcmp(first_token, "{") == 0) {
        Mr_Compilator_openScope(mra, NULL, NULL); 
        strVectorDestroy(vct); 
        return; 
    }
    if(strcmp(first_token, "}") == 0) {
        Mr_Compilator_closeScope(mra); 
        strVectorDestroy(vct);
        return;
    }
    if(strcmp(first_token, "CRC_OUT") == 0) {
        handleCustomPrinting(mra);
        strVectorDestroy(vct); 
        return; 
    }
    if((strcmp(first_token, "if") == 0)) {
        handleSimpleIfStatement(mra);
        strVectorDestroy(vct); 
        return; 
    }
    if((strcmp(first_token, "while") == 0)) {
        handleSimpleWhileStatement(mra);
        strVectorDestroy(vct); 
        return; 
    }
    
    if(strVectorSearch(vct, "=") == -1 && strVectorSearch(vct, "(") != -1) {
        type_desc* td = Data_lookUp(mra->data, first_token, 0); 
    if(td || strcmp(first_token, "void") == 0) {
        handleFunctionDefinition(mra); 
        strVectorDestroy(vct);
        free(td); 
        return; 
    }
        handleFunctionCall(mra, token); 
        if((strVectorSearch(mra->defined_functions, token)) != -1) {
        strVectorDestroy(vct); 
        return; 
    }
        printf("return type \"%s\" does not exist error on line %d. aborting compilation...\n", first_token, 
            mra->processed_tokens); 
        abort(); 
    } 
    else {
    int pointer_count = count_asterisks(vct);
    type_desc* tdp = Data_lookUp(mra->data, first_token, pointer_count);
    if(tdp) {
        handleNonExistantVar(mra, tdp); 
    } else { 
        handleExistantVar(mra, first_token); 
    }
    free(tdp);
    }
    strVectorDestroy(vct); 
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
char* Mr_Compilator_AssignVar(Mr_Compilator* mra, variable var, int already_stored, char* val, char* store_at) {
    long long ival = atoll(val); 
    long long limit = Data_checkOverflow(mra->data, var.td->type_name, var.td->pointer_count);
    if(abs(ival) > limit) {
        printf("%s overflow detected on line %d, aborting compilation...\n", var.td->type_name,
        mra->processed_tokens);
        abort(); 
    }
    var.assigned_val = val; 
    varVectorReplace(mra->current_variables, &var, varVectorSearch(mra->current_variables, &var)); 
    char* instr = instructions_assignVar(var, val, already_stored, mra->sp_pos, store_at);
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
    char* instr = instructions_readVar(*var, "t0", "sp", mra->sp_pos);
    strVectorAppend(mra->generated, instr);
    free(instr); 
    char* val = strdup(var->assigned_val); 
    varFree(var); 
    return val; 
}
//function adds a comment 
void Mr_Compilator_addComment(Mr_Compilator* mra, char* comment) {
    char* instr = instructions_addComment(comment); 
    strVectorAppend(mra->generated, instr); 
    free(instr); 
}

//PRIVATE ACCESS: 
char* handle_pointer_arithmetic(Mr_Compilator* mra, variable first_var, variable second_var, char* op) {
    if((strcmp(first_var.variable_name, "const") == 0 || first_var.td->pointer_count == 0) && 
        (strcmp(second_var.variable_name, "const") == 0 || second_var.td->pointer_count == 0))return NULL;
    if(strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        printf("multiplication and division is not allowed in pointer arithmetic error on line %d. aborting compilation...\n", 
        mra->processed_tokens); 
        abort(); 
    }

    if(strcmp(op, "+") == 0) {
        if(strcmp(second_var.variable_name, "const") != 0 && second_var.td->pointer_count > 0) {
            printf("pointer cannot be the second term of the summation error on line %d. aborting compilation...\n", 
            mra->processed_tokens); 
            abort(); 
        }
        char* result = malloc(100); 
        snprintf(result, 100, "%d", (atoi(first_var.assigned_val)) 
        + (first_var.td->final_type_size)*(atoi(second_var.assigned_val)));
        return result;  
    }
     if(strcmp(op, "-") == 0) {
        if(strcmp(second_var.variable_name, "const") != 0 && second_var.td->pointer_count > 0) {
            printf("pointer cannot be the second term of the difference error on line %d. aborting compilation...\n", 
            mra->processed_tokens); 
            abort(); 
        }
        char* result = malloc(100); 
        snprintf(result, 100, "%d", (atoi(first_var.assigned_val)) 
        - (first_var.td->final_type_size)*(atoi(second_var.assigned_val)));
        return result;  
    }
    return NULL; 
}

//PRIVATE ACCESS: returns first_var op second_var
char* opValues(Mr_Compilator* mra, variable first_var, variable second_var, char* op) {
    char* ptr_res = handle_pointer_arithmetic(mra, first_var, second_var, op); 
    if(ptr_res)return ptr_res;  
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
//PRIVATE ACCESS: returns value of variable positioned at given offset(returns -1 if such does not exist)
int get_var_at_address(Mr_Compilator* mra, int offset) {
    varVector* variables = mra->current_variables; 
    int size = varVectorLength(variables); 
    for(int i = 0; i < size; i++) {
        variable* curr = varVectorGet(variables, i);
        if(curr->offset == offset) {
            int value = atoi(curr->assigned_val);
            varFree(curr); 
            return value; 
        } 
        varFree(curr); 
    }
    return -1; 
}

//PRIVATE ACCESS: returns op var
char* opValue(Mr_Compilator* mra, variable var, char* op) {
    int val = atoi(var.assigned_val); 
    char* result = malloc(100); 

    if(strcmp(op, "U*") == 0) {
        if(var.td->pointer_count == 0) {
            printf("cannot dereference the non - pointer type error on line %d. aborting compilation...\n", 
                mra->processed_tokens); 
            abort(); 
        }
        var.td->pointer_count--; 
        //find the variable which is at var.assigned_val position 
        int val = get_var_at_address(mra, atoi(var.assigned_val)); 
        snprintf(result, 100, "%d", val); 
    }
    else if(strcmp(op, "U&") == 0) {
        snprintf(result, 100, "%d", var.offset);
    }
    return result; 
} 

//function does operation op on given two variables and returns the resulting value
char* Mr_Compilator_opVariables(Mr_Compilator* mra, variable first_var, variable second_var, char* op) {
    char* res = opValues(mra, first_var, second_var, op); 
    char* instr = instructions_opVars(first_var, second_var, "t0", op, mra->sp_pos); 
    strVectorAppend(mra->generated, instr); 
    free(instr); 
    return res; 
} 
//functions operates on given variable and returns the resulting value
char* Mr_Compilator_opVariable(Mr_Compilator* mra, variable var, char* op) {
    char* res = opValue(mra, var, op); 
    char* instr = instructions_opVar(var, "t0", op, mra->sp_pos); 
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

void Mr_Compilator_createBranch(Mr_Compilator* mra,  char* label_name, int label_index, char* val, int is_variable) {
        char instr[100]; instr[0] = '\0'; 
    if(!is_variable) {
        snprintf(instr, 100, "li t0, %s\n", val);  
    }
     char* branch_instr = instructions_createBranch(label_name, label_index);
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
    strVectorDestroy(mra->defined_functions); 
    strVectorDestroy(mra->defined_function_descriptions); 
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