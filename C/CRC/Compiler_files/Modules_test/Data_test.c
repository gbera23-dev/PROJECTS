//function's purpose is to test the Data module of the program
#include <stdio.h> 
#include <stdlib.h>
#include "Data.h"
#include <unistd.h>

void test(Data* td, char* x, int size) {
    printf("Starting the test for type_name %s and type_size %d\n", x, size);
    sleep(1);
    type_desc* elem = Data_lookUp(td, x); 
    printf("we have successfully retrieved the type_desc of %s\n", x);
    if(elem == NULL) {
        printf("we have successfully determined that %s is not a real type\n", x);
    } else {
    assert(strcmp(elem->type_name, x) == 0); 
    printf("Assertion was complete, we have successfully determined that type_name is really %s\n", x);
    assert(elem->type_size == size); 
    printf("Assertion was complete, we have successfully determined that type_size is really %d\n", size);
    }
    printf("- - - - - - - - - - - - - - - - - - - -\n");
    printf("test for type_name %s and type_size %d has been successfull!\n", x, size);
}


int main() {
    Data* td = Data_init();
    assert(td); 
    printf("assertion was complete, new static array has been successfully created\n");
    test(td, "hello", 0); 
    test(td, "double", 8); 
    test(td, "int", 4); 
    test(td, "char", 1);
    test(td, "float", 4);  
    Data_destroy(td); 
    printf("Assertion was complete, we have successfully destroyed the static array\n");
    return 0; 
}