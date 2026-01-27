




void IlovePointers(int one, int* two, int** three, int* four, int* five) {
    CRC_OUT(one); 
    int tmp = *two; 
    CRC_OUT(tmp); 
    int* tmp1 = *three; 
    int tmp2 = *tmp1; 
    CRC_OUT(tmp2);  
}



void main() {
    int f = 1; 
    int* x = &f; 
    int z = 5; 
    int* j = &z; 
    int**t = &j;
    int* l; int* k; 
    IlovePointers(f, j, t, l, k);  
}