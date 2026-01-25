

void main() {;

int tmp1 = 10; int tmp2 = 10; int tmp3 = 10; int tmp4 = 10; int tmp5 = 10; 

while(tmp1) {;

    while(tmp2) {;
    
        while(tmp3) {;
        
            while(tmp4) {;
            
                while(tmp5) {;
                    int m; int n; int p; 
                    int sum_total = tmp1 + tmp2 + tmp3 + tmp4 + tmp5; 
                    CRC_OUT(sum_total); 
                    tmp5 = tmp5 - 1; 
                }; 
                tmp4 = tmp4 - 1; 
            }; 
            tmp3 = tmp3 - 1; 
        }; 
        tmp2 = tmp2 - 1; 
    }; 
    tmp2 = 10; 
    tmp3 = 10; 
    tmp4 = 10; 
    tmp5 = 10; 
    tmp1 = tmp1 - 1;
}; 
};