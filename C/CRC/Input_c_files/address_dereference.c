

void main() {
    int x = 20; 
    int *p = (&x); 
    int **q = (&p); 
    int ***z = (&q); 
    int **e = (*z); 
    int *f = (*e);
    int u = (*f);
    CRC_OUT(u); 
}