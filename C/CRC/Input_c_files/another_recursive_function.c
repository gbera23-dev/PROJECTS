

/*we need to write a recursive function that will output all possible combinations of summing up two numbers that
result into a global variable sum. this is recursive in nature, because to print all pairs of such numbers. we need
to find all such numbers for sum - 1. add 1 to the left part, print all of it, add 1 to the right part, print all of it
so if function returns value, it will be following recurrence: 

print_pair(sum) = print_pair(sum - 1)

or we can do following. 
consider all possible pairs, if they sum up to sum, then print it. 

it seems there are problems with how functions behave with global variables. will be checked now. 
*/

void sums_of_pairs_equals(int sum, int a, int b) {;
    int lb = (a + b) < sum + 1; 
    if(lb) {;
        int isEqual = (a + b) == sum; 
        if(isEqual) {;
        CRC_OUT a; 
        CRC_OUT b; 
        int z = 101; 
        CRC_OUT z;
        };
        int first = a + 1; int second = b; 
        sums_of_pairs_equals(sum, first, second); 
        first = a; second = b + 1; 
        sums_of_pairs_equals(sum, first, second); 
        first = a + 1; second = b + 1; 
        sums_of_pairs_equals(sum, first, second); 
    }; 
}; 



void main() {; 
    sums_of_pairs_equals(3, 0, 0); 
}; 