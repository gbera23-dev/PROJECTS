#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "Mr_Compilator.h"
#include <time.h>
Mr_Compilator* TEST_INIT() { 
   Mr_Compilator* new_asm = Mr_Compilator_init(); 
    assert(new_asm->data && new_asm->generated && new_asm->current_variables && 
    new_asm->sp_pos == 0); 
    printf("new Mr_Compilator has been successfully created and all is good!\n"); 
    printf("size of varVector is %d and size of strVector is %d\n", 
        varVectorLength(new_asm->current_variables),  
    strVectorLength(new_asm->generated));
    return new_asm;
}
//this test creates num int variables(with different names)
void TEST_ONE(Mr_Compilator* new_asm) {
    int num = 20; 
    for(int i = 0; i < num; i++) {
        char token[1000]; 
        char* types[3]; 
        types[0] = "int"; 
        types[1] = "short"; 
        types[2] = "char"; 
        snprintf(token, 1000, "%s %c = %d", types[(rand() % 3)], 48 + i,  i);
        Mr_Compilator_Ask(new_asm, token); 
    }
}
//does reassignment to 125 for all variables currently allocated in stack 
void TEST_TWO(Mr_Compilator* new_asm) {
     for(int i = 0; i < varVectorLength(new_asm->current_variables); i++) {
        variable* new_var = varVectorGet(new_asm->current_variables, i);
        char token[1000]; 
        snprintf(token, 1000, "%s = 125", new_var->variable_name); 
        Mr_Compilator_Ask(new_asm, token); 
        varFree(new_var); 
    }
}
//sums up all the variables onto the new variable 
void TEST_THREE(Mr_Compilator* new_asm) {
    Mr_Compilator_Ask(new_asm, "int accumulator"); 
    for(int i = 0; i < varVectorLength(new_asm->current_variables); i++) {
        variable* new_var = varVectorGet(new_asm->current_variables, i);  
        char token[1000]; 
        snprintf(token, 1000, "accumulator = accumulator + %s", new_var->variable_name); 
        if(strcmp(new_var->variable_name, "accumulator"))
        Mr_Compilator_Ask(new_asm, token); 
        Mr_Compilator_Ask(new_asm, "CRC_OUT accumulator");
        varFree(new_var); 
    }
}
//tests opening a new bracket 
void TEST_FOUR(Mr_Compilator* new_asm) {
    printf("after?\n");
    Mr_Compilator_Ask(new_asm, "{"); 
    printf("before?\n");
    Mr_Compilator_Ask(new_asm, "int mustBeDeleted1 = 3");
    Mr_Compilator_Ask(new_asm, "int mustBeDeleted2 = 3");
    Mr_Compilator_Ask(new_asm, "int mustBeDeleted3 = 3");
    variable dummy_var; dummy_var.variable_name = "mustBeDeleted1"; 
    variable* var = varVectorGet(new_asm->current_variables, varVectorSearch(new_asm->current_variables, &dummy_var)); 
    varPrint(var);  
    Mr_Compilator_Ask(new_asm, "}"); 
    assert(strVectorLength(new_asm->open_scopes) == 0);
    assert(varVectorSearch(new_asm->current_variables, var) == -1); 
    varFree(var); 
    printf("TEST COMPLETE\n"); 
}

int main() {
    srand(time(NULL)); 
    Mr_Compilator* new_asm = TEST_INIT(); 
    Data* data = new_asm->data; 
    TEST_ONE(new_asm);  
    TEST_TWO(new_asm); 
    TEST_THREE(new_asm); 
    TEST_FOUR(new_asm); 
     for(int i = 0; i < varVectorLength(new_asm->current_variables); i++) {
        variable* new_var = varVectorGet(new_asm->current_variables, i);
        varPrint(new_var);
        varFree(new_var);  
    }
    printf("size of accumulator shall be: %d\n", 125*(varVectorLength(new_asm->current_variables) - 1));
    printf("- - - -- - - -- - - - - -- - - \n");
    strVector* stv = Mr_Compilator_finish(new_asm);
    for(int i = 0; i < strVectorLength(stv); i++) {
        char* str = strVectorGet(stv, i);
        printf("%s", str); free(str); 
    }
    strVectorDestroy(stv); 
    return 0; 
}