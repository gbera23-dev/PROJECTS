



int tmp1 = 20; 
int tmp2 = 0; 
int LIM = 100; 

int cond = (tmp1 + tmp2) < LIM; 

while(cond) {;
    tmp2 =  tmp2 + 1; 
    int x = tmp1 / tmp2; 
    tmp1 = tmp1 + 1; 
    int y = x;
    CRC_OUT y; 
    cond = (tmp1 + tmp2) < LIM; 
}; 