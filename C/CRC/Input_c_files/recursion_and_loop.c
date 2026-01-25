
/*deep recursion with 10 calls per call*/


void recurse(int x, int num_calls){;
    int lb = x > -1; 
    if(lb) {;
        CRC_OUT(x); 
        while(num_calls) {;
            int arg1 = x - 1; 
            recurse(arg1, num_calls); 
            num_calls = num_calls - 1; 
        }; 
    }; 
};


void main(){;
    recurse(5, 3); 
};