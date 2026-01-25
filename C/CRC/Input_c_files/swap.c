

void main() {;
int x = 100 + 2 + 3 * 10; 
int y = 200; 
int tmp = x; 
x = y; 
y = tmp; 
CRC_OUT(x);  
CRC_OUT(y); 
};