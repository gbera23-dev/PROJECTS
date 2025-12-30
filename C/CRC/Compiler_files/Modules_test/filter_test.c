#include "filter.h"
#include <stdio.h> 
#include <stdlib.h>

int main() {
    Mr_Compilator* mcp = Mr_Compilator_init(); 
    filter* fltr = filter_init(mcp);
    char instr[1000] = "int x = 3 + 5 - 2 / 3 * 5"; 
    filter_analyze(fltr, instr);
    strVector* strv = Mr_Compilator_finish(mcp); 
    filter_destroy(fltr); 
    printf("COMPILATION RESULT BELOW\n");
    for(int i = 0; i < strVectorLength(strv); i++) {
    char* currInstr = strVectorGet(strv, i); 
    printf("%s", currInstr); 
    free(currInstr); 
  }
    strVectorDestroy(strv); 
    return 0; 
}