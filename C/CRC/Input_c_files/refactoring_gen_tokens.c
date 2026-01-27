

void main() {
    int x = 5; 
    int f = 10;  
    short *p = &x; 
    int *y = p + 2;
    int z = *(y);  
    CRC_OUT(z); 
}