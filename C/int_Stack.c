#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
//MISSION, Make this generic 
typedef struct {
  int* elems; 
  int log_len; 
  int alloc_len; 
} Stack;

void StackInit(Stack* s) {
	s->log_len = 0; 
	s->alloc_len = 4; 
	s->elems = malloc(s->alloc_len*sizeof(int));
	assert(s->elems != NULL); 
}
void StackDestroy(Stack* s) {
	free(s->elems); 
}

void StackPush(Stack* s, int value) {
		if(s->log_len == s->alloc_len) {
		s->alloc_len *= 2; 
		s->elems = realloc(s->elems, s->alloc_len*sizeof(int)); 
		assert(s->elems != NULL); 
	}
	*(s->elems + s->log_len) = value; 
	s->log_len++; 
}

int StackPop(Stack* s) {
	assert(s->log_len > 0); 
	s->log_len--; 
	int val = *(s->elems + s->log_len); 
	return val; 
}

int main(int argc, char** argv) {
	Stack s; 
	StackInit(&s); 
	for(int i = 0; i < 2; i++) {
		StackPush(&s, i); 
	}
	int top1 = StackPop(&s);
	int top2 = StackPop(&s);  
	printf("%d and %d", top1, top2);
	StackDestroy(&s); 
}
