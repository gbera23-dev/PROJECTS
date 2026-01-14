#include "filter.h"
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
int get_priority(char* ch) {
    if(*ch == '+') {
        return 0; 
    }
    if(*ch == '-') {
        return 0; 
    }
    if(*ch == '*') {
        return 1; 
    }
    if(*ch == '/') {
        return 1; 
    }
    if(*ch == '(' || *ch == ')' || *ch == '=') {
        return -100; 
    }
    return 67; 
}
char* separate_operators(char* token) {
    char* new_tok = malloc(2*strlen(token) + 1); //size is just a safety precaution 
    int priority;
    int curr_pos = 0; 
    for(int i = 0; i < strlen(token); i++) {
        priority = get_priority(token + i);
        printf("%d\n", priority);
        if(priority == 67) {
            new_tok[curr_pos++] = token[i]; 
        } else {
            new_tok[curr_pos++] = ' '; 
            new_tok[curr_pos++] = token[i]; 
            new_tok[curr_pos++] = ' '; 
        }
    }
    free(token); 
    new_tok[curr_pos] = '\0'; 
    return new_tok;  
}

void TEST_SEPARATE_OPERATORS(char* c) {
    char* res = separate_operators(c);
    printf("%s\n", res);  
    printf("%ld\n", strlen(res)); 
}

int main() {
  TEST_SEPARATE_OPERATORS(strdup("((15/(7-(1+1)))*3)-(2+(1+1))"));
  //   Mr_Compilator* mcp = Mr_Compilator_init(); 
  //   filter* fltr = filter_init(mcp);
  //   char instr[1000] = "int x = 3 + 5 - 2 / 3 * 5"; 
  //   filter_analyze(fltr, instr);
  //   strVector* strv = Mr_Compilator_finish(mcp); 
  //   filter_destroy(fltr); 
  //   printf("COMPILATION RESULT BELOW\n");
  //   for(int i = 0; i < strVectorLength(strv); i++) {
  //   char* currInstr = strVectorGet(strv, i); 
  //   printf("%s", currInstr); 
  //   free(currInstr); 
  // }
  //   strVectorDestroy(strv); 
    return 0; 
}