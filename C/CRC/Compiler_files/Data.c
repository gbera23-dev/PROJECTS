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
*/
const int num_tokens = 3; 


type_desc* Data_init() {
    type_desc a[num_tokens]; 
    type_desc* arr = malloc(num_tokens*sizeof(type_desc));
    arr[0].type_name = "char"; arr[0].type_size = 1; 
    arr[1].type_name = "double"; arr[1].type_size = 8; 
    arr[2].type_name = "int"; arr[2].type_size = 4; 
    return arr; 
}

type_desc* Data_lookUp(type_desc* td, char* type_name) {
    //implementation is not efficient, but since size is small, it is sufficient
    type_desc* cpy = NULL; 
    for(int i = 0; i < num_tokens; i++) {
        if(strcmp(td[i].type_name, type_name) == 0) {
           cpy = malloc(sizeof(type_desc)); 
            cpy->type_name = type_name; 
            cpy->type_size = td[i].type_size; 
            return cpy; 
        }
    }
    return cpy; 
}

void Data_destroy(type_desc* td) {
    if(td)free(td); 
}
