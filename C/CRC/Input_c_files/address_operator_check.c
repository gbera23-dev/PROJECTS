




void main() {
    int initial = 30; 
    int tmp1 = 1;
    int tmp2 = 2; 
    int tmp3 = 3; 
    int tmp4 = 4; 
    int tmp5 = 5; 
    int tmp6 = 6; 
    int tmp7 = 7; 
    int tmp8 = 8; 
    int* initial_ptr = &initial; 
    int idx = 1; 
    int LIM = 9; 
    int lb = idx < LIM; 
    while(lb) {
        int* ptr_to_elem_at_idx = initial_ptr + idx; 
        int val = *ptr_to_elem_at_idx; 
        CRC_OUT(val); 
        idx = idx + 1; 
        lb = idx < LIM; 
    }
}