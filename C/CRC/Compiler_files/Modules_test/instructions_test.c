//function's purpose is to test the Data module of the program
#include <stdio.h> 
#include <stdlib.h>
#include "instructions.h"
#include <unistd.h>

int main() {
    variable var; 
    var.assigned_val = "3"; 
    var.offset = 4; 
    var.td = malloc(sizeof(type_desc)); 
    var.td->type_name = "int"; 
    var.td->type_size = 4; 
    var.variable_name = "x"; 
    printf("%s", instructions_assignVar(var, "10", 4)); 
    printf("%s", instructions_readVar(var, "t0", 4)); 
    printf("%s", instructions_declareVar(var.td)); 
    printf("%s", instructions_printVar(var, 4));
    return 0; 
}