/*
 * slice_inl.h
 *
 *  Created on: Jun 24, 2014
 *      Author: Sergio Gonzalez
 */

#pragma once

#include "ph_base.h"

namespace ph {

// === Slice
// Conforms:   release, append, count
// Operators:  []
template<typename T>
struct Slice {
    T* ptr;
    size_t n_elems;
    size_t n_capacity;
    const T& operator[](const int64 i) {
        ph_assert(i >= 0);
        ph_assert((size_t )i < n_elems);
        return ptr[i];
    }
};

// Create a Slice
template<typename T>
Slice<T> MakeSlice(size_t n_capacity) {
    Slice<T> slice;
    slice.n_capacity = n_capacity;
    slice.n_elems = 0;
#if defined(PH_SLICES_ARE_MANUAL)
    slice.ptr = phalloc(T, n_capacity);
#else
    slice.ptr = phanaged(T, n_capacity);
#endif
    return slice;
}

template<typename T>
#if defined(PH_SLICES_ARE_MANUAL)
void release(Slice<T>* s) {
    if (s->ptr) {
        phree(s->ptr);
    }
#else
void release(Slice<T>*) {
#ifdef PH_DEBUG
    printf("WARNING: Releasing a memory managed array\n");
#endif
#endif
}

// Add an element to the end.
template<typename T>
void append(Slice<T>* slice, T elem) {
    if (slice->n_elems > 0 && slice->n_capacity == slice->n_elems) {
        slice->n_capacity *= 2;
#if defined(PH_SLICES_ARE_MANUAL)
        T* new_mem = phalloc(T, slice->n_capacity);
        memcpy(new_mem, slice->ptr, sizeof(T) * slice->n_elems);
        phree(slice->ptr);
        slice->ptr = new_mem;
#else
        slice->ptr = phanaged_realloc(T, slice->ptr,
                sizeof(T) * slice->n_elems);
#endif
    }
    slice->ptr[slice->n_elems] = elem;
    slice->n_elems++;
}
/*
 * NOT IN USE
 * TODO: Remove?
template<typename T>
void append_array(Slice<T>* slice, T* elems, int64 n_elems) {
    for(int64 i = 0; i < n_elems; ++i) {
        append(slice, elems[i]);
    }
}
*/

template<typename T>
int64 count(Slice<T> slice) {
    return (int64)slice.n_elems;
}

}  // ns ph

