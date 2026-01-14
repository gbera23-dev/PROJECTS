
{;
short x = 3; 
int y = 5; 
int tmp = x; 
x = y; 
y = tmp; 
CRC_OUT x; 
CRC_OUT y; 
};

{;
int x = 5; 
int y = 7; 
int tmp = x + y; 
tmp = tmp * 2; 
CRC_OUT tmp; 
{;
int z = ( ( ( ( tmp + ( x * y ) ) ) ) ) ; 
CRC_OUT z; 
};
int z = 0; 
CRC_OUT z;

};
