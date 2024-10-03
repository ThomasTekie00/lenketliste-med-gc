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
    if (!address) return;  // Sjekk om adressen er NULL og returner umiddelbart hvis det er tilfellet

    // Få tilgang til referansetelleren
    int *reference_count = (int *)((char *)address - sizeof(int));

    // Sjekk om referansetelleren er gyldig og returner hvis den er 0 eller mindre
    if (*reference_count <= 0) {
        return;
    }

    // Decrementer referansetelleren
    (*reference_count)--;

    // Hvis referansetelleren når 0, frigjør minnet
    if (*reference_count == 0) {
        free(reference_count);  // Frigjør hele minneblokken når referansetelleren har nådd 0
    }
}



