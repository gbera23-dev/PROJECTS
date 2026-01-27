








void main() {
    int x = 5;
    int *  z= &x; 
    int**g = &z;
    int*** m = &g; 
    int p = *(*(*m)); 
    CRC_OUT(p);  
}