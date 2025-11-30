#include <stdio.h> 
#include <stdlib.h> 

const int INITIAL_CAPACITY = 1024; 

/*Takes out RAW tokens from the input C file*/
char* tokenize(FILE* fptr, int* token_count) {
  int current_capacity = INITIAL_CAPACITY;
  char* mem_head = malloc(current_capacity);
  int i = 0; 
  int current_char; 
  while((current_char = fgetc(fptr)) != EOF) {
    if(current_char == '\n')continue;
     if(current_char != ';') {
      mem_head[i] = current_char; 
    } else {
        (*token_count)++;
        mem_head[i] = '\n';
    }
    i++; 
    if(i == current_capacity) {
      current_capacity *= 2; 
      mem_head = realloc(mem_head, current_capacity); 
    }
}
  mem_head[i] = 0; 
  return mem_head; 
}


int main() {
  FILE* cptr; //pointer to c file we shall compile 
  FILE* sptr; //pointer to s file we write compiled assembly in
  cptr = fopen("input.c", "r"); 
  int token_count = 0; 
  char* tokens = tokenize(cptr, &token_count); 
  fclose(cptr); 
  printf("%s", tokens); 
  printf("in total %d tokens detected\n", token_count);
  return 0; 
}
