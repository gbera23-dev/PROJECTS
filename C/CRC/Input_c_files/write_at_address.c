








/*
how to do this? 
I believe that the part of the expression before = operator needs special treatment too, in the
case, when we are handling undefined variable. 
I will branch out undefined variable 
*/
void main() {
    int x = 3; 
    int*ptr=&x; 
    int**j = &ptr; 
    *ptr = 5 + 100 - 2;
    CRC_OUT(x);  
}