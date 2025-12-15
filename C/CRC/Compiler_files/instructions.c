#include "instructions.h"
#include <stdio.h> 
#include <stdlib.h>

const int instruction_size = 1000; 

 char* instructions_declareVar(type_desc* td) {
    return instructions_spMove(-td->type_size);
}

 char* instructions_assignVar(variable var, char* val, int sp_pos) {
        char* instruction = malloc(instruction_size); 
        char* loading_type;  
        if(var.td->type_size == 1)loading_type = "sb";
        else loading_type = "sw"; 

    snprintf(instruction, instruction_size, "li t0, %s\n%s t0, %d(sp)\n", val, loading_type, 
    sp_pos - var.offset); 
    return instruction;
} 

 char* instructions_readVar(variable var, char* reg, int sp_pos) {
        char* instruction = malloc(instruction_size); 
        char* loading_type;  
        if(var.td->type_size == 1)loading_type = "lb";
        else loading_type = "lw"; 

    snprintf(instruction, instruction_size, 
        "%s %s, %d(sp)\n", loading_type, reg, sp_pos - var.offset); 
    return instruction;
}

 char* instructions_spMove(int offset) {
        char* instruction = malloc(instruction_size); 
    snprintf(instruction, instruction_size, "addi sp, sp %d\n", offset); 
    return instruction;
}
 char* instructions_printVar(variable var, int sp_pos) {
        char* instruction = malloc(instruction_size); 
        char* ch = instructions_readVar(var, "a1", sp_pos);
    snprintf(instruction, instruction_size, "%sli a0, 10\necall\n", ch);
    free(ch);  
    return instruction;
 }
