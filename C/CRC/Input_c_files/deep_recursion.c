


void funct(int start_int, int LIM) {;
    int bl = !(start_int > (LIM));
    if(bl) {;
    CRC_OUT start_int;
    int tmp = start_int + 1;
    funct(tmp, LIM); 
    tmp = start_int * 2; 
    funct(tmp, LIM); 
    tmp = start_int * 3; 
    funct(tmp, LIM); 
    tmp = start_int + 2; 
    funct(tmp, LIM);
    };
}; 




void main() {; 
    int LIM = 10; 
    funct(1, LIM); 
}; 