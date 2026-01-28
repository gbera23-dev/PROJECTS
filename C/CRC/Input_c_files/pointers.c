
void pointerChain() {
    int x = 42;  int y = 17; int z = -8;
    int *p = &x; int *q = &y; int *r = &z;
    int **pp = &p; int **qq = &q;
    *p = (*q * -3) + (*r / 2) - (((*p > *q) && (*r < 0)) || !(*p == *q)) * 5;
    int jojojo = *p; 
    CRC_OUT(jojojo); 
    **pp = (*(*qq) + *r) * 2 - (!(*(*pp) > 0) || (*p == *q)) * 10;
    jojojo = *(*pp);
    CRC_OUT(jojojo); 
}

void main() {
    pointerChain(); 
}
