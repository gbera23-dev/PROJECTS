
int p = 10;
int t = 5;  

void funct(int arg1,short arg2,int arg3,int arg4,char arg5) {;
    int x = arg1; short y = arg2; 
    int tmp = arg1 + arg2; 
    if(tmp) {;
        y = x; 
    }; 
    CRC_OUT(arg3); CRC_OUT(arg4); CRC_OUT(arg5); 
}; 


void hello_world(int arg1) {;
    CRC_OUT(arg1); 
}; 


void main() {;
    int v = p + t;   
    CRC_OUT(p); 
    CRC_OUT(v);
}; 