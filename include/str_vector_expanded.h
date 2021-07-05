#ifndef STR_VECTOR_EXPANDED_H
#define STR_VECTOR_EXPANDED_H

#include <stdio.h>
#include "str_vector.h"

// creates vector with data from in
void str_vector_create(str_vector_t *vector,FILE *in);

// prints vector's content
void str_vector_print(str_vector_t vector,FILE *out);

// frees all the strings that were allocated by the process of creation
void str_vector_free_all_str(str_vector_t *vector);

#endif
