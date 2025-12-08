//final version

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
const int defaultCapacity = 4; 
//vector *v is the pointer to the newly created struct obj, we are using these functions to operate on it
void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation){
    v->log_size = 0; 
    v->elem_size = elemSize; 
    assert(initialAllocation >= 0); 
    assert(elemSize > 0); 
    v->capacity = initialAllocation != 0 ? initialAllocation : defaultCapacity; 
    v->clean_up = freeFn; 
    v->head = malloc(v->elem_size*v->capacity); //allocates elem_size * capacity amount of memory 
}
//first we free client's elements(as they could simply be also pointers to some memory in heap)
//and then we free our v->head 
void VectorDispose(vector *v){
    if(v->clean_up != NULL) {
        for(int i = 0; i < v->log_size; i++) {
            (*v->clean_up)((char*)v->head + v->elem_size*i);
        }
    }
    free(v->head); 
}

int VectorLength(const vector *v){ 
    return v->log_size; 
}

void *VectorNth(const vector *v, int position){ 
    assert(position >= 0 && position < v->log_size); 
    return (char*)v->head + v->elem_size*position;
 }

void VectorReplace(vector *v, const void *elemAddr, int position){
    assert(elemAddr != NULL); 
    assert(position >= 0 && position < v->log_size); 
    void* to_replace = (char*)v->head + v->elem_size*position; 
    if(v->clean_up != NULL)(*v->clean_up)(to_replace); 
    memcpy(to_replace, elemAddr, v->elem_size); 
}

void VectorInsert(vector *v, const void *elemAddr, int position){
    assert(position >= 0 && position <= v->log_size); 
    assert(elemAddr != NULL); 
    if(v->log_size == v->capacity) {
        v->capacity *= 2; 
        v->head = realloc(v->head, v->capacity*v->elem_size); 
    }
    //does not need memory move
    if(position == v->log_size)VectorAppend(v, elemAddr); 
    else {
        void* position_before = (char*)v->head + v->elem_size*position; 
        void* position_after = (char*)position_before + v->elem_size; 
        memmove(position_after, position_before, v->elem_size*(v->log_size - position)); 
        memcpy(position_before, elemAddr, v->elem_size);
        v->log_size++;  
    }
}

void VectorAppend(vector *v, const void *elemAddr){
    assert(elemAddr != NULL); 
    if(v->log_size == v->capacity) {
        v->capacity *= 2; 
        v->head = realloc(v->head, v->capacity*v->elem_size); 
    }
    memcpy((char*)v->head + v->log_size*v->elem_size, elemAddr, v->elem_size); 
    v->log_size++; 
}

void VectorDelete(vector *v, int position){
    assert(position >= 0 && position < v->log_size);
    assert(v->log_size > 0); 
    if(v->clean_up != NULL) {
    (*v->clean_up)((char*)v->head + v->elem_size*position);
    }
    if(position != v->log_size - 1) {
        void* position_before = (char*)v->head + v->elem_size*position; 
        void* position_after = (char*)position_before + v->elem_size; 
        memmove(position_before, position_after, v->elem_size*(v->log_size - position - 1));
    }
    v->log_size--; 
}

void VectorSort(vector *v, VectorCompareFunction compare){
    assert(compare != NULL); 
    qsort(v->head, v->log_size, v->elem_size, compare); 
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData){
    assert(mapFn != NULL); 
    void* current; 
    for(int i = 0; i < v->log_size; i++) {
        current = (char*)v->head + v->elem_size*i; 
        mapFn(current, auxData); 
    }
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, 
    VectorCompareFunction searchFn, int startIndex, int isSorted){ 
    if(v->log_size == 0)return kNotFound; 
    assert(searchFn != NULL); 
    assert(startIndex >= 0 && startIndex <= v->log_size); 
    assert(key != NULL); 
    void* ptr_to_elem = NULL;
    if(isSorted) {
        ptr_to_elem = bsearch(key, (char*)v->head + v->elem_size*startIndex, v->log_size - startIndex, 
        v->elem_size, searchFn); 
    }
    else {
        int i = startIndex;
       for(i = startIndex; i < v->log_size; i++) {
         ptr_to_elem = (char*)v->head + i*v->elem_size; 
         if(searchFn(ptr_to_elem, key) == 0)break; 
       }
       if(i == v->log_size)ptr_to_elem = NULL; 
    }
        return ptr_to_elem != NULL ? (((char*)ptr_to_elem - (char*)v->head) / v->elem_size) : kNotFound; 
    } 
