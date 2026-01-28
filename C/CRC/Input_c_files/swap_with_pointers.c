


void swap(int* x, int* y) {
    int tmp1 = 0; 
    int * tmp = &tmp1; 
    *tmp = *x;  
    *x = *y; 
    *y = *tmp; 
}


void main() {
    int x = 3; 
    int y = 5; 
    int *xptr = &x;
    int *yptr = &y; 
    swap(xptr, yptr); 
    CRC_OUT(x); 
    CRC_OUT(y); 
}