

void hello() {
    int z = 6; 
    CRC_OUT(z); 
}


void main() {
    int x = 3; 
    int y = 5; 
    int tmp = x + y; 
    CRC_OUT(tmp); 
    int LIM = 100; 
    while(LIM) {
        CRC_OUT(LIM); 
        LIM = LIM - 1; 
    }
    hello(); 
}