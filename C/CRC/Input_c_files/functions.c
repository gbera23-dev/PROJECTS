



void print_even_numbers(int z) {;
    int tmp = 0; 
    int bl = (tmp < z); 
    CRC_OUT z; 
    while(bl) {;
        int is_even = !((tmp / 2) == ((tmp - 1) / 2)); 
        if(is_even) {;
            CRC_OUT tmp; 
        }; 
        tmp = tmp + 1; 
        bl = tmp < z; 
    }; 
};



void main() {;
    int z = 100; 
    while(z) {;
    print_even_numbers(z);
    z = z - 1; 
    }; 
};