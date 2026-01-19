#include "filter.h"
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

//PRIVATE ACCESS: for convenience, I will transform token's whitespaced information into strVector 
strVector* to_vector(char* token, char* terminator) {
    char* tkn = strdup(token); //tokenizer violates string
    strVector* new_vect = strVectorInit(); 
    char* first_token = strtok(tkn, terminator); 
    strVectorAppend(new_vect, first_token);
    while(1) {
        first_token = strtok(NULL, terminator); 
        if(first_token == NULL)break; 
        strVectorAppend(new_vect, first_token); 
    }
    free(tkn);
    return new_vect;  
}

int main() {
    // Data* data = Data_init(); 
    // Mr_Compilator* mcp = Mr_Compilator_init(); 
    // filter* fltr = filter_init(mcp);
    strVector* vct = to_vector("\nint\ndzudu\nsdsd\n", "\n");
    for(int i = 0; i < strVectorLength(vct); i++) {
        char* curr = strVectorGet(vct, i); 
        printf("%s\n", curr); 
        free(curr); 
    }
    // char* token = malloc(100); 
    // snprintf(token, 100, "int z = 3 == 7");
    // printf("%s", replace_logical_operators(token)); 
    // char instr[1000] = "int x = 3 + 5&&2 / 3 || 5"; 
    // filter_analyze(fltr, instr);
    // strVector* strv = Mr_Compilator_finish(mcp); 
    // filter_destroy(fltr); 
    // // printf("COMPILATION RESULT BELOW\n");
    // for(int i = 0; i < strVectorLength(strv); i++) {
    // char* currInstr = strVectorGet(strv, i); 
    // printf("%s", currInstr); 
    // free(currInstr); 
    // strVectorDestroy(strv); 
    return 0; 
}