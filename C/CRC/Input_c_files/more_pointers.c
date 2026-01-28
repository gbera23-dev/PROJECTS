




void extremeNesting(int *res) {
    int a = 15; int b = -8; int c = 22;int d = -13;
    int *pa = &a; int *pb = &b; int *pc = &c; int *pd = &d;
    *res = (((((*pa * -3) / (+5 - -2) + ((*pb > *pc) && (*pd < 0))) * 
                ((*pa + *pb) > (*pc * -1))) || 
               (((!(*pa < *pb) && (*pc == -(*pd))) || ((*pa / -2) > *pd)) && 
                ((*pb - *pc) < ((*pd + *pa) * -1)))) &&
              ((((*pc * *pd) / (+*pa - -*pb) > -50) || 
                (!((*pa > *pb) && (*pc < *pd)) && (*pa + *pc) > 0)) || 
               (!(*pb == *pd) && ((*pa - *pb) * (*pc + *pd)) > 100)));
}


void main() {
    int x; 
    int* xptr = &x; 
    extremeNesting(xptr); 
    CRC_OUT(x); 
}