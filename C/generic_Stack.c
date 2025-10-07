#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
//MISSION, Make this generic 
//first of all, we need to know how much memory does this object 
//maintains, and that needs to be passed by the client. let it be 
//mem_size. also we have to change the pointer type of elems into 
//a void*.
typedef struct {
  void* elems; 
  int log_len; 
  int alloc_len; 
  size_t mem_size; //amount of memory  
} Stack;
//only thing changed here is sizeof(int) into mem_size that is passed
//to the function 
void StackInit(Stack* s, size_t mem_size) { 
	s->mem_size = mem_size; 
	s->log_len = 0; 
	s->alloc_len = 4; 
	s->elems = malloc(s->alloc_len*mem_size);
	assert(s->elems != NULL); 
}
//needs nothing else, s itself may or may not be allocated in heap
//it depends on client, he could have done the following: Stack s; 
//StackInit(&s, sizeof(type)); StackDestroy(&s); or this: 
//Stack* s = malloc(sizeof(s)); second case is dynamic allocation. 
//and it is the responsibility of the client to free it(and is different
//from our allocated memory for elems, so we free s->elems only.  
void StackDestroy(Stack* s) {
	free(s->elems); 
}
//instead of int, we get the address of the type and its size
//if logic needs a little change in realloc.  
//code at line 42 needs fundamental change. traversing void* array is 
//impossible without casting, as pointer arithmetic needs to know which
//kind of pointer we are working on, and void* has no size, therefore,
//it is convenient to cast it into some type of pointer, maybe for the
//best the type that maintains address of one byte memory, that is char.
//so we cast s->elems into char* and then move it by mem_size*log_len
//and not just log_len, because our type needs memory mem_size
void StackPush(Stack* s, void* elem) {
		if(s->log_len == s->alloc_len) {
		s->alloc_len *= 2; 
		s->elems = realloc(s->elems, s->alloc_len*s->mem_size); 
		assert(s->elems != NULL); 
	}
	memcpy((char*)s->elems + s->mem_size*s->log_len, elem, s->mem_size); 
	s->log_len++; 
}
//must return the top element(so we need to return the pointer to this
//element, but this is unsafe, it is better to copy the memory 
//somewhere and return the address of that, because returning this 
//pointer gives client access to our working space
void* StackPop(Stack* s) {
	assert(s->log_len > 0); 
	s->log_len--; 
	void* val = (char*)s->elems + s->log_len*s->mem_size; 
	void* copy = malloc(s->mem_size); 
	copy = memcpy(copy, val, s->mem_size); 
	return copy; 
}

int main(int argc, char** argv) { 
	Stack s; 
	StackInit(&s, sizeof(int)); 
	for(int i = 0; i < 10; i++) 
	StackPush(&s, &i);
	int elem = *(int*)StackPop(&s);
	printf("%d", elem); 
	StackDestroy(&s);
}
