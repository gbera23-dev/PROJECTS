#include <stdio.h> 
#include <stdlib.h> 
#include "filter.h"

//returns new filter instance. Ownership is transferred to a client
filter* filter_init(Mr_Compilator* cmp) {
    filter* fltr = malloc(sizeof(filter)); 
    fltr->cmp = cmp; 
    return fltr; 
}
//PRIVATE ACCESS: determines if str is a string representation of a number
int isNumber(const char* str) {
    const char* trav = str; 
    while(*trav != '\0') {
        char curr = *trav; 
        if(curr < '0' || curr > '9')return 0; 
        trav++; 
    }
    return 1; 
}
//PRIVATE ACCESS: 
int cnt_elems(strVector* v, char* str) {
    int asterisk_count = 0;  
    int size = strVectorLength(v); 
    for(int i = 0; i < size; i++) {
        char* curr = strVectorGet(v, i); 
        if(strcmp(curr, "=") == 0) {
            free(curr); 
            break; 
        }
        if(strcmp(curr, str) == 0) {
            asterisk_count++; 
        }
        free(curr); 
    }
    return asterisk_count; 
}
//PRIVATE ACCESS: for convenience, I will transform token's whitespaced information into strVector 
strVector* to_vector(char* token, char* terminator) {
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
//PRIVATE ACCESS: Takes out the part from left until = occurs, also deletes those tokens from strVector
char* before_expr(strVector* vct) {
  char buffer[10000]; 
    buffer[0] = '\0';
    while(1) {
        char* curr = strVectorGet(vct, 0); 
        if(strcmp(curr, "=") == 0) {
            strVectorDelete(vct, 0); 
            free(curr); 
            break; 
        }
        strVectorDelete(vct, 0); 
        strcat(buffer, curr); 
        strcat(buffer, " "); 
        free(curr); 
    }
   buffer[strlen(buffer) - 1] = '\0'; 
   return strdup(buffer); 
}
//PRIVATE ACCESS: Given the character, determines its operational priority
int get_priority(char* ch, Data* td) {    
    return Data_getPriority(td, ch);  
}

//PRIVATE ACCESS: handles special case, when the input is ( or )
void handleParenthesis(char* curr, strVector* operation_stack, strVector* posfix_vect) {
    if(strcmp(curr, "(") == 0) {
        strVectorAppend(operation_stack, curr); 
    } else {
        while(strVectorLength(operation_stack) > 0) {
            char* curr_top = strVectorGet(operation_stack, strVectorLength(operation_stack) - 1);
            strVectorDelete(operation_stack, strVectorLength(operation_stack) - 1); 
            if(strcmp(curr_top, "(") == 0) {
                free(curr_top); 
                break; 
            } else {
                strVectorAppend(posfix_vect, curr_top); 
            }
            free(curr_top); 
        }
    }
}

//PRIVATE ACCESS: uses two stack approach to generate posfix expression and puts answers in posfix_vect
void generate_posfix(strVector* vct, strVector* posfix_vect, Data* td) {
    strVector* operation_stack = strVectorInit(); 
    for(int i = 0; i < strVectorLength(vct); i++) {
        char* curr = strVectorGet(vct, i); 
        char buffer[10000];
        snprintf(buffer, 10000, "%s", curr); 
        free(curr);  
        if(strcmp(buffer,"(") == 0 || strcmp(buffer, ")") == 0) {
            handleParenthesis(buffer, operation_stack, posfix_vect); 
            continue; 
        }
        if(strlen(buffer) <= 2 && get_priority(buffer, td) != -1) {
            while(strVectorLength(operation_stack) > 0) {
                char* curr_top = strVectorGet(operation_stack, strVectorLength(operation_stack) - 1);
                if(get_priority(curr_top, td) >= get_priority(buffer, td)) { 
                    strVectorAppend(posfix_vect, curr_top);
                    strVectorDelete(operation_stack, strVectorLength(operation_stack) - 1);
                    free(curr_top);  
                    continue; 
                }
                free(curr_top);
                break; 
        }
            strVectorAppend(operation_stack, buffer); 
        } 
        
        else {
            strVectorAppend(posfix_vect, buffer); 
        }
    }
    //flushing the stack 
    while(strVectorLength(operation_stack) > 0) {
        char* top = strVectorGet(operation_stack, strVectorLength(operation_stack) - 1); 
        strVectorDelete(operation_stack, strVectorLength(operation_stack) - 1); 
        strVectorAppend(posfix_vect, top); 
        free(top); 
    }
    strVectorDestroy(operation_stack); 
}

//PRIVATE ACCESS: Transfers expression to posfix representation 
strVector* posfix_rep(strVector* vct, Data* td) {
    strVector* posfix_vect = strVectorInit(); 
    char* init_str = before_expr(vct); 
    strVectorAppend(posfix_vect, init_str); 
    free(init_str); 
    generate_posfix(vct, posfix_vect, td); 
    return posfix_vect; 
}

/*PRIVATE ACCESS: determines if operator is logical or not*/
int are_logical_operators(strVector* vct) {
    char* operators[3] = {"&&", "||", "=="}; 
    for(int i = 0; i < 3; i++) {
        if(strVectorSearch(vct, operators[i]) != -1)return 1; 
    }
    return 0; 
}
//PRIVATE_ACCESS:
strVector* generate_logical_operator_replacements(strVector* v) {
    char* operator = strVectorGet(v, strVectorLength(v) - 2);
    char* second_elem = strVectorGet(v, strVectorLength(v) - 1); 
    char* first_elem = strVectorGet(v, strVectorLength(v) - 3); 
    int assignment_idx = strVectorSearch(v, "="); 
    char* variable_name = strVectorGet(v, assignment_idx - 1); 
    char* bracket_part= malloc(10000);
    determine_bracketPart(bracket_part, operator, first_elem, second_elem, variable_name);  
    char* complete_token = malloc(10000); complete_token[0] = 0; 
    if(assignment_idx == 2) {
        char* type_name = strVectorGet(v, 0); 
        snprintf(complete_token, 10000, "\n%s %s\n", type_name, variable_name); 
        free(type_name); 
    }
    strcat(complete_token, bracket_part);
    free(second_elem); free(operator); free(first_elem); free(variable_name); free(bracket_part); 
    strVectorDestroy(v); 
    strVector* strv = to_vector(complete_token, "\n");
    free(complete_token);  
    return strv; 
}

/*PRIVATE ACCESS: replaces ==, ||, && instructions with instructions good sir can understand.
note that > and < are not logical operators, they are comparison operators. so is ==, but we 
will leave it as an exception(I wrote cool implementation of == with simple ifs)
*/
strVector* replace_logical_operators(Mr_Compilator* mra, char* token) {
    strVector* v = to_vector(token, " "); 
    int size = strVectorLength(v); 
    if(!are_logical_operators(v)) {
        strVectorDestroy(v); 
        strVector* ret = strVectorInit(); strVectorAppend(ret, token);
        return ret; 
    }
    return generate_logical_operator_replacements(v); 
}
//PRIVATE ACCESS: 
void transform_and_ask(Mr_Compilator* mra, char* curr_token) {
     strVector *v = replace_logical_operators(mra, curr_token);
     for (int j = 0; j < strVectorLength(v); j++) {
        char *tok = strVectorGet(v, j);
        Mr_Compilator_Ask(mra, tok);
        free(tok);
    }
    strVectorDestroy(v); 
}

//PRIVATE ACCESS: modifies stack neatly to handle unary operations  
void handleTransformableUnaryOperation(strVector* operand_stack, char** curr) {
    if (strcmp((*curr), "!") == 0) {
        free(*curr);
        (*curr) = strdup("==");
        strVectorAppend(operand_stack, "0");
    }
    else if (strcmp((*curr), "U+") == 0) {
        free(*curr);
        (*curr) = strdup("+");
        strVectorAppend(operand_stack, "0");
    }
    else if (strcmp((*curr), "U-") == 0) {
        char *top_elem = strVectorGet(operand_stack, strVectorLength(operand_stack) - 1);
        free(*curr);
        (*curr) = strdup("-");
        strVectorDelete(operand_stack, strVectorLength(operand_stack) - 1);
        strVectorAppend(operand_stack, "0");
        strVectorAppend(operand_stack, top_elem);
        free(top_elem);
    }
}
//PRIVATE ACCESS
char* get_variable_name(strVector* posfix_vct) {
    char* first_tok = strVectorGet(posfix_vct, 0);
    strVector* to_vct = to_vector(first_tok, " ");
    free(first_tok);
    char* variable_name = strVectorGet(to_vct, strVectorLength(to_vct) - 1); 
    strVectorDestroy(to_vct); 
    return variable_name; 
}

char* build_standard_unary_token(Mr_Compilator* mra, char* base_type, int pointer_count, char* curr, int* tmp_id, char* var_name) {
    char variable_type[100]; variable_type[0] = 0; 
    char buffer[1000]; 
    strcat(variable_type, base_type); 
    for(int i = 0; i < pointer_count; i++) {
        char tmp[100]; snprintf(tmp, 100, " %s ", "*"); 
        strcat(variable_type, tmp); 
    }
    snprintf(buffer, 1000, "%s tmp_%d = %s %s", variable_type, *tmp_id, curr, var_name); 
    return strdup(buffer); 
}

//PRIVATE ACCESS: 
int handle_standard_unary_operation(Mr_Compilator* mra, strVector* operand_stack, char* curr, int* tmp_id) {
    if(strcmp(curr, "U*") != 0 && strcmp(curr, "U&") != 0)return 0; 
    char* top = strVectorGet(operand_stack, strVectorLength(operand_stack) - 1); 
    variable dummy_var; dummy_var.variable_name = top; 
    strVectorDelete(operand_stack, strVectorLength(operand_stack) - 1);
    int idx = varVectorSearch(mra->current_variables, &dummy_var);
    if(idx == -1){
        printf("dereferencing and getreference operators work on variables in stack error at line %d. aborting compilation...\n",
        mra->processed_tokens);
        abort();  
    } 
    variable* var = varVectorGet(mra->current_variables, idx); 
    int pointer_count = var->td->pointer_count; 
    char* base_type = var->td->type_name; 
    char* variable_name = var->variable_name; 
    if(strcmp(curr, "U*") == 0)pointer_count--; 
    else pointer_count++;  
    if(pointer_count == -1) {
        printf("dereference operator does not work on non - pointer types error on line %d. aborting compilation...\n", 
        mra->processed_tokens); 
        abort(); 
    }
    char* res = build_standard_unary_token(mra, base_type, pointer_count, curr, tmp_id, variable_name); 
    transform_and_ask(mra, res); 
    char tmp_name[100]; snprintf(tmp_name, 100, "tmp_%d", *tmp_id); 
    strVectorAppend(operand_stack, tmp_name); 
    (*tmp_id)++; 
    varFree(var); 
    free(res); 
    free(top);
    return 1; 
}

void handle_binary_operation(Mr_Compilator* mra, strVector* operand_stack, strVector* posfix_vct, char* curr, int* tmp_id) {
    char buffer[10000]; char var_type[100]; var_type[0] = 0; 
    char* second = strVectorGet(operand_stack, strVectorLength(operand_stack) - 1); 
    strVectorDelete(operand_stack, strVectorLength(operand_stack) - 1); 
    char* first = strVectorGet(operand_stack, strVectorLength(operand_stack) - 1); 
    strVectorDelete(operand_stack, strVectorLength(operand_stack) - 1);
    variable dummy_var; dummy_var.variable_name = first;  
    int idx = varVectorSearch(mra->current_variables, &dummy_var);
    if(idx == -1)  {
        strcat(var_type, "int");  
    } else {
        variable* var = varVectorGet(mra->current_variables, idx);
        int pointer_count = var->td->pointer_count; 
        char* base_type = var->td->type_name; 
        char* variable_name = var->variable_name; 
            strcat(var_type, base_type); 
    for(int i = 0; i < pointer_count; i++) {
        char tmp[100]; snprintf(tmp, 100, " %s ", "*"); 
        strcat(var_type, tmp); 
    }
    varFree(var); 
    }
    snprintf(buffer, 10000, "%s tmp_%d = %s %s %s", var_type, *tmp_id, first, curr, second);
    transform_and_ask(mra, buffer); 
    char tmp_name[100]; snprintf(tmp_name, 100, "tmp_%d", *tmp_id); 
    strVectorAppend(operand_stack, tmp_name); 
    (*tmp_id)++; 
    free(first); 
    free(second);  
}

//PRIVATE ACCESS: Generates necessary tokens for Mr_Compilator to understand complex expressions
//there is a problem with this approach. tmp variable is always of type int, which means that 
//dereferencing will not work and I will get the error. 
//THIS IS THE ONE MORE FUNCTION THAT NEEDS REFACTORING
void gen_operations(Mr_Compilator* mra, strVector* operand_stack, strVector* posfix_vct) {
    int tmp_id = 1; 
    int size = strVectorLength(posfix_vct); 
    char* variable_name = get_variable_name(posfix_vct); 
    for(int i = 1; i < strVectorLength(posfix_vct); i++) {
        char* curr = strVectorGet(posfix_vct, i);        
        if(get_priority(curr, mra->data) == -1) {
            strVectorAppend(operand_stack, curr); 
            free(curr); 
            continue; 
        }
        handleTransformableUnaryOperation(operand_stack, &curr);
        if(handle_standard_unary_operation(mra, operand_stack, curr, &tmp_id)) {
            free(curr); 
            continue; 
        }
        handle_binary_operation(mra, operand_stack, posfix_vct, curr, &tmp_id); 
        free(curr); 
    }
           char* res = strVectorGet(operand_stack, 0);
    char final[10000]; 
    snprintf(final, 10000, "%s = %s", variable_name, res); 
    Mr_Compilator_Ask(mra, final); 
    free(variable_name); 
    free(res);
}

//PRIVATE ACCESS: Generates parts of a complex expression 
void generate_parts(Mr_Compilator* mra, strVector* posfix_vct) {
    strVector* operand_stack = strVectorInit();
    char* var_declaration = strVectorGet(posfix_vct, 0);  
    strVector* to_vct = to_vector(var_declaration, " "); 
    if(strVectorLength(to_vct) > 1) {
        Mr_Compilator_Ask(mra, var_declaration); 
    }
    free(var_declaration); 
    Mr_Compilator_Ask(mra, "{"); 
    gen_operations(mra, operand_stack, posfix_vct);
    Mr_Compilator_Ask(mra, "}");
    strVectorDestroy(operand_stack);  
    strVectorDestroy(to_vct); 
}

//PRIVATE ACCESS: Spaces out operators in the expression(i.e int x=3+5 to int x = 3 + 5)
char* separate_operators(char* token, Data* td) {
    char* new_tok = malloc(2*strlen(token) + 100); //size is just a safety precaution 
    int priority_one = -1;
    int priority_two = -1; 
    int curr_pos = 0; 
    for(int i = 0; i < strlen(token); i++) {
        char operator_size_one[10];
        char operator_size_two[10]; 
        operator_size_one[0] = token[i]; operator_size_one[1] = '\0'; 
        if(i + 1 < strlen(token)) {
            operator_size_two[0] = token[i];
            operator_size_two[1] = token[i + 1]; 
            operator_size_two[2] = '\0';  
        }
        priority_one = get_priority(operator_size_one, td); 
        if(i + 1 < strlen(token))priority_two = get_priority(operator_size_two, td); 
        if(priority_two != -1) {
            new_tok[curr_pos++] = ' '; 
            new_tok[curr_pos++] = token[i]; 
            new_tok[curr_pos++] = token[i + 1];
            new_tok[curr_pos++] = ' '; 
            i++; continue;  
        } else {
            if(priority_one == -1) {
                new_tok[curr_pos++] = token[i]; 
            } else {
                 new_tok[curr_pos++] = ' '; 
            new_tok[curr_pos++] = token[i]; 
            new_tok[curr_pos++] = ' '; 
            }
        }
    }
    new_tok[curr_pos] = '\0'; 
    return new_tok;  
}

/*PRIVATE ACCESS*/
void determine_bracketPart(char* bracket_part, char* operator, char* first_elem, char* second_elem, char* 
variable_name) {
    if(strcmp(operator, "==") == 0) {
        snprintf(bracket_part, 10000,
         "{\nint tmp_0__ = %s - %s\nint bool_tmp = 1\nif ( tmp_0__ ) {\nbool_tmp = 0\n}\n%s = bool_tmp\n}\n", 
        first_elem, second_elem, variable_name); 
    }
    else if(strcmp(operator, "&&") == 0) {
        snprintf(bracket_part, 10000,
         "{\nint bool_tmp = 0\nif ( %s ) {\n if ( %s ) {\nbool_tmp = 1\n }\n }\n%s = bool_tmp\n}\n", 
        first_elem, second_elem, variable_name);
    }
    else if(strcmp(operator, "||") == 0) {
        snprintf(bracket_part, 10000,
         "{\nint bool_tmp = 0\nif ( %s ) {\n bool_tmp = 1\n }\nif ( %s ) {\n bool_tmp = 1\n}\n %s = bool_tmp\n}\n", 
        first_elem, second_elem, variable_name);
    } else {
        bracket_part[0] = '\0'; 
    }
}

//PRIVATE ACCESS: adds U to unary + and - Client must put unary symbol in parenthesis along with number
void add_unary_symbols(strVector* v, filter* fltr) {
    int count = 0; 
    int size = strVectorLength(v); 
    for(int i = 1; i < size; i++) {
        char* curr = strVectorGet(v, i);
        char* previous = strVectorGet(v, i - 1);
        variable dummy_var; dummy_var.variable_name = previous; 
        int idx = varVectorSearch(fltr->cmp->current_variables, &dummy_var);
        int equal_idx = strVectorSearch(v, "=");
        if((strcmp(previous, ")") != 0) && !isNumber(previous) && (idx == -1)) {
            if(strcmp(curr, "+") == 0) {
                strVectorReplace(v, "U+", i); 
            }
            else if(strcmp(curr, "-") == 0) {
                strVectorReplace(v, "U-", i); 
            }
            else if(strcmp(curr, "*") == 0 && i > equal_idx) {
                strVectorReplace(v, "U*", i); 
            }
            else if(strcmp(curr, "&") == 0) {
                strVectorReplace(v, "U&", i); 
            }
        }
        free(curr); 
        free(previous); 
    }
}
//PRIVATE ACCESS: 
int check_for_unary_operators(strVector* vct) {
    char* arr[5] = {"!", "U+", "U-", "U*", "U&"}; 
    for(int i = 0; i < 5; i++) {
        if(strVectorSearch(vct, arr[i]) != -1)return 0; 
    }
    return 1; 
}

//PRIVATE ACCESS: 
int token_is_edible(filter* fltr, strVector* vct) {
    int is_function_logic = strVectorSearch(vct, "=") == -1 && strVectorSearch(vct, "(") != -1;  
    int asterisk_count = cnt_elems(vct, "U*"); 
    int is_small = (strVectorLength(vct) - asterisk_count) <= 6; 
    int are_no_unary_operators = check_for_unary_operators(vct); 
    return (is_small && are_no_unary_operators) || is_function_logic || (strVectorSearch(vct, "=") == -1); 
}
//PRIVATE ACCESS: 
int handleEdibleTokens(filter* fltr, strVector* vct, char* token) {
    if(token_is_edible(fltr, vct)) {
            strVector* v = replace_logical_operators(fltr->cmp, token); 
        for(int j = 0; j < strVectorLength(v); j++) {
           char* tok = strVectorGet(v, j);
           Mr_Compilator_Ask(fltr->cmp, tok);
           free(tok);  
        }
        strVectorDestroy(v); 
        strVectorDestroy(vct); 
        free(token); 
        return 1; 
    }
    return 0; 
}
//PRIVATE ACCESS: 
void handleInedibleTokens(filter* fltr, strVector* vct, char* token) {
    strVector *posfix_vct;
    posfix_vct = posfix_rep(vct, fltr->cmp->data);
    // now it is time to use another num stack and generate needed tokens
    generate_parts(fltr->cmp, posfix_vct);
    strVectorDestroy(vct);
    strVectorDestroy(posfix_vct);
    free(token);
}

//analyzes given token. It will determine whether compiler can handle a token or not. And if it cannot, it will dissolve it into parts. 
void filter_analyze(filter* fltr, char* token) {
    token = separate_operators(token, fltr->cmp->data); 
    strVector* vct = to_vector(token, " "); 
    add_unary_symbols(vct, fltr); 
    if(handleEdibleTokens(fltr, vct, token)) {
        return; 
    }
    handleInedibleTokens(fltr, vct, token); 
} 

//destroys given instance of a filter, once the compiler ends its work. filter must die too, but I will let these modules to not depend. 
void filter_destroy(filter* fltr) {
    if(fltr)free(fltr);
}
