

/*
problem here is that when function is compiled, x does not exist, so injecting x instead of *ptr creates complications. 
this was the same problem for global variables, as sp offsets were wrong. I need to think about this. this is important...
if I let main to compile first, then it does not know about fact. as it seems, injection of variable name will not always
work, so I need to come up with a different approach, thing is I do not even really need to know whether variable on that
address exists or not. I will think about this tomorrow, and COMMIT all this tomorrow. 

**ptr = 3; 

lw t0, some(sp) //int ** ptr 
lw t0, 0(t0) //int * ptr 


*/


void funct(int* ptr) {
    /*define a variable on the exact address*/
    int y = 5; 
    *ptr = 5 + 3 - 4 + 2 * y;
    int x = *ptr; 
    CRC_OUT(x); 
}


void main() {
    int x = 3; 
    int* ptr = &x; 
    funct(ptr); 
}
