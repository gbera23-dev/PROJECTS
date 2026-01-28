



void multiplyoradd(int n, int LIM, int* countptr) {
    int lb = n < LIM; 
    if(lb) {
        int sumarg = n + 1; 
        int mularg = n * 2; 
        multiplyoradd(sumarg, LIM, countptr); 
        multiplyoradd(mularg, LIM, countptr); 
    }
    int ptrval = *countptr; 
    ptrval = ptrval + 1; 
    *countptr = ptrval; 
}



void main() {
    int count = 0; 
    int* countptr = &count; 
    int n = 1; 
    int LIM = 10;
    multiplyoradd(n, LIM, countptr); 
    CRC_OUT(count); 
}