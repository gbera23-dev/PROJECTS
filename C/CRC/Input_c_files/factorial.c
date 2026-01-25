




void factorial(int n, int sol) {;
    int lb = n == 0;
    if(lb) {;
        CRC_OUT(sol); 
    }; 
    lb = !lb; 
    if(lb) {; 
    int x = n - 1; 
    int y = n * sol; 
    factorial(x, y);
    }; 
}; 




void main() {; 
    factorial(12, 1); 
}; 