#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "Mr_Assembler.h"
#include <time.h>
Mr_Assembler* TEST_INIT() { 
   Mr_Assembler* new_asm = Mr_Assembler_init(); 
    assert(new_asm->data && new_asm->generated && new_asm->current_variables && 
    new_asm->sp_pos == 0); 
    printf("new Mr_Assembler has been successfully created and all is good!\n"); 
    printf("size of varVector is %d and size of strVector is %d\n", 
        varVectorLength(new_asm->current_variables),  
    strVectorLength(new_asm->generated));
    return new_asm;
}
//this test creates 100 int variables(with different names)
void TEST_ONE(Mr_Assembler* new_asm) {
    for(int i = 0; i < 100; i++) {
        char token[1000]; 
        char* types[3]; 
        types[0] = "int"; 
        types[1] = "long"; 
        types[2] = "char"; 
        snprintf(token, 1000, "%s %c = %d", types[(rand() % 3)], 48 + i,  i);
        Mr_Assembler_Ask(new_asm, token); 
    }
}
//does reassignment to 125 for all variables currently allocated in stack 
void TEST_TWO(Mr_Assembler* new_asm) {
     for(int i = 0; i < varVectorLength(new_asm->current_variables); i++) {
        variable* new_var = varVectorGet(new_asm->current_variables, i);
        char token[1000]; 
        snprintf(token, 1000, "%s = 125", new_var->variable_name); 
        Mr_Assembler_Ask(new_asm, token); 
        varFree(new_var); 
    }
}

int main() {
    srand(time(NULL)); 
    Mr_Assembler* new_asm = TEST_INIT(); 
    Data* data = new_asm->data; 
    TEST_ONE(new_asm);  
    TEST_TWO(new_asm); 
     for(int i = 0; i < varVectorLength(new_asm->current_variables); i++) {
        variable* new_var = varVectorGet(new_asm->current_variables, i);
        varPrint(new_var);
        varFree(new_var);  
    }
    printf("- - - -- - - -- - - - - -- - - \n");
    strVector* stv = Mr_Assembler_finish(new_asm);
    for(int i = 0; i < strVectorLength(stv); i++) {
        char* str = strVectorGet(stv, i);
        printf("%s", str); free(str); 
    }
    strVectorDestroy(stv); 
    return 0; 
}