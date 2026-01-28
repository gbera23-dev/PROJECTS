


void fib(int n, int* result, int* count_ptr) {
    int lb = n > 0;
    if(lb) {
        int tmp1 = *result;
        *result = tmp1*n;  
        n = n - 1; 
        int tmp = *count_ptr; 
        *count_ptr = tmp + 1; 
        fib(n, result, count_ptr); 
    } 
}



void main() {
    int count = 0; 
    int res = 1; 
    int* res_ptr = &res; 
    int* count_ptr = &count; 
    int n = 10; 
    fib(n, res_ptr, count_ptr); 
    int u = *count_ptr; 
    CRC_OUT(u);
    int v = *res_ptr; 
    CRC_OUT(v); 
}