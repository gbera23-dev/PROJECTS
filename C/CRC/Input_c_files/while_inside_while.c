




void nested_loop(int x, int y) {
    while(x) {
        int tmp = y; 
        while(y) {
            CRC_OUT(y); 
            y = y - 1; 
        }
        y = tmp;
        x = x - 1; 
    }
}


void main() {
    int x = 6; 
    int y = 5; 
    nested_loop(x, y); 
}