


void print_even_numbers(int x, int LIM) {; 
    int bl = x < LIM; 
    if(bl) {;
        CRC_OUT(x); 
        x = x + 2;
        print_even_numbers(x, LIM); 
    }; 
}; 


void fib(int n, int prev, int curr) {;
    int bl = (n - 1) < 1;
    if(bl) {;
        CRC_OUT(curr); 
    };  
    bl = !bl; 
    if(bl) {;
    int tmp = curr; 
    curr = prev + curr;
    prev = tmp; 
    n = n - 1; 
    fib(n, prev, curr);
    };  
}; 


void write_first_LIM_fib_nums(int LIM) {;
    int n = 1;
    int lb = n < (LIM + 1); 
    while(lb) {;
        fib(n, 0, 1); 
        n = n + 1; 
        lb = n < (LIM + 1); 
    }; 
}; 



void main() {;
    print_even_numbers(0, 101);
    write_first_LIM_fib_nums(20);
}; 