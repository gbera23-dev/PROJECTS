#include <stdio.h> 
#include <stdlib.h>
#include "strVector.h"
#include <unistd.h>
#include <assert.h>
#include <string.h>

void test_init(strVector** vect) {
    printf("creating a new strVector...\n");
    (*vect) = strVectorInit(); 
    assert(*vect); 
    printf("new string vector has been successfully created!\n"); 
}

void test_append(strVector* vect, int x) {
 printf("Adding 5 elements to a string vector...\n");
    char gijoba[10000]; 
    for(int i = 0; i < x; i++) {
        snprintf(gijoba, 10000, "element%d", i); 
        strVectorAppend(vect, gijoba); 
    }
    printf("Elements have been succesfully added!\n"); 
}

void test_size(strVector* vect, int x) {
    printf("finding size of the vect\n");
    printf("size of the string vector is %d\n", strVectorLength(vect)); 
    assert(strVectorLength(vect) == x); 
    printf("size test successful!\n"); 
}


void test_get(strVector* vect, int x) {
    printf("finding and printing first %d elements of vect", x); 
  printf("Elements are: ");
    char* elem; 
    for(int i = 0; i < strVectorLength(vect); i++) {
        elem = strVectorGet(vect, i); 
        printf("%s ", elem);
        free(elem);  
    }
    printf("\n");
    printf("get test successful!\n");
}

void test_delete(strVector* vect, int pos, int x) {
    printf("deleting element at position %d\n", pos);
    strVectorDelete(vect, pos); 
    assert(strVectorLength(vect) == (x - 1));
    test_get(vect, x - 1); 
    printf("delete successful\n");  
}

void test_delete_all(strVector* vect, int x) {
    printf("deleting all elements of the string vector\n"); 
    while(strVectorLength(vect) > 0) {
        test_delete(vect, 0, x);
        x--;  
    }
    printf("delete all successfull!\n");
}
void test_insert(strVector* vect) {
    printf("starting inserting at even indices\n");
    char gijoba[10000]; 
    for(int i = 0; i < strVectorLength(vect); i += 2) {
        snprintf(gijoba, 10000, "element%d", -i); 
        strVectorInsert(vect, gijoba, i); 
    }
    printf("insert test success!\n"); 
}

void test_replace(strVector* vect) {
    printf("starting replacing\n");
    for(int i = 0; i < strVectorLength(vect); i++) {
        strVectorReplace(vect, "uii", i); 
    }
    printf("replace test successful!\n");
}

void test_search(strVector* vect) {
    printf("starting search\n");
    for(int i = 0; i < strVectorLength(vect); i++) {
        char* elem = strVectorGet(vect, i);
        int x = strVectorSearch(vect, elem); 
        free(elem);
        printf("value of x is: %d\n", x); 
    }
    printf("search was successful!\n");
}

void test_all(strVector* vect, int len) {
       test_init(&vect); 
       test_append(vect, len); 
       test_size(vect, len); 
       test_get(vect, len); 
       test_search(vect); 
       test_insert(vect);
       //test_replace(vect); 
       len = strVectorLength(vect); 
       test_get(vect, len); 
       test_delete(vect, len - 1, len); 
       //test_delete_all(vect, strVectorLength(vect)); 
    strVectorDestroy(vect); 
    printf("string vector has been successfully destroyed!\n");
    printf("All tests complete!\n");
}

int main() {
       strVector* vect;
       test_all(vect, 100); 
    return 0; 
}