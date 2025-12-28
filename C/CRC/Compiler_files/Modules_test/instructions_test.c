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
    var.variable_name = "char"; 
    variable second_var; 
    second_var.assigned_val = "13"; 
    second_var.offset = 8;
    second_var.td = malloc(sizeof(type_desc)); 
       second_var.td->type_name = "short"; 
    second_var.td->type_size = 2; 
    second_var.variable_name = "zz"; 
    printf("%s", instructions_assignVar(var, "10",0, 4)); 
    printf("%s", instructions_readVar(var, "t0", 4)); 
    printf("%s", instructions_declareVar(var.td)); 
    printf("%s", instructions_printVar(var, 4));
    printf("%s", instructions_opVars(var, second_var, "t0", "/", 8)); 
    printf("%s", instructions_opVars(var, second_var, "t1", "+", 8)); 
    printf("%s", instructions_opVars(var, second_var, "t2", "-", 8)); 
    printf("%s", instructions_opVars(var, second_var, "t5", "*", 8)); 
    return 0; 
}