
#ifndef _Data_
#define _Data_
#include <assert.h>
#include <string.h>
//purpose of this struct is to release a little burden from Mr_Assembler
typedef struct {
  char* type_name; //name of the type: like double, int, char, char* so on 
  int type_size; //amount of memory needed for the type, like 4 bytes for int, 4 bytes for char* and so on
} type_desc; 
/*
Initializes new static memory block that stores information about all types and amount of memory needed to store
that type
*/
type_desc* Data_init(); 
/*
Looks up particular type_name, and if it finds the name, returns pointer to copy of it, otherwise, returns NULL.
Function passes the ownership of memory to a client.  
*/
type_desc* Data_lookUp(type_desc* td, char* type_name); 
/*
deletes the static array from heap, will be called by main after Mr_assembler finishes his job. 
*/
void Data_destroy(type_desc* td); 

#endif
