

void main() {;

int y = 3;
short x = 10; 
int z = x * ( x + x ) - y + x;
z = z + 5; 
{;
int accumulator = z + x + y;
CRC_OUT(accumulator);

};  
CRC_OUT(z);
};