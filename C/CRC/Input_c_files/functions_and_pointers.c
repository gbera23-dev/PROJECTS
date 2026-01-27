

/*let us pass reference(global variable) to see how many calls happen in a recursive function
but I can only read data, not write in data, 
*/


void see_data(int* one, int* two) {
    int f1 = *one; 
    int v = *two;
    CRC_OUT(f1);
    CRC_OUT(v);  
}

void main() {
    int z = 5; 
    int p = 2; 
    int* zptr = &z;  
    int* rptr = &p; 
    see_data(zptr, rptr); 
}