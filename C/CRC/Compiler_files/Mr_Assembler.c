#include <stdio.h> 
#include <stdlib.h> 
#include "Mr_Assembler.h"
#include "Data.h"
#include "vector.h"
/*
This is our machine, our robot, who takes in the token and throws
out RISC - V assembly instructions, which then will be written in out - file in CRC.c, from which whole 
program starts execution. The robot will not need to store any separate data. It will throw out assembly 
instructions at place. It will store vector of declared variables(which will be defined in h file). 
it will have access to available types 
*/