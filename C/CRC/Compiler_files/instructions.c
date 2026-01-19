#include "instructions.h"
#include <stdio.h> 
#include <stdlib.h>

const int instruction_size = 10000; 

 char* instructions_declareVar(type_desc* td) {
    return instructions_spMove(-td->type_size);
}

 char* instructions_assignVar(variable var, char* val, int already_stored, int sp_pos) {
        char* instruction = malloc(instruction_size); 
        char* loading_type;  
        if(var.td->type_size == 1)loading_type = "sb";
        else if(var.td->type_size == 2)loading_type = "sh"; 
        else loading_type = "sw"; 
        if(!already_stored) {
    snprintf(instruction, instruction_size, "li t0, %s\n%s t0, %d(sp)\n", val, loading_type, 
    sp_pos - var.offset); 
        } else {
    snprintf(instruction, instruction_size, "%s t0, %d(sp)\n", loading_type, 
    sp_pos - var.offset); 
        }
    return instruction;
} 

 char* instructions_readVar(variable var, char* reg, int sp_pos) {
        char* instruction = malloc(instruction_size); 
        char* loading_type;  
        if(var.td->type_size == 1)loading_type = "lb";
        else if(var.td->type_size == 2) loading_type = "lh";
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
    snprintf(instruction, instruction_size, "%sli a0, 1\necall\nli a0, 11\nli a1, 10\necall\n", ch);
    free(ch);  
    return instruction;
 }

//PRIVATE ACCESS: Used for determining a way of operating two registers based on op and put answer in reg
char* opRegisters(char* instruction, char* reg, char* op) {
    char buffer[10000] = ""; 
    if(strcmp(op, "+") == 0) {
        snprintf(buffer, instruction_size, "add %s, t5, t6\n", reg);
        return strcat(instruction, buffer); 
    }
    else if(strcmp(op, "-") == 0) {
        snprintf(buffer, instruction_size, "sub %s, t5, t6\n", reg);
       return strcat(instruction, buffer); 
    }
    else if(strcmp(op, "*") == 0) {
        snprintf(buffer, instruction_size, "mul %s, t5, t6\n", reg);
        return strcat(instruction, buffer); 
    }
    else if(strcmp(op, "/") == 0) {
        snprintf(buffer, instruction_size, "div %s, t5, t6\n", reg);
        return strcat(instruction, buffer);  
    }
    else if(strcmp(op, "<") == 0) {
        snprintf(buffer, instruction_size, "slt %s, t5, t6\n", reg);
        return strcat(instruction, buffer);  
    }
    else if(strcmp(op, ">") == 0) {
        snprintf(buffer, instruction_size, "slt %s, t6, t5\n", reg);
        return strcat(instruction, buffer);   
    }
    return NULL; 
}

//PRIVATE ACCESS: Used for getting appropriate function instructions for valid variables stored in stack
char* opVariables(variable first_var, variable second_var, char* reg, char* op, int sp_pos) {
    char* instruction = malloc(instruction_size);
    instruction[0] = '\0';
    char* first_instr;
    char* second_instr;

    if(strcmp(first_var.variable_name, "const")) {
        first_instr = instructions_readVar(first_var, "t5", sp_pos); 
    } else {
        first_instr = malloc(instruction_size);
        snprintf(first_instr, instruction_size,
    "li t5, %s\n", first_var.assigned_val); 
    }

    if(strcmp(second_var.variable_name, "const")) {
        second_instr = instructions_readVar(second_var, "t6", sp_pos);  
    } else {        
        second_instr = malloc(instruction_size); 
         snprintf(second_instr, instruction_size, 
    "li t6, %s\n", second_var.assigned_val);
    }

    instruction = strcat(instruction, first_instr); 
    instruction = strcat(instruction, second_instr);
    free(first_instr); 
    free(second_instr); 
    return opRegisters(instruction, reg, op); 
}

char* instructions_opVars(variable first_var, variable second_var, char* reg, char* op, int sp_pos) {
    return opVariables(first_var, second_var, reg, op, sp_pos); 
}

char* instructions_createLabel(char* label_name, int tmp_id) {
    char* instruction = malloc(instruction_size); 
    if(label_name) {
    snprintf(instruction, instruction_size, "%s :\n", label_name); 
    } else {
        snprintf(instruction, instruction_size, "tmplb_%d :\n", tmp_id); 
    }
    return instruction; 
} 

char* instructions_createBranch(int tmp_id) {
    char* instruction = malloc(instruction_size);
    snprintf(instruction, instruction_size, "beq t0, zero, G%d\n", tmp_id); 
    return instruction; 
}
