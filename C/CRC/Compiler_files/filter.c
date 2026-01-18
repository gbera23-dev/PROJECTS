#include <stdio.h> 
#include <stdlib.h> 
#include "filter.h"

//returns new filter instance. Ownership is transferred to a client
filter* filter_init(Mr_Compilator* cmp) {
    filter* fltr = malloc(sizeof(filter)); 
    fltr->cmp = cmp; 
    return fltr; 
}

//PRIVATE ACCESS: for convenience, I will transform token's whitespaced information into strVector 
strVector* to_vector(char* token) {
    char* tkn = strdup(token); //tokenizer violates string
    strVector* new_vect = strVectorInit(); 
    char* first_token = strtok(tkn, " "); 
    strVectorAppend(new_vect, first_token);
    while(1) {
        first_token = strtok(NULL, " "); 
        if(first_token == NULL)break; 
        strVectorAppend(new_vect, first_token); 
    }
    free(tkn);
    return new_vect;  
}
//PRIVATE ACCESS: Takes out the part from left until = occurs, also deletes those tokens from strVector
char* before_expr(strVector* vct) {
  char buffer[1000]; 
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
        char buffer[1000];
        snprintf(buffer, 1000, "%s", curr); 
        free(curr);  
        if(strcmp(buffer,"(") == 0 || strcmp(buffer, ")") == 0) {
            handleParenthesis(buffer, operation_stack, posfix_vect); 
            continue; 
        }
        if(strlen(buffer) == 1 && get_priority(buffer, td) != -1) {
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
//PRIVATE ACCESS: Generates necessary tokens for Mr_Compilator to understand complex expressions
void gen_operations(strVector* operand_stack, strVector* posfix_vct, strVector* gen_tokens, Data* td) {
    int tmp_id = 1; 
    char* beforeEquals = strVectorGet(gen_tokens, 0);
    char* name; 
    char* first_token = strtok(beforeEquals, " "); 
    char* second_token = strtok(NULL, " "); 
    if(second_token != NULL)name = second_token; 
    else {
        name = first_token;
        strVectorDelete(gen_tokens, 0); 
    } 
    for(int i = 0; i < strVectorLength(posfix_vct); i++) {
        char* curr = strVectorGet(posfix_vct, i); 
        char buffer[1000]; 
        if(get_priority(curr, td) == -1 || (strlen(curr) > 1 && (curr[1] >= '0' && curr[1] <= '9'))) {
            strVectorAppend(operand_stack, curr); 
        } else {
            char* second = strVectorGet(operand_stack, strVectorLength(operand_stack) - 1); 
            strVectorDelete(operand_stack, strVectorLength(operand_stack) - 1); 
            char* first = strVectorGet(operand_stack, strVectorLength(operand_stack) - 1); 
            strVectorDelete(operand_stack, strVectorLength(operand_stack) - 1);
            snprintf(buffer, 1000, "int tmp_%d = %s %s %s", tmp_id, first, curr, second); 
            char name[1000]; 
            snprintf(name, 1000, "tmp_%d", tmp_id); 
            strVectorAppend(operand_stack, name); 
            strVectorAppend(gen_tokens, buffer);
            free(first); 
            free(second);  
            tmp_id++;
        }
        free(curr); 
    }
    char* res = strVectorGet(operand_stack, 0);
    char final[1000]; 
    snprintf(final, 1000, "%s = %s", name, res); 
    strVectorAppend(gen_tokens, final); 
    free(res); 
    free(beforeEquals); 
}
//PRIVATE ACCESS: Generates parts of a complex expression 
strVector* generate_parts(strVector* posfix_vct, Data* td) {
    strVector* gen_tokens = strVectorInit();
    strVector* operand_stack = strVectorInit(); 
    char* initial = strVectorGet(posfix_vct, 0); 
    strVectorAppend(gen_tokens, initial); 
    free(initial);  
    strVectorDelete(posfix_vct, 0); 
    strVectorAppend(gen_tokens, "{"); 
    gen_operations(operand_stack, posfix_vct, gen_tokens, td);
    strVectorAppend(gen_tokens, "}");
    strVectorDestroy(operand_stack);  
    return gen_tokens; 
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

//analyzes given token. It will determine whether compiler can handle a token or not. And if it cannot, it will dissolve it into parts. 
void filter_analyze(filter* fltr, char* token) {
    token = separate_operators(token, fltr->cmp->data); 
    strVector* vct = to_vector(token); 
    strVector* posfix_vct; 
    strVector* dissolved_parts; 
    //hardcoded 6 is the number of tokens in following expression int x = z + y; for instance 
    if(strVectorLength(vct) <= 6) {
        Mr_Compilator_Ask(fltr->cmp, token); 
        strVectorDestroy(vct); 
        free(token); 
        return; 
    }
    posfix_vct = posfix_rep(vct, fltr->cmp->data); 
    //now it is time to use another num stack and generate needed tokens 
    dissolved_parts = generate_parts(posfix_vct, fltr->cmp->data); 
    for(int i = 0; i < strVectorLength(dissolved_parts); i++) {
        char* curr_token = strVectorGet(dissolved_parts, i); 
        Mr_Compilator_Ask(fltr->cmp, curr_token); 
        free(curr_token); 
    }
    free(token); 
    strVectorDestroy(vct); 
    strVectorDestroy(posfix_vct); 
    strVectorDestroy(dissolved_parts); 
} 
//destroys given instance of a filter, once the compiler ends its work. filter must die too, but I will let these modules to not depend. 
void filter_destroy(filter* fltr) {
    if(fltr)free(fltr);
}
