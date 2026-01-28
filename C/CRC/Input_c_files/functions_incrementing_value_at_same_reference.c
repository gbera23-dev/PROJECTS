



void incr1(int* common) {
    int x = *common; 
    x = x + 1; 
    *common = x; 
}


void incr2(int* common) {
    int x = *common; 
    x = x + 1; 
    *common = x; 
}

void incr3(int* common) {
    int x = *common; 
    x = x + 1; 
    *common = x; 
}


void main() {
    int x = 0; 
    int* xptr = &x; 
    incr1(xptr); incr2(xptr); incr3(xptr); 
    int val = *xptr; 
    CRC_OUT(val); 
}