



void main() {
    int x = 3; 
    int * y = &x; 
    int ** z = &y; 
    int *** m = &z; 
    ***m = 10; 
    CRC_OUT(x); 
}