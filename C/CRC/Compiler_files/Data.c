#include <stdio.h> 
#include <stdlib.h> 
#include "Data.h"
#include <string.h>
/*
The file is used to maintain all the necessary tokens that shall be scanned, recognized and, for which, 
eventually, appropriate assembly code will be written. This is the crux of compiler, if this miniature database
is not properly written, it will create many complications later. 

This file essentially initializes new static array in heap that(for now) stores names of primitive types and
amount of memory needed for each. Currently our compilator will only support variable declarations, operations
between variables and variable reassignment. This is just a little pebble inside the ocean, but it is the 
starting point. 

I will also add functions(module is too small) that generate and return char arrays based on
requirements
*/
const int num_tokens = 3; 


Data* Data_init() {
    Data* my_data = malloc(sizeof(Data)); 
    type_desc a[num_tokens]; 
    type_desc* arr = my_data->type_descs = malloc(num_tokens*sizeof(type_desc));
    arr[0].type_name = "char"; arr[0].type_size = 1; 
    arr[1].type_name = "float"; arr[1].type_size = 4; 
    arr[2].type_name = "int"; arr[2].type_size = 4; 
    return my_data; 
}

type_desc* Data_lookUp(Data* td, char* type_name) {
    //implementation is not efficient, but since size is small, it is sufficient
    type_desc* cpy = NULL; 
    for(int i = 0; i < num_tokens; i++) {
        if(strcmp(td->type_descs[i].type_name, type_name) == 0) {
           cpy = malloc(sizeof(type_desc)); 
            cpy->type_name = type_name; 
            cpy->type_size = td->type_descs[i].type_size; 
            return cpy; 
        }
    }
    return cpy; 
}

void Data_destroy(Data* td) {
    if(td->type_descs)free(td->type_descs); 
    if(td)free(td); 
}
