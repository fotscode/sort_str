#ifndef STR_VECTOR_EXPANDED_H
#define STR_VECTOR_EXPANDED_H

#include <stdio.h>
#include "str_vector.h"

void str_vector_create(str_vector_t *vector,FILE *in);

void str_vector_print(str_vector_t vector,FILE *out);

void str_vector_free_all_str(str_vector_t *vector);

#endif
