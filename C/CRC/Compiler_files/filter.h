#ifndef _filter_
#define _filter_
#include "Mr_Compilator.h"
/*
Welcome to filter module. This module is used to prepare inputted tokens, cook them up, before sending them to Mr_Compilator. Filter takes
responsibility temporarily to send instructions to Mr_Compilator and then gives the hold back to Mr_Compilator. This module will be 
responsible for few things. First of all, in this module, we will implement dual - stack approach algorithm for turning complex token 
expression to a number of tokens Mr_Compilator can handle. Similar to expression_example in input_c_files. The filter will also eventually
take hold of responsibility of error handler, so that token can really be compiled. I have high hopes and expectations from this module.  
*/

typedef struct {
  Mr_Compilator* cmp; 
}filter; 
//returns new filter instance. Ownership is transferred to a client
filter* filter_init(Mr_Compilator* cmp); 
//analyzes given token. It will determine whether compiler can handle a token or not. And if it cannot, it will dissolve it into parts.
void filter_analyze(filter *fltr, char *token);
//destroys given instance of a filter, once the compiler ends its work. filter must die too, but I will let these modules to not depend. 
void filter_destroy(filter* fltr); 
//Signatures of private access functions will be added here. client must be aware to not use the private access functions


int isNumber(const char* str); 
int cnt_elems(strVector* v, char* str);
strVector* to_vector(char* token, char* terminator); 
char* before_expr(strVector* vct); 
int get_priority(char* ch, Data* td); 
void handleParenthesis(char* curr, strVector* operation_stack, strVector* posfix_vect); 
void generate_posfix(strVector* vct, strVector* posfix_vect, Data* td); 
strVector* posfix_rep(strVector* vct, Data* td); 
int are_logical_operators(strVector* vct); 
strVector* generate_logical_operator_replacements(strVector* v);  
strVector* replace_logical_operators(Mr_Compilator* mra, char* token); 
void transform_and_ask(Mr_Compilator* mra, char* curr_token); 
void handleTransformableUnaryOperation(strVector* operand_stack, char** curr); 
char* get_variable_name(strVector* posfix_vct); 
char* build_standard_unary_token(Mr_Compilator* mra, char* base_type, 
  int pointer_count, char* curr, int* tmp_id, char* var_name); 
int handle_standard_unary_operation(Mr_Compilator* mra, strVector* operand_stack, char* curr, int* tmp_id); 
void handle_binary_operation(Mr_Compilator* mra, strVector* operand_stack, strVector* posfix_vct, char* curr, int* tmp_id); 
void gen_operations(Mr_Compilator* mra, strVector* operand_stack, strVector* posfix_vct); 
void generate_parts(Mr_Compilator* mra, strVector* posfix_vct); 
char* separate_operators(char* token, Data* td); 
void determine_bracketPart(char* bracket_part, char* operator, char* first_elem, char* second_elem, char* 
variable_name); 
void add_unary_symbols(strVector* v, filter* fltr); 
int check_for_unary_operators(strVector* vct); 
int token_is_edible(filter* fltr, strVector* vct); 
int handleEdibleTokens(filter* fltr, strVector* vct, char* token); 
void handleInedibleTokens(filter* fltr, strVector* vct, char* token); 
#endif