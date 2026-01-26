


void modify(int t) {
    int* p = t; 
    int val = *p; 
    CRC_OUT(val); 
}


void main() {
    int x = 10; 
    int* t = &x; 
    modify(t); 
}