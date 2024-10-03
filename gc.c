#include <assert.h>
#include <stdlib.h>
#include "gc.h"
#include <stdio.h>

/*
 *      This reference counting garbage collector works by simply storing a
 *      reference count next to the allocated memory in the following way:
 *
 *          [reference count][allocated memory]
 *
 *      When it gets a call to gc_malloc it simply allocates the give size plus
 *      sizeof(int), and whenever it gets a call to gc_register or gc_free it
 *      shifts the address over by the size of an int to inspect the reference
 *      count.
 *
 */

// Allocates a contiguous piece of garbage-collected memory of a certain size
void *gc_malloc(size_t size) {
    void *allocated = malloc(size + sizeof(int));

    *(int *) allocated = 1;

    return allocated + sizeof(int);
}

// Registers use of a certain piece of memory. IE takes a pointer to an
// already-allocated piece of memory and increments the reference counter for
// this memory.
void gc_register(void *address) {
    address = address - sizeof(int);
    int *reference_count = (int *) address;

    assert(*reference_count > 0);

    (*reference_count)++;
}

// Unregisters use of the memory pointed to by ptr. If the reference counter is
// zero at this point the memory can be safely freed, otherwise it must be kept
// intact. 
void gc_free(void *address) {
    if (!address) {
        printf("Forsøk på å frigjøre en NULL-peker.\n");
        return;
    }

    int *reference_count = (int *)((char *)address - sizeof(int));
    printf("Før frigjøring, referanseteller: %d\n", *reference_count);

    assert(*reference_count > 0);

    (*reference_count)--;
    printf("Etter frigjøring, referanseteller: %d\n", *reference_count);

    if (*reference_count == 0) {
        free(reference_count);
        printf("Minne frigjort for adressen %p.\n", address);
    }
}

int main(){
    void *ptr = gc_malloc(100);
    gc_free(ptr);
    
    void *ptr2 = gc_malloc(200);
    gc_register(ptr2);
    gc_free(ptr2);
    gc_free(ptr2);

    gc_free(NULL);

    printf("Alle tester er fullført.\n");

    return 0;
    
}
