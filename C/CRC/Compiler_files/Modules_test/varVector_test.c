#include <stdio.h> 
#include <stdlib.h>
#include "varVector.h"
#include <unistd.h>
#include <assert.h>
#include <string.h>
//will be fully changed from string to variable
void test_init(varVector** vect) {
    printf("creating a new varVector...\n");
    (*vect) = varVectorInit(); 
    assert(*vect); 
    printf("new variable vector has been successfully created!\n"); 
}

void test_append(varVector* vect, int x) {
 printf("Adding %d elements to a variable vector...\n", x);
    variable* gijoba; 
      type_desc td;
    td.type_name = "int"; 
    td.type_size = 4; 
    for(int i = 0; i < x; i++) {
        char toAdd[1000]; 
        snprintf(toAdd, 1000, "johny%d", i); 
        gijoba = varCreate(toAdd, "3", i, &td); 
        varVectorAppend(vect, gijoba); 
        varFree(gijoba); 
    }
    printf("Elements have been succesfully added!\n"); 
}

void test_size(varVector* vect, int x) {
    printf("finding size of the vect\n");
    printf("size of the variable vector is %d\n", varVectorLength(vect)); 
    assert(varVectorLength(vect) == x); 
    printf("size test successful!\n"); 
}


void test_get(varVector* vect) {
    printf("finding and printing first %d elements of vect", varVectorLength(vect)); 
  printf("Elements are: ");
    variable* elem; 
    for(int i = 0; i < varVectorLength(vect); i++) {
        elem = varVectorGet(vect, i); 
        varPrint(elem); 
        varFree(elem); 
    }
    printf("\n");
    printf("get test successful!\n");
}

void test_delete(varVector* vect, int pos, int x) {
    printf("deleting element at position %d\n", pos);
    varVectorDelete(vect, pos); 
    assert(varVectorLength(vect) == (x - 1));
    test_get(vect); 
    printf("delete successful\n");  
}

void test_delete_all(varVector* vect, int x) {
    printf("deleting all elements of the variable vector\n"); 
    while(varVectorLength(vect) > 0) {
        test_delete(vect, 0, x);
        x--;  
    }
    printf("delete all successfull!\n");
}
void test_insert(varVector* vect) {
    printf("starting inserting at even indices\n");
      variable* gijoba; 
      type_desc td;
    td.type_name = "int"; 
    td.type_size = 4; 
    for(int i = 0; i < varVectorLength(vect); i += 2) {
        char toAdd[1000]; 
        snprintf(toAdd, 1000, "yespapa%d", i); 
        gijoba = varCreate(toAdd, "3", i, &td); 
        varVectorInsert(vect, gijoba, i); 
        varFree(gijoba); 
    }
    printf("insert test success!\n"); 
}

void test_replace(varVector* vect) {
    printf("starting replacing\n");
     variable* gijoba; 
      type_desc td;
    td.type_name = "double"; 
    td.type_size = 4; 
    for(int i = 0; i < varVectorLength(vect); i++) {
        char toAdd[1000]; 
        snprintf(toAdd, 1000, "yespapa%d", i); 
        gijoba = varCreate(toAdd, "3", i, &td); 
        varVectorReplace(vect, gijoba, i);
        varFree(gijoba);  
    }
    printf("replace test successful!\n");
}

void test_search(varVector* vect) {
    printf("starting search\n");
    for(int i = 0; i < varVectorLength(vect); i++) {
        variable* elem = varVectorGet(vect, i);
        int x = varVectorSearch(vect, elem); 
        varFree(elem);
        printf("value of x is: %d\n", x); 
    }
    printf("search was successful!\n");
}

void test_all(varVector* vect, int len) {
       test_init(&vect); 
       test_append(vect, len); 
       test_size(vect, len); 
       test_get(vect); 
      test_search(vect); 
       test_insert(vect);
       test_replace(vect); 
       len = varVectorLength(vect); 
       test_get(vect); 
       test_delete(vect, len - 1, len); 
       test_delete_all(vect, varVectorLength(vect)); 
    varVectorDestroy(vect); 
    printf("variable vector has been successfully destroyed!\n");
    printf("All tests complete!\n");
 }
// //tests for variable methods 
// void test_create() {
//     printf("starting creating variables\n");
//     variable vars[100]; 

// }

int main() {
       varVector* vect;
       test_all(vect, 100);
    return 0; 
}