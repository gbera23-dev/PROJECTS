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
#endif