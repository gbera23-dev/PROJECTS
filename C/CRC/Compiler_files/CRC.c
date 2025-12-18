#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "strVector.h"
#include <assert.h>
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
/*Does a dirty work of removing extra whitespaces from tokens*/
char* clean(char* tokens) {
  char* cleaned_tokens = malloc(strlen(tokens));
  int i = 0, j = 0;  
  for(int i = 0; i <= strlen(tokens); i++) {
    if(tokens[i] != 32) {
        cleaned_tokens[j] = tokens[i]; 
        j++; 
    } else {
      if(tokens[i - 1] != '\n') {
        cleaned_tokens[j] = tokens[i]; 
        j++; 
      }
    }
  }
  free(tokens); //no longer needed
  return cleaned_tokens; 
}

/*Analyses user input and checks whether given file is the valid C file*/
FILE* inputErrorHandler(int argc, char** argv) {
  if(argc == 1) {
    printf("No input file provided for compilation\n");
    abort(); 
  }
  if(argc > 2) {
    printf("Please, provide a single file for compilation(this is not GCC)\n");
    abort(); 
  }
  char* file_name = argv[1]; 
  if(strcmp(file_name + strlen(file_name) - 2, ".c") != 0) {
    printf("Please, provide a proper c file(must end with .c)\n"); 
    abort(); 
  } 
  FILE* cptr = fopen(file_name, "r");
  if(!cptr) {
    printf("File is not found on the system(Please, provide a complete path)\n");
    abort(); 
  } 
  return cptr; 
}

int main(int argc, char* argv[]) {
  FILE* cptr = NULL;
  FILE* sptr = NULL;
  cptr = inputErrorHandler(argc, argv); 
  int token_count = 0; 
  char* tokens = clean(tokenize(cptr, &token_count)); 
  fclose(cptr); 
  printf("%s", tokens); 
  printf("in total %d tokens detected\n", token_count);
  return 0; 
}
