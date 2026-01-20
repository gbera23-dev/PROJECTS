#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "strVector.h"
#include "Mr_Compilator.h"
#include "filter.h"
#include <assert.h>
const int INITIAL_CAPACITY = 1024; 

char* remove_comments(char* mem_head) {
  int mem_size = strlen(mem_head); 
  char* ans = malloc(mem_size + 1); 
  int in_comment = 0; 
  int curr_idx = 0; 
  for(int i = 0; i < mem_size; i++) {
    if(i + 1 < mem_size && mem_head[i] == '/' && mem_head[i + 1] == '*') {
      in_comment = 1; 
    } 
     if(i + 1 < mem_size && mem_head[i] == '*' && mem_head[i + 1] == '/') {
      in_comment = 0; 
      i++; continue; 
    } 
    if(in_comment)continue; 
    ans[curr_idx++] = mem_head[i]; 
  }
  ans[curr_idx] = '\0'; 
  return ans; 
}

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
  char* comments_removed = remove_comments(mem_head); 
  free(mem_head); 
  return comments_removed;  
}


/*Does a dirty work of removing extra whitespaces from tokens*/
char* clean(char* tokens) {
  char* cleaned_tokens = malloc(strlen(tokens));
  int i = 0, j = 0;  
  while(tokens[i] == 32) {
    i++; 
  }
  for(; i <= strlen(tokens); i++) {
    if(tokens[i] != 32) {
        cleaned_tokens[j] = tokens[i]; 
        j++; 
    } else {
      if((tokens[i - 1] != '\n' && tokens[i - 1] != 32 && (i + 1 <= strlen(tokens) && tokens[i + 1] != 32))) {
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
  if(argc > 3) {
    printf("Please, provide less than three files: one as input C file, one for output s file\n"); 
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
/*Function initializes new strVector for storing tokens of the given file*/
strVector* initVector(strVector* strv, char* tokens) {
  strVector* tokVector = strVectorInit();
  char* tok = strtok(tokens, "\n"); 
  while(tok) {
    strVectorAppend(tokVector, tok); 
    tok = strtok(NULL, "\n"); 
  }
  free(tokens); 
  return tokVector; 
}
/*Analyses output file and checks whether given file exists or not and if it does, whether it has valid format*/
FILE* outputErrorHandler(int argc, char* argv[]) {
  char* file_name; 
  if(argc == 3) {
    file_name = argv[2]; 
  }  else {
    file_name = "out.s";
  }
   if(strcmp(file_name + strlen(file_name) - 2, ".s") != 0) {
    printf("Please, provide a proper risc-v file(must end with .s)\n"); 
    abort(); 
  } 
  FILE* sptr = fopen(file_name, "w"); 
  if(!sptr) {
      printf("File is not found on the system(Please, provide a complete path)\n");
    abort(); 
  }
  return sptr; 
} 

int main(int argc, char* argv[]) {
  FILE* cptr = NULL;
  FILE* sptr = NULL;
  cptr = inputErrorHandler(argc, argv); 
  int token_count = 0; 
  char* tokens = clean(tokenize(cptr, &token_count)); 
  fclose(cptr); 
  // printf("%s", tokens); 
  // printf("in total %d tokens detected\n", token_count);
  strVector* tokVector = initVector(tokVector, tokens); 
  Mr_Compilator* compilator = Mr_Compilator_init(); 
  filter* fltr = filter_init(compilator); 
  //now, we start quering for Mr_Compilator 
  for(int i = 0; i < strVectorLength(tokVector); i++) {
    char* currToken = strVectorGet(tokVector, i); 
    filter_analyze(fltr, currToken); 
    free(currToken); 
  }
  strVector* ans = Mr_Compilator_finish(compilator); 
  filter_destroy(fltr); 
  sptr = outputErrorHandler(argc, argv); 
  for(int i = 0; i < strVectorLength(ans); i++) {
    char* curr = strVectorGet(ans, i); 
    fwrite(curr, strlen(curr), 1, sptr); 
    free(curr); 
  }
  fclose(sptr); 
  strVectorDestroy(ans); 
  strVectorDestroy(tokVector); 
  return 0; 
}
