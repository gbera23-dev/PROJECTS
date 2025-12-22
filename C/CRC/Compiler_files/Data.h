
#ifndef _Data_
#define _Data_
#include <assert.h>
#include <string.h>
//purpose of this struct is to release a little burden from Mr_Assembler
typedef struct {
  char* type_name; //name of the type: like double, int, char, char* so on 
  int type_size; //amount of memory needed for the type, like 4 bytes for int, 4 bytes for char* and so on
} type_desc; 

typedef struct {
  char* variable_name; //name of our variable
  char* assigned_val; //value assigned to our variable
  type_desc* td; //description of its type and size
  int offset; //offset from initial sp position(sp_pos(sp)) to the variable
} variable; 

typedef struct {
  type_desc* type_descs; 
} Data; 

/*
Initializes new static memory block that stores information about all types and amount of memory needed to store
that type, also generates char array assembly instructions based on requirements. 
*/
Data* Data_init(); 
/*
Looks up particular type_name, and if it finds the name, returns pointer to copy of it, otherwise, returns NULL.
Function passes the ownership of memory to a client.  
*/
type_desc* Data_lookUp(Data* td, char* type_name); 

/*
Function returns overflow value for each type in Data. If the value overflows, we throw compiler error
*/
unsigned long long Data_checkOverflow(Data* td, char* type_name); 

/*
deletes the static array from heap, will be called by main after Mr_assembler finishes his job. 
*/
void Data_destroy(Data* td); 

#endif
